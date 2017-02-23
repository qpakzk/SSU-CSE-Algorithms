#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef int keytype;
typedef int index;

void merge(int h, int m, const keytype U[], const keytype V[], keytype S[]) {
	index i = 0, j = 0, k = 0;

	//각각 정렬된 배열 U와 배열 V의 원소들을 비교하여 배열 S에 정렬하면서 배열 U와 배열 V를 배열 S에 합병한다.
	while(i < h && j < m) {
		if(U[i] < V[j]) {
			S[k] = U[i];
			i++;
		}
		else {
			S[k] = V[j];
			j++;
		}
		k++;
	}

	//비교 후 배열 U 또는 배열 V에 배열 S에 저장하지 않고  남아있는 원소들을 모두 배열 S에 복사한다.
	if(i >= h) {
		for(index p = j; p < m; p++, k++)
			S[k] = V[p];
	}

	if(j >= m) {
		for(index p = i; p < h; p++, k++)
			S[k] = U[p];
	}
}

void merge_sort(int n, keytype S[]) {
	if(n > 1) {
		const  int h = n / 2, m = n - h;
		keytype U[h], V[m];
		//배열 S를 배열 U와 배열 V에 나누어 저장한다.
		for(index i = 0; i < h; i++)
			U[i] = S[i];
		for(int i = 0; i < m; i++)
			V[i] = S[h + i];

		merge_sort(h, U);//배열 U mergesort 진행
		merge_sort(m, V);//배열 V mergesort 진행
		merge(h, m, U, V, S);//각각 정렬된 배열 U와 배열 V를 배열 S에 합병  정렬하면서 저장 한다.
	}
}

int main(void) {

	keytype *S;
	int N;
	struct timeval begin, end;//merge_sort 실행시간 측정
	double time;

	printf("입력받을 데이터 개수: ");
	scanf("%d", &N);

	S = (keytype *)malloc(sizeof(keytype) * N);
	printf("정렬할 데이터 입력: ");
	for(index i = 0; i < N; i++)
		scanf("%d", &S[i]);

	gettimeofday(&begin, NULL);
	merge_sort(N, S);
	gettimeofday(&end, NULL);

	time = (double)(end.tv_usec - begin.tv_usec) / 1000000 + (double)(end.tv_sec - begin.tv_sec);
	for(index i = 0; i < N; i++)
		printf("%d ", S[i]);
	printf("\n");
	printf("Total time: %lf seconds\n", time);
	free(S);
	return 0;
}
