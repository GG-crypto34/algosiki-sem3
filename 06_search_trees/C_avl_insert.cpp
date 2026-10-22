#include <algorithm>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

class AvlTree {
    struct Vertex {
        int key;
        int height = 1;
        Vertex* left = nullptr;
        Vertex* right = nullptr;
        explicit Vertex(int value) : key(value) {}
    };
    Vertex* root_ = nullptr;

    static int height_of(const Vertex* vertex) { return vertex ? vertex->height : 0; }

    static void refresh(Vertex* vertex) {
        vertex->height = 1 + std::max(height_of(vertex->left), height_of(vertex->right));
    }

    static int balance_factor(const Vertex* vertex) {
        return height_of(vertex->right) - height_of(vertex->left);
    }

    static Vertex* rotate_left(Vertex* pivot) {
        Vertex* promoted = pivot->right;
        pivot->right = promoted->left;
        promoted->left = pivot;
        refresh(pivot);
        refresh(promoted);
        return promoted;
    }

    static Vertex* rotate_right(Vertex* pivot) {
        Vertex* promoted = pivot->left;
        pivot->left = promoted->right;
        promoted->right = pivot;
        refresh(pivot);
        refresh(promoted);
        return promoted;
    }

    static Vertex* rebalance(Vertex* vertex) {
        refresh(vertex);
        if (balance_factor(vertex) > 1) {
            if (balance_factor(vertex->right) < 0) vertex->right = rotate_right(vertex->right);
            return rotate_left(vertex);
        }
        if (balance_factor(vertex) < -1) {
            if (balance_factor(vertex->left) > 0) vertex->left = rotate_left(vertex->left);
            return rotate_right(vertex);
        }
        return vertex;
    }

    static Vertex* insert_into(Vertex* vertex, int key) {
        if (!vertex) return new Vertex(key);
        if (key == vertex->key) return vertex;
        if (key < vertex->key) vertex->left = insert_into(vertex->left, key);
        else vertex->right = insert_into(vertex->right, key);
        return rebalance(vertex);
    }

public:
    AvlTree() = default;
    AvlTree(const AvlTree&) = delete;
    AvlTree& operator=(const AvlTree&) = delete;

    ~AvlTree() {
        std::vector<Vertex*> pending;
        if (root_) pending.push_back(root_);
        while (!pending.empty()) {
            Vertex* vertex = pending.back();
            pending.pop_back();
            if (vertex->left) pending.push_back(vertex->left);
            if (vertex->right) pending.push_back(vertex->right);
            delete vertex;
        }
    }

    void insert(int key) { root_ = insert_into(root_, key); }
    int height() const { return height_of(root_); }
    std::optional<int> root() const {
        return root_ ? std::optional<int>(root_->key) : std::nullopt;
    }

    bool contains(int key) const {
        const Vertex* vertex = root_;
        while (vertex && vertex->key != key) {
            vertex = key < vertex->key ? vertex->left : vertex->right;
        }
        return vertex != nullptr;
    }

    void print() const {
        if (!root_) {
            std::cout << "Empty\n";
            return;
        }
        std::vector<const Vertex*> pending{root_};
        while (!pending.empty()) {
            const Vertex* vertex = pending.back();
            pending.pop_back();
            std::cout << vertex->key << ' ';
            if (vertex->right) pending.push_back(vertex->right);
            if (vertex->left) pending.push_back(vertex->left);
        }
        std::cout << '\n';
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    AvlTree tree;
    int requests;
    if (!(std::cin >> requests)) return 0;
    for (int request = 0; request < requests; ++request) {
        std::string command;
        std::cin >> command;
        if (command == "height") std::cout << tree.height() << '\n';
        else if (command == "print") tree.print();
        else if (command == "root") {
            auto key = tree.root();
            if (key) std::cout << *key << '\n';
            else std::cout << "Empty\n";
        }
        else {
            int key;
            std::cin >> key;
            if (command == "add") tree.insert(key);
            else if (command == "exists") std::cout << (tree.contains(key) ? "YES" : "NO") << '\n';
        }
    }
}
