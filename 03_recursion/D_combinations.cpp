#include <algorithm>
#include <iostream>
#include <vector>

unsigned long long combination_count(int size, int chosen) {
    chosen = std::min(chosen, size - chosen);
    unsigned long long result = 1;
    for (int index = 1; index <= chosen; ++index) {
        result = result * (size - chosen + index) / index;
    }
    return result;
}

void print_combinations(int size, int remaining, int first, std::vector<int>& prefix) {
    if (remaining == 0) {
        for (int value : prefix) std::cout << value << ' ';
        std::cout << '\n';
        return;
    }
    for (int value = first; value <= size - remaining + 1; ++value) {
        prefix.push_back(value);
        print_combinations(size, remaining - 1, value + 1, prefix);
        prefix.pop_back();
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int size, chosen;
    if (!(std::cin >> size >> chosen)) return 0;
    std::cout << combination_count(size, chosen) << '\n';
    std::vector<int> prefix;
    print_combinations(size, chosen, 1, prefix);
}
