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
	points.insert(p);
  	for (char c : input) {
  		switch (c) {
  			case 'v': p.y++; break;
  			case '^': p.y--; break;
  			case '<': p.x++; break;
  			case '>': p.x--; break;
  			default: break;
  		}
  		points.insert(p);
  	}

	return points.size();
}

int main(int argc, char** argv) {
	auto runner = Runner<int>(solve, 2015, 03);
	runner.add_test_string(">", 2);
	runner.add_test_string("^>v<", 4);
	runner.add_test_string("^v^v^v^v^v", 2);

	runner.add_input_file("i1.txt");

	runner.run();
}