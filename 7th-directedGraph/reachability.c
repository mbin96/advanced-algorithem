#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct node{
    int vertex;
    int weight;
    struct node *next;
}node;

///////////////define and golbal variable///////
#define MAXNODE 100
#define UNSEEN (INT_MIN+1)

node *G[MAXNODE];
FILE *fp;
int nodematrix[MAXNODE][MAXNODE];
int marker[MAXNODE];//

//////////////////////////////////////////////

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


void visit(int i){
    printf("%3c",intToChar(i));
}


void printAdjlist(node *g[], int v){
    int i;
    node *t;
    for(i = 0; i < v; i++){
        printf("\n%c : ",intToChar(i));
        for(t = g[i]; t!= NULL; t = t->next){
            printf("-> %c:%d ", intToChar(t->vertex),t->weight);
        }
    }
}


void inputAdjjList(node * g[], int * v, int * e) {
	char vertex[3];
	int i, j, w;
	node *t;
	printf("\ninput numberof node and edge\n");// 
	fscanf(fp,"%d %d", v, e);//입력받기. 앞이 노드 뒤가 엣지.
	for (i = 0; i < (*v); i++) {
		g[i] = NULL;
	}

	for (j = 0; j < *e; j++) {
		printf("\ninput two nodes consist of edge >");
		fscanf(fp, "%s %d", vertex, &w);
		
        //가지 분석해 리스트 만들기.
        i = nameToInt(vertex[0]);
		t = (node *)malloc(sizeof(node));
		t->vertex = nameToInt(vertex[1]);
		t->next = g[i];
        t->weight = w;
		g[i] = t;

	}
}

void depthFirstNonRecurList(node * a[], int v){
    int i;          //루프카운터 변수이자 그래프의 시작 인덱스 지정 변수
    int j;          //인덱스
    node * p;       //탐색 포인터

    //스택과 경로마커의 초기화
    init_stack();       
    for(i = 0; i < v; i++){
        marker[i] = 0; 
    }

    for(i = 0; i < v; i++){ // 분리된 그래프들이 여러개가 있을수있으므로
        for(j = 0; j < v; j++){
            marker[j] = 0;
        }
        push(i); // 첫실행 할 head 리스트 노드 푸시
        marker[i] = 1;
        printf("\n%c : ",intToChar(i));

        while(!stackEmpty()){   //하나로 이어진 그래프는 while이내에서 끝난다.
            j = pop();          //다음에 실행할 인덱스를 갱신해준다.
            //p = a[j];           //스택에서 하나 꺼내서 대응하는 현재 노드와 연결된 노드리스트를 불러온다.
            visit(j);
            for (p = a[j]; p != NULL; p = p -> next){               
                if (0 == marker[p -> vertex]){  //아직 방문을 안하고 스택에 안들어간 노드만 스택에 넣는다    
                    push(p -> vertex);          
                    marker[p -> vertex] = 1;    //스택에 들어간 노드는 2를 마크
                }
            }
            
        }
        
    }
}

///////////////////warshall////////////
void warshall(int a[][MAXNODE], int v){
    int x, y, z ,k;
    for (y = 0; y < v; y++){
        for(x = 0; x < v; x++){
            if (a[x][y] == 1){
                for(z = 0; z < v;z++){
                    if(a[y][z] == 1){
                        a[x][z] = 1;
                    }
                }        
            }
        }
    }
}

void inputAdjMatrix(int a[][MAXNODE], int *v, int *e) {
	char vertex[3];
	int i, j;
	node *t;
	printf("\ninput numberof node and edge\n");// 
	fscanf(fp,"%d %d", v, e);//입력받기. 앞이 노드 뒤가 엣지.
	for(i = 0; i < *v ; i++){
        for(j = 0; j< *v; j++){
            a[i][j] = 0; //초기화
        }
    }
    for(i = 0; i < *v; i++){
        a[i][i] = 1;
    }
	for (j = 0; j < *e; j++) {
		printf("\ninput two nodes consist of edge >");
		fscanf(fp, "%s", vertex);
		
        int c = nameToInt(vertex[0]);
        int b = nameToInt(vertex[1]);
        a[c][b]=1;
        


	}
}

void printmatrix(int a[][MAXNODE], int v){
    printf("\n");
    for (int i = 0; i < v; i++){
        for (int j = 0; j < v; j++){
            printf("%3d",a[i][j]);

        }
        printf("\n");
    }
}
//////////////////////////////////

int main(){
    int v, e;
    fp = fopen("graph.txt", "rt");

    inputAdjMatrix(nodematrix,&v,&e);
    printmatrix(nodematrix,v);
    warshall(nodematrix,v);
    printmatrix(nodematrix,v);
    inputAdjjList(G, &v, &e);
    depthFirstNonRecurList(G,v);
    fclose(fp);
}