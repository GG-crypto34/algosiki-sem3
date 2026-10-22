#include <algorithm>
#include <iostream>
#include <vector>

long long count_inversions(std::vector<long long>& values, std::vector<long long>& buffer,
                           std::size_t begin, std::size_t end) {
    if (end - begin < 2) return 0;
    std::size_t middle = begin + (end - begin) / 2;
    long long inversions = count_inversions(values, buffer, begin, middle);
    inversions += count_inversions(values, buffer, middle, end);
    std::size_t left = begin, right = middle, output = begin;
    while (left < middle && right < end) {
        if (values[left] <= values[right]) {
            buffer[output++] = values[left++];
        } else {
            inversions += static_cast<long long>(middle - left);
            buffer[output++] = values[right++];
        }
    }
    while (left < middle) buffer[output++] = values[left++];
    while (right < end) buffer[output++] = values[right++];
    std::copy(buffer.begin() + begin, buffer.begin() + end, values.begin() + begin);
    return inversions;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int count;
    if (!(std::cin >> count)) return 0;
    std::vector<long long> values(count);
    for (auto& value : values) std::cin >> value;
    std::vector<long long> buffer(count);
    std::cout << count_inversions(values, buffer, 0, values.size()) << '\n';
}
