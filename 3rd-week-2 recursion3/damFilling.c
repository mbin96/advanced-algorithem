#include <stdio.h>
#include <stdlib.h>
#define BLK 7

void display();
int fillRegion(int * arr, int x, int y){
    if (arr[y*BLK+x]!=1){
        return 0;
    }else{
        arr[y*BLK+x]=2;
        display(arr);
        fillRegion(arr, x+1,y);
    fillRegion(arr, x-1,y);
    fillRegion(arr, x,y+1);
    fillRegion(arr, x,y-1);
    fillRegion(arr, x-1,y-1);
    fillRegion(arr, x+1,y-1);
    fillRegion(arr, x-1,y+1);
    fillRegion(arr, x+1,y+1);
    }
    
}

void display(int * arr){
    for(int y =0 ;y<BLK;y++){

        for(int x = 0;x<BLK;x++){
            printf("%d",arr[y*BLK+x]);

        }
        printf("\n");
    }
}

int main(){
    int arr[BLK*BLK] = {   0,0,0,0,0,0,0,
                        0,0,1,1,1,0,0,
                        0,1,0,0,0,1,0,
                        0,1,0,0,0,1,0,
                        0,1,0,0,1,0,0,
                        0,0,1,1,1,0,0,
                        0,0,0,0,0,0,0
                    };
    fillRegion(arr,2,1);
    display(arr);
}