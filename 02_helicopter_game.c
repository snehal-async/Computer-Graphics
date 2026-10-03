#include "raylib.h"
#include <stdlib.h>
#include <time.h>

typedef struct { float x, gapY, gapH; } Obstacle;

static void draw_helicopter(float x, float y)
{
    DrawEllipse((int)x, (int)y, 35, 15, BLUE);
    DrawEllipse((int)x+8, (int)y-2, 13, 8, SKYBLUE);
    DrawRectangle((int)x-8, (int)y-24, 4, 12, GRAY);
    DrawLine((int)x-35, (int)y-28, (int)x+25, (int)y-28, WHITE);
    DrawLineEx((Vector2){x+32,y}, (Vector2){x+48,y-8}, 4, YELLOW);
    DrawLineEx((Vector2){x-18,y+12}, (Vector2){x-25,y+23}, 3, WHITE);
    DrawLineEx((Vector2){x+18,y+12}, (Vector2){x+25,y+23}, 3, WHITE);
    DrawLine((int)x-25,(int)y+23,(int)x+25,(int)y+23,WHITE);
    DrawCircle((int)x+14,(int)y-3,3,WHITE);
}

int main(void)
{
    const int W=1100,H=700;
    InitWindow(W,H,"Helicopter Game - Computer Graphics");
    SetTargetFPS(60);
    srand((unsigned)time(NULL));

    float hx=180, hy=H/2.0f, vy=0;
    Obstacle obs[5];
    for(int i=0;i<5;i++){
        obs[i].x=500+i*180;
        obs[i].gapY=180+rand()%260;
        obs[i].gapH=170;
    }
    int score=0, gameOver=0;

    while(!WindowShouldClose()){
        if(!gameOver){
            if(IsKeyDown(KEY_UP)) vy-=0.55f;
            if(IsKeyDown(KEY_DOWN)) vy+=0.55f;
            vy*=0.94f;
            hy+=vy;

            for(int i=0;i<5;i++){
                obs[i].x-=4.5f;
                if(obs[i].x < -40){
                    obs[i].x=W+100;
                    obs[i].gapY=160+rand()%300;
                    score++;
                }
            }

            if(hy<65 || hy>H-65) gameOver=1;
            for(int i=0;i<5;i++){
                Rectangle top={obs[i].x,55,40,obs[i].gapY-obs[i].gapH/2-55};
                Rectangle bottom={obs[i].x,obs[i].gapY+obs[i].gapH/2,40,H-(obs[i].gapY+obs[i].gapH/2)-55};
                Rectangle heli={hx-35,hy-15,70,30};
                if(CheckCollisionRecs(heli,top)||CheckCollisionRecs(heli,bottom)) gameOver=1;
            }
        } else if(IsKeyPressed(KEY_R)){
            hx=180; hy=H/2.0f; vy=0; score=0; gameOver=0;
            for(int i=0;i<5;i++){obs[i].x=500+i*180;obs[i].gapY=180+rand()%260;}
        }

        BeginDrawing();
        ClearBackground((Color){5,8,20,255});
        DrawText("HELICOPTER GAME", 400, 22, 34, YELLOW);
        DrawRectangle(0,55,W,15,RED); DrawRectangle(0,H-70,W,15,RED);

        for(int i=0;i<5;i++){
            float a=obs[i].gapY-obs[i].gapH/2;
            float b=obs[i].gapY+obs[i].gapH/2;
            DrawRectangle((int)obs[i].x,55,40,(int)a-55,DARKGRAY);
            DrawRectangle((int)obs[i].x,(int)b,40,H-70-(int)b,DARKGRAY);
            DrawRectangleLines((int)obs[i].x,55,40,(int)a-55,GRAY);
            DrawRectangleLines((int)obs[i].x,(int)b,40,H-70-(int)b,GRAY);
        }
        draw_helicopter(hx,hy);
        DrawText(TextFormat("Score: %d",score),25,H-45,22,GREEN);
        DrawText("UP / DOWN = move    ESC/window = exit",350,H-45,20,WHITE);

        if(gameOver){
            DrawRectangle(300,260,500,170,Fade(BLACK,0.85f));
            DrawText("GAME OVER",430,295,42,RED);
            DrawText("Press R to restart",430,355,25,YELLOW);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
