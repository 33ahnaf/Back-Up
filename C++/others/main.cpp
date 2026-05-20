#include <iostream>
#include <raylib.h>

using namespace std;

const int screen_width = 800, screen_height = 600;

class Ball{
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw(){
        DrawCircle(x, y, radius, WHITE);
    }
    void Update(){
        x += speed_x;
        y += speed_y;

        if(y + radius >= screen_height || y + radius <= 0){
            speed_y *= -1;
        }
        if(x + radius >= screen_width || x + radius <= 0){
            speed_x *= -1;
        }

    }
};

class Paddle{
public:
    float x, y;
    float width, height;
    int speed;

    void Draw(){
        DrawRectangle(x, y, width, height, WHITE);
    }

    void Update(){
        if(IsKeyDown(KEY_UP)){
            y -= speed;
        }
        if(IsKeyDown(KEY_DOWN)){
            y += speed;
        }
        if(y <= 10){
            y = 10;
        }
        if(y + height >= screen_height - 10){
            y = screen_height - height - 10;
        }
    }
};

class CPU_Paddle: public Paddle{
public:
    void Update(int ball_y){
        if(ball_y > y + (height/2)){
            y += speed;
        }else if(ball_y < y + (height/2)){
            y -= speed;
        }
    }
};

Ball ball;
Paddle player;
CPU_Paddle cpu;

int main(){
    cout << "Game is now running..." << endl;
    InitWindow(screen_width, screen_height, "My Pong Game!");
    SetTargetFPS(60);

    ball.radius = 15;
    ball.x = (screen_width/2);
    ball.y = (screen_height/2);
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.width = 25;
    player.height = 120;
    player.x = (screen_width - player.width) - 10;
    player.y = (screen_height/2) - (player.height/2);
    player.speed = 6;

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = (screen_height/2) - (cpu.height/2);
    cpu.speed = 6;

    while(WindowShouldClose() == false) {
        BeginDrawing();

        // Updating
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        // Drawing
        ClearBackground(BLACK);
        DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);
        ball.Draw();
        cpu.Draw();
        player.Draw();
       
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
