// // #define _GNU_SOURCE // only needed for C
// #include <stdio.h>
// #include "AudioStreamer.h"
// #include "GUI.h"
// #include <raylib.h>
// #include <dirent.h>

// #define LCD_WIDTH 320
// #define LCD_HEIGHT 240
// #define LCD_TARGET_FPS 20

// int main(int argc, char **argv){
//     // if(argc > 1){
//     //     GRAPHICS_INIT();
//     //     streamAudio(argv[1]);
//     //     GRAPHICS_END();
//     // }else{
//     //     printf("Error: Argument not given!\n");
//     //     return -1;
//     // }

//     struct dirent *entry;
//     DIR *dir = opendir("./assets/Musics");
//     if(dir == NULL){
//         printf("Could not open directory!");
//         return 1;
//     }
//     // while((entry = readdir(dir)))
//     //     printf("%s\n", entry->d_name);


//     GRAPHICS_INIT();
//     while(!IsWindowReady());
//     while(!WindowShouldClose()){Z$$$$44  
//         BeginDrawing();
//         ClearBackground(MAROON);
//         DrawText(readdir(dir)->d_name, LCD_WIDTH/2, LCD_HEIGHT/2, 10, GREEN);
//         EndDrawing();
//     }
//     GRAPHICS_END();


//     closedir(dir);
//     return 0;
// }

#include <stdio.h>
#include "globals.h"
#include "GUI.h"
#include "AudioStreamer.h"

int main(){
    GRAPHICS_INIT();
    // while(!WindowShouldClose()){
    // UpdateGUI();
    // }
    // GRAPHICS_END();
    AudioStreamer audio;
    app.isPlaying = true;
    app.selectedSong = "Tears";
    audio.load(app.selectedSong);
    while(!audio.audioShouldStop){
        audio.update();
    }
    audio.unload();
    GRAPHICS_END();
    return 0;
}