#include <cstdio>
#include <cstdlib>

int n, k;

class LinkedNode {
public:
	LinkedNode *_next, *_prev;
	int _value;

	LinkedNode() {
		_next = NULL;
		_prev = NULL;
		_value = 0;
	}
};

/*
2
6
4
5
7
3
1*/

LinkedNode m[100005];

int main(int argc, char **argv) {
	freopen("artin.txt", "r", stdin);

#ifndef __APPLE__
	freopen("artout.txt", "w", stdout);
#endif

	scanf("%d", &n);
	scanf("%d", &k);

	LinkedNode *first = &m[1];

	for (int i = 1; i <= n; i++) {
		m[i]._value = i;
		if (i > 1) {
			m[i]._prev = &m[i-1];
		}
		if (i < n) {
			m[i]._next = &m[i+1];
		}
	}

	while (k--) {
		int x, y;
		scanf("%d %d", &x, &y);

		LinkedNode *theNode = &m[x];

		if (y == 0 && theNode == first) {
			continue;
		}

		{
			if (theNode == first) {
				first = theNode->_next;
			}
			// unlink
			LinkedNode *prevNode = theNode->_prev;
			LinkedNode *nextNode = theNode->_next;

			if (prevNode) {
				prevNode->_next = nextNode;
			}
			if (nextNode) {
				nextNode->_prev = prevNode;
			}
		}

		theNode->_next = NULL;
		theNode->_prev = NULL;

		if (y == 0) {
			

			

			theNode->_next = first;
			first->_prev = theNode;
			first = theNode;
		} else {


			LinkedNode *anchorNode = &m[y];

			LinkedNode *anchorNextNode = anchorNode->_next;
			anchorNode->_next = theNode;
			theNode->_prev = anchorNode;
			theNode->_next = anchorNextNode;
			if (anchorNextNode) {
				anchorNextNode->_prev = theNode;
			}
		}
	}

	for (; first; first = first->_next) {
		printf("%d\n", first->_value);
	}


	return 0;
}