#include <stdio.h>
#include <stdlib.h>
#define MAXNODE 17
#define SOURCE 'S'
#define SINK 'T'

typedef struct _head{
    int count;
    struct _node *next;
} head;

//////////////global////////////
head network[MAXNODE];
FILE *fp;
int capacity[MAXNODE][MAXNODE];
int flow[MAXNODE][MAXNODE];
int residual[MAXNODE][MAXNODE];
int marker[MAXNODE];
int parent[MAXNODE];
int path[MAXNODE];


int nameToInt(char c){
    if(c == SOURCE)
        return 0;
    else if(c == SINK)
        return 1;
    return c - 'A' + 2;
}

char intToChar(int i){
    if (i == 0)
        return SOURCE;
    else if (i == 1)
        return SINK;
    return i + 'A' + 2;
}
int clearMatrix(int mtrx[][MAXNODE], int vrtx){
    for (int i = 0; i<vrtx; i++){
        for (int j = 0; j < vrtx; j++){
            mtrx[i][j] = 0;
        }
    }
}


    //////////////////queue////////////

//전역변수 선언
int queue[MAXNODE];
int front, rear;

//큐초기화
void initQueue(){
    front = rear = 0;
}

void put(int value){
    queue[rear] = value;
    rear = ++rear % MAXNODE;
}

int get(){
    int value;
    value = queue[front];
    front = ++front % MAXNODE;
    return value;
}

int queueEmpty(){
    if (front == rear)
        return 1;
    else
        return 0;
}

///////////////////////queue end///////




///////////////////////////print

void printMatrix(int graph[][MAXNODE], int v){
    for (int i = 0; i < v ; i++){
        for (int j = 0; j < v; j++){
            printf("%3d", graph[j][i]);
        }
        printf("\n");
    }
}





//////////////////////print end

void setPath(){
    int * tmp;
    int i, count = 0;
    tmp = (int *)calloc(MAXNODE, sizeof(int));
    i = nameToInt('S');
    //i
    while (i>=0){
        tmp[count] = i;
        i = parent[i];
        count++;
    }
    for (i = 0; i < count; i++){
        path[i] = tmp[count - i - 1];
    }
    path[i] = -1;//EOF
    free(tmp);
}

int getAugmentPath(int graph[][MAXNODE], int v, int s, int t)
{
    int i, j;
    //initialize
    initQueue();
    for (i = 0; i < v; i++){
        marker[i] = 0;
        parent[i] = -1;
    }
    i = nameToInt('S');
    //첫발문인경우 실행
    if(marker[i] == 0){
        put(i);
        marker[i] = 1;
        while(!queueEmpty()){
            i = get();
            if(i == nameToInt('T'))
                break;//끝이면 종료
            for (j = 0;j<v;j++){
                if(graph[i][j] != 0){
                    if(marker == 0){
                        put(j);
                        marker[j] = 1;
                        parent[j] = i;
                    }
                }
            }
        }
    }
    setPath();
    if (i == nameToInt('T'))
        return 1;
    else
        return 0;
}



void constructResidual(int capa[][MAXNODE], int flo[][MAXNODE], int resi[][MAXNODE], int v){
    int i, j;
    for (i = 0; i < v; i++){
        for (j = 0; j < v; j++){
            resi[i][j] = capa[i][j] - flo[i][j];
        }
    }
}

void networkFlow(int cap[][MAXNODE], int flo[][MAXNODE], 
                int resi[][MAXNODE], int vrtx, int s, int t){
    //초기화
    int i, min;
    clearMatrix(flo, vrtx);
    clearMatrix(resi, vrtx);
    //최초 residual 그래프 구하기
    constructResidual(cap, flo, resi, vrtx);
    
    //update flow - while no more argument path
    while(getAugmentPath(resi,vrtx,s,t)){
        min = __INT_MAX__;
        for (i = 1; path[i] > -1; i++)
            if(min > resi[path[i-1]][path[i]])
                min = resi[path[i-1]][path[i]];
        for (i = 1; path[i] > -1; i++){
            flo[path[i - 1]][path[i]] = flo[path[i - 1]][path[i]] + min;
            flo[path[i]][path[i - 1]] = - flo[path[i - 1]][path[i]];
            //전체flow패스에 residual path를 더래주는 과정
        }
        constructResidual(cap, flo, resi, vrtx);
    }
}

void inputAdjMatrix(int *v, int *e){
    char vertex[3];
    int i, j, tmpCap, tmpFlo;
    
    printf("\ninput numberof node and edge\n"); //
    fscanf(fp, "%d %d", v, e);                  //입력받기. 앞이 노드 뒤가 엣지.
    for (i = 0; i < *v; i++){
        for (j = 0; j < *v; j++)
        {
            capacity[i][j] = 0;
        }
    }

    for (j = 0; j < *e; j++){
        printf("\ninput two nodes consist of edge >");
        fscanf(fp, "%s", vertex);

        //가지 분석해 리스트 만들기.
        capacity[nameToInt(vertex[0])][nameToInt(vertex[1])] = 1;
        
    }
}



int main(){
    int v, e;
    fp = fopen("11th-Network\graphMatchingInput.txt", "rt");
    inputAdjMatrix(&v, &e);
    printMatrix(flow, v);
    networkFlow(capacity, flow, residual, v, 0, 1);

    printMatrix(residual, v);
    printMatrix(flow, v);
}
