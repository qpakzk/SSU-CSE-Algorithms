#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef int index;
typedef int keytype;

//교환함수
void swap(keytype *itemA, keytype *itemB) {
	keytype temp = *itemA;
	*itemA = *itemB;
	*itemB = temp;
}

void partition(index low, index high, index *pivotpoint, keytype S[]) {
	index i, j;
	keytype pivotitem;//pivot으로 삼을 값 저장

	pivotitem = S[low];
	j = low;//j로 pivotpoint 찿기
	for(i = low + 1; i <= high; i++) {
		//pivotitem보다 작은 값은 pivotitem 왼쪽으로 이동
		if(S[i] < pivotitem) {
			j++;
			swap(&S[i], &S[j]);
		}
	}
	*pivotpoint = j;
	swap(&S[low], &S[*pivotpoint]);
}

void quicksort(index low, index high, keytype S[]) {
	index pivotpoint;//pivot index 저장
	
	if(high > low) {
		partition(low, high, &pivotpoint, S);//pivotpoint를 중심으로 나눈다.
		quicksort(low, pivotpoint - 1, S);//pivotpoint 왼쪽 정렬
		quicksort(pivotpoint + 1, high, S);//pivotpoint 오른쪽 정렬
	}
}
int main(void) {
	keytype *S;
	int N;
	struct timeval begin, end;//quicksort 실행시간 측정
	double time;

	printf("입력할 데이터 개수: ");
	scanf("%d", &N);

	S = (keytype *)malloc(sizeof(keytype) * N);
	printf("정렬할 데이터 입력: ");
	for(index i = 0; i < N; i++)
		scanf("%d", &S[i]);

	gettimeofday(&begin, NULL);
	quicksort(0, N - 1, S);
	gettimeofday(&end, NULL);

	time = (double)(end.tv_usec - begin.tv_usec) / 1000000 + (double)(end.tv_sec - begin.tv_sec);

	for(index i = 0; i < N; i++)
		printf("%d ", S[i]);
	printf("\n");
	printf("Total time: %lf seconds\n", time);

	free(S);
	return 0;
}
