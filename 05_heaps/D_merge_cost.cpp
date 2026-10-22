#include <functional>
#include <iostream>
#include <utility>
#include <vector>

template <class Value, class Before = std::less<Value>>
class BinaryHeap {
    std::vector<Value> items_;
    Before before_;

    void sift_down(std::size_t parent) {
        while (2 * parent + 1 < items_.size()) {
            std::size_t child = 2 * parent + 1;
            if (child + 1 < items_.size() && before_(items_[child + 1], items_[child])) ++child;
            if (!before_(items_[child], items_[parent])) break;
            std::swap(items_[parent], items_[child]);
            parent = child;
        }
    }

public:
    explicit BinaryHeap(std::vector<Value> values) : items_(std::move(values)) {
        for (std::size_t parent = items_.size() / 2; parent > 0; --parent) sift_down(parent - 1);
    }

    std::size_t size() const { return items_.size(); }

    void push(Value value) {
        items_.push_back(std::move(value));
        std::size_t child = items_.size() - 1;
        while (child > 0) {
            std::size_t parent = (child - 1) / 2;
            if (!before_(items_[child], items_[parent])) break;
            std::swap(items_[child], items_[parent]);
            child = parent;
        }
    }

    Value pop() {
        Value answer = items_.front();
        items_.front() = std::move(items_.back());
        items_.pop_back();
        if (!items_.empty()) sift_down(0);
        return answer;
    }
};

long long minimum_merge_cost(std::vector<long long> sizes) {
    BinaryHeap<long long> files(std::move(sizes));
    long long total = 0;
    while (files.size() > 1) {
        long long first = files.pop();
        long long merged = first + files.pop();
        total += merged;
        files.push(merged);
    }
    return total;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int count;
    if (!(std::cin >> count)) return 0;
    std::vector<long long> sizes(count);
    for (auto& size : sizes) std::cin >> size;
    std::cout << minimum_merge_cost(std::move(sizes)) << '\n';
}
