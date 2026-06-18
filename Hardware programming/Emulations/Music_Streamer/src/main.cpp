// // #define _GNU_SOURCE // only needed for C
#include <atomic>
#include <thread>
#include "globals.h"
#include "GUI.h"
#include "AudioStreamer.h"
#include "HandleInputs.h"

std::atomic<bool> AudioRunning(true);

void AudioThread(void){
    while(AudioRunning){
        audio.update();
        if(!app.isPlaying)
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main(){
    app.display = TFT_320x240;
    RAYLIB_INIT();
    std::thread audioThread(AudioThread);

    while(!WindowShouldClose()){
        UpdateGUI();
        HandleInputs();
    }

    AudioRunning = false;
    if(audioThread.joinable())
        audioThread.join();
    
    RAYLIB_END();
    return 0;
}
