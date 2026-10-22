#include <iostream>
#include <utility>
#include <vector>

class SpanCalculator {
    std::vector<std::pair<int, int>> decreasing_;
    int position_ = 0;

public:
    int append(int price) {
        while (!decreasing_.empty() && decreasing_.back().second <= price) {
            decreasing_.pop_back();
        }
        int previous = decreasing_.empty() ? -1 : decreasing_.back().first;
        int span = position_ - previous;
        decreasing_.push_back({position_++, price});
        return span;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    SpanCalculator spans;
    int price;
    while (std::cin >> price) std::cout << spans.append(price) << ' ';
    std::cout << '\n';
}
