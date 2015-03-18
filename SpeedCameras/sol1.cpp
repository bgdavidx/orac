#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <cstring>

#define D() do { for (int i = 0; i < N; i++) { \
		printf("%s ", out[i].c_str()); \
	} \
	printf("\n"); } while (0);

#define MAX_N 1005

struct Node {
	Node *prev, *next;
	std::string plate;
};

int N;
//std::vector<std::string> out(MAX_N);
std::map<std::string, int> in;
std::map<int, std::string> inMirror;
std::map<std::string, Node*> nodeMap;
bool switched[MAX_N] = {0};
Node *head, *tail;

int main() {
	freopen("camin.txt", "r", stdin);
#ifndef __APPLE__
	freopen("camout.txt", "w", stdout);
#endif
	
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		char s[10];
		scanf("%s", s);
		in[s] = i;
		inMirror[i] = s;
	}

	Node *prev = NULL;

	for (int i = 0; i < N; i++) {
		char s[10];
		scanf("%s", s);
		//out[i] = s;
		Node *n = new Node();
		n->plate = s;
		nodeMap[s] = n;
		if (prev) {
			n->prev = prev;
			prev->next = n;
		} else {
			head = n;
		}

		prev = n;
	}

	tail = prev;

/*	for (int i = 0; i < N; i++) {
		printf("%s ", out[i].c_str());
	}
	printf("\n");*/

	/*
	TRS80MCX
	IOI2004
	DEB18N
	REDCAR
	REGINA41

	IOI2004
	REGINA41
	REDCAR
	TRS80MCX
	DEB18N


	
	
	
	TRS80MCX
	IOI2004
	DEB18N
	REDCAR
	REGINA41

	IOI2004, REGINA41, REDCAR, REGINA41

	REGINA41 IOI2004 REDCAR TRS80MCX DEB18N 
	IOI2004 REDCAR TRS80MCX DEB18N REGINA41 
	IOI2004 TRS80MCX DEB18N REDCAR REGINA41 
	TRS80MCX IOI2004 DEB18N REDCAR REGINA41 

	IOI2004
	REGINA41
	REDCAR
	TRS80MCX
	DEB18N


	
	
	TRS80MCX
	IOI2004
	DEB18N
	REDCAR
	REGINA41

*/

	/*
REDCAR
L0LL1P0P
UQ9396
109DLY
B1LKENT

B1LKENT
UQ9396
REDCAR
L0LL1P0P
109DLY

B1LKENT
UQ9396
REDCAR
L0LL1P0P
109DLY



REDCAR
L0LL1P0P
UQ9396
109DLY
B1LKENT

*/

	int ans = 0;

	for (;;) {
		bool inOrder = true;

		Node *cur = head;
		int i = 0;

		while (cur) {
			std::string wtf = cur->plate;
			//printf("processing %s %d\n", wtf.c_str(), i);
			int where = in[wtf];

			if (in[wtf] != i) {
				int prevIndex = where-1;
				// swap i and either last item or nodeMap[inMirror[prevIndex]]
				//out.erase(out.begin()+i);

				//printf("%s is misplaced\n", wtf.c_str());

				Node *move = nodeMap[wtf];

				{
					Node *next = move->next;
					Node *prev = move->prev;

					if (next) {
						next->prev = prev;
					}

					if (prev) {
						prev->next = next;
					}
				}

				if (prevIndex == -1) {
					//out.push_back(wtf);
					move->next = NULL;
					move->prev = NULL;

					tail->next = move;
					move->prev = tail;
					tail = move;
					//printf("Move %s to end\n", move->plate.c_str());
				} else {
					//std::vector<std::string>::iterator idx = std::find(out.begin(), out.end(), inMirror[prevIndex]);
					//out.insert(idx+1, wtf);
					Node *idx = nodeMap[inMirror[prevIndex]];
					//printf("Insert %s after %s\n", move->plate.c_str(), idx->plate.c_str());

					if (move == head) {
						head = move->next;
					}

					move->next = NULL;
					move->prev = NULL;

					Node *next = idx->next;

					idx->next = move;
					move->prev = idx;

					if (next) {
						next->prev = move;
						move->next = next;
					}

					if (idx == tail) {
						tail = move;
					}
				}

				inOrder = false;

				if (!switched[where]) {
					ans++;
				}
				switched[where] = true;

				//D();

				/*{
					Node *blah = head;

					while (blah) {
						printf("%s ", blah->plate.c_str());
						blah = blah->next;
					}
					printf("\n");
				}*/

				break;
			}

			cur = cur->next;
			i++;
		}

		if (inOrder) {
			break;
		}
	}

	printf("%d\n", ans);
	return 0;

}