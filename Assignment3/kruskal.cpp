#include <iostream>
#include <queue>
#define N 5
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

//disjoint set data structure 2 시작
struct nodetype {
	int parent;
	int depth;
};

typedef nodetype universe[100];
universe U;

void makeset(int i) {
	U[i].parent = i;
	U[i].depth = 0;
}

int find(int i) {
	int j;
	j = i;
	while(U[j].parent != j)
		j = U[j].parent;
	return j;
}

void merge(int p, int q) {
	if(U[p].depth == U[q].depth) {//트리의 깊이가 증가한다.
		U[p].depth = U[p].depth + 1;
		U[q].parent = p;
	}
	else if(U[p].depth < U[q].depth)//깊이가 작은 트리를 자식노드로 만든다
		U[p].parent = q;
	else
		U[q].parent = p;
}

bool equal(int p, int q) {
	if(p == q)
		return true;
	else
		return false;
}

void initial(int n) {
	int i;
	for(i = 1; i <= n; i++)
		makeset(i);
}

//disjoint set data structure 2 끝

//우선순위큐에서 비교 기준(weight) 설정하는 구조체
struct compare {
  bool operator()(const set_of_edge& l, const set_of_edge& r)
  {
      return l.weight > r.weight;
  }
};

//F에 저장된 원소개수 계산
int size(set_of_edge F[], int n) {
	int cnt = 0;
	for(int i = 1; i <= n-1; i++) {
		if(F[i].weight == 0) {
			break;
		}
		cnt++;
	}
	return cnt++;
}

//크루스칼 알고리즘
void kruskal(int n, int m, set_of_edge E[], set_of_edge F[]) {
	int i, j;
	int p, q;
	edge e;

	//E에 속한 m개의 이음선을 가중치가 작은 것부터 차례대로 정렬
	priority_queue<set_of_edge,vector<set_of_edge>, compare > pq;
	for(int s = 0; s < m; s++)
    pq.push(E[s]);

	//n개의 서로소 부분집합을 초기화
	initial(n);
	int s = 1;
	while(size(F, n) < n - 1) {
		e = pq.top().e;//아직 고려되지 않은 이음선 중에서 가중치가 최소인 이음선
		pq.pop();

		//e로 연결된 정점의 인덱스
		i = e.v1;
		j = e.v2;
		p = find(i);
		q = find(j);
		if(!equal(p, q)) {
			merge(p, q);
			set_of_edge res;
			res.e = e;
			F[s++] = res;//e를 F에 추가
		}
	}

}


int main(void) {
	set_of_edge E[] = {
		{{1, 2}, 4},
		{{1, 3}, 3},
		{{1, 4}, 8},
		{{2, 4}, 7},
		{{3, 4}, 5},
		{{3, 5}, 2},
		{{4, 5}, 6}
	};

	int m = sizeof(E) / sizeof(E[0]);
	set_of_edge F[N] = {0};

	kruskal(N + 1, m, E, F);
	for(int i = 1; i <= N - 1; i++)
		cout << "<" << F[i].e.v1 << " - " << F[i].e.v2 << ">" << endl;
	return 0;
}
