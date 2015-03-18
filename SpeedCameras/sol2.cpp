#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <cstring>

const int MAX_N = 1005;

struct Node {
	Node *prev, *next;
	std::string plate;
	int where;
};

int N;
std::map<std::string, int> in;
std::vector<std::string> inV(MAX_N);
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
		inV[i] = s;
	}

	Node *prev = NULL;

	for (int i = 0; i < N; i++) {
		char s[10];
		scanf("%s", s);
		Node *n = new Node();
		n->plate = s;
		n->where = in[s];
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

	int ans = 0;

	for (;;) {
		bool inOrder = true;

		Node *cur = head;
		int i = 0;

		while (cur) {
			std::string wtf = cur->plate;
			int where = cur->where;

			if (where != i) {
				int prevIndex = where-1;

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
					move->next = NULL;

					tail->next = move;
					move->prev = tail;
					tail = move;
				} else {
					Node *idx = nodeMap[inV[prevIndex]];

					if (move == head) {
						head = move->next;
					}

					move->next = NULL;

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