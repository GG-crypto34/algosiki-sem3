#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

struct IndexedValue {
    long long value;
    int position;
};

std::pair<int, int> find_pair(std::vector<IndexedValue>& values, long long target) {
    std::sort(values.begin(), values.end(), [](const auto& left, const auto& right) {
        if (left.value != right.value) return left.value < right.value;
        return left.position < right.position;
    });
    int left = 0, right = static_cast<int>(values.size()) - 1;
    while (left < right) {
        long long sum = values[left].value + values[right].value;
        if (sum == target) {
            return std::minmax(values[left].position, values[right].position);
        }
        if (sum < target) ++left;
        else --right;
    }
    return {-1, -1};
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int count;
    if (!(std::cin >> count)) return 0;
    std::vector<IndexedValue> values(count);
    for (int index = 0; index < count; ++index) {
        std::cin >> values[index].value;
        values[index].position = index + 1;
    }
    long long target;
    std::cin >> target;
    auto [first, second] = find_pair(values, target);
    std::cout << first;
    if (first != -1) std::cout << ' ' << second;
    std::cout << '\n';
}
