#include <utils.h>

bool check_pwd(const std::string& pwd) {
	if (pwd.find_first_of("iol") != std::string::npos) return false;

	int double_count = 0;
	for (int i = 0; i < pwd.size()-1; i++) {
		if (pwd[i] == pwd[i+1]) {
			double_count++;
			i++;
		}
	}
	if (double_count < 2) return false;

	for (int i = 0; i < pwd.size()-2; i++) {
		if (pwd[i+1] == pwd[i]+1 && pwd[i+2] == pwd[i]+2)
			return true;
	}
	return false;
}

std::string solve(const std::string &input) {
	std::string pwd = input;
	do {
		for (int i = pwd.size()-1; i >= 0; i--) {
			if (pwd[i] == 'z') {
				pwd[i] = 'a';
			} else {
				pwd[i]++;
				break;
			}
		}
	} while (!check_pwd(pwd));

	return pwd;
}

int main(int argc, char** argv) {
	auto runner = Runner<std::string>(solve, 2015, 11);

	runner.add_test_string("abcdefgh", "abcdffaa");
	runner.add_test_string("ghijklmn", "ghjaabcc");

	runner.add_input_file("i1.txt");

	runner.run();
}