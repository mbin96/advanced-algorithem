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

//////////////////////////depthsearch
void visitPrint(int i){
    printf("%3c",intToChar(i));
}

void depthFirstNonRecurList(node * a[], int v){
    int i;//루프카운터 변수이자 인덱스
    int j;//인덱스
    node * p;
    init_stack();       //스택 초기화
    for(i = 0; i < v; i++){
        marker[i] = 0; //첫실행시에 경로마커의 초기화
    }
    for(i = 0; i < v; i++){ // 분리된 그래프들이 여러개가 있을수있으므로
        j = i; //인덱스에 i값을 넣어준다.
        push(j); // 첫실행 할 노드 푸시
        while(!stackEmpty()){   //하나로 이어진 그래프는 while이내에서 끝난다.
            j = pop();          //다음에 실행할 인덱스를 갱신해준다.
            p = a[j];           //스택에서 하나 꺼내서 대응하는 현재 노드와 연결된 노드리스트를 불러온다.
            if(1 != marker[j]){ //방문하지 않았으면 마커를 1로 바꾸고 연결된 노트들을 스택에 넣는다.
                marker[j] = 1;
                visitPrint(j);

                for (p = a[j]; p != NULL; p = p -> next){    //현재 노드와 연결된 노드를 스택에 넣는다.            
                    if (0 == marker[p -> vertex]){              //연결된노드가 방문 안한 노드인경우에만 푸시
                        push(p -> vertex);
                        marker[p -> vertex] = 2; //스택에 들어가고 아직 방문안한수는 2가 들어간다
                    }
                }

            }
        
        }
        printf("\n그래프 하나 서치완료\n\n");
    }
}

//////////////////////////depthsearchEnd

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
	printAdjList(GL, &v);

    depthFirstNonRecurList(GL, v);
}



















