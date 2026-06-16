// // #define _GNU_SOURCE // only needed for C
#include <stdio.h>
#include "globals.h"
#include "GUI.h"
#include "AudioStreamer.h"

int main(){
    RAYLIB_INIT();
    while(!WindowShouldClose()){
        UpdateGUI();
        audio.update();
    }
    RAYLIB_END();
    return 0;
}
