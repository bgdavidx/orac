#include <cstdio>
#include <cstdlib>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <algorithm>

const int MAX_N = 2005;
const int MAX_Y = 1000001;

//7 14 12 19
//l r  l  y

typedef std::pair<int, int> Point;
typedef bool (*PlaneSplitter)(Point&, Point&);

#define MakePoint(X, Y) (std::make_pair((X), (Y)))

bool compareX(Point &p1, Point &p2) {
	return p1.first < p1.first;
}

bool compareY(Point &p1, Point &p2) {
	return p1.second < p2.second;
}

const PlaneSplitter split[2] = { compareX, compareY };

inline int comp(Point &p, int axis) {
	return axis == 0 ? p.first : p.second;
}

class KDNode {
public:
	KDNode *left, *right;
	Point data;

	KDNode(std::vector<Point> &pts, int start, int end, int depth) : left(NULL), right(NULL) {
		std::sort(pts.begin()+start, pts.begin()+end, split[depth % 2]);

		int median = start+((end-start)/2);
		data = pts[median];

		/*for (int i = 0; i < depth; i++) {
			printf("\t");
		}

		printf("MEDIAN=%d %d SPLIT ON %s=%d\n", data.first, data.second, depth%2==0?"X":"Y", depth%2==0?data.first:data.second);
		*/

		if (start != end) {
			if (start < median)
				this->left = new KDNode(pts, start, median-1, depth+1);
			if (end > median)
				this->right = new KDNode(pts, median+1, end, depth+1);
		}
	}

	int findMax(int left, int right, int low, int yy, int depth) {
		//printf("findMax(%d %d %d %d %d)\n", left, right, low, yy, depth);
		int axis = depth % 2;

		int ans = 0;

		if (left) {
			if (axis == 0) {
				if (data.first < right) {
					int leftAns = this->left->findMax(left, right, low, yy, depth+1);
					if (leftAns > ans) {
						ans = leftAns;
					}
				}
			} else {
				if (data.second < low) {
					int topAns = this->left->findMax(left, right, low, yy, depth+1);

					if (topAns > ans) {
						ans = topAns;
					}
				}
			}
		}

		if (data.first > left && data.first < right && data.second <= low) {
			//printf("InRect\n");
			int w = right-left;
			int h = yy - data.second;

			if (h >= w) {
				int thisAns = w+h;

				if (thisAns > ans) {
					ans = thisAns;
				}
			}
		} else {
			//printf("%d %d not in rect\n", data.first, data.second);
		}

		if (axis == 0 && right) {
			if (data.first > left) {
				int rightAns = this->right->findMax(left, right, low, yy, depth+1);

				if (rightAns > ans) {
					ans = rightAns;
				}
			}
		} else {
			/*if (data.second >= low) {
				int bottomAns = this->right->findMax(left, right, low, yy, depth+1);

				if (bottomAns > ans) {
					ans = bottomAns;
				}
			}*/
		}

		return ans;
	}
};

std::vector<Point> in;
int N;

int main() {
#ifdef __APPLE__
	freopen("starin.txt", "r", stdin);
#endif

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		in.push_back(MakePoint(x, y));
	}

	KDNode *kd = new KDNode(in, 0, N-1, 0);

	int ans = 0;

	for (int i = 0; i < in.size(); i++) {
		for (int j = i+1; j < in.size(); j++) {
			Point p1 = in[i];
			Point p2 = in[j];

			if (p1.second == p2.second) {
				int x1 = std::min(p1.first, p2.first);
				int x2 = std::max(p1.first, p2.first);

				int w = x2-x1;

				if (w >= 3) {
					int lowy = p1.second - w;
					// (x1, 0), (x2, lowy)

					int teh = kd->findMax(x1, x2, lowy, p1.second, 0);

					if (teh > ans) {
						ans = teh;
					}
				}
			}
		}
	}

	printf("%d\n", ans);

	return 0;
}