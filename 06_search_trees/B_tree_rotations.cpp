#include <iostream>
#include <string>
#include <vector>

class SearchTree {
    struct Vertex {
        int key;
        Vertex* left = nullptr;
        Vertex* right = nullptr;
        explicit Vertex(int value) : key(value) {}
    };
    Vertex* root_ = nullptr;

public:
    SearchTree() = default;
    SearchTree(const SearchTree&) = delete;
    SearchTree& operator=(const SearchTree&) = delete;

    ~SearchTree() {
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

    void insert(int key) {
        Vertex** link = &root_;
        while (*link) {
            if ((*link)->key == key) return;
            link = key < (*link)->key ? &(*link)->left : &(*link)->right;
        }
        *link = new Vertex(key);
    }

    void rotate(int key, bool left) {
        Vertex** link = &root_;
        while (*link && (*link)->key != key) {
            link = key < (*link)->key ? &(*link)->left : &(*link)->right;
        }
        if (!*link) return;
        Vertex* pivot = *link;
        Vertex* promoted = left ? pivot->right : pivot->left;
        if (!promoted) return;
        if (left) {
            pivot->right = promoted->left;
            promoted->left = pivot;
        } else {
            pivot->left = promoted->right;
            promoted->right = pivot;
        }
        *link = promoted;
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
    SearchTree tree;
    int count;
    if (!(std::cin >> count)) return 0;
    for (int index = 0; index < count; ++index) {
        int key;
        std::cin >> key;
        tree.insert(key);
    }
    int requests;
    std::cin >> requests;
    for (int request = 0; request < requests; ++request) {
        std::string command;
        std::cin >> command;
        int key;
        std::cin >> key;
        tree.rotate(key, command == "left");
        tree.print();
    }
}
