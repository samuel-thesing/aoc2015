#include <iostream>

#include <io_utils.h>
#include <utils.h>
#include <Logger.h>
#include <set>

#define YEAR "2015"
#define DAY "03"

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
	Logger::init();
	std::cout << "Advent of Code " << YEAR << " Day " << DAY << std::endl
		<< "-------------------------------------------------------------" << std::endl;

	std::string input = read_file("i1.txt");
	auto result = solve(input);
	std::cout << result << std::endl;
}