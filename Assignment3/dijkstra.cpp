#include <iostream>
#define N 5
#define INF 1000//무한대 표현
using namespace std;

//이음선
struct edge {
	int v1;
	int v2;
};

//이음선 집합
struct set_of_edge {
	edge e;
	int weight;
};

//다익스트라 알고리즘
void dijkstra(int n, int (*W)[N + 1], set_of_edge *F) {
	int i, vnear, min;
	edge e;
	int touch[n + 1];
	int length[n + 1];

	//각 정점에 대해서 v1에서 출발하는 현재 최단경로의 마지막 정점을 v1으로 초기화한다.
	//그 경로의 길이는 v1에서의 이음선 상의 가중치를 초기화한다.
	for(i = 2; i <= n; i++) {
		touch[i] = 1;
		length[i] = W[1][i];
	}

	int repeat = 1;
	int s = 1;
	//n-1개 정점을 모두 Y에 추가
	while(repeat  <= n - 1) {//최단 경로를 갖는지 각 정점을 점검
		min = INF;
		for(i = 2; i <= n; i++) {
			if(0 <= length[i] && length[i] < min) {
				min = length[i];
				vnear = i;
			}
		}

		e.v1 = touch[vnear];
		e.v2 = vnear;
		set_of_edge res;
		res.e = e;
		F[s++] = res;

		for(i = 2; i <= n; i++) {
			if(length[vnear] + W[vnear][i] < length[i]) {
				length[i] = length[vnear] + W[vnear][i];
				touch[i] = vnear;
			}
		}
		length[vnear] = -1;
		repeat++;
	}

}

int main(void) {
	int W[N + 1][N + 1] = {
		{-1,-1,-1,-1,-1,-1},
		{-1, 0, 7, 5, 4, 1},
		{-1, INF, 0, 5, INF, INF},
		{-1, INF, INF, 0, 2, 6},
		{-1, INF, INF, INF, 0, 7},
		{-1, INF, INF, INF, INF, 0}
	};
	set_of_edge F[N] = {0};

	dijkstra(N, W, F);

	for(int i = 1; i <= N - 1; i++)
		cout << "<" << F[i].e.v1 << " -> " << F[i].e.v2 << ">" << endl;

	return 0;
}
