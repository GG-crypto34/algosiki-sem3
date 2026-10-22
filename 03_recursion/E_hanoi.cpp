#include <iostream>

void transfer_disks(int count, int source, int destination, int spare) {
    if (count == 0) return;
    transfer_disks(count - 1, source, spare, destination);
    std::cout << count << ' ' << source << ' ' << destination << '\n';
    transfer_disks(count - 1, spare, destination, source);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int count;
    if (!(std::cin >> count)) return 0;
    std::cout << ((1ULL << count) - 1) << '\n';
    transfer_disks(count, 1, 3, 2);
}
