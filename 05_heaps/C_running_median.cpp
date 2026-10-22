#include <functional>
#include <iostream>
#include <string>
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
    BinaryHeap() = default;

    std::size_t size() const { return items_.size(); }
    bool empty() const { return items_.empty(); }
    const Value& top() const { return items_.front(); }

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

class RunningMedian {
    BinaryHeap<long long, std::greater<long long>> lower_;
    BinaryHeap<long long> upper_;

public:
    void add(long long value) {
        if (lower_.empty() || value <= lower_.top()) lower_.push(value);
        else upper_.push(value);
        if (lower_.size() > upper_.size() + 1) upper_.push(lower_.pop());
        else if (upper_.size() > lower_.size()) lower_.push(upper_.pop());
    }

    long long median() const { return lower_.top(); }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    RunningMedian values;
    int requests;
    if (!(std::cin >> requests)) return 0;
    for (int request = 0; request < requests; ++request) {
        std::string command;
        std::cin >> command;
        if (command == "ADD") {
            long long value;
            std::cin >> value;
            values.add(value);
        } else if (command == "FIND_MEDIAN") {
            std::cout << values.median() << '\n';
        }
    }
}
