#include "HandleInputs.h"
#include "AudioStreamer.h"
#include "globals.h"

void HandleInputs(void){
    int key = GetKeyPressed();
    while(key != 0){
        switch(key){
            case KEY_Q:
                bassGain = bassGain >= HIGH_LIMIT ? HIGH_LIMIT : bassGain + DELTA; showINFO(); break;

            case KEY_A:
                bassGain = bassGain <= LOW_LIMIT ? LOW_LIMIT : bassGain - DELTA; showINFO(); break;

            case KEY_W:
                midGain = midGain >= HIGH_LIMIT ? HIGH_LIMIT : midGain + DELTA; showINFO(); break;

            case KEY_S:
                midGain = midGain <= LOW_LIMIT ? LOW_LIMIT : midGain - DELTA; showINFO(); break;

            case KEY_E:
                treGain = treGain >= HIGH_LIMIT ? HIGH_LIMIT : treGain + DELTA; showINFO(); break;

            case KEY_D:
                treGain = treGain <= LOW_LIMIT ? LOW_LIMIT : treGain - DELTA; showINFO(); break;

            case KEY_R:
                junoRate = junoRate >= HIGH_LIMIT ? HIGH_LIMIT : junoRate + 0.05f; showINFO(); break;

            case KEY_F:
                junoRate = junoRate <= LOW_LIMIT ? LOW_LIMIT : junoRate - 0.05f; showINFO(); break;

            case KEY_T:
                junoDepth = junoDepth >= 10000 ? 10000 : junoDepth + 100.0f; showINFO(); break;

            case KEY_G:
                junoDepth = junoDepth <= 0 ? 0 : junoDepth - 100.0f; showINFO(); break;

            case KEY_Y:
                junoMix = junoMix >= HIGH_LIMIT ? HIGH_LIMIT : junoMix + 0.05f; showINFO(); break;

            case KEY_H:
                junoMix = junoMix <= LOW_LIMIT ? LOW_LIMIT : junoMix - 0.05f; showINFO(); break;

            case KEY_U:
                reverbMix = reverbMix >= HIGH_LIMIT ? HIGH_LIMIT : reverbMix + 0.05f; showINFO(); break;

            case KEY_J:
                reverbMix = reverbMix <= LOW_LIMIT ? LOW_LIMIT : reverbMix - 0.05f; showINFO(); break;

            case KEY_I:
                reverbFeedback = reverbFeedback >= HIGH_LIMIT ? HIGH_LIMIT : reverbFeedback + 0.05f; showINFO(); break;

            case KEY_K:
                reverbFeedback = reverbFeedback <= LOW_LIMIT ? LOW_LIMIT : reverbFeedback - 0.05f; showINFO(); break;

            case KEY_SPACE:
                audio.pauseAudio = !audio.pauseAudio; printf("%s\n", audio.pauseAudio ? "Streaming paused!" : "Resumed!"); break;

            case KEY_COMMA:
                audio.rewindAudio(5000); audio.progressBar(); break;

            case KEY_PERIOD:
                audio.fastForwardAudio(5000); audio.progressBar(); break;

        }
        key = GetKeyPressed();
    }
}