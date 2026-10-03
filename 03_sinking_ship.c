#include "raylib.h"
#include "raymath.h"
#include <math.h>

static void draw_ship(float x, float y)
{
    Vector2 hull[6]={{x-70,y},{x+70,y},{x+48,y+30},{x-45,y+30},{x-65,y+15},{x-70,y}};
    DrawTriangle(hull[0],hull[1],hull[2],WHITE);
    DrawTriangle(hull[0],hull[2],hull[3],WHITE);
    DrawRectangle((int)x-25,(int)y-28,50,28,LIGHTGRAY);
    DrawRectangle((int)x-20,(int)y-23,12,10,SKYBLUE);
    DrawRectangle((int)x+5,(int)y-23,12,10,SKYBLUE);
    DrawRectangle((int)x-5,(int)y-65,8,37,GRAY);
    DrawTriangle((Vector2){x+3,y-62},(Vector2){x+35,y-45},(Vector2){x+3,y-30},RED);
    DrawRectangle((int)x-48,(int)y+30,96,7,RED);
}

int main(void)
{
    const int W=1100,H=700;
    InitWindow(W,H,"Sinking Ship - Computer Graphics");
    SetTargetFPS(60);

    float shipX=150, shipY=430, sink=0;
    bool night=false, hit=false;

    while(!WindowShouldClose()){
        if(IsKeyPressed(KEY_SPACE)) night=!night;
        if(!hit){
            if(IsKeyDown(KEY_LEFT)) shipX-=3;
            if(IsKeyDown(KEY_RIGHT)) shipX+=3;
            shipX=Clamp(shipX,90.0f,W-90.0f);
            if(shipX>W-230) hit=true;
        } else {
            sink+=0.8f;
            shipY+=0.7f;
        }

        BeginDrawing();
        ClearBackground(night?(Color){5,10,35,255}:SKYBLUE);

        if(night){
            DrawCircle(90,90,34,WHITE);
            DrawCircle(105,80,30,(Color){5,10,35,255});
        } else {
            DrawCircle(90,90,38,YELLOW);
            for(int i=0;i<12;i++){
                float a=i*30*PI/180.0f;
                DrawLine(90+(int)cosf(a)*45,90+(int)sinf(a)*45,
                         90+(int)cosf(a)*62,90+(int)sinf(a)*62,YELLOW);
            }
        }

        DrawText("SINKING SHIP",430,22,34,YELLOW);
        DrawRectangle(0,H/2,W,H/2,BLUE);

        for(int x=0;x<W;x+=55){
            DrawLine(x,H/2+35,x+25,H/2+35,SKYBLUE);
            DrawLine(x+20,H/2+85,x+48,H/2+85,SKYBLUE);
        }

        DrawTriangle((Vector2){W-170,H/2+10},
                     (Vector2){W-110,H/2-45},
                     (Vector2){W-50,H/2+10},DARKGRAY);

        if(!hit) draw_ship(shipX,shipY);
        else if(sink<180) draw_ship(shipX,shipY);

        DrawText("LEFT / RIGHT = move",25,H-45,20,WHITE);
        DrawText("SPACE = day/night",300,H-45,20,YELLOW);
        DrawText("ESC / close window = exit",560,H-45,20,GREEN);

        if(hit){
            DrawText("SHIP HIT!  SINKING...",390,125,30,RED);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
