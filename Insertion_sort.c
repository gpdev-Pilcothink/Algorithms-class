#include <stdio.h>
#pragma warning(disable:4996)

void Insertion_sort(int N,int A[]);


int main() {
	int* A;
	int N;
	scanf("%d", &N);
	A = (int *)malloc(sizeof(int) * N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &A[i]);
	}

	Insertion_sort(N, A);

	for (int i = 0; i < N; i++) {
		printf("%d ", A[i]);
	}

}
void Insertion_sort(int N,int A[]) {
	int key = 0;
	int i = 0;
	for (int j = 1; j < N; j++) {
		key = A[j];
		i = j - 1;
		while (i > -1 && A[i] > key) {
			A[i + 1] = A[i];
			i = i - 1;
		}
		A[i + 1] = key;
	}
}