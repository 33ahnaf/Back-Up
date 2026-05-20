#include <stdio.h>
#include <raylib.h>

#define winX 700
#define winY 500
#define FramesToSkip 3

int currentW, currentH;

void INIT_PROGRAM(void);
void END_PROGRAM(void);
void Update_Window_Size_Variables(int *, int *);
void gotoNextFrame(void);



int main(){
    INIT_PROGRAM();
    InitAudioDevice();
    Music music1 = LoadMusicStream("archangle.mp4");
    Update_Window_Size_Variables(&currentW, &currentH);
    while(!WindowShouldClose()){
        if(IsKeyPressed(KEY_F)){
            ToggleFullscreen();
            gotoNextFrame();
            Update_Window_Size_Variables(&currentW, &currentH);
        }
        if(IsKeyPressed(KEY_P)){
            PlayMusicStream(music1);
        }
        BeginDrawing();
        ClearBackground(MAROON);
        EndDrawing();
    }
    UnloadMusicStream(music1);
    CloseAudioDevice();
    END_PROGRAM();
    return 0;
}



void INIT_PROGRAM(void){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(winX, winY, "Music Player");
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
}

void END_PROGRAM(void){
    CloseWindow();
}

void Update_Window_Size_Variables(int *width, int *height){
    *width = GetRenderWidth();
    *height = GetRenderHeight();
}

void gotoNextFrame(void){
    for(int i = 0; i < FramesToSkip; i++){
        BeginDrawing();
        EndDrawing();
    }
}