#include <stdio.h>
#include<stdlib.h>
#define MAXNODE 17

typedef struct _node {
	int vertex;
	struct _node *next;
}node;

node *GL[MAXNODE];

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

int marker[MAXNODE];//

int nameToInt(char c) {
	return c - 'A';
}

char intToChar(int i) {
	return i + 'A';
}

///////////////////////////print
void printNext(node a){
    printf("%c",intToChar(a.vertex));
    if (a.next!=NULL){
        printNext(*(a.next));
    }
}
void printAdjList(node * a[], int *v) {
	

	for (int i = 0; i < *v; i++) {
        printf("%3c",intToChar(i));

        printf("%3c",intToChar((*a[i]).vertex));
        if ((*a[i]).next!=NULL){
            printNext(*((*a[i]).next));
        }
        printf("\n");
	}
    
	
}

//////////////////////print end

///////////////////////biconnectivity//////////
int sonOfRoot=0, order=0;
int AP_recur(node *a[], int i){//현 노드와 연결된 최 상위 노드를 리턴함
    node *t;
    int min, m;
    marker[i] = min = ++order;
    for (t = a[i]; t != NULL; t = t->next){//현 노드에 연결된 자식 노드가 없을때까지 실행
        if(i == 0 && marker[t->vertex] == 0){//첫 시작 노드인경우
            sonOfRoot++;
        }
        if(marker[t->vertex]==0){//연결된 노드가 0인경우
            m = AP_recur(a, t->vertex);//연결된 노드의 값이
            if(m < min) {
                min = m;
            }
            if(m >= marker[i] && i != 0){//단절점인경우
                printf("* %c %2d : %d\n",intToChar(i),marker[i],m);//노드자기자신,방문순서,연결된 최상위 노드
            }else{//단절점이 아닌경우
                printf("%c %2d : %d\n", intToChar(i), marker[i],m);
            }
        }else if (marker[t->vertex] < min){//연결된 노드에 이미 방문했으며 연결된 노드가 더 상위 노드인경우
            min = marker[t -> vertex];
        }
    }
    return min;
}
void AP_search(node *a[], int v){
    int i, n=0;
    node *t;
    //마커의 초기화
    for (i = 0; i < v; i++){
        marker[i]=0;
    }

    order = sonOfRoot = 0;//루트 초기화

    AP_recur(a,0);

    if (sonOfRoot > 1){
        printf("* ");
    }else{
        printf("    ");
    }
    printf("%c son : %d\n", intToChar(0), sonOfRoot);
}

void visitPrint(int i){
    printf("%3c",intToChar(i));
}

void inputAdjList(node * a[], int *v, int *e) {
	char vertex[3];
	int i, j;
	node *t;
	printf("\ninput numberof node and edge\n");// 
	scanf("%d %d", v, e);//입력받기. 앞이 노드 뒤가 엣지.
	for (i = 0; i < *v; i++) {
		a[i] = NULL;
	}

	for (j = 0; j < *e; j++) {
		printf("\ninput two nodes consist of edge >");
		scanf("%s", vertex);
		i = nameToInt(vertex[0]);
		t = (node *)malloc(sizeof(node));
		t->vertex = nameToInt(vertex[1]);
		t->next = a[i];
		a[i] = t;
        printf("%c",intToChar(a[i]->vertex));

		i = nameToInt(vertex[1]);
		t = (node *)malloc(sizeof(node));
		t->vertex = nameToInt(vertex[0]);
		t->next = a[i];
		a[i] = t;
	}
}

int main() {
	int v, e;

	inputAdjList(GL, &v, &e);
	//printAdjList(GL, &v);
    AP_search(GL, v);
    //depthFirstNonRecurList(GL, v);
}



















