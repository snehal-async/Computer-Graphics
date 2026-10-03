#include "raylib.h"

static int peg[3][8], top[3]={0,0,0}, moves=0, n=5;
static float timer=0;
static bool finished=false;

static void draw_hanoi(void)
{
    const int W=1000,H=700, base=560;
    int px[3]={250,500,750};

    BeginDrawing();
    ClearBackground((Color){10,10,18,255});
    DrawText("TOWER OF HANOI",365,25,34,YELLOW);

    DrawRectangle(80,base,W-160,25,(Color){145,85,35,255});
    for(int i=0;i<3;i++) DrawRectangle(px[i]-7,base-300,14,300,(Color){190,120,50,255});

    for(int p=0;p<3;p++){
        for(int j=0;j<top[p];j++){
            int d=peg[p][j];
            int width=28+d*20;
            int y=base-30-(j+1)*35;
            Color c=(Color){50+d*35,80+(d*25)%140,220-d*25,255};
            DrawRectangle(px[p]-width,y,width*2,30,c);
            DrawRectangleLines(px[p]-width,y,width*2,30,WHITE);
        }
    }
    DrawText("A",px[0]-8,base+35,28,WHITE);
    DrawText("B",px[1]-8,base+35,28,WHITE);
    DrawText("C",px[2]-8,base+35,28,WHITE);

    DrawText(TextFormat("Moves: %d",moves),30,80,22,GREEN);
    if(!finished) DrawText("Automatic animation - ESC / close window to exit",250,640,20,LIGHTGRAY);
    else DrawText("PUZZLE COMPLETED!",390,640,22,YELLOW);
    EndDrawing();
}

static void move_disk(int from,int to)
{
    int d=peg[from][--top[from]];
    peg[to][top[to]++]=d;
    moves++;
}

static void hanoi_step(int count,int from,int aux,int to)
{
    /* This recursive solver is used to generate the move list. */
    if(count==0)return;
    hanoi_step(count-1,from,to,aux);
    move_disk(from,to);
    hanoi_step(count-1,aux,from,to);
}

int main(void)
{
    const int W=1000,H=700;
    InitWindow(W,H,"Tower of Hanoi - Computer Graphics");
    SetTargetFPS(60);

    /* Build initial state. */
    for(int i=n;i>=1;i--) peg[0][top[0]++]=i;

    /* We need an independent move list so the animation can show one move at a time. */
    int movesFrom[64], movesTo[64], moveCount=0;
    /* Generate moves using a small local recursive function is not possible in standard C,
       so use an iterative known sequence for 5 disks. */
    /* Reset and generate the legal sequence with an explicit simulation. */
    top[0]=top[1]=top[2]=0;
    for(int i=n;i>=1;i--) peg[0][top[0]++]=i;

    int total=(1<<n)-1;
    int src=0, aux=1, dst=2;
    if(n%2==0){int t=aux;aux=dst;dst=t;}
    int temp[3][8], tt[3]={0,0,0};
    for(int i=n;i>=1;i--) temp[0][tt[0]++]=i;

    for(int m=1;m<=total;m++){
        int from,to;
        int type=(m-1)%3;
        if(type==0){from=src;to=dst;}
        else if(type==1){from=src;to=aux;}
        else {from=aux;to=dst;}

        /* Find a legal direction between the selected pegs. */
        int a=from,b=to;
        if(tt[a]==0 || (tt[b]>0 && temp[b][tt[b]-1] < temp[a][tt[a]-1])){
            int t=a;a=b;b=t;
        }
        movesFrom[moveCount]=a;
        movesTo[moveCount]=b;
        moveCount++;

        temp[b][tt[b]++]=temp[a][--tt[a]];
    }

    /* Restore visible initial state. */
    top[0]=top[1]=top[2]=0;
    for(int i=n;i>=1;i--) peg[0][top[0]++]=i;
    moves=0;

    int step=0;
    while(!WindowShouldClose()){
        timer+=GetFrameTime();
        if(!finished && timer>0.55f){
            if(step<moveCount){
                move_disk(movesFrom[step],movesTo[step]);
                step++;
                timer=0;
            } else finished=true;
        }
        draw_hanoi();
    }

    CloseWindow();
    return 0;
}
