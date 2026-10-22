#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

long long covered_count(std::vector<std::pair<long long, long long>>& intervals) {
    if (intervals.empty()) return 0;
    std::sort(intervals.begin(), intervals.end());
    auto [begin, end] = intervals.front();
    long long covered = 0;
    for (std::size_t index = 1; index < intervals.size(); ++index) {
        auto [next_begin, next_end] = intervals[index];
        if (next_begin <= end + 1) end = std::max(end, next_end);
        else {
            covered += end - begin + 1;
            begin = next_begin;
            end = next_end;
        }
    }
    return covered + end - begin + 1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    long long stalls;
    int count;
    if (!(std::cin >> stalls >> count)) return 0;
    std::vector<std::pair<long long, long long>> intervals(count);
    for (auto& interval : intervals) std::cin >> interval.first >> interval.second;
    std::cout << stalls - covered_count(intervals) << '\n';
}
