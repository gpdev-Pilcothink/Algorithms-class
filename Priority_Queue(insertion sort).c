//우선순위 큐(리스트 기반-선택 정렬)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma warning(disable:4996)

typedef struct node {
	int elem; // 자료형의 경우 해결하고자 하는 문제에 따라서 조절해보자
	struct node* prev;
	struct node* next;
}node;

typedef struct {
	node* header;
	node* trailer;
	int n; //노드 개수
}double_linked_list;

double_linked_list *list;
double_linked_list *Priority_Queue;

//우선순위 큐 ADT
void insertItem(double_linked_list *L,int e); //여기선 e가 key로 전제한다.
int removeMin(double_linked_list *L);
int size(double_linked_list *L);
int minElement(double_linked_list *L);
void PQ_sort(double_linked_list *L);

//리스트 ADT
void initialize(double_linked_list* L);
node* getnode();
void addLast(double_linked_list *L,int e);
int element_remove(double_linked_list* L, int r);
int element_removeFisrt(double_linked_list *L);
void traverse(double_linked_list *L);
int traverse_search_min_rank(double_linked_list *L);
void invalidRankException();
void FullListException();
void emptyListException();
//연결리스트 구현시 필요한 함수
void addNodeBefore(node* p, int e);
int removeNode(node* p);

int main(){
	double_linked_list *List;
	List=(double_linked_list *)malloc(sizeof(double_linked_list));
	initialize(List);
	int n,number;
	scanf("%d", &n);
	if(n>0){
		for(int i=0; i<n; i++){
			scanf("%d", &number);
			addLast(List,number);
		}
		PQ_sort(List);
		traverse(List);
	}
}


// 우선순위 큐 ADT
void insertItem(double_linked_list *L, int e){ //O(1)
	addLast(L,e);
	return;
}
int removeMin(double_linked_list *L){ //O(N)
	return minElement(L);
}
int size(double_linked_list *L){
	return L->n;
}
int minElement(double_linked_list *L){ //O(N)
	int e;
	int min_rank=1;
	min_rank=traverse_search_min_rank(L);
	e=element_remove(L,min_rank);
	return e;
}
bool isEmpty(double_linked_list *L){
	if(L->header->next==L->trailer)
		return true;
	else
		return false;
}
void PQ_sort(double_linked_list *L){
	int e=0;//원소를 담을 공간
	double_linked_list* Priority_Queue;
	Priority_Queue=(double_linked_list *)malloc(sizeof(double_linked_list));
	initialize(Priority_Queue);
	while(isEmpty(L)==false){  //리스트에 비어있지 않다면
		e=element_removeFisrt(L);
		insertItem(Priority_Queue,e);
	}
	while(isEmpty(Priority_Queue)==false){
		e=removeMin(Priority_Queue);
		addLast(L,e);
	}
	return;
}

//리스트 ADT
void initialize(double_linked_list* L) {
	L->header = getnode();
	L->trailer = getnode();
	L->header->next = L->trailer;
	L->trailer->prev = L->header;
	L->n = 0;
	return;
}
node* getnode() {
	node* newnode = (node*)malloc(sizeof(node));
	newnode->prev = NULL;
	newnode->elem = 0;
	newnode->next = NULL;
	return newnode;
}
void addLast(double_linked_list *L,int e) {
	node* p;
	p = L->header->next;
	for (int i = 1; i <= L->n; i++) {
		p = p->next;
	}
	addNodeBefore(p, e);
	L->n += 1;
	return;
}
int element_remove(double_linked_list* L,int r) {
	node* p;
	int e = 0;
	if (r<1 || r > L->n) {
		invalidRankException();
		return 0;
	}
	if (L->n == 0) {
		emptyListException();
		return 0;
	}
	p = L->header;
	for (int i = 1; i <= r; i++) {
		p = p->next;
	}
	e = removeNode(p);
	L->n -= 1;
	return e;
}
int element_removeFisrt(double_linked_list *L) {
	node* p;
	int e = 0;
	if (L->n == 0) {
		emptyListException();
		return 0;
	}
	p = L->header->next;
	e = removeNode(p, e);
	L->n -= 1;
	return e;
}
void traverse(double_linked_list *L) {
	node* p;
	p = L->header->next;
	while (p != L->trailer) {
		printf("%d\n", p->elem);
		//여기 위로 원소 방문 행위 코드 입력
		p = p->next;

	}
	printf("\n");
	return;
}
int traverse_search_min_rank(double_linked_list *L) {
	node* p;
	int min= 2147483647; //int형의 경우 최대값
	int rank_count=1;
	int return_rank;
	p = L->header->next;
	while (p != L->trailer) {
		if(p->elem<min){
			min=p->elem;
			return_rank=rank_count;
		}
		//여기 위로 원소 방문 행위 코드 입력
		p = p->next;
		rank_count++;
	}
	return return_rank;
}
void invalidRankException() {
	printf("접근 할수 없는 범위에 접근하였습니다. 다시 시도하십시요.");
}
void FullListException() {
	printf("리스트가 이미 만원입니다. 다시 시도하십시요.");
}
void emptyListException() {
	printf("리스트에 아무것도 존재하지 않습니다. 다시 시도하십시요.");
}
//연결리스트 구현시 필요한 함수
void addNodeBefore(node* p, int e) {
	node* q;
	q = getnode();
	q->elem = e;
	q->prev = p->prev;
	q->next = p;
	p->prev->next = q;
	p->prev = q;
	return;
}
int removeNode(node* p) {
	int e;
	e = p->elem;
	p->prev->next = p->next;
	p->next->prev = p->prev;
	free(p);
	return e;
}