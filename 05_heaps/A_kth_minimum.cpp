#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

class OrderStatistic {
    std::vector<long long> values_;

    void sort_small(std::size_t begin, std::size_t end) {
        for (std::size_t index = begin + 1; index < end; ++index) {
            long long value = values_[index];
            std::size_t position = index;
            while (position > begin && values_[position - 1] > value) {
                values_[position] = values_[position - 1];
                --position;
            }
            values_[position] = value;
        }
    }

    long long select(std::size_t begin, std::size_t end, std::size_t rank) {
        while (end - begin > 5) {
            std::size_t groups = 0;
            for (std::size_t first = begin; first < end; first += 5) {
                std::size_t last = std::min(first + 5, end);
                sort_small(first, last);
                std::size_t median = first + (last - first) / 2;
                std::swap(values_[begin + groups], values_[median]);
                ++groups;
            }
            long long pivot = select(begin, begin + groups, begin + groups / 2);
            std::size_t less = begin, current = begin, greater = end;
            while (current < greater) {
                if (values_[current] < pivot) std::swap(values_[less++], values_[current++]);
                else if (values_[current] > pivot) std::swap(values_[current], values_[--greater]);
                else ++current;
            }
            if (rank < less) end = less;
            else if (rank >= greater) begin = greater;
            else return pivot;
        }
        sort_small(begin, end);
        return values_[rank];
    }

public:
    explicit OrderStatistic(std::vector<long long> values) : values_(std::move(values)) {}

    long long kth(std::size_t rank) { return select(0, values_.size(), rank - 1); }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int count, rank;
    if (!(std::cin >> count >> rank)) return 0;
    std::vector<long long> values(count);
    for (auto& value : values) std::cin >> value;
    std::cout << OrderStatistic(std::move(values)).kth(rank) << '\n';
}
