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
int weight[MAXNODE];
int parent[MAXNODE];
FILE *fp;
int nheap = 0;
int heap[MAXNODE];

//////////////////////////////////////////////


int nameToInt(char c) {
	return c - 'A';
}

char intToChar(int i) {
	return i + 'A';
}

////////////heap/////////////
void upheap(int *a, int k){
    int v;
    v = a[k];
    while(weight[a[k/2]] <= weight[v] && k/2 > 0){
        a[k] = a[k/2];
        k /= 2;
    }
    a[k] = v;

}


void downheap(int *a, int k){
    int i, v;
    v = a[k];
    while(k <= nheap / 2){
        //2배 즉 k의 자식노드값을 구함
        i = k << 1;
        //자식노드가 존재하면서 오른쪽 자식노드값이 큰경우
        if(i < nheap && weight[a[i]] < weight[a[i+1]]){
            i++;//큰값을 올려야 하니까 오른쪽값을 선택
        }
        //자식노드값이 더 작은경우엔 끝냄.
        if(weight[v] >= weight[a[i]]){
            break;
        }
        //부모노드값을 큰 자식값으로 바꾼다.
        a[k] = a[i];
        k = i;
    }
    //가장 작은 자식노드에 값넣기
    a[k] = v;
}

void insert(int *a, int *n, int v){
    //노드의 맨 끝에 공간은 만들고 값을 넣음
    a[++(*n)] = v;
    upheap(a, *n);
}

int pqEmpty(){
    if(nheap ==0) return 1;
    return 0;
}

int pqExtract(int *a){
    int v = a[1];
    //꺼내고나서 끝값 줄이기(공간없애기)
    a[1] = a[nheap--];
    downheap(a,1);
    return v;
}

//가중치 값이 변경(작아짐) 되었을때 그 부모값부터 재정렬
void adjustHeap(int *a, int n){
    int k;
    for(k = n/2; k >=1; k--){
        downheap(a,k);
    }

}

void pqInit(){
    nheap=0; //heap의 초기화
}

/////////////heapend///////////////////////
void printHeap(int h[]){
    int i;
    printf("\n");
    for(i = 1; i <= nheap; i++){
        printf("%c:%d ", intToChar(h[i]), weight[h[i]]);
    }
}
void visit(int i){
    printf("%3c",intToChar(i));
}


int pqUpdate(int h[], int v, int p){
    if(weight[v] == UNSEEN){ //미방문인 경우
        h[++nheap] = v;
        weight[v] = p;      //음수 웨이트를 넣어줌
        upheap(h, nheap);
        return 1;
    }else{
        if(weight[v] < p){ //p는 음수인 가중치이므로, fringe vertex이면서 새 가중치가 이전 가중치보다 더 작은경우 실행
            weight[v] = p;  //가중치가 더 작은경우 해당 가중치로 변경
            adjustHeap(h,nheap);    //가중치가 변경된게 있으니 힙 정렬
            return 1;       
        }else{
            return 0;   //갱신안된경우
        }
    }
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


void inputAdjjList(node * g[], int *v, int *e) {
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
		fscanf(fp, "%s %d", vertex, &w);
		
        //가지 분석해 리스트 만들기.
        i = nameToInt(vertex[0]);
		t = (node *)malloc(sizeof(node));
		t->vertex = nameToInt(vertex[1]);
		t->next = g[i];
        t->weight = w;
		g[i] = t;

        //위 코드랑 반대로 동작
		i = nameToInt(vertex[1]);
		t = (node *)malloc(sizeof(node));
		t->vertex = nameToInt(vertex[0]);
		t->next = g[i];
        t->weight = w;
		g[i] = t;
	}
}

void PFSadjlist(node *g[], int v){
    int i;
    node *t;
    pqInit();
    for(i = 0; i < v; i++){
        weight[i] = UNSEEN;//초기값 설정
        parent[i] = 0; //tree 설정
    }
    for(i = 0; i < v; i++){
        if(weight[i] == UNSEEN){    //즉 맨 첫번째로 방문한것
            parent[i] = -1; //set root
            pqUpdate(heap, i, UNSEEN);//첫방문이므로 힙의 끝에 공간 만들고 넣은뒤  up힙
            
            while(!pqEmpty()){
                printHeap(heap);
                i = pqExtract(heap);//힙에서 하나 가져오기
                weight[i] = -weight[i];//무게의 역(루트방문의 경우 int_min의 역수인 intmax가 된다)
                visit(i);   //방문표시
                for(t = g[i]; t !=NULL; t = t -> next){ //리스트 따라가기
                    if(weight[t->vertex] < 0){  //UNSEEN 노드나 fringe노드인 경우
                        if(pqUpdate(heap, t-> vertex, -t -> weight)){   // i와 (t->vertex)간의 무게 비교. 
                            parent[t->vertex] = i;//이전무게보다 작은경우 변경하고 부모노드의 갱신
                        }
                    }
                }
            }
        }
    }
}

////////////////////////////////HW start/////////////////////////////////////
int calCost(int weight[], int v){
    int cost = 0;
    for(int i = 1; i < v; i++){
        cost += weight[i];      //fringe 노드를 tree vertex로 할때의 각각의 가중치를 다 더한
    }
    return cost;
}

void printParent(int v){
    for (int i = 0; i < v; i++){
        if(parent[i] > -1){
            printf("%c's parent is %c\n",intToChar(i),intToChar(parent[i])); //루트노드 외의 경우엔 부모를 출력 
        }else{
            printf("%c is root\n",intToChar(i));    
        }
    }
}
////////////////////////////////HW end//////////////////////////////////////




int main(){
    int v, e;
    fp = fopen("graph.txt", "rt");

    inputAdjjList(G, &v, &e);
    printf("\nOriginal Graph\n");
    printAdjlist(G, v);
    printf("\nVisit order of Minimum Spaning tree\n");
    PFSadjlist(G, v);
    ///////////////////////HW start///////////////////////////
    printf("\nMinimum Coat is %d\n",calCost(weight, v));
    printParent(v);
    ///////////////////////HW end///////////////////////////
    fclose(fp);
}