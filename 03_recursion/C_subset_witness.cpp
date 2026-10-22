#include <algorithm>
#include <iostream>
#include <vector>

struct SubsetSum {
    long long total;
    unsigned mask;
};

std::vector<SubsetSum> subset_sums(const std::vector<long long>& values, int begin, int end) {
    std::vector<SubsetSum> sums{{0, 0}};
    for (int index = begin; index < end; ++index) {
        std::size_t previous_size = sums.size();
        for (std::size_t entry = 0; entry < previous_size; ++entry) {
            auto partial = sums[entry];
            sums.push_back({partial.total + values[index], partial.mask | (1u << (index - begin))});
        }
    }
    return sums;
}

void append_values(std::vector<long long>& answer, const std::vector<long long>& values,
                   unsigned mask, int begin, int end) {
    for (int index = begin; index < end; ++index) {
        if (mask & (1u << (index - begin))) answer.push_back(values[index]);
    }
}

bool find_subset(const std::vector<long long>& values, long long target,
                 std::vector<long long>& answer) {
    int middle = values.size() / 2;
    auto left = subset_sums(values, 0, middle);
    auto right = subset_sums(values, middle, values.size());
    std::sort(right.begin(), right.end(), [](const auto& first, const auto& second) {
        if (first.total != second.total) return first.total < second.total;
        return first.mask > second.mask;
    });
    for (const auto& partial : left) {
        long long remaining = target - partial.total;
        auto match = std::lower_bound(right.begin(), right.end(), remaining,
            [](const SubsetSum& entry, long long total) { return entry.total < total; });
        if (match == right.end() || match->total != remaining) continue;
        if (partial.mask == 0 && match->mask == 0) continue;
        answer.clear();
        append_values(answer, values, partial.mask, 0, middle);
        append_values(answer, values, match->mask, middle, values.size());
        return true;
    }
    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int count;
    if (!(std::cin >> count)) return 0;
    std::vector<long long> values(count);
    for (auto& value : values) std::cin >> value;
    long long target;
    std::cin >> target;
    std::vector<long long> answer;
    bool found = find_subset(values, target, answer);
    std::cout << (found ? "Yes" : "No") << '\n';
    if (found) {
        std::cout << answer.size() << '\n';
        for (long long value : answer) std::cout << value << ' ';
        std::cout << '\n';
    }
}
