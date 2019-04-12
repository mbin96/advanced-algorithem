#include <stdlib.h>
#include <stdio.h>

////////////heap/////////////
void upheap(int *a, int k){
    int v;
    v = a[k];
    a[0] = 2147483637;

    //부모노드값이 현 노드보다 더 작은경우 값을 바꿔준다.
    while(a[k/2] <= v && k/2 > 0){
        //부모노드를 확인해서 노드값을 밑으로 내림
        a[k] = a[k/2];
        k /= 2;
    }
    //마지막에 가능한 최상위 루트에 값을 넣어줌 
    a[k] = v;
}
void downheap(int *a, int n, int k){
    int i, v;
    v = a[k];
    while(k <= n / 2){
        //2배 즉 k의 자식노드값을 구함
        i = k << 1;
        //자식노드가 존재하면서 오른쪽 자식노드값이 큰경우
        if(i < n && a[i] < a[i+1]){
            i++;//큰값을 올려야 하니까 오른쪽값을 선택
        }
        //자식노드값이 더 작은경우엔 끝냄.
        if(v >= a[i]){
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
int extract(int *a, int *n){
    int v = a[1];
    //꺼내고나서 끝값 줄이기(공간없애기)
    a[1] = a[(*n)--];
    downheap(a,*n,1);
    return v;
}
void heapSort(int * a, int size){
    int i;
    int heapNode = 0; //
    int * heap = calloc(size+1,sizeof(int));
    for(i = 1; i <= size; i++){
        insert(heap, &heapNode, a[i]);
        printf("%d", a[i]);
    }
    for(i = heapNode; i>=1; i--){
        a[i] = extract(heap,&heapNode);
        printf("%d",a[i]);
    }
}

/////////////heapend///////////////////////
int main(){
    int node[] = {NULL,9,3,1,5,7}; //sort 할 입력값
    heapSort(node, 5);

}