#include <iostream>
#include <vector>

class QueensSearch {
    int size_;
    std::vector<int> placement_;
    std::vector<bool> columns_, rising_, falling_;
    unsigned long long solutions_ = 0;

    void visit(int row, bool emit) {
        if (row == size_) {
            if (emit) {
                for (int column : placement_) std::cout << column + 1 << ' ';
                std::cout << '\n';
            } else {
                ++solutions_;
            }
            return;
        }
        for (int column = 0; column < size_; ++column) {
            int ascending = row + column;
            int descending = row - column + size_;
            if (columns_[column] || rising_[ascending] || falling_[descending]) continue;
            columns_[column] = rising_[ascending] = falling_[descending] = true;
            placement_[row] = column;
            visit(row + 1, emit);
            columns_[column] = rising_[ascending] = falling_[descending] = false;
        }
    }

public:
    explicit QueensSearch(int size)
        : size_(size), placement_(size), columns_(size), rising_(2 * size + 1),
          falling_(2 * size + 1) {}

    void print_solutions() {
        solutions_ = 0;
        visit(0, false);
        std::cout << solutions_ << '\n';
        visit(0, true);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int size;
    if (std::cin >> size) QueensSearch(size).print_solutions();
}
