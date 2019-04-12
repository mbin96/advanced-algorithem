#include <stdio.h>
#include <stdlib.h>

typedef struct list{
    int key;
    struct list * next;
    struct list * prev;
}list;


//////////////////queue////////////
list * head, * tail;//전역함수

//큐초기화
void initQueue(){
    head = (list *)calloc(1,sizeof(list));
    tail = (list *)calloc(1,sizeof(list));
    head -> prev = head;
    head -> next = tail;
    tail -> prev = head;
    tail -> next = tail;
}

int put(int value){
    list *temp;
    temp = (list *)calloc(1,sizeof(list));
    if(temp==NULL) {
        printf("outof mem");
        return -1;
    }

    temp -> key = value;
    //주소연결
    temp -> next = tail;
    temp -> prev = tail -> prev;
    tail -> prev -> next = temp;
    tail -> prev = temp;
    return value;

}

int get(){
    list * temp;
    int value;
    temp = head -> next;
    if (temp == tail) return -1;

    value = temp -> key;
    head -> next = temp -> next;
    temp -> next -> prev = head;
    free(temp);
    return value;
}

int queueEmpty(){
    if ((head -> next) == tail){
        return 1;
    }else return 0;
}

///////////////////////queue end///////

#define MAXNODE 17

typedef struct _node {
	int vertex;
	struct _node *next;
}node;

node *GL[MAXNODE];

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

void breadthFirstNonRecurList(node * a[], int v){
    int i;          //루프카운터 변수이자 그래프의 시작 인덱스 지정 변수
    int j;          //인덱스
    node * p;       //탐색 포인터

    //스택과 경로마커의 초기화
    initQueue();       
    for(i = 0; i < v; i++){
        marker[i] = 0; 
    }

    for(i = 0; i < v; i++){ // 분리된 그래프들이 여러개가 있을수있으므로
        j = i; //인덱스에 시작점인 i값을 넣어준다.
        put(j); // 첫실행 할 head 리스트 노드 푸시

        while(!queueEmpty()){   //하나로 이어진 그래프는 while이내에서 끝난다.
            j = get();          //다음에 실행할 인덱스를 갱신해준다.
            p = a[j];           //스택에서 하나 꺼내서 대응하는 현재 노드와 연결된 노드리스트를 불러온다.
            
            //방문 하지 않은 마커인경우 마커를 1로 바꾸고 연결된 노트들을 스택에 넣는다.
            if(1 != marker[j]){ 
                marker[j] = 1;  //헤드 마킹을 한다.
                visitPrint(j);  //프린트
                //현재 노드와 연결된 노드를 스택에 넣는다. 단 연결된 노드가 이미 스택에 들어있는경우엔 무시
                //p는 head에 연결된 첫 노드부터 연결리스트를 탐색한다. 탐색은 마지막 연결리스트까지 계속한다. 
                for (p = a[j]; p != NULL; p = p -> next){               
                    if (0 == marker[p -> vertex]){  //아직 방문을 안하고 스택에 안들어간 노드만 스택에 넣는다    
                        put(p -> vertex);          
                        marker[p -> vertex] = 2;    //스택에 들어간 노드는 2를 마크
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

    breadthFirstNonRecurList(GL, v);
}
