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
 *     ambi_cropac.h (include header)
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

#ifndef __AMBI_CROPAC_H_INCLUDED__
#define __AMBI_CROPAC_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

/***********/
/* Presets */
/***********/

typedef enum _CH_ORDER{
    CH_ACN = 1
}CH_ORDER;

typedef enum _NORM_TYPES{
    NORM_N3D = 1,
    NORM_SN3D
}NORM_TYPES;
    
    
/******************/
/* Main Functions */
/******************/
    
/* creates an instance of ambi_cropac */
void ambi_cropac_create(void** const phAmbi);              /* address of ambi_cropac handle */

/* destroys an instance of ambi_cropac */
void ambi_cropac_destroy(void** const phAmbi);             /* address of ambi_cropac handle */

/* initialises an instance of ambi_cropac */
void ambi_cropac_init(void* const hAmbi,                   /* ambi_cropac handle */
                      int samplerate);                     /* host sample rate */
    
/* decodes the input spherical harmonic signals to loudspeaker or headphone signals */
void ambi_cropac_process(void* const hAmbi,                /* ambi_cropac handle */
                         float** const inputs,             /* input channels, [nInputs][nSampes] */
                         float** const outputs,            /* output channels, [nOutputs][nSampes] */
                         int nInputs,                      /* number of channels in 'inputs' matrix */
                         int nOutputs,                     /* number of channels in 'outputs' matrix */
                         int nSamples,                     /* number of samples in 'inputs' matrix */
                         int isPlaying);                   /* flag, 1: if there is signal in the buffers */

    
/*****************/
/* Set Functions */
/*****************/
    
/* Set reInit Flags to 1 */
void ambi_cropac_refreshParams(void* const hAmbi);

/* Check if any reInit Flags are active, and reinitialise if they are. Only call when playback has stopped. */
void ambi_cropac_checkReInit(void* const hAmbi);
    
void ambi_cropac_setBalance(void* const hAmbi, float newValue, int bandIdx);

void ambi_cropac_setBalanceAllBands(void* const hAmbi, float newValue);

void ambi_cropac_setDecBalance(void* const hAmbi, float newValue, int bandIdx);

void ambi_cropac_setDecBalanceAllBands(void* const hAmbi, float newValue);
    
void ambi_cropac_setCovAvg(void* const hAmbi, float newValue);

void ambi_cropac_setUseDefaultHRIRsflag(void* const hAmbi, int newState);
    
void ambi_cropac_setSofaFilePath(void* const hAmbi, const char* path);

void ambi_cropac_setChOrder(void* const hAmbi, int newOrder);

void ambi_cropac_setNormType(void* const hAmbi, int newType);

void ambi_cropac_setDecEnableMaxrE(void* const hAmbi, int newState);
    
void ambi_cropac_setEnableRotation(void* const hAmbi, int newState);
    
void ambi_cropac_setYaw(void* const hAmbi, float newYaw);

void ambi_cropac_setPitch(void* const hAmbi, float newPitch);

void ambi_cropac_setRoll(void* const hAmbi, float newRoll);

void ambi_cropac_setFlipYaw(void* const hAmbi, int newState);

void ambi_cropac_setFlipPitch(void* const hAmbi, int newState);

void ambi_cropac_setFlipRoll(void* const hAmbi, int newState);

void ambi_cropac_setRPYflag(void* const hAmbi, int newState);
    
    
/*****************/
/* Get Functions */
/*****************/
    
float ambi_cropac_getBalance(void* const hAmbi, int bandIdx);

float ambi_cropac_getBalanceAllBands(void* const hAmbi); /* returns the first value */

void ambi_cropac_getBalanceHandle(void* const hAmbi,
                                  float** pX_vector,
                                  float** pY_values,
                                  int* pNpoints);

float ambi_cropac_getDecBalance(void* const hAmbi, int bandIdx);

float ambi_cropac_getDecBalanceAllBands(void* const hAmbi); /* returns the first value */

void ambi_cropac_getDecBalanceHandle(void* const hAmbi,
                                     float** pX_vector,
                                     float** pY_values,
                                     int* pNpoints);
    
float ambi_cropac_getCovAvg(void* const hAmbi);

int ambi_cropac_getUseDefaultHRIRsflag(void* const hAmbi);

char* ambi_cropac_getSofaFilePath(void* const hAmbi);

int ambi_cropac_getChOrder(void* const hAmbi);

int ambi_cropac_getNormType(void* const hAmbi);
    
int ambi_cropac_getDecEnableMaxrE(void* const hAmbi);
    
int ambi_cropac_getNumEars(void);
    
int ambi_cropac_getNumberOfBands(void);
    
int ambi_cropac_getNSHrequired(void);
    
int ambi_cropac_getEnableRotation(void* const hAmbi);
    
float ambi_cropac_getYaw(void* const hAmbi);

float ambi_cropac_getPitch(void* const hAmbi);

float ambi_cropac_getRoll(void* const hAmbi);

int ambi_cropac_getFlipYaw(void* const hAmbi);

int ambi_cropac_getFlipPitch(void* const hAmbi);

int ambi_cropac_getFlipRoll(void* const hAmbi);
    
int ambi_cropac_getRPYflag(void* const hAmbi);
    
int ambi_cropac_getNDirs(void* const hAmbi);
    
int ambi_cropac_getNTriangles(void* const hAmbi);

int ambi_cropac_getHRIRlength(void* const hAmbi);

int ambi_cropac_getHRIRsamplerate(void* const hAmbi);
 
int ambi_cropac_getDAWsamplerate(void* const hAmbi);
    
int ambi_cropac_getProcessingDelay(void);
    
    
#ifdef __cplusplus
}
#endif


#endif /* __AMBI_CROPAC_H_INCLUDED__ */


