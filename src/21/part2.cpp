#include <utils.h>

struct Item {
	std::string name;
	int cost;
	int damage;
	int armor;
};

struct Stats {
	int hp;
	int damage;
	int armor;
};

typedef std::array<std::vector<Item>, 3> Shop;

Shop read_shop(std::string s) {
	std::vector<std::string> types = split(s, "\n\n");
	assert(types.size() == 3);
	const auto pattern = std::regex(R"((.+)\s+(\d+)\s+(\d+)\s+(\d+))");
	Shop shop{};
	for (int j = 0; j < types.size(); ++j) {
		auto lines = split(types[j], "\n");
		shop[j] = std::vector<Item>();
		for (int i = 1; i < lines.size(); i++) {
			const auto [name, cost, damage, armor] = extract_data<std::string, int, int, int>(pattern, lines[i]);
			shop[j].emplace_back(name, cost, damage, armor);
		}
	}

	return shop;
}

typedef std::vector<std::pair<int, int>> Constraints;

bool is_win(const Stats& boss, int damage, int armor) {
	int boss_hp = boss.hp;
	int player_hp = 100;
	while (true) {
		boss_hp -= max(1, damage - boss.armor);
		if (boss_hp <= 0) {
			return true;
		}
		player_hp -= max(1, boss.damage - armor);
		if (player_hp <= 0) {
			return false;
		}
	}
}

int search(const Shop& shop, const Constraints& constraints, const Stats& boss, Stats player, int typeIdx = 0, int cost = 0, int currentCount = 0, int currentIdx = 0) {
	if (typeIdx >= shop.size()) {
		return !is_win(boss, player.damage, player.armor) ? cost : 0;
	}

	int max_cost = 0;

	if (currentCount >= constraints[typeIdx].first) { // minimum of type reached
		max_cost = max(max_cost, search(shop, constraints, boss, player, typeIdx+1, cost));
	}

	if (currentCount >= constraints[typeIdx].second) { // already searching next type because minimum was reached
		return max_cost;
	}

	// not maximum for type reached
	for (int i = currentIdx; i < shop[typeIdx].size(); ++i) {
		const auto& item = shop[typeIdx][i];
		Stats player_upgraded = {player.hp, player.damage + item.damage, player.armor + item.armor};
		max_cost = max(max_cost, search(shop, constraints, boss, player_upgraded, typeIdx, cost + item.cost, currentCount+1, i+1));
	}
	return max_cost;
}

int solve(const std::string &input) {
	Shop shop = read_shop(read_file("shop.txt"));

	std::regex pattern("Hit Points: (\\d+)\nDamage: (\\d+)\nArmor: (\\d+)");
	const auto [hp, damage, armor] = extract_data<int, int, int>(pattern, input);

	Constraints constraints{ // minimum, maximum
		{1, 1},
		{0, 1},
		{0, 2}
	};

	auto result = search(shop, constraints, {hp, damage, armor}, {100, 0, 0});

	return result;
}

int main(int argc, char** argv) {
    auto runner = Runner<int>(solve, 2015, 21);

    runner.add_input_file("i1.txt");

    runner.run();
}