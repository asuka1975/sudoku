#include <algorithm>
#include <numeric>
#include <map>
#include <vector>
#include <random>
#include <chrono>
#include "answer.h"
#include "question.h"

using std::chrono::system_clock;

static bool can_remove(std::array<int, 81> question, int x, int y);
static int count_answer(std::array<int, 81>& question);

std::array<int, 81> create_question(std::array<int, 81> answer) {
	system_clock::time_point p = system_clock::now();
	std::mt19937 mt(system_clock::to_time_t(p));
	std::vector<int> indexes(81); std::iota(indexes.begin(), indexes.end(), 0);
	for(int i = 0; i < 81; i++) {
		int index = indexes[mt() % indexes.size()];
		int x = index % 9, y = index / 9;
		if(can_remove(answer, x, y)) {
			answer[x + y * 9] = 0;
		}
		indexes.erase(std::find(indexes.begin(), indexes.end(), index));
	}
	
	return answer;
}

static bool can_remove(std::array<int, 81> question, int x, int y) {
	question[x + y * 9] = 0;
	return count_answer(question) == 1;
}

static int count_answer(std::array<int, 81>& question) {
	int index = std::distance(question.begin(), std::find(question.begin(), question.end(), 0));
	if(index >= 81) return 1;
	int x = index % 9, y = index / 9;
	auto valids = valid_numbers(question, x, y);
	if(valids.empty()) return 0;
	int count = 0;
	for(auto v : valids) {
		question[x + y * 9] = v;
		count += count_answer(question);
		question[x + y * 9] = 0;
		if(count > 1) return count;
	}
	return count;
}