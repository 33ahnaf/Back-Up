#include "SerialHandleInputs.h"
#include "AudioStreamer.h"
#include "globals.h"
#include "GUI.h"
#include <Arduino.h>

void HandleInputs(void){
    if(Serial.available()){
        char c = Serial.read();
        switch(c){
            case 'q': bassGain = bassGain >= HIGH_LIMIT ? HIGH_LIMIT : bassGain + DELTA; audio.showINFO(); break;
            case 'a': bassGain = bassGain <= LOW_LIMIT  ? LOW_LIMIT  : bassGain - DELTA; audio.showINFO(); break;

            case 'w': midGain = midGain >= HIGH_LIMIT ? HIGH_LIMIT : midGain + DELTA; audio.showINFO(); break;
            case 's': midGain = midGain <= LOW_LIMIT  ? LOW_LIMIT  : midGain - DELTA; audio.showINFO(); break;

            case 'e': treGain = treGain >= HIGH_LIMIT ? HIGH_LIMIT : treGain + DELTA; audio.showINFO(); break;
            case 'd': treGain = treGain <= LOW_LIMIT  ? LOW_LIMIT  : treGain - DELTA; audio.showINFO(); break;

            case 'r': junoRate = junoRate >= HIGH_LIMIT ? HIGH_LIMIT : junoRate + 0.05f; audio.showINFO(); break;
            case 'f': junoRate = junoRate <= LOW_LIMIT  ? LOW_LIMIT  : junoRate - 0.05f; audio.showINFO(); break;

            case 't': junoDepth = junoDepth >= 10000 ? 10000 : junoDepth + 100.0f; audio.showINFO(); break;
            case 'g': junoDepth = junoDepth <= 0 ? 0 : junoDepth - 100.0f; audio.showINFO(); break;

            case 'y': junoMix = junoMix >= HIGH_LIMIT ? HIGH_LIMIT : junoMix + 0.05f; audio.showINFO(); break;
            case 'h': junoMix = junoMix <= LOW_LIMIT ? LOW_LIMIT : junoMix - 0.05f; audio.showINFO(); break;

            case 'u': reverbMix = reverbMix >= HIGH_LIMIT ? HIGH_LIMIT : reverbMix + 0.05f; audio.showINFO(); break;
            case 'j': reverbMix = reverbMix <= LOW_LIMIT ? LOW_LIMIT : reverbMix - 0.05f; audio.showINFO(); break;

            case 'i': reverbFeedback = reverbFeedback >= HIGH_LIMIT ? HIGH_LIMIT : reverbFeedback + 0.05f; audio.showINFO(); break;
            case 'k': reverbFeedback = reverbFeedback <= LOW_LIMIT ? LOW_LIMIT : reverbFeedback - 0.05f; audio.showINFO(); break;

            case ' ': audio.pauseAudio = !audio.pauseAudio; Serial.println(audio.pauseAudio ? "Streaming paused!" : "Resumed!"); break;

            case ',': audio.rewindAudio(5000);      audio.progressBar(); break;
            case '.': audio.fastForwardAudio(5000); audio.progressBar(); break;


            case  'o':
                switch(app.currentScreen){
                    case SCREEN_SONG_BROWSER: songBrowser.HandleInput(1, 0, 0, 0); break;
                    case SCREEN_MENU        : ui.HandleInput(1, 0, 0, 0);          break;
                } break;
            
            case  'l':
                switch(app.currentScreen){
                    case SCREEN_SONG_BROWSER: songBrowser.HandleInput(0, 1, 0, 0); break;
                    case SCREEN_MENU        : ui.HandleInput(0, 1, 0, 0);          break;
                } break;
            
            case '\'':
                switch(app.currentScreen){
                    case SCREEN_SONG_BROWSER: songBrowser.HandleInput(0, 0, 1, 0); break;
                    case SCREEN_MENU        : ui.HandleInput(0, 0, 1, 0);          break;
                } break;
            
            case  ']':
                switch(app.currentScreen){
                    case SCREEN_SONG_BROWSER: songBrowser.HandleInput(0, 0, 0, 1); break;
                    case SCREEN_MENU        : ui.HandleInput(0, 0, 0, 1);          break;
                    case SCREEN_AUDIO_PLAYER: audioPlayer.HandleInput(1);          break;
                } break;
        }
    }
}