#include <iostream>
#define N 4 
using namespace std;

bool promising(int i, bool W[][N + 1], int vcolor[]) {
	int j = 1;
	bool sw = true;
	while(j < i && sw) {
		if(W[i][j] && vcolor[i] == vcolor[j])
			sw = false;
		j++;
	}

	return sw;
}

int m_coloring(int i, int m, bool W[][N + 1], int vcolor[]) {
	int color;
	static int count = 0;	
	if(promising(i, W, vcolor)) {
		if(i == N) {
			for(int k = 1; k <= N; k++)
				cout << vcolor[k] << " ";
			cout << endl;
			count++;
		}
		else {
			for(color = 1; color <= m; color++) {
				vcolor[i + 1] = color;
				m_coloring(i + 1, m, W, vcolor);
			}
		}
	}	

	return count;
}

int main(void) {
	bool W[N + 1][N + 1] = {
		{0, 0, 0, 0, 0},
		{0, 0, 1, 1, 1},
		{0, 1, 0, 1, 0},
		{0, 1, 1, 0, 1},
  		{0, 1, 0, 1, 0}	
	};
	int m = 3;
	int vcolor[N + 1] = {0};
	int  count = m_coloring(0, m, W, vcolor);
	cout << "해의 개수: " << count << endl;
	return 0;
}
