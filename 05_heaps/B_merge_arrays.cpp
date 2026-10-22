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

    bool empty() const { return items_.empty(); }

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

struct Cursor {
    long long value;
    std::size_t array;
    std::size_t position;
};

struct SmallerValue {
    bool operator()(const Cursor& left, const Cursor& right) const {
        return left.value < right.value;
    }
};

void print_merged(const std::vector<std::vector<long long>>& arrays) {
    std::vector<Cursor> first_items;
    for (std::size_t index = 0; index < arrays.size(); ++index) {
        if (!arrays[index].empty()) first_items.push_back({arrays[index][0], index, 0});
    }
    BinaryHeap<Cursor, SmallerValue> pending(std::move(first_items));
    while (!pending.empty()) {
        Cursor current = pending.pop();
        std::cout << current.value << ' ';
        ++current.position;
        if (current.position < arrays[current.array].size()) {
            current.value = arrays[current.array][current.position];
            pending.push(current);
        }
    }
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int count;
    if (!(std::cin >> count)) return 0;
    std::vector<std::vector<long long>> arrays(count);
    for (auto& array : arrays) {
        int size;
        std::cin >> size;
        array.resize(size);
        for (auto& value : array) std::cin >> value;
    }
    print_merged(arrays);
}
