#include <algorithm>
#include <iostream>
#include <vector>

struct SubsetSum {
    long long total;
    bool nonempty;
};

std::vector<SubsetSum> subset_sums(const std::vector<long long>& values, int begin, int end) {
    std::vector<SubsetSum> sums{{0, false}};
    for (int index = begin; index < end; ++index) {
        std::size_t previous_size = sums.size();
        for (std::size_t entry = 0; entry < previous_size; ++entry) {
            long long total = sums[entry].total + values[index];
            sums.push_back({total, true});
        }
    }
    return sums;
}

bool has_subset(const std::vector<long long>& values, long long target) {
    int middle = values.size() / 2;
    auto left = subset_sums(values, 0, middle);
    auto right = subset_sums(values, middle, values.size());
    std::sort(right.begin(), right.end(), [](const auto& first, const auto& second) {
        if (first.total != second.total) return first.total < second.total;
        // A nonempty zero-sum subset must precede the empty subset.
        return first.nonempty > second.nonempty;
    });
    for (const auto& partial : left) {
        long long remaining = target - partial.total;
        auto match = std::lower_bound(right.begin(), right.end(), remaining,
            [](const SubsetSum& entry, long long total) { return entry.total < total; });
        if (match != right.end() && match->total == remaining
            && (partial.nonempty || match->nonempty)) return true;
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
    std::cout << (has_subset(values, target) ? "Yes" : "No") << '\n';
}
