#include "raylib.h"
#include <math.h>

int main(void)
{
    const int W=1100,H=700;
    InitWindow(W,H,"Bouncing Ball - Computer Graphics");
    SetTargetFPS(60);

    Vector2 p={130,130};
    Vector2 v={320,250};
    float radius=28;

    while(!WindowShouldClose()){
        float dt=GetFrameTime();
        p.x+=v.x*dt;
        p.y+=v.y*dt;

        if(p.x<radius){p.x=radius;v.x=fabsf(v.x);}
        if(p.x>W-130-radius){p.x=W-130-radius;v.x=-fabsf(v.x);}
        if(p.y<80+radius){p.y=80+radius;v.y=fabsf(v.y);}
        if(p.y>H-90-radius){p.y=H-90-radius;v.y=-fabsf(v.y);}

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("BOUNCING BALL",425,25,34,YELLOW);

        /* Perspective floor */
        int floorY=H-90;
        for(int y=floorY;y<H;y+=22) DrawLine(0,y,W,y,BLUE);
        for(int x=0;x<W;x+=55) DrawLine(x,floorY,W/2,floorY,BLUE);

        /* Wall */
        DrawRectangle(W-130,80,20,H-170,BLUE);
        for(int y=85;y<H-100;y+=25)
            for(int x=W-128;x<W-110;x+=25)
                DrawRectangle(x,y,20,18,SKYBLUE);

        /* Simple shadow */
        float shadowScale=1.0f-(p.y/H)*0.45f;
        DrawEllipse((int)p.x,H-98, (int)(35*shadowScale), 7, Fade(GRAY,0.55f));

        DrawCircleV(p,radius,RED);
        DrawCircle((int)p.x-8,(int)p.y-9,8,(Color){255,110,110,255});

        DrawText("Real-time animation using raylib",30,H-60,20,LIGHTGRAY);
        DrawText("ESC / close window = exit",800,H-60,18,YELLOW);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
