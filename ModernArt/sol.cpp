#include <cstdio>
#include <cstdlib>

int n, k;

class LinkedNode {
public:
	LinkedNode *_next, *_prev;
	int _value;

	LinkedNode(int v) : _value(v) {
		_next = NULL;
		_prev = NULL;
	}
};

class LinkedList {
public:
	LinkedNode *_head;
	LinkedNode *_tail;

	LinkedList() {
		_head = _tail = NULL;
	}

	LinkedNode * addLast(int v) {
		if (!_head) {
			_head = new LinkedNode(v);
			_tail = _head;
		} else {
			LinkedNode *newNode = new LinkedNode(v);
			newNode->_prev = _tail;
			_tail->_next = newNode;
			_tail = newNode;
		}

		return _tail;
	}

	void swapNodes(LinkedNode *n1, LinkedNode *n2) {
		LinkedNode *n1Prev = n1->_prev;
		LinkedNode *n1Next = n1->_next;

		LinkedNode *n2Prev = n2->_prev;
		LinkedNode *n2Next = n2->_next;

		if (n1Prev) {
			n1Prev->_next = n2;
			n2->_prev = n1Prev;
		}

		if (n1Next) {
			n1Next->_prev = n2;
			n2->_next = n1Next;
		}

		if (n2Prev) {
			n2Prev->_next = n1;
			n1->_prev = n2Prev;
		}

		if (n2Next) {
			n2Next->_prev = n1;
			n1->_next = n2Next;
		}

		if (n1 == _head) {
			_head = n2;
		} else if (n2 == _head) {
			_head = n1;
		}

		if (n1 == _tail) {
			_tail = n2;
		} else if (n2 == _tail) {
			_tail = n1;
		}
	}

	void setFirst(LinkedNode *node) {
		node->_next = _head;
		if (_head) {
			_head->_prev = node;
		}
		_head = node;
	}

	void linkRight(LinkedNode *linkNode, LinkedNode *insertNode) {
		// link this node.
		insertNode->_next = linkNode->_next;
		linkNode->_next = insertNode;
		insertNode->_prev = linkNode;

		if (linkNode == _tail) {
			_tail = insertNode;
		}
	}

	void unlink(LinkedNode *node) {
		LinkedNode *prev = node->_prev;
		LinkedNode *next = node->_next;

		if (!prev) {
			_head = next;
		} else {
			prev->_next = next;
			node->_prev = NULL;
		}

		if (!next) {
			_tail = prev;
		} else {
			next->_prev = prev;
			node->_next = NULL;
		}
	}
};

LinkedNode *m[100001];

int main(int argc, char **argv) {
	freopen("artin.txt", "r", stdin);
	freopen("artout.txt", "w", stdout);

	scanf("%d", &n);
	scanf("%d", &k);

	LinkedList list;

	for (int i = 1; i <= n; i++) {
		LinkedNode *insertNode = list.addLast(i);
		m[i] = insertNode;
	}

	for (int i = 0; i < k; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		
		LinkedNode *theNode = m[x];

		list.unlink(theNode);

		if (y == 0) {
			list.setFirst(theNode);
		} else {
			LinkedNode *anchorNode = m[y];
			list.linkRight(anchorNode, theNode);
		}
	}

	LinkedNode *node = list._head;

	while (node) {
		printf("%d\n", node->_value);
		node = node->_next;
	}


	return 0;
}