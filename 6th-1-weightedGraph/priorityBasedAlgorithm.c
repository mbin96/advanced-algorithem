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


void inputAdjMatrix(int a[][MAXNODE], int *v, int *e) {
	char vertex[3];
	int i, j, w;
	node *t;
	printf("\ninput numberof node and edge\n");// 
	fscanf(fp,"%d %d", v, e);//입력받기. 앞이 노드 뒤가 엣지.
	for(i = 0; i < *v ; i++){
        for(j = 0; j< *v;j++){
            a[i][j] = INT_MAX; //초기화
        }
    }
    for(i = 0; i<*v; i++){
        a[i][i]=0;
    }
	for (j = 0; j < *e; j++) {
		printf("\ninput two nodes consist of edge >");
		fscanf(fp, "%s %d", vertex, &w);
		
        i = nameToInt(vertex[0]);
        j = nameToInt(vertex[1]);

        a[i][j] = w;
        a[j][i] = w;


	}
}

int distanse[MAXNODE], check[MAXNODE];

void dijkstra(int a[][MAXNODE], int s, int v){
    int x =0, y, d;
    int i, checked=0;
    for (x = 0; x < v ; x++){
        distanse[x] = a[s][x];
        if(x != s){
            parent[x] = s;
        }
    }
    check[s] = 1;
    checked++;

    print_distance(distanse[x], s, v);
    while(check[x]){
        x++;
    }
    for(i = x; i<v; i++){
        if (check[i] == 0 && distance [i] < distance[x]){
            x = i;
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

    inputAdjMatrix(G, &v, &e);
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