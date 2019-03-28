#include <stdio.h>
#define MAXNODE 17
void printAdjMatrix(int a[][MAXNODE], int *v){
    int i,j;

    for(i = 0;i < v; i++){
        print("%3c",intToChar(i));
    }

    print("\n");

    for(i = 0; i < v; i++){
        printf("%3c",intToChar(i));

    }
};

int nameToInt(char c){
    return c-'A';
}

char intToChar(int i){
    return i+'A';
}

void inputAdjMatrix(int a[][MAXNODE], int *v, int *e){
    char vertex[3];
    int i, j, k;
    printf("\ninput numberof node and edge\n");// 
    scanf("%d %d", v, e);//입력받기. 앞이 노드 뒤가 엣지.
    for(i = 0; i < *v ; i++){
        for(j = 0; j< *v;j++){
            a[i][j] = 0; //초기화
        }
    }
    for(i = 0; i<*v; i++){
        a[i][i]=1;
    }
    for(k = 0; k < *e; k++){
        printf("\ninput two nodes consist of edge >");
        scanf("%s", vertex);
        i = nameToInt(vertex[0]);
        j = nameToInt(vertex[1]);
        a[i][j] = 1;
        a[j][i] = 1;
    }
}

int main(){
    inputAdjMatrix(GL, &v, &e);
	printAdjMatrix(GL, &v);
}