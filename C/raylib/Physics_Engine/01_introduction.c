#include <stdio.h>
#include <raylib.h>

#define CURRENT_LOCATION_GRAVITATIONAL_ACCELERATION 9.78998
#define winX 700
#define winY 500
#define FramesToSkip 3
#define CIRCLE_accX 0.0
#define CIRCLE_accY CURRENT_LOCATION_GRAVITATIONAL_ACCELERATION
#define BOUNCE_DAMPING 0.8

int currentW, currentH;

typedef struct Circle{
    double x;
    double y;
    double accX;
    double accY;
    float radius;
    Color color;
} Circle;

void INIT_PROGRAM(void);
void END_PROGRAM(void);
void Update_Window_Size_Variables(int *, int *);
void ResetCircle(Circle *);
void gotoNextFrame(void);
void UpdateCircle(Circle *);



int main(){
    INIT_PROGRAM();
    Update_Window_Size_Variables(&currentW, &currentH);
    Circle circle1 = {currentW/2, currentH/2, CIRCLE_accX, CIRCLE_accY, 30.0f, WHITE};
    while(!WindowShouldClose()){
        Update_Window_Size_Variables(&currentW, &currentH);
        if(IsKeyPressed(KEY_F)){
            ToggleFullscreen();
            gotoNextFrame();
            Update_Window_Size_Variables(&currentW, &currentH);
            ResetCircle(&circle1);
        }
        BeginDrawing();
        ClearBackground(MAROON);
        DrawFPS(0, 0);
        DrawCircle(circle1.x, circle1.y, circle1.radius, circle1.color);
        UpdateCircle(&circle1);
        EndDrawing();
    }
    END_PROGRAM();
    return 0;
}



void INIT_PROGRAM(void){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(winX, winY, "Lab");
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
}

void END_PROGRAM(void){
    CloseWindow();
}

void Update_Window_Size_Variables(int *width, int *height){
    *width = GetRenderWidth();
    *height = GetRenderHeight();
}

void ResetCircle(Circle *circle){
    circle->x = GetRenderWidth()/2;
    circle->y = GetRenderHeight()/2;
    circle->accX = CIRCLE_accX;
    circle->accY = CIRCLE_accY;
}

void gotoNextFrame(void){
    for(int i = 0; i < FramesToSkip; i++){
        BeginDrawing();
        EndDrawing();
    }
}

void UpdateCircle(Circle *circle){
    // if(circle->y + circle->radius > currentH || circle->y - circle->radius < 0) circle->accY *= -1;
    // if(circle->x + circle->radius > currentW || circle->x - circle->radius < 0) circle->accX *= -1;
    if(circle->y + circle->radius > currentH){
        circle->y = currentH - circle->radius;
        circle->accY *= -BOUNCE_DAMPING * GetFrameTime();
    }else{
        circle->accY += (circle->accY * GetFrameTime());
    }
    circle->x += circle->accX;
    circle->y += circle->accY;
}