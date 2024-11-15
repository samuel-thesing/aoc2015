#include <utils.h>

struct Point {
	int x;
	int y;

	bool operator<(const Point &other) const {
		if (x == other.x)
			return y < other.y;
		return x < other.x;
	}
};

int solve(const std::string &input) {
	std::set<Point> points;
	auto p = Point{0,0};
	auto p2 = Point{0,0};
	bool flag = false;
	points.insert(p);
	for (char c : input) {
		if (flag) {
			switch (c) {
				case 'v': p.y++; break;
				case '^': p.y--; break;
				case '<': p.x++; break;
				case '>': p.x--; break;
				default: break;
			}
			points.insert(p);
		} else {
			switch (c) {
				case 'v': p2.y++; break;
				case '^': p2.y--; break;
				case '<': p2.x++; break;
				case '>': p2.x--; break;
				default: break;
			}
			points.insert(p2);
		}
		flag = !flag;
	}

	return points.size();
}

int main(int argc, char** argv) {
	auto runner = Runner<int>(solve, 2015, 03);
	runner.add_test_string("^v", 3);
	runner.add_test_string("^>v<", 3);
	runner.add_test_string("^v^v^v^v^v", 11);

	runner.add_input_file("i1.txt");

	runner.run();
}