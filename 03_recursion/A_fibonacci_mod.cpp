#include <iostream>
#include <utility>

std::pair<long long, long long> fibonacci_pair(int index, long long modulus) {
    if (index == 0) return {0, 1 % modulus};
    auto [current, following] = fibonacci_pair(index / 2, modulus);

    // F(2k) = F(k) * (2F(k+1) - F(k)); F(2k+1) = F(k)^2 + F(k+1)^2.
    // With modulus <= 10^9, every intermediate product fits in long long.
    long long even = current * ((2 * following - current + modulus) % modulus) % modulus;
    long long odd = (current * current + following * following) % modulus;
    return index % 2 ? std::make_pair(odd, (even + odd) % modulus)
                     : std::make_pair(even, odd);
}

int main() {
    int index;
    long long modulus;
    if (!(std::cin >> index >> modulus)) return 0;
    std::cout << fibonacci_pair(index, modulus).second << '\n';
}
