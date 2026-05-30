#include "DSP_Effects.h"
#include "globals.h"
#include "MISC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define REVERB_DELAY 250 // 250ms
#define JUNO_DELAY 50 // 50ms
#define MODULE_NAME "DSP_Effects"

// optimal DO NOT TOUCH
float lowCut = 0.01;
float highCut = 0.125;

void ReverbState::applyReverb(float *sample){
    float delayed = buffer[writePos];
    *sample = *sample + delayed * reverbMix;
    buffer[writePos] = *sample + delayed * reverbFeedback;
    writePos++;
    if(writePos >= size)
        writePos = 0;
}

void JunoState::applyJuno(float *sample){
    buffer[writePos] = *sample;

    float lfo1 = (sin(phase1) + 1.0f) * 0.5f;
    float lfo2 = (sin(phase2) + 1.0f) * 0.5f;

    float delay1 = 200 + lfo1 * junoDepth;
    float delay2 = 200 + lfo2 * junoDepth;

    int readPos1 = writePos - (int)delay1;
    int readPos2 = writePos - (int)delay2;

    if(readPos1 < 0) readPos1 += size;
    if(readPos2 < 0) readPos2 += size;

    float delayed1 = buffer[readPos1];
    float delayed2 = buffer[readPos2];

    float chor = (delayed1 + delayed2) * 0.5f;

    *sample = *sample * (1.0f - junoMix) + chor * junoMix;
    writePos++;
    if(writePos >= size)
        writePos = 0;
    phase1 += junoRate * 0.001f;
    phase2 += junoRate * 0.001f * 0.7f;
    if(phase1 > 6.283185f) phase1 -= 6.283185f;
    if(phase2 > 6.283185f) phase2 -= 6.283185f;
}

void ReverbState::allocate(uint32_t sample_rate){
    size = (REVERB_DELAY / 1000.0f) * sample_rate;
    buffer = (float*)malloc(size * sizeof(float));
    if(!buffer){
        printf("Error: ReverbState malloc() failed! [%s]\n", MODULE_NAME);
        while(1);
    }
    memset(buffer, 0, size * sizeof(float));
    printf("Reverb size: %u\n", size);
}

void ReverbState::release(void){
    free(buffer);
    size = 0;
}

void JunoState::allocate(uint32_t sample_rate){
    size = (JUNO_DELAY / 1000.0f) * sample_rate;
    buffer = (float*)malloc(size * sizeof(float));
    if(!buffer){
        printf("Error: JunoState malloc() failed! [%s]\n", MODULE_NAME);
        while(1);
    }
    memset(buffer, 0, size * sizeof(float));
    printf("Juno size: %u\n", size);
}

void JunoState::release(void){
    free(buffer);
    size = 0;
}

void Reverb_Juno_allocate_all(uint32_t sample_rate, ReverbState *revL, ReverbState *revR, JunoState *junoL, JunoState *junoR){
    revL->allocate(sample_rate);
    revR->allocate(sample_rate);
    junoL->allocate(sample_rate);
    junoR->allocate(sample_rate);
}

void Reverb_Juno_release_all(ReverbState *revL, ReverbState *revR, JunoState *junoL, JunoState *junoR){
    revL->release();
    revR->release();
    junoL->release();
    junoR->release();
}

void EQState::applyEQ(uint8_t *sample, ReverbState *rs, JunoState *js){
    // Normalize
    float s = (float)(*sample - 128);

    // low band
    low += lowCut * (s - low);

    // high band
    float hp = s - low;
    high += highCut * (hp - high);

    float mid = s - low - high;
    float out = low * bassGain + mid * midGain + high * treGain;

    // if(st == &left){
    //     revL.applyReverb(&out, reverbMix, reverbFeedback);
    //     junoL.applyJuno(&out, junoRate, junoDepth, junoMix);
    // }else if(st == &right){
    //     revR.applyReverb(&out, reverbMix, reverbFeedback);
    //     junoR.applyJuno(&out, junoRate, junoDepth, junoMix);
    // }

    rs->applyReverb(&out);
    js->applyJuno(&out);

    *sample = constrain((int)(out + 128), 0, 255);
}