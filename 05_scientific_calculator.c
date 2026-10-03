#include "raylib.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef struct { Rectangle r; const char *label; } Button;

static bool clicked(Button b)
{
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
           CheckCollisionPointRec(GetMousePosition(),b.r);
}

int main(void)
{
    const int W=800,H=700;
    InitWindow(W,H,"Scientific Calculator - Computer Graphics");
    SetTargetFPS(60);

    const char *labels[]={
        "sin","cos","tan","log","sqrt",
        "7","8","9","/","C",
        "4","5","6","*","(",
        "1","2","3","-","=",
        "0",".","^","+"," )"
    };
    Button btn[25];
    for(int i=0;i<25;i++){
        int col=i%5,row=i/5;
        btn[i].r=(Rectangle){100+col*115,180+row*75,95,58};
        btn[i].label=labels[i];
    }

    char display[100]="0";
    double a=0,b=0,result=0;
    char op=0;
    bool error=false;

    while(!WindowShouldClose()){
        for(int i=0;i<25;i++){
            if(clicked(btn[i])){
                const char *s=btn[i].label;
                if(s[0]>='0'&&s[0]<='9'){
                    if(display[0]=='0'&&display[1]=='\0') display[0]=0;
                    if((int)strlen(display)<80) strcat(display,s);
                } else if(s[0]=='.'){
                    if(!strchr(display,'.')) strcat(display,".");
                } else if(s[0]=='C'){
                    strcpy(display,"0"); a=b=result=0; op=0; error=false;
                } else if(!strcmp(s,"sin")||!strcmp(s,"cos")||!strcmp(s,"tan")||
                          !strcmp(s,"log")||!strcmp(s,"sqrt")){
                    double v=atof(display);
                    if(!strcmp(s,"sin")) result=sin(v*PI/180.0);
                    else if(!strcmp(s,"cos")) result=cos(v*PI/180.0);
                    else if(!strcmp(s,"tan")) result=tan(v*PI/180.0);
                    else if(!strcmp(s,"log")) { if(v<=0) error=true; else result=log10(v); }
                    else { if(v<0) error=true; else result=sqrt(v); }
                    if(!error) strcpy(display,TextFormat("%.6g",result));
                } else if(s[0]=='+'||s[0]=='-'||s[0]=='*'||s[0]=='/'||s[0]=='^'){
                    a=atof(display); op=s[0]; strcpy(display,"0");
                } else if(s[0]=='='){
                    b=atof(display);
                    if(op=='+') result=a+b;
                    else if(op=='-') result=a-b;
                    else if(op=='*') result=a*b;
                    else if(op=='/' && b!=0) result=a/b;
                    else if(op=='^') result=pow(a,b);
                    else if(op=='/' && b==0) error=true;
                    strcpy(display,error?"ERROR":TextFormat("%.6g",result));
                    op=0;
                }
            }
        }

        BeginDrawing();
        ClearBackground((Color){20,20,30,255});
        DrawText("SCIENTIFIC CALCULATOR",225,30,32,YELLOW);
        DrawRectangle(90,90,620,65,(Color){190,230,190,255});
        DrawText(display,110,108,34,BLACK);

        for(int i=0;i<25;i++){
            Color c=(i<5)?BLUE:((i%5==3||i%5==4)?ORANGE:GRAY);
            if(btn[i].label[0]=='C') c=RED;
            if(btn[i].label[0]=='=') c=GREEN;
            DrawRectangleRec(btn[i].r,c);
            DrawRectangleLinesEx(btn[i].r,2,WHITE);
            int tw=MeasureText(btn[i].label,22);
            DrawText(btn[i].label,(int)(btn[i].r.x+btn[i].r.width/2-tw/2),
                     (int)(btn[i].r.y+18),22,WHITE);
        }
        DrawText("Mouse: click buttons | sin/cos/tan use degrees",170,590,20,LIGHTGRAY);
        DrawText("ESC / close window = exit",285,625,20,YELLOW);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
