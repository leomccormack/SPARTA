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
 *     ambi_cropac.c
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

void ambi_cropac_create
(
    void ** const phAmbi
)
{
    ambi_cropac_data* pData = (ambi_cropac_data*)malloc(sizeof(ambi_cropac_data));
    if (pData == NULL) { return;/*error*/ }
    *phAmbi = (void*)pData;
    int t, ch, band;

	/* default user parameters */
    for (band = 0; band<HYBRID_BANDS; band++){
		pData->EQ[band] = 1.0f;
        pData->decBalance[band] = 1.0f;
        pData->balance[band] = 1.0f;
    }
	pData->useDefaultHRIRsFLAG = 1; /* pars->sofa_filepath must be valid to set this to 0 */
	pData->chOrdering = CH_ACN;
	pData->norm = NORM_N3D;
	pData->rE_WEIGHT = 0;
    pData->covAvgCoeff = 0.75f;
	pData->enableRotation = 0;
	pData->yaw = 0.0f;
	pData->pitch = 0.0f;
	pData->roll = 0.0f;
	pData->bFlipYaw = 0;
	pData->bFlipPitch = 0;
	pData->bFlipRoll = 0;
	pData->useRollPitchYawFlag = 0;
    
    /* afSTFT stuff */
    afSTFTinit(&(pData->hSTFT), HOP_SIZE, NUM_SH_SIGNALS, NUM_EARS, 0, 1);
    pData->STFTOutputFrameTF = (complexVector**)malloc2d(TIME_SLOTS, NUM_EARS, sizeof(complexVector));
    for(t=0; t<TIME_SLOTS; t++) {
        for(ch=0; ch< NUM_EARS; ch++) {
            pData->STFTOutputFrameTF[t][ch].re = (float*)calloc(HYBRID_BANDS, sizeof(float));
            pData->STFTOutputFrameTF[t][ch].im = (float*)calloc(HYBRID_BANDS, sizeof(float));
        }
    }
    pData->tempHopFrameTD = (float**)malloc2d( MAX(NUM_SH_SIGNALS, NUM_EARS), HOP_SIZE, sizeof(float));
    pData->STFTInputFrameTF = (complexVector**)malloc2d(TIME_SLOTS, NUM_SH_SIGNALS, sizeof(complexVector));
    for(t=0; t<TIME_SLOTS; t++) {
        for(ch=0; ch< NUM_SH_SIGNALS; ch++) {
            pData->STFTInputFrameTF[t][ch].re = (float*)calloc(HYBRID_BANDS, sizeof(float));
            pData->STFTInputFrameTF[t][ch].im = (float*)calloc(HYBRID_BANDS, sizeof(float));
        }
    }

    /* codec data */
    pData->pars = (codecPars*)malloc(sizeof(codecPars));
    codecPars* pars = pData->pars; 
    pars->sofa_filepath = NULL;
    pars->hrirs = NULL;
    pars->hrir_dirs_deg = NULL;
    pars->itds_s = NULL;
    pars->hrtf_fb = NULL;
    
    /* flags */
    pData->reInitCodec = 1;
}

void ambi_cropac_destroy
(
    void ** const phAmbi
)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(*phAmbi);
    codecPars *pars = pData->pars;
    int t, ch;
    
    if (pData != NULL) {
        if(pData->hSTFT!=NULL)
            afSTFTfree(pData->hSTFT);
        for (t = 0; t<TIME_SLOTS; t++) {
            if(pData->STFTInputFrameTF!=NULL){
                for (ch = 0; ch< NUM_SH_SIGNALS; ch++) {
                    free(pData->STFTInputFrameTF[t][ch].re);
                    free(pData->STFTInputFrameTF[t][ch].im);
                }
            }
            for (ch = 0; ch< NUM_EARS; ch++) {
                free(pData->STFTOutputFrameTF[t][ch].re);
                free(pData->STFTOutputFrameTF[t][ch].im);
            }
        }
        free2d((void**)pData->STFTInputFrameTF, TIME_SLOTS);
        free2d((void**)pData->STFTOutputFrameTF, TIME_SLOTS);
        if(pData->tempHopFrameTD!=NULL)
            free2d((void**)pData->tempHopFrameTD, MAX(NUM_EARS, NUM_SH_SIGNALS));
        
        if(pars->hrtf_fb!= NULL)
            free(pars->hrtf_fb);
        if(pars->itds_s!= NULL)
            free(pars->itds_s);
        if(pars->hrirs!= NULL)
            free(pars->hrirs);
        if(pars->hrir_dirs_deg!= NULL)
            free(pars->hrir_dirs_deg);
        free(pars);

        free(pData);
        pData = NULL;
    }
}

void ambi_cropac_init
(
    void * const hAmbi,
    int          sampleRate
)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    int band;
    
    /* define frequency vector */
    pData->fs = sampleRate;
    for(band=0; band <HYBRID_BANDS; band++){
        if(sampleRate == 44100)
            pData->freqVector[band] =  (float)__afCenterFreq44100[band];
        else /* Assume 48kHz */
            pData->freqVector[band] =  (float)__afCenterFreq48e3[band];
    } 

	/* reinitialise if needed */
	ambi_cropac_checkReInit(hAmbi);
}

void ambi_cropac_process
(
    void  *  const hAmbi,
    float ** const inputs,
    float ** const outputs,
    int            nInputs,
    int            nOutputs,
    int            nSamples,
    int            isPlaying
)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    codecPars* pars = pData->pars;
    int n, t, sample, ch, i, j, band;
    int o[SH_ORDER+2];
    const float_complex calpha = cmplxf(1.0f,0.0f), cbeta = cmplxf(0.0f, 0.0f);
    float Rxyz[3][3], postGain;
    float_complex M_rot[NUM_SH_SIGNALS][NUM_SH_SIGNALS];
    float* M_rot_tmp;
    
    /* local copies of user parameters */
    int rE_WEIGHT, enableRot;
    NORM_TYPES norm;
 
    /* decode audio to loudspeakers or headphones */
    if ( (nSamples == FRAME_SIZE) && (isPlaying) && (pData->reInitCodec==0) ) {
        /* copy user parameters to local variables */
        for(n=0; n<SH_ORDER+2; n++){  o[n] = n*n;  }
        norm = pData->norm;
        rE_WEIGHT = pData->rE_WEIGHT;
        enableRot = pData->enableRotation;
        postGain = powf(10.0f, (POST_GAIN_DB)/20.0f);
        
        /* Load time-domain data */
        for(i=0; i < MIN(NUM_SH_SIGNALS, nInputs); i++)
            memcpy(pData->SHFrameTD[i], inputs[i], FRAME_SIZE * sizeof(float));
        for(; i<NUM_SH_SIGNALS; i++)
            memset(pData->SHFrameTD[i], 0, FRAME_SIZE * sizeof(float)); /* fill remaining channels with zeros, to avoid funky behaviour */
        
        /* account for input normalisation scheme */
        switch(norm){
            case NORM_N3D:  /* already in N3D, do nothing */
                break;
            case NORM_SN3D: /* convert to N3D */
                for (n = 0; n<SH_ORDER+1; n++)
                    for (ch = o[n]; ch<o[n+1]; ch++)
                        for(i = 0; i<FRAME_SIZE; i++)
                            pData->SHFrameTD[ch][i] *= sqrtf(2.0f*(float)n+1.0f);
                break;
        }
        
        /* Apply time-frequency transform (TFT) */
        for ( t=0; t< TIME_SLOTS; t++) {
            for( ch=0; ch < NUM_SH_SIGNALS; ch++)
                for ( sample=0; sample < HOP_SIZE; sample++)
                    pData->tempHopFrameTD[ch][sample] = pData->SHFrameTD[ch][sample + t*HOP_SIZE];
            afSTFTforward(pData->hSTFT, (float**)pData->tempHopFrameTD, (complexVector*)pData->STFTInputFrameTF[t]);
        }
        for(band=0; band<HYBRID_BANDS; band++)
            for( ch=0; ch < NUM_SH_SIGNALS; ch++)
                for ( t=0; t<TIME_SLOTS; t++)
                    pData->SHframeTF[band][ch][t] = cmplxf(pData->STFTInputFrameTF[t][ch].re[band], pData->STFTInputFrameTF[t][ch].im[band]);
    
        /* Apply rotation */
		if (enableRot) {
			M_rot_tmp = malloc(NUM_SH_SIGNALS*NUM_SH_SIGNALS * sizeof(float));
			yawPitchRoll2Rzyx(pData->yaw, pData->pitch, pData->roll, pData->useRollPitchYawFlag, Rxyz);
			getSHrotMtxReal(Rxyz, M_rot_tmp, SH_ORDER);
			for (i = 0; i < NUM_SH_SIGNALS; i++)
				for (j = 0; j < NUM_SH_SIGNALS; j++)
					M_rot[i][j] = cmplxf(M_rot_tmp[i*NUM_SH_SIGNALS + j], 0.0f);
			free(M_rot_tmp);
            for (band = 0; band < HYBRID_BANDS; band++) {
                cblas_cgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, NUM_SH_SIGNALS, TIME_SLOTS, NUM_SH_SIGNALS, &calpha,
                            M_rot, NUM_SH_SIGNALS,
                            pData->SHframeTF[band], TIME_SLOTS, &cbeta,
                            pData->SHframeTF_rot[band], TIME_SLOTS);
            }
		}
        
        /* mix to headphones */
        for (band = 0; band < HYBRID_BANDS; band++) {
            cblas_cgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, NUM_EARS, TIME_SLOTS, NUM_SH_SIGNALS, &calpha,
                        pars->M_dec[band], NUM_SH_SIGNALS,
                        enableRot ? pData->SHframeTF_rot[band] : pData->SHframeTF[band], TIME_SLOTS, &cbeta,
                        pData->binframeTF[band], TIME_SLOTS);
        }
          
        /* inverse-TFT */
        for (band = 0; band < HYBRID_BANDS; band++) {
            for (ch = 0; ch < NUM_EARS; ch++) {
                for (t = 0; t < TIME_SLOTS; t++) {
                    pData->STFTOutputFrameTF[t][ch].re[band] = crealf(pData->binframeTF[band][ch][t]);
                    pData->STFTOutputFrameTF[t][ch].im[band] = cimagf(pData->binframeTF[band][ch][t]);
                }
            }
        }
        for (t = 0; t < TIME_SLOTS; t++) {
            afSTFTinverse(pData->hSTFT, pData->STFTOutputFrameTF[t], pData->tempHopFrameTD);
            for (ch = 0; ch < MIN(NUM_EARS, nOutputs); ch++)
                for (sample = 0; sample < HOP_SIZE; sample++)
                    outputs[ch][sample + t* HOP_SIZE] = pData->tempHopFrameTD[ch][sample] * postGain;
            for (; ch < nOutputs; ch++) /* fill remaining channels with zeros */
                for (sample = 0; sample < HOP_SIZE; sample++)
                    outputs[ch][sample + t* HOP_SIZE] = 0.0f;
        }
    }
    else
        for (ch=0; ch < nOutputs; ch++)
            memset(outputs[ch],0, FRAME_SIZE*sizeof(float));
}


/* Set Functions */

void ambi_cropac_refreshParams(void* const hAmbi)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    pData->reInitCodec = 1; 
}

void ambi_cropac_checkReInit(void* const hAmbi)
{
	ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);

	/* reinitialise if needed */
	if (pData->reInitCodec == 1) {
		pData->reInitCodec = 2;
		ambi_cropac_initCodec(hAmbi);
		pData->reInitCodec = 0;
	}
}

void ambi_cropac_setBalance(void* const hCmp, float newValue, int bandIdx)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hCmp);
    pData->balance[bandIdx] = newValue;
}

void ambi_cropac_setBalanceAllBands(void* const hAmbi, float newValue)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    int band;
    
    for(band=0; band<HYBRID_BANDS; band++)
        pData->balance[band] = newValue;
}

void ambi_cropac_setDecBalance(void* const hAmbi, float newValue, int bandIdx)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    pData->decBalance[bandIdx] = newValue;
}

void ambi_cropac_setDecBalanceAllBands(void* const hAmbi, float newValue)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    int band;
    
    for(band=0; band<HYBRID_BANDS; band++)
        pData->decBalance[band] = newValue;
}

void ambi_cropac_setCovAvg(void* const hAmbi, float newValue)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    pData->covAvgCoeff = newValue;
}

void ambi_cropac_setUseDefaultHRIRsflag(void* const hAmbi, int newState)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    
    if((!pData->useDefaultHRIRsFLAG) && (newState)){
        pData->useDefaultHRIRsFLAG = newState;
        pData->reInitCodec = 1;
    }
}

void ambi_cropac_setSofaFilePath(void* const hAmbi, const char* path)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    codecPars* pars = pData->pars;
    
    pars->sofa_filepath = malloc(strlen(path) + 1);
    strcpy(pars->sofa_filepath, path);
    pData->useDefaultHRIRsFLAG = 0;
    pData->reInitCodec = 1;
}

void ambi_cropac_setChOrder(void* const hAmbi, int newOrder)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    pData->chOrdering = (CH_ORDER)newOrder;
}

void ambi_cropac_setNormType(void* const hAmbi, int newType)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    pData->norm = (NORM_TYPES)newType;
}

void ambi_cropac_setDecEnableMaxrE(void* const hAmbi, int newState)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    if(pData->rE_WEIGHT != newState){
        pData->rE_WEIGHT = newState;
        pData->reInitCodec=1;
    }
}

void ambi_cropac_setEnableRotation(void* const hAmbi, int newState)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    pData->enableRotation = newState;
}

void ambi_cropac_setYaw(void  * const hAmbi, float newYaw)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    pData->yaw = pData->bFlipYaw == 1 ? -DEG2RAD(newYaw) : DEG2RAD(newYaw);
}

void ambi_cropac_setPitch(void* const hAmbi, float newPitch)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    pData->pitch = pData->bFlipPitch == 1 ? -DEG2RAD(newPitch) : DEG2RAD(newPitch);
}

void ambi_cropac_setRoll(void* const hAmbi, float newRoll)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    pData->roll = pData->bFlipRoll == 1 ? -DEG2RAD(newRoll) : DEG2RAD(newRoll);
}

void ambi_cropac_setFlipYaw(void* const hAmbi, int newState)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    if(newState !=pData->bFlipYaw ){
        pData->bFlipYaw = newState;
        ambi_cropac_setYaw(hAmbi, -ambi_cropac_getYaw(hAmbi));
    }
}

void ambi_cropac_setFlipPitch(void* const hAmbi, int newState)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    if(newState !=pData->bFlipPitch ){
        pData->bFlipPitch = newState;
        ambi_cropac_setPitch(hAmbi, -ambi_cropac_getPitch(hAmbi));
    }
}

void ambi_cropac_setFlipRoll(void* const hAmbi, int newState)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    if(newState !=pData->bFlipRoll ){
        pData->bFlipRoll = newState;
        ambi_cropac_setRoll(hAmbi, -ambi_cropac_getRoll(hAmbi));
    }
}

void ambi_cropac_setRPYflag(void* const hAmbi, int newState)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    pData->useRollPitchYawFlag = newState;
}

/* Get Functions */

float ambi_cropac_getBalance(void  * const hAmbi, int bandIdx)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    return pData->balance[bandIdx];
}

float ambi_cropac_getBalanceAllBands(void  * const hAmbi)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    return pData->balance[0];
}

void ambi_cropac_getBalanceHandle
(
    void* const hAmbi,
    float** pX_vector,
    float** pY_values,
    int* pNpoints
)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    (*pX_vector) = &pData->freqVector[0];
    (*pY_values) = &pData->balance[0];
    (*pNpoints) = HYBRID_BANDS;
}

float ambi_cropac_getDecBalance(void  * const hAmbi, int bandIdx)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    return pData->decBalance[bandIdx];
}

float ambi_cropac_getDecBalanceAllBands(void  * const hAmbi)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    return pData->decBalance[0];
}

void ambi_cropac_getDecBalanceHandle
(
    void* const hAmbi,
    float** pX_vector,
    float** pY_values,
    int* pNpoints
)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    (*pX_vector) = &pData->freqVector[0];
    (*pY_values) = &pData->decBalance[0];
    (*pNpoints) = HYBRID_BANDS;
}

float ambi_cropac_getCovAvg(void* const hAmbi)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    return pData->covAvgCoeff;
}

int ambi_cropac_getUseDefaultHRIRsflag(void* const hAmbi)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    return pData->useDefaultHRIRsFLAG;
}

char* ambi_cropac_getSofaFilePath(void* const hAmbi)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    codecPars* pars = pData->pars;
    if(pars->sofa_filepath!=NULL)
        return pars->sofa_filepath;
    else
        return "no_file";
}

int ambi_cropac_getChOrder(void* const hAmbi)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    return (int)pData->chOrdering;
}

int ambi_cropac_getNormType(void* const hAmbi)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    return (int)pData->norm;
}

int ambi_cropac_getDecEnableMaxrE(void* const hAmbi)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    return pData->rE_WEIGHT;
}

int ambi_cropac_getNumEars()
{ 
    return NUM_EARS;
}

int ambi_cropac_getNumberOfBands()
{
    return HYBRID_BANDS;
}

int ambi_cropac_getNSHrequired()
{ 
    return NUM_SH_SIGNALS;
}

int ambi_cropac_getEnableRotation(void* const hAmbi)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    return pData->enableRotation;
}

float ambi_cropac_getYaw(void* const hAmbi)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    return pData->bFlipYaw == 1 ? -RAD2DEG(pData->yaw) : RAD2DEG(pData->yaw);
}

float ambi_cropac_getPitch(void* const hAmbi)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    return pData->bFlipPitch == 1 ? -RAD2DEG(pData->pitch) : RAD2DEG(pData->pitch);
}

float ambi_cropac_getRoll(void* const hAmbi)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    return pData->bFlipRoll == 1 ? -RAD2DEG(pData->roll) : RAD2DEG(pData->roll);
}

int ambi_cropac_getFlipYaw(void* const hAmbi)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    return pData->bFlipYaw;
}

int ambi_cropac_getFlipPitch(void* const hAmbi)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    return pData->bFlipPitch;
}

int ambi_cropac_getFlipRoll(void* const hAmbi)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    return pData->bFlipRoll;
}

int ambi_cropac_getRPYflag(void* const hAmbi)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    return pData->useRollPitchYawFlag;
}

int ambi_cropac_getNDirs(void* const hAmbi)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    codecPars* pars = pData->pars;
    return pars->N_hrir_dirs;
}

int ambi_cropac_getNTriangles(void* const hAmbi)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    codecPars* pars = pData->pars;
    return pars->N_Tri;
}

int ambi_cropac_getHRIRlength(void* const hAmbi)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    codecPars* pars = pData->pars;
    return pars->hrir_len;
}

int ambi_cropac_getHRIRsamplerate(void* const hAmbi)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    codecPars* pars = pData->pars;
    return pars->hrir_fs;
}

int ambi_cropac_getDAWsamplerate(void* const hAmbi)
{
    ambi_cropac_data *pData = (ambi_cropac_data*)(hAmbi);
    return pData->fs;
}

int ambi_cropac_getProcessingDelay()
{
    return 12*HOP_SIZE;
}
