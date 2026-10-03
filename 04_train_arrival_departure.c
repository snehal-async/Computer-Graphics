#include "raylib.h"

enum { IDLE, ARRIVING, STOPPED, DEPARTING };

static void draw_station(int W,int H)
{
    DrawRectangle(180,180,W-360,210,LIGHTGRAY);
    DrawTriangle((Vector2){150,180},(Vector2){W/2,80},(Vector2){W-150,180},RED);
    DrawRectangle(270,270,560,65,(Color){255,220,80,255});
    DrawText("RAILWAY STATION",370,287,30,BLACK);
    DrawRectangle(475,325,150,65,BROWN);
    DrawRectangle(210,220,90,70,SKYBLUE);
    DrawRectangle(W-300,220,90,70,SKYBLUE);

    int railY=H-130;
    DrawRectangle(0,railY,W,10,DARKGRAY);
    DrawRectangle(0,railY+35,W,10,DARKGRAY);
    for(int x=0;x<W;x+=35) DrawLine(x,railY,x+15,railY+45,BROWN);
}

static void draw_train(float x,int H)
{
    float y=H-220;
    DrawRectangle((int)x,(int)y,190,80,BLUE);
    DrawRectangle((int)x+15,(int)y+15,45,30,SKYBLUE);
    DrawRectangle((int)x+72,(int)y+15,45,30,SKYBLUE);
    DrawRectangle((int)x+129,(int)y+15,45,30,SKYBLUE);
    DrawRectangle((int)x,y+62,190,8,YELLOW);
    DrawCircle((int)x+45,(int)y+85,16,DARKGRAY);
    DrawCircle((int)x+150,(int)y+85,16,DARKGRAY);
    DrawCircle((int)x+45,(int)y+85,7,LIGHTGRAY);
    DrawCircle((int)x+150,(int)y+85,7,LIGHTGRAY);
}

int main(void)
{
    const int W=1100,H=700;
    InitWindow(W,H,"Train Arrival and Departure - Computer Graphics");
    SetTargetFPS(60);

    float x=-220;
    int state=IDLE;

    while(!WindowShouldClose()){
        if(IsKeyPressed(KEY_A)) state=ARRIVING;
        if(IsKeyPressed(KEY_S)) state=STOPPED;
        if(IsKeyPressed(KEY_D)) state=DEPARTING;

        if(state==ARRIVING){x+=4;if(x>=260){x=260;state=STOPPED;}}
        if(state==DEPARTING){x+=6;if(x>W)x=-220,state=IDLE;}

        BeginDrawing();
        ClearBackground((Color){35,65,120,255});
        DrawCircle(930,85,35,WHITE);
        DrawText("TRAIN ARRIVAL AND DEPARTURE",300,25,30,YELLOW);
        draw_station(W,H);
        draw_train(x,H);

        DrawText("A = ARRIVE",80,600,22,GREEN);
        DrawText("S = STOP",280,600,22,YELLOW);
        DrawText("D = DEPART",450,600,22,SKYBLUE);
        DrawText("ESC / close window = exit",690,600,20,WHITE);

        const char *status = state==ARRIVING?"TRAIN ARRIVING":
                            state==STOPPED?"TRAIN STOPPED":
                            state==DEPARTING?"TRAIN DEPARTING":"READY";
        DrawText(status,470,120,24,WHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
