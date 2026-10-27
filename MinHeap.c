#include<stdio.h>

#include<stdlib.h>

typedef struct {
    int dist;
    int node;
} HeapNode;

typedef struct {
    HeapNode *head;
    int CurrentSize;
    int Capacity;
} MinHeap;

void swap(HeapNode *p, HeapNode *q){
    HeapNode t = *p;
    *p = *q;
    *q = t;
}

int less(HeapNode *p, HeapNode *q){
    if (p->dist != q->dist){
        return p->dist < q->dist;
    }
    return p->node < q->node;
}

int Heapinit(MinHeap *h){
    h->CurrentSize = 0;
    h->Capacity = 8;
    h->head = malloc(8*sizeof(HeapNode));
    return h->head != NULL;
}

int push(MinHeap *h, HeapNode *r){
    if(h->CurrentSize == h->Capacity){
        HeapNode *temp = NULL;
        temp = realloc(h->head, h->Capacity * 2 * sizeof(HeapNode));
        if(temp == NULL) return 0;
        h->head = temp;
        h->Capacity *= 2;
    }
    h->head[h->CurrentSize].dist = r->dist;
    h->head[h->CurrentSize].node = r->node;
    int i = h->CurrentSize;
    h->CurrentSize++;
    while(i > 0){
        int parent = (i-1)/2;
        if(less(&h->head[i], &h->head[parent])){
            swap(&h->head[i],&h->head[parent]);
        }
        else break;
        i = parent;
    }
    return 1;
}

HeapNode pop(MinHeap *h){
    HeapNode g = {-1,-1};
    if(h->CurrentSize == 0) return g;
    h->CurrentSize--;
    HeapNode smallest = h->head[0];
    h->head[0].dist = h->head[h->CurrentSize].dist;
    h->head[0].node = h->head[h->CurrentSize].node;
    int i = 0;
    while(1){
        int minimum = i;
        int left = 2*i + 1;
        int right = 2*i + 2;
        if(left < h->CurrentSize && less(&h->head[left],&h->head[i])){
            minimum = left;
        }
        if(right < h->CurrentSize && less(&h->head[right],&h->head[minimum])){
            minimum = right;
        }
        if(i == minimum) break;
        swap(&h->head[i],&h->head[minimum]);
        i = minimum;
    }
    return smallest;
}
void destroy(MinHeap *h){
    free(h->head);
    h->CurrentSize = 0;
    h->Capacity = 0;
    h->head = NULL;
}
int main()
{  //Sample Initialization for use
    MinHeap m;
    MinHeap *p = &m;
    if(!Heapinit(p)) return 1;
    HeapNode r;
    HeapNode *q = &r;
    q->dist = 5;
    q->node = 1;
    if(!push(p,q)) return 1;
    printf("Current distance: %d Current Node : %d" ,p->head[0].dist,p->head[0].node);
    destroy(p);
    return 0;
}
