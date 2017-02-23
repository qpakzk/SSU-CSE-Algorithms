#include <stdio.h>
#define N 5 //N: vertex의 개수
#define INFINITY 10000 //무한대 설정

/* number, index를 int type으로 정의 */
typedef int number;
typedef int index;

/*
* < Floyd's Algorithm >
* n: vertex의 개수
* W: 그래프를 인접행렬로 나타냄
* D[i][j]: 각 vi에서 vj까지 가는  최단 거리
* P[i][j]
* - vi에서 vj까지 가는 최단 경로의 중간에 놓여 있는 정점이 최소한 하나는 있는 경우 -> 그 놓여 있는 정점 중에서 가장 큰 index 대입
* - 최단경로의 중간에 놓여 있는 정점이 없는 경우 -> 0 대입
*/
void floyd(int n, const number (*W)[n + 1], number (*D)[n + 1], index (*P)[n + 1]) {
	index i, j, k;
	//P[i][j]를 0으로 초기화
	for(i = 1; i <= n; i++)
		for(j = 1; j <= n; j++)
			P[i][j] = 0;

	/* vi에서 vj까지 다른 vertex를 거치지 않고 직접 가는 경우는 W와 같다 */
	for(i = 1; i <= n; i++)
		for(j = 1; j <= n; j++)
			D[i][j] = W[i][j];

	/* 최단경로의 거리 구하기 */
	for(k = 1; k <= n; k++) {
		for(i = 1; i <= n; i++) {
			for(j = 1; j <= n; j++) {
				//D[i][j] = minimum(D[i][j], D[i][k] + D[k][j]);
				if(D[i][k] + D[k][j] < D[i][j]) {
					P[i][j] = k;
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}
}

/* 최단경로로 갈 때 지나가는 vertex를 찾는 함수 */
void path(index q, index r, int (*P)[N + 1]) {
	if(P[q][r] != 0) {
		path(q, P[q][r], P);//vi에서 v(k-1)까지 최단경로
		printf("v%d ", P[q][r]);//vk
		path(P[q][r], r, P);//v(k+1)에서 vj까지 최단경로
	}
}

int main(void) {
	/*
	*  directed, weighted graph의 인접행렬
	*  W[i][j]
	*  - vi에서 vj로 가는 edge의 가중치 값
	*  - v1에서 vj로 가는 edge가 없으면 무한대(INFINITY) 대입
	*  - i == j 이면 0 대입
	*/
	//vertex를 1부터 시작하기 위해 배열 index가 0인 부분은 사용하지 않음(사용하는 않는 공간은 -1 대입)
	const number W[N + 1][N + 1] = {

		{-1, -1, -1, -1, -1, -1},
		{-1, 0, 9, INFINITY, 3, INFINITY},
		{-1, 1, 0, 4, INFINITY, 3},
		{-1, 1, INFINITY, 0, 4, 5},
		{-1, INFINITY, INFINITY, 2, 0, INFINITY},
		{-1, INFINITY, 2, 7, INFINITY, 0}
	};

	number D[N + 1][N + 1] = {-1};
	index P[N + 1][N + 1] = {-1};

	floyd(N, W, D, P);

	// 최소 가중치 출력
	printf("v%d에서 v%d로 가는 최단 경로의 거리: %d\n", 1, 5, D[1][5]);

	//최단경로로 갈 때 방문하는 모든 vertex 출력
	printf("최단경로: v%d ", 1);
	if(P[1][5] != 0)
   		path(1, 5, P);
	printf("v%d\n", 5);

	return 0;
}
