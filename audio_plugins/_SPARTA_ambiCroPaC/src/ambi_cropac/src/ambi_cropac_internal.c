/*
 Copyright 2018 Leo McCormack
 
 Permission to use, copy, modify, and/or distribute this software for any purpose with or
 without fee is hereby granted, provided that the above copyright notice and this permission
 notice appear in all copies.
 
 THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO
 THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT
 SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR
 ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF
 CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
 OR PERFORMANCE OF THIS SOFTWARE.
*/
/*
 * Filename:
 *     ambi_cropac_internal.c 
 * Description:
 *     A first-order parametric binaural Ambisonic decoder for reproducing ambisonic signals
 *     over headphones. The algorithm is based on the segregation of the direct and diffuse
 *     streams using the Cross-Pattern Coherence (CroPaC) spatial post-filter, described in:
 *         Delikaris-Manias, S. and Pulkki, V., 2013. Cross pattern coherence algorithm for
 *         spatial filtering applications utilizing microphone arrays. IEEE Transactions on
 *         Audio, Speech, and Language Processing, 21(11), pp.2356-2367.
 *     The output of a linear binaural ambisonic decoder is then adaptively mixed, in such a
 *     manner that the covariance matrix of the output stream is brought closer to that of
 *     the target covariance matrix, derived from the direct/diffuse analysis. For more
 *     information on this optimised covariance domain rendering, the reader is directed to:
 *         Vilkamo, J., Bäckström, T. and Kuntz, A., 2013. Optimized covariance domain
 *         framework for time–frequency processing of spatial audio. Journal of the Audio
 *         Engineering Society, 61(6), pp.403-411.
 *     Optionally, a SOFA file may be loaded for personalised headphone listening.
 * Dependencies:
 *     saf_utilities, afSTFTlib, saf_hrir, saf_vbap, saf_sh
 * Author, date created:
 *     Leo McCormack, 12.01.2018
 */

#include "ambi_cropac_internal.h"
#define SAF_ENABLE_SOFA_READER
#include "saf_sofa_reader.h" 

void ambi_cropac_initCodec
(
    void* const hAmbi
)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    codecPars* pars = pData->pars;
    int i, j, k, band, t, nDirs_td;
    int* hrir_closest_idx;
    float scale;
    float* Y_td, *t_dirs;
    float_complex* M_dec_t, *hrtf_fb_short;
    const float_complex calpha = cmplxf(1.0f, 0.0f), cbeta = cmplxf(0.0f, 0.0f);
    
    /* load sofa file or load default hrir data */
    if(!pData->useDefaultHRIRsFLAG && pars->sofa_filepath!=NULL){
#ifdef SAF_ENABLE_SOFA_READER
        loadSofaFile(pars->sofa_filepath,
                     &pars->hrirs,
                     &pars->hrir_dirs_deg,
                     &pars->N_hrir_dirs,
                     &pars->hrir_len,
                     &pars->hrir_fs);
        if((pars->hrirs==NULL) || (pars->hrir_dirs_deg == NULL))
            pData->useDefaultHRIRsFLAG = 1;
#else
        pData->useDefaultHRIRsFLAG = 1;
#endif
    }
    if(pData->useDefaultHRIRsFLAG){
        /* load defaults */
        pars->N_hrir_dirs = __default_N_hrir_dirs;
        pars->hrir_len = __default_hrir_len;
        pars->hrir_fs = __default_hrir_fs;
        if(pars->hrirs != NULL)
            free(pars->hrirs);
        pars->hrirs = malloc(pars->N_hrir_dirs * NUM_EARS * (pars->hrir_len)*sizeof(float));
        for(i=0; i<pars->N_hrir_dirs; i++)
            for(j=0; j<NUM_EARS; j++)
                for(k=0; k< pars->hrir_len; k++)
                    pars->hrirs[i*NUM_EARS*(pars->hrir_len) + j*(pars->hrir_len) + k] = (float)__default_hrirs[i][j][k];
        if(pars->hrir_dirs_deg != NULL)
            free(pars->hrir_dirs_deg);
        pars->hrir_dirs_deg = malloc(pars->N_hrir_dirs * NUM_EARS * sizeof(float));
        for(i=0; i<pars->N_hrir_dirs; i++)
            for(j=0; j<2; j++)
                pars->hrir_dirs_deg[i*2+j] = (float)__default_hrir_dirs_deg[i][j];
    }
    
    /* estimate the ITDs for each HRIR */
    if(pars->itds_s!= NULL){
        free(pars->itds_s);
        pars->itds_s = NULL;
    }
    estimateITDs(pars->hrirs, pars->N_hrir_dirs, pars->hrir_len, pars->hrir_fs, &(pars->itds_s));
    
    /* convert hrirs to filterbank coefficients */
    if(pars->hrtf_fb!= NULL){
        free(pars->hrtf_fb);
        pars->hrtf_fb = NULL;
    }
#if USE_NEAREST_HRIRS
        HRIRs2FilterbankHRTFs(pars->hrirs, pars->N_hrir_dirs, pars->hrir_len, pars->itds_s, (float*)pData->freqVector, HYBRID_BANDS, 1, &(pars->hrtf_fb));
#else
        HRIRs2FilterbankHRTFs(pars->hrirs, pars->N_hrir_dirs, pars->hrir_len, pars->itds_s, (float*)pData->freqVector, HYBRID_BANDS, 0, &(pars->hrtf_fb));
#endif
    
    /* define t-design */
    t = 4*(SH_ORDER);
    nDirs_td = __Tdesign_nPoints_per_degree[t-1];
    t_dirs = (float*)__HANDLES_Tdesign_dirs_deg[t-1];
 
    /* define M_dec_td (decoder to t-design) */
    Y_td = NULL;
    getRSH(SH_ORDER, t_dirs, nDirs_td, &Y_td);
    float* Y_td_mrE,* a_n;
    M_dec_t = malloc(NUM_SH_SIGNALS*nDirs_td*sizeof(float_complex));
    if(pData->rE_WEIGHT){
        Y_td_mrE  = malloc(NUM_SH_SIGNALS*nDirs_td*sizeof(float));
        a_n = malloc(NUM_SH_SIGNALS*NUM_SH_SIGNALS*sizeof(float));
        getMaxREweights(SH_ORDER, a_n);
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, NUM_SH_SIGNALS, nDirs_td, NUM_SH_SIGNALS, 1.0f,
                    a_n, NUM_SH_SIGNALS,
                    Y_td, nDirs_td, 0.0f,
                    Y_td_mrE, nDirs_td);
        memcpy(Y_td, Y_td_mrE, NUM_SH_SIGNALS*nDirs_td*sizeof(float));
        free(Y_td_mrE);
        free(a_n);
    }
    scale = 1.0f/(float)nDirs_td;
    for(i=0; i<nDirs_td*NUM_SH_SIGNALS; i++)
        M_dec_t[i] = cmplxf(Y_td[i] * scale, 0.0f);
    
#if USE_NEAREST_HRIRS
    /* M_dec(f) = H(f) * M_dec_td */
    hrir_closest_idx = malloc(nDirs_td*sizeof(int));
    hrtf_fb_short = malloc(NUM_EARS*nDirs_td*sizeof(float_complex));
    findClosestGridPoints(pars->hrir_dirs_deg, pars->N_hrir_dirs, t_dirs, nDirs_td, 1, hrir_closest_idx, NULL, NULL);
    memset(pars->M_dec, 0, HYBRID_BANDS*NUM_EARS*NUM_SH_SIGNALS*sizeof(float_complex));
 
    for(band=0; band<HYBRID_BANDS; band++){
        for(i=0; i<nDirs_td; i++){
            hrtf_fb_short[0*nDirs_td+i] = pars->hrtf_fb[band*NUM_EARS*(pars->N_hrir_dirs)+0*(pars->N_hrir_dirs) + hrir_closest_idx[i]];
            hrtf_fb_short[1*nDirs_td+i] = pars->hrtf_fb[band*NUM_EARS*(pars->N_hrir_dirs)+1*(pars->N_hrir_dirs) + hrir_closest_idx[i]];
        }
        cblas_cgemm(CblasRowMajor, CblasNoTrans, CblasTrans, NUM_EARS, NUM_SH_SIGNALS, nDirs_td, &calpha,
                    hrtf_fb_short, nDirs_td,
                    M_dec_t, nDirs_td, &cbeta,
                    pars->M_dec[band], NUM_SH_SIGNALS);
    }

    free(hrir_closest_idx);
    free(hrtf_fb_short);
    
    /* Alternatively, use triangular interpolation: */
#else
    /* calculate interpolation table */
    int N_gtable,nTriangles;
    float* gtable;
    gtable = NULL;
    generateVBAPgainTable3D_srcs(t_dirs, nDirs_td, pars->hrir_dirs_deg, pars->N_hrir_dirs, 0, 1, &gtable, &N_gtable, &pars->N_Tri);
    VBAPgainTable2InterpTable(gtable, nDirs_td, pars->N_hrir_dirs);
    
    /* M_dec(f) = H(f) * M_dec_td */
    hrtf_fb_short = malloc(HYBRID_BANDS*NUM_EARS*nDirs_td*sizeof(float_complex));
    memset(pars->M_dec, 0, 2*HYBRID_BANDS*NUM_EARS*NUM_SH_SIGNALS*sizeof(float_complex));
    interpFilterbankHRTFs(pars->hrtf_fb, pars->itds_s, pData->freqVector, gtable, pars->N_hrir_dirs, HYBRID_BANDS, nDirs_td, j, hrtf_fb_short);

    for(band=0; band<HYBRID_BANDS; band++){
        cblas_cgemm(CblasRowMajor, CblasNoTrans, CblasTrans, NUM_EARS, NUM_SH_SIGNALS, nDirs_td, &calpha,
                    &hrtf_fb_short[band*NUM_EARS*nDirs_td], nDirs_td,
                    M_dec_t, nDirs_td, &cbeta,
                    pars->M_dec[band], NUM_SH_SIGNALS);
    }
    free(gtable);
#endif
    
    free(M_dec_t);
    free(Y_td);
}
 





