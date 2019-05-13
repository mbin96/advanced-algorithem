#include <stdio.h>
#include<stdlib.h>
#define MAXNODE 17


typedef struct _node {
	int vertex;
	struct _node *next;
}node;

typedef struct _head{
    int count;
    struct _node *next;
}head;

//////////////global////////////
head network[MAXNODE];
node *GL[MAXNODE];
FILE *fp;

//////////////////stack/////////////////

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
void printAdjList(node * a[], int v) {
	

	for (int i = 0; i < v; i++) {
        printf("%3c",intToChar(i));

        if(a[i] != NULL){
            printf("%3c",intToChar((*a[i]).vertex));
            if ((*a[i]).next!=NULL){
                printNext(*((*a[i]).next));
            }
            
        }
        printf("\n");
	}
    
	
}

//////////////////////print end

void setCountOutdegree(head net[], int v){
    int i, j;
    int count;
    node *t;
    for (i = 0; i < v; i++){
        count = 0;
        for (t = net[i].next; t != NULL; t = t -> next){
            count++;
        }
        net[i].count = count;
    }
}

//////////////////////////depthsearch
void visitPrint(int i){
    printf("%3c",intToChar(i));
}

void revTopoSort(head net[], node * a[], int v){
    int i;          //루프카운터 변수이자 그래프의 시작 인덱스 지정 변수
    int j;          //인덱스
    int k;
    node * p;       //탐색 포인터

    //스택과 경로마커의 초기화
    init_stack();    
    
    for(i = 0; i < v; i++){ 
        if(!net[i].count){
            push(i); // 첫실행 할 것들 상위노드가 없는것들
        }
    }

    for(i = 0; i < v; i++){
        while(!stackEmpty()){   //하나로 이어진 그래프는 while이내에서 끝난다.
            j = pop();          //다음에 실행할 인덱스를 갱신해준다.
            visitPrint(j);  //프린트
            //현재 노드와 연결된 노드를 스택에 넣는다. 단 연결된 노드가 이미 스택에 들어있는경우엔 무시
            //p는 head에 연결된 첫 노드부터 연결리스트를 탐색한다. 탐색은 마지막 연결리스트까지 계속한다. 
            for(k = 0; k < v; k++){
                for (p = net[k].next; p != NULL; p = p -> next){               
                    if(p->vertex == j){
                        net[k].count--;
                        if (!net[k].count){  //아직 방문을 안하고 스택에 안들어간 노드만 스택에 넣는다    
                            push(k);          
                        }
                    }
                }
            }
        }
    }
}

//////////////////////////depthsearchEnd

void inputAdjList(node * g[], int *v, int *e) {
	char vertex[3];
	int i, j, w;
	node *t;
	printf("\ninput numberof node and edge\n");// 
	fscanf(fp,"%d %d", v, e);//입력받기. 앞이 노드 뒤가 엣지.
	for (i = 0; i < *v; i++) {
		g[i] = NULL;
	}

	for (j = 0; j < *e; j++) {
		printf("\ninput two nodes consist of edge >");
		fscanf(fp, "%s", vertex);
		
        //가지 분석해 리스트 만들기.
        i = nameToInt(vertex[0]);
		t = (node *)malloc(sizeof(node));
		t->vertex = nameToInt(vertex[1]);
		t->next = g[i];
		g[i] = t;

	}
}

void netCopy(head network[], node * a[], int v){
    for (int j = 0; j < v; j++){
        network[j].next = a[j];
    }
   
}

int main() {
	int v, e;
    fp = fopen("directedAcycleGraph.txt", "rt");
	inputAdjList(GL, &v, &e);
	printAdjList(GL, v);
    netCopy(network, GL, v);
    setCountOutdegree(network, v);
    revTopoSort(network, GL, v);
}



















