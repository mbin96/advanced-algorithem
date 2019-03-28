#include <stdio.h>
#include<stdlib.h>
#define MAXNODE 17

int marker[MAXNODE];
int GM[MAXNODE][MAXNODE];

//////////////////stack

#define MAX 10
int stack[MAX];
int top;


void init_stack(void){
    top = -1;
}
int stackEmpty(){
    return (top < 0);
}

int push(int t){
    if(top >= MAX-1){
        printf("stack over\n");
        return -1;
    }

    stack[++top] = t;
    return t;
}

int pop(){
    if(top <0){
        printf("stack under\n");
        return -1;
    }
    return stack[top--];
}


////////////////stack end

int nameToInt(char c) {
	return c - 'A';
}

char intToChar(int i) {
	return i + 'A';
}

void printAdjMatrix(int a[][MAXNODE], int *v){
    int i,j;

    for(i = 0;i < v; i++){
        printf("%3c",intToChar(i));
    }

    printf("\n");

    for(i = 0; i < v; i++){
        printf("%3c",intToChar(i));

    }
};

void visit(int i){
    printf("%3c",intToChar(i));
}

void depthFirstNonRecurMatrix(int a[][MAXNODE], int v){
    int i, j;
    init_stack();
    for(i = 0; i < v; i++){
        marker[i] = 0;
    }
    for(i = 0; i < v; i++){
        if(marker[i]==0){
            push(i);
            marker[i] = 1;
            while(!stackEmpty()){
                i = pop();
                visit(i);
                for (j = 0; j < v; j++){
                    if(a[i][j] != 0){
                        if(marker[j] == 0){
                            push(j);
                            marker[j]=0;
                        }
                    }
                }
            }
        }
    }
}

void depthFirstRecurMatrix(int a[][MAXNODE], int v, int i){
    int j;
    marker[i] = 1;
    visit(i);
    for(j = 0; j < v; j++){
        if(a[i][j] != 0){
            if(marker[j] ==0){
                depthFirstRecurMatrix(a,v,j);
            }
        }
    }
}

void depthFirstAdjMatrix(int a[][MAXNODE], int v){
    int i;
    for(i = 0; i < v; i++){
        marker[i] = 0;
    }
    for(i = 0; i < v; i++){
        if(marker[i] == 0){
            depthFirstRecurMatrix(a, v, i);
        }
    }
}


void inputAdjMatrix(int a[][MAXNODE], int *v, int *e){
    char vertex[3];
    int i, j, k;
    printf("\ninput numberof node and edge\n");// 
    scanf("%d %d", v, e);//입력받기. 앞이 노드 뒤가 엣지.
    for(i = 0; i < *v ; i++){
        for(j = 0; j < *v;j++){
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
    int v, e;

    inputAdjMatrix(GM, &v, &e);
	//printAdjMatrix(GM, &v);
    depthFirstAdjMatrix(GM, v);
    //depthFirstNonRecurMatrix(GM, v);
}