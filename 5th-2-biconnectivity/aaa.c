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

/*
//////////////////////////depthsearch
void visitPrint(int i){
    printf("%3c",intToChar(i));
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
        j = i; //인덱스에 시작점인 i값을 넣어준다.
        push(j); // 첫실행 할 head 리스트 노드 푸시

        while(!stackEmpty()){   //하나로 이어진 그래프는 while이내에서 끝난다.
            j = pop();          //다음에 실행할 인덱스를 갱신해준다.
            p = a[j];           //스택에서 하나 꺼내서 대응하는 현재 노드와 연결된 노드리스트를 불러온다.
            
            //방문 하지 않은 마커인경우 마커를 1로 바꾸고 연결된 노트들을 스택에 넣는다.
            if(1 != marker[j]){ 
                marker[j] = 1;  //헤드 마킹을 한다.
                visitPrint(j);  //프린트
                //현재 노드와 연결된 노드를 스택에 넣는다. 단 연결된 노드가 이미 스택에 들어있는경우엔 무시
                //p는 head에 연결된 첫 노드부터 연결리스트를 탐색한다. 탐색은 마지막 연결리스트까지 계속한다. 
                for (p = a[j]; p != NULL; p = p -> next){               
                    if (0 == marker[p -> vertex]){  //아직 방문을 안하고 스택에 안들어간 노드만 스택에 넣는다    
                        push(p -> vertex);          
                        marker[p -> vertex] = 2;    //스택에 들어간 노드는 2를 마크
                    }
                }
            }
        }
        printf("\n그래프 하나 서치완료\n\n");
    }
}

//////////////////////////depthsearchEnd
*/

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



















