//
// Created by hungr on 2020/03/08.
//

#include <algorithm>
#include <numeric>
#include <chrono>
#include <vector>
#include <memory>
#include <random>
#include "answer.h"

using std::chrono::system_clock;

static void set_template(std::array<int, 81>& ary);
static void init_firstline(std::array<int, 81>& ary, std::mt19937& mt);
static void init_secondline(std::array<int, 81>& ary, std::mt19937& mt);
static void init_thirdline(std::array<int, 81>& ary, std::mt19937& mt);
static bool fill_all(std::array<int, 81>& ary, std::mt19937& mt);

std::array<int, 81> create_answer() {
    std::array<int, 81> answer{};
    answer.fill(0);
    set_template(answer);

    return answer;
}

std::set<int> valid_numbers(std::array<int, 81>& ary, int x, int y) {
    std::set<int> valids = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    for(int i = 0; i < 9; i++) {
        if(ary[i + y * 9]) valids.erase(ary[i + y * 9]);
        if(ary[x + i * 9]) valids.erase(ary[x + i * 9]);
        int _x = i % 3, _y = i / 3;
        if(ary[_x + x / 3 * 3 + (_y + y / 3 * 3) * 9]) valids.erase(ary[_x + x / 3 * 3 + (_y + y / 3 * 3) * 9]);
    }
    return valids;
}

void set_template(std::array<int, 81>& ary) {
    system_clock::time_point p = system_clock::now();
    std::mt19937 mt(system_clock::to_time_t(p));

    init_firstline(ary, mt);
    init_secondline(ary, mt);
    init_thirdline(ary, mt);
    fill_all(ary, mt);
}

void init_firstline(std::array<int, 81>& ary, std::mt19937& mt) {
    std::iota(ary.begin(), ary.begin() + 9, 1);
    std::shuffle(ary.begin(), ary.begin() + 9, mt);
}

void init_secondline(std::array<int, 81>& ary, std::mt19937& mt) {
    std::array<int, 6> target{}; std::copy(ary.begin() + 3, ary.begin() + 9, target.begin());
    std::shuffle(target.begin(), target.end(), mt);
    std::copy(target.begin(), target.begin() + 3, ary.begin() + 9);
    std::vector<int> use;
    for(int i = 0; i < 3; i++) {
        if(std::count(ary.begin() + 9, ary.begin() + 12, ary[i + 6]) == 0) {
            use.push_back(ary[i + 6]);
        }
    }
    int cur = use.size();
    std::set<int> unuse = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::for_each(ary.begin() + 3, ary.begin() + 12, [&unuse](auto a) { unuse.erase(a); });
    std::for_each(unuse.begin(), unuse.end(), [&use](auto a) { use.push_back(a); });
    std::shuffle(use.begin() + cur, use.end(), mt);
    std::copy(use.begin(), use.begin() + 3, ary.begin() + 12);
    for(auto a : { 1, 2, 3, 4, 5, 6, 7, 8, 9 }) unuse.insert(a);
    std::for_each(ary.begin() + 9, ary.begin() + 15, [&unuse](auto a) { unuse.erase(a); });
    std::copy(unuse.begin(), unuse.end(), ary.begin() + 15);
    std::shuffle(ary.begin() + 15, ary.begin() + 18, mt);
}

void init_thirdline(std::array<int, 81>& ary, std::mt19937& mt) {
    for(int i = 0; i < 3; i++) {
        std::set<int> unuse = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::for_each(ary.begin() + i * 3, ary.begin() + i * 3 + 3, [&unuse](auto a) { unuse.erase(a); });
        std::for_each(ary.begin() + i * 3 + 9, ary.begin() + i * 3 + 12, [&unuse](auto a) { unuse.erase(a); });
        std::copy(unuse.begin(), unuse.end(), ary.begin() + i * 3 + 18);
        std::shuffle(ary.begin() + i * 3 + 18, ary.begin() + i * 3 + 21, mt);
    }
}

bool fill_all(std::array<int, 81>& ary, std::mt19937& mt) {
    int index = std::distance(ary.begin(), std::find(ary.begin(), ary.end(), 0));
    if(index >= 81) return true;
    int x = index % 9, y = index / 9;
    auto valids = valid_numbers(ary, x, y);
    if(valids.empty()) return false;
    std::vector<int> nums; nums.reserve(valids.size());
    for(auto v : valids) nums.push_back(v);
    while(!nums.empty()) {
        int r = mt() % (nums.size());
        ary[index] = nums[r];
        nums.erase(nums.begin() + r);
        if(fill_all(ary, mt)) return true;
    }
    ary[index] = 0;
    return false;
}