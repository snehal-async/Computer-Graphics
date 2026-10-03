#include "raylib.h"
#include <math.h>

#define PI 3.14159265358979323846

static Vector2 hand_end(Vector2 c, float len, float deg)
{
    float a = (deg - 90.0f) * (float)PI / 180.0f;
    Vector2 p = { c.x + len * cosf(a), c.y + len * sinf(a) };
    return p;
}

int main(void)
{
    const int W = 1000, H = 700;
    InitWindow(W, H, "Analog Clock - Computer Graphics");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        double secTotal = GetTime();
        int sec = (int)fmod(secTotal, 60.0);
        int min = (int)(secTotal / 60.0) % 60;
        int hour = (int)(secTotal / 3600.0) % 12;

        Vector2 c = { W/2.0f, H/2.0f + 10 };
        float r = 220.0f;

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("ANALOG CLOCK", 365, 35, 32, YELLOW);
        DrawCircle((int)c.x + 10, (int)c.y + 12, r + 12, Fade(DARKGRAY, 0.7f));
        DrawCircle((int)c.x, (int)c.y, r + 8, BLUE);
        DrawCircle((int)c.x, (int)c.y, r, (Color){15, 35, 85, 255});
        DrawCircleLines((int)c.x, (int)c.y, r, SKYBLUE);

        for (int i = 0; i < 60; i++)
        {
            float a = (i * 6.0f - 90.0f) * (float)PI / 180.0f;
            float outer = r - 12;
            float inner = (i % 5 == 0) ? r - 35 : r - 23;
            Color col = (i % 5 == 0) ? WHITE : LIGHTGRAY;
            Vector2 p1 = {c.x + cosf(a)*inner, c.y + sinf(a)*inner};
            Vector2 p2 = {c.x + cosf(a)*outer, c.y + sinf(a)*outer};
            DrawLineEx(p1, p2, (i % 5 == 0) ? 5 : 2, col);
        }

        const char *nums[] = {"12","1","2","3","4","5","6","7","8","9","10","11"};
        for (int i = 0; i < 12; i++)
        {
            float a = (i * 30.0f - 90.0f) * (float)PI / 180.0f;
            float rr = r - 70;
            int tw = MeasureText(nums[i], 28);
            DrawText(nums[i], (int)(c.x + cosf(a)*rr - tw/2),
                     (int)(c.y + sinf(a)*rr - 14), 28, WHITE);
        }

        float hourAngle = hour*30.0f + min*0.5f + sec/120.0f;
        float minAngle  = min*6.0f + sec*0.1f;
        float secAngle  = sec*6.0f;

        DrawLineEx(c, hand_end(c, r-75, hourAngle), 10, WHITE);
        DrawLineEx(c, hand_end(c, r-45, minAngle), 7, SKYBLUE);
        DrawLineEx(c, hand_end(c, r-28, secAngle), 3, RED);
        DrawCircle((int)c.x, (int)c.y, 9, RED);
        DrawCircle((int)c.x, (int)c.y, 4, WHITE);

        DrawText("Live system-time style animation", 345, H-65, 20, LIGHTGRAY);
        DrawText("ESC / close window to exit", 385, H-35, 18, YELLOW);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
