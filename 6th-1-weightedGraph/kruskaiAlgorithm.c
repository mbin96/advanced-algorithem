#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct edge{
    int vertex1;
    int vertex2;
    int weight;
}Edge;

///////////////define and golbal variable///////
#define MAXNODE 50
#define MAXEDGE 100
#define ONLYFIND 0
#define UNION 1


int height[MAXNODE];
int parent[MAXNODE];
FILE *fp;
int cost;
int nheap = 0;
int heap[MAXNODE];
Edge edge[MAXNODE];

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
    while(edge[(a[k/2])].weight <= edge[v].weight && k/2 > 0){
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
        i = k << 1;//자식노드
        //자식노드가 존재하면서 오른쪽 자식노드값이 큰경우
        if(i < nheap && edge[a[i]].weight < edge[a[i+1]].weight){
            i++;//큰값을 올려야 하니까 오른쪽값을 선택
        }
        //자식노드값이 더 작은경우엔 끝냄.
        if(edge[v].weight >= edge[a[i]].weight){
            break;
        }
        //부모노드값을 큰 자식값으로 바꾼다.
        a[k] = a[i];
        k = i;
    }
    //가장 작은 자식노드에 값넣기
    a[k] = v;
}

void pqInsert(int *a, int v){
    //힙의 맨 끝에 공간은 만들고 값을 넣음
    a[++(nheap)] = v;
    upheap(a, nheap);
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


void visit(int i){
    cost += edge[i].weight;
    printf("visit edge %c %c\n",intToChar(edge[i].vertex1),intToChar(edge[i].vertex2));
}




void findInit(int elem){
    int i;
    for (i = 0; i < elem; i++){
        parent[i] = -1;
    }
}

void inputEdge(Edge edge[], int * v, int * e){
    char vertex[3];
    int  j, w;
	printf("\ninput numberof node and edge\n");// 
	fscanf(fp,"%d %d", v, e);//입력받기. 앞이 노드 뒤가 엣지.
	
	for (j = 0; j < *e; j++) {
		printf("\ninput two nodes consist of edge >");
		fscanf(fp, "%s %d", vertex, &w);
		
        //vertex[2] = NULL;
        edge[j].vertex1 = nameToInt(vertex[0]);
        edge[j].vertex2 = nameToInt(vertex[1]);
        edge[j].weight = w;

	}
}

void unionSet(int elem, int asso){
    parent[elem] = asso;
}

int findSet(int elem, int asso, int flag){
    int i = elem, j = asso;
    while(parent[i] >= 0){
        i = parent[i];
    }
    while(parent[j] >= 0){
        j = parent[j];
    }
    if(flag == UNION && i != j){
        unionSet(i,j);
        
    }
    return (i != j);
}


void kruskai(Edge edge[], int v, int e){
    int n, val =0;
    findInit(v);        //모든 노드의 부모 초기화
    pqInit();           //힙 초기화
    for(n=0; n<e; n++){
        pqInsert(heap, n);  //힙에 엣지를 집어넣자

    }
    n=0;
    while(!pqEmpty()){
        val = pqExtract(heap);  //힙에서 맨 끝값 꺼내기(즉 weight가 가장 작은엣지 꺼냄)
        if (findSet(edge[val].vertex1, edge[val].vertex2, UNION)){
            visit(val);
            n++;
        }
        if (n == v-1){
            break;
        }
    }

}



int main(){
    int v, e;
    fp = fopen("graph.txt", "rt");

    inputEdge(edge, &v, &e);
    //printf("\nOriginal Graph\n");
    //printAdjlist(G, v);
    printf("\nVisit order of Minimum Spaning tree\n");
    kruskai(edge, v, e);
    ///////////////////////HW start///////////////////////////
    //printf("\nMinimum Coat is %d\n",calCost(weight, v));
    //printParent(v);
    ///////////////////////HW end///////////////////////////
    fclose(fp);
}