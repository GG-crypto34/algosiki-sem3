#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class SearchTree {
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

    static void refresh_path(const std::vector<Vertex*>& path) {
        for (auto position = path.rbegin(); position != path.rend(); ++position) refresh(*position);
    }

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
        std::vector<Vertex*> path;
        Vertex** link = &root_;
        while (*link) {
            if ((*link)->key == key) return;
            path.push_back(*link);
            link = key < (*link)->key ? &(*link)->left : &(*link)->right;
        }
        *link = new Vertex(key);
        refresh_path(path);
    }

    void erase(int key) {
        std::vector<Vertex*> path;
        Vertex** link = &root_;
        while (*link && (*link)->key != key) {
            path.push_back(*link);
            link = key < (*link)->key ? &(*link)->left : &(*link)->right;
        }
        if (!*link) return;
        Vertex* removed = *link;
        if (removed->left && removed->right) {
            path.push_back(removed);
            Vertex** successor = &removed->right;
            while ((*successor)->left) {
                path.push_back(*successor);
                successor = &(*successor)->left;
            }
            removed->key = (*successor)->key;
            removed = *successor;
            *successor = removed->right;
        } else {
            *link = removed->left ? removed->left : removed->right;
        }
        delete removed;
        refresh_path(path);
    }

    bool contains(int key) const {
        const Vertex* vertex = root_;
        while (vertex && vertex->key != key) {
            vertex = key < vertex->key ? vertex->left : vertex->right;
        }
        return vertex != nullptr;
    }

    int height() const { return height_of(root_); }

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
    int requests;
    if (!(std::cin >> requests)) return 0;
    for (int request = 0; request < requests; ++request) {
        std::string command;
        std::cin >> command;
        if (command == "height") std::cout << tree.height() << '\n';
        else if (command == "print") tree.print();
        else {
            int key;
            std::cin >> key;
            if (command == "add") tree.insert(key);
            else if (command == "del") tree.erase(key);
            else if (command == "exists") std::cout << (tree.contains(key) ? "YES" : "NO") << '\n';
        }
    }
}
