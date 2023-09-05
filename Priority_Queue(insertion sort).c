//�켱���� ť(����Ʈ ���-���� ����)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma warning(disable:4996)

typedef struct node {
	int elem; // �ڷ����� ��� �ذ��ϰ��� �ϴ� ������ ���� �����غ���
	struct node* prev;
	struct node* next;
}node;

typedef struct {
	node* header;
	node* trailer;
	int n; //��� ����
}double_linked_list;

double_linked_list *list;
double_linked_list *Priority_Queue;

//�켱���� ť ADT
void insertItem(double_linked_list *L,int e); //���⼱ e�� key�� �����Ѵ�.
int removeMin(double_linked_list *L);
int size(double_linked_list *L);
int minElement(double_linked_list *L);
void PQ_sort(double_linked_list *L);

//����Ʈ ADT
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
//���Ḯ��Ʈ ������ �ʿ��� �Լ�
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


// �켱���� ť ADT
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
	int e=0;//���Ҹ� ���� ����
	double_linked_list* Priority_Queue;
	Priority_Queue=(double_linked_list *)malloc(sizeof(double_linked_list));
	initialize(Priority_Queue);
	while(isEmpty(L)==false){  //����Ʈ�� ������� �ʴٸ�
		e=element_removeFisrt(L);
		insertItem(Priority_Queue,e);
	}
	while(isEmpty(Priority_Queue)==false){
		e=removeMin(Priority_Queue);
		addLast(L,e);
	}
	return;
}

//����Ʈ ADT
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
		//���� ���� ���� �湮 ���� �ڵ� �Է�
		p = p->next;

	}
	printf("\n");
	return;
}
int traverse_search_min_rank(double_linked_list *L) {
	node* p;
	int min= 2147483647; //int���� ��� �ִ밪
	int rank_count=1;
	int return_rank;
	p = L->header->next;
	while (p != L->trailer) {
		if(p->elem<min){
			min=p->elem;
			return_rank=rank_count;
		}
		//���� ���� ���� �湮 ���� �ڵ� �Է�
		p = p->next;
		rank_count++;
	}
	return return_rank;
}
void invalidRankException() {
	printf("���� �Ҽ� ���� ������ �����Ͽ����ϴ�. �ٽ� �õ��Ͻʽÿ�.");
}
void FullListException() {
	printf("����Ʈ�� �̹� �����Դϴ�. �ٽ� �õ��Ͻʽÿ�.");
}
void emptyListException() {
	printf("����Ʈ�� �ƹ��͵� �������� �ʽ��ϴ�. �ٽ� �õ��Ͻʽÿ�.");
}
//���Ḯ��Ʈ ������ �ʿ��� �Լ�
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