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

    static Vertex* erase_from(Vertex* vertex, int key) {
        if (!vertex) return nullptr;
        if (key < vertex->key) vertex->left = erase_from(vertex->left, key);
        else if (key > vertex->key) vertex->right = erase_from(vertex->right, key);
        else {
            if (!vertex->left || !vertex->right) {
                Vertex* child = vertex->left ? vertex->left : vertex->right;
                delete vertex;
                return child;
            }
            Vertex* successor = vertex->right;
            while (successor->left) successor = successor->left;
            vertex->key = successor->key;
            vertex->right = erase_from(vertex->right, successor->key);
        }
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
    void erase(int key) { root_ = erase_from(root_, key); }
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

    std::optional<int> ceiling(int key) const {
        const Vertex* vertex = root_;
        std::optional<int> candidate;
        while (vertex) {
            if (vertex->key >= key) {
                candidate = vertex->key;
                vertex = vertex->left;
            } else vertex = vertex->right;
        }
        return candidate;
    }

    std::optional<int> floor(int key) const {
        const Vertex* vertex = root_;
        std::optional<int> candidate;
        while (vertex) {
            if (vertex->key <= key) {
                candidate = vertex->key;
                vertex = vertex->right;
            } else vertex = vertex->left;
        }
        return candidate;
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

void print_optional(std::optional<int> result, const char* missing) {
    if (result) std::cout << *result << '\n';
    else std::cout << missing << '\n';
}

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
        else if (command == "root") print_optional(tree.root(), "Empty");
        else {
            int key;
            std::cin >> key;
            if (command == "add") tree.insert(key);
            else if (command == "del") tree.erase(key);
            else if (command == "exists") std::cout << (tree.contains(key) ? "YES" : "NO") << '\n';
            else if (command == "next") print_optional(tree.ceiling(key), "None");
            else if (command == "prev") print_optional(tree.floor(key), "None");
        }
    }
}
