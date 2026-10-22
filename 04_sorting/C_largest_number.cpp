#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

bool comes_before(const std::string& left, const std::string& right) {
    for (std::size_t index = 0; index < left.size() + right.size(); ++index) {
        char first = index < left.size() ? left[index] : right[index - left.size()];
        char second = index < right.size() ? right[index] : left[index - right.size()];
        if (first != second) return first > second;
    }
    return false;
}

void print_largest_number(std::vector<std::string>& parts) {
    std::sort(parts.begin(), parts.end(), comes_before);
    bool all_zero = true;
    for (const auto& part : parts) {
        if (part.find_first_not_of('0') != std::string::npos) all_zero = false;
    }
    if (all_zero) {
        std::cout << "0\n";
        return;
    }
    for (const auto& part : parts) std::cout << part;
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int count;
    if (!(std::cin >> count)) return 0;
    std::vector<std::string> parts(count);
    for (auto& part : parts) std::cin >> part;
    print_largest_number(parts);
}
