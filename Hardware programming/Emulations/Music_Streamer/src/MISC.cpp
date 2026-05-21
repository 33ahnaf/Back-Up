#include "MISC.h"
#include "globals.h"

void showINFO(void){
    // printf("bass: %1.1f  mid: %1.1f  tre: %1.1f     lowCut: %1.3f  highCut: %1.3f     reverbMix: %1.2f  reverbFeedback: %1.2f\n", bassGain, midGain, treGain, lowCut, highCut, reverbMix, reverbFeedback);
    printf("\nbass: %1.1f  mid: %1.1f  tre: %1.1f     junoRate: %1.2f  junoDepth: %4.1f  junoMix: %1.2f     reverbMix: %1.2f  reverbFB: %1.2f\n", bassGain, midGain, treGain, junoRate, junoDepth, junoMix, reverbMix, reverbFeedback);
}

void fastForwardAudio(AudioFile *audioFile){
    if(ftell(audioFile->stream) + audioFile->sample_rate*2*5 > audioFile->file_size){
        fseek(audioFile->stream, audioFile->file_size-1, SEEK_SET);
        // printf("\nCurrent position: %dth byte\n", ftell(audioFile->stream));
    }else{
        fseek(audioFile->stream, audioFile->sample_rate*2*5, SEEK_CUR);
        // printf("\nCurrent position: %dth byte\n", ftell(audioFile->stream));
    }
}

void rewindAudio(AudioFile *audioFile){
    if(ftell(audioFile->stream) - audioFile->sample_rate*2*5 > 0){
        fseek(audioFile->stream, ftell(audioFile->stream) - audioFile->sample_rate*2*5, SEEK_SET);
        // printf("\nCurrent position: %dth byte\n", ftell(audioFile->stream));
    }else{
        fseek(audioFile->stream, audioFile->header_size, SEEK_SET);
        // printf("\nCurrent position: %dth byte\n", ftell(audioFile->stream));
    }
}

void progressBar(AudioFile *audioFile){
    int progress = (int)((double)ftell(audioFile->stream) / audioFile->data_size * 100.0f);
    int totalSeconds = audioFile->data_size / (audioFile->sample_rate*2);
    int currentSecond = (ftell(audioFile->stream) - audioFile->header_size) / (audioFile->sample_rate*2);
    printf("\r%3d%%", progress);
    printf(" [");
    for(int i = 0; i < 50; i++){
        if(i < progress/2)
            printf("+");
        else
            printf(" ");
    }
    printf("]\t%02d:%02d / %02d:%02d", currentSecond/60, currentSecond%60, totalSeconds/60, totalSeconds%60);
    fflush(stdout);
}