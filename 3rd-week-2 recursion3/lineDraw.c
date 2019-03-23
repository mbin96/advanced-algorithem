#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define BLK 20


int drawLine(int * canvas, int x1, int y1, int x2, int y2){
    int x3,y3;
    if (abs(x2-x1)<=1&&abs(y2-y1)<=1){
        return 0 ;
    }else{
        x3=(x2-x1)/2;
        y3=(y2-y1)/2;

            canvas[y3*BLK+x3]=1;
        
        
        drawLine(canvas, x1,y1,x3,y3);
        drawLine(canvas,x3,y3,x2,y2);
    }
}

void display(int *canvas){
    for(int y =0 ;y<BLK;y++){

        for(int x = 0;x<BLK;x++){
            printf("%d",canvas[y*20+x]);

        }
        printf("\n");
    }
}

int main(){
    int i, j;
    int * canvas = (int *)calloc(BLK*BLK,sizeof(int));
    drawLine(canvas,1,1,15,15);
    display(canvas);
}
