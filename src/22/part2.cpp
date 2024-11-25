#include <utils.h>

struct Player {
	int hp;
	int mana;
};

struct Enemy {
	int hp;
	int attack;
};

std::vector spellcosts = {53, 73, 113, 173, 229};
std::vector cooldownStats = {0, 0, 6, 6, 5};

void spellTicks(std::vector<int>& cooldowns, Player& player, Enemy& enemy) {
	for (int i = 2; i < cooldowns.size(); i++) {
		if (cooldowns[i] <= 0) continue;
		cooldowns[i]--;
		switch (i) {
			case 2: break;
			case 3:
				enemy.hp -= 3;
			break;
			case 4:
				player.mana += 101;
			break;
			default:
				Logger::critical("Unknown Spell Type");
			return;
		}
	}
}

void castSpell(int spell, Player& player, Enemy& enemy) {
	switch (spell) {
		case 0:
			enemy.hp -= 4;
		return;
		case 1:
			player.hp += 2;
		enemy.hp -= 2;
		return;
		case 2:
		case 3:
		case 4:
			return;

		default:
			Logger::critical("Unknown Spell Type");
	}
}

int playerTurn(Player player, Enemy enemy, std::vector<int> cooldowns, int manaSpent) {
	player.hp--;
	if (player.hp <= 0) {
		return std::numeric_limits<int>::max();
	}

	spellTicks(cooldowns, player, enemy);

	if (enemy.hp <= 0) {
		return manaSpent;
	}

	int min_mana = std::numeric_limits<int>::max();

	for (int i = 4; i >= 0 ; i--) {
		if (cooldowns[i] != 0 || spellcosts[i] > player.mana)
			continue;

		Player player2 = player;
		Enemy enemy2 = enemy;
		std::vector<int> cooldowns2 = cooldowns;

		castSpell(i, player2, enemy2);
		player2.mana -= spellcosts[i];

		cooldowns2[i] = cooldownStats[i];

		// boss turn
		spellTicks(cooldowns2, player2, enemy2);

		if (enemy2.hp <= 0) {
			min_mana = min(min_mana, manaSpent + spellcosts[i]);
			continue;
		}

		player2.hp -= max(1, enemy2.attack - (cooldowns2[2] ? 7 : 0));

		min_mana = min(min_mana, playerTurn(player2, enemy2, cooldowns2, manaSpent + spellcosts[i]));
		cooldowns2[i] = 0;
	}
	return min_mana;
}

int solve(const std::string &input, const Player& player) {
	std::regex pattern("Hit Points: (\\d+)\nDamage: (\\d+)");
	const auto [hp, damage] = extract_data<int, int>(pattern, input);

	Enemy enemy = {hp, damage};

	return playerTurn(player, enemy, std::vector(5, 0), 0);
}

int main(int argc, char** argv) {
    auto runner = Runner<int, Player>(solve, 2015, 22);

    runner.add_input_file("i1.txt", {50, 500});

    runner.run();
}