#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Participant {
    std::string login;
    long long solved;
    long long penalty;
};

bool ranks_before(const Participant& left, const Participant& right) {
    if (left.solved != right.solved) return left.solved > right.solved;
    if (left.penalty != right.penalty) return left.penalty < right.penalty;
    return left.login < right.login;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int count;
    if (!(std::cin >> count)) return 0;
    std::vector<Participant> participants(count);
    for (auto& participant : participants) {
        std::cin >> participant.login >> participant.solved >> participant.penalty;
    }
    std::sort(participants.begin(), participants.end(), ranks_before);
    for (const auto& participant : participants) std::cout << participant.login << '\n';
}
