#include <iostream>
#include <climits>
#include <memory>
#include <random>
#include <ctime>

class Node {
public:
    int key;
    std::unique_ptr<std::unique_ptr<Node>[]> forward;

    explicit Node(int key, int level)
        : key(key), forward(std::make_unique<std::unique_ptr<Node>[]>(level + 1)) {}
};

class SkipList {
    int maxLevel;
    int level;
    std::unique_ptr<Node> header;

public:
    explicit SkipList(int maxLevel)
        : maxLevel(maxLevel), level(0), header(std::make_unique<Node>(INT_MIN, maxLevel)) {}

    [[nodiscard]] int randomLevel() const {
        static std::random_device rd;
        static std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, 1);

        int lvl = 0;
        while (distribution(generator) && lvl < maxLevel) {
            ++lvl;
        }
        return lvl;
    }

    std::unique_ptr<Node> createNode(int key, int level) {
        return std::make_unique<Node>(key, level);
    }

    void insertElement(int key);
    [[nodiscard]] bool searchElement(int key) const;
    void deleteElement(int key);
    void displayList() const;
};

void SkipList::insertElement(int key) {
    std::unique_ptr<Node>* update[maxLevel + 1] {};
    Node* current = header.get();

    for (int i = level; i >= 0; --i) {
        while (current->forward[i] && current->forward[i]->key < key) {
            current = current->forward[i].get();
        }
        update[i] = &current->forward[i];
    }

    current = current->forward[0].get();

    if (!current || current->key != key) {
        int rlevel = randomLevel();

        if (rlevel > level) {
            for (int i = level + 1; i <= rlevel; ++i) {
                update[i] = &header->forward[i];
            }
            level = rlevel;
        }

        auto newNode = createNode(key, rlevel);

        for (int i = 0; i <= rlevel; ++i) {
            newNode->forward[i] = std::move(*update[i]);
            *update[i] = std::move(newNode);
        }

        std::cout << "Successfully inserted key " << key << std::endl;
    }
}

bool SkipList::searchElement(int key) const {
    Node* current = header.get();
    for (int i = level; i >= 0; --i) {
        while (current->forward[i] && current->forward[i]->key < key) {
            current = current->forward[i].get();
        }
    }

    current = current->forward[0].get();

    if (current && current->key == key) {
        std::cout << "Found key: " << key << std::endl;
        return true;
    }

    std::cout << "Key not found: " << key << std::endl;
    return false;
}

void SkipList::deleteElement(int key) {
    std::unique_ptr<Node>* update[maxLevel + 1] {};
    Node* current = header.get();

    for (int i = level; i >= 0; --i) {
        while (current->forward[i] && current->forward[i]->key < key) {
            current = current->forward[i].get();
        }
        update[i] = &current->forward[i];
    }

    current = current->forward[0].get();

    if (current && current->key == key) {
        for (int i = 0; i <= level; ++i) {
            if (update[i]->get() != current) break;
            *update[i] = std::move(current->forward[i]);
        }

        while (level > 0 && !header->forward[level]) {
            --level;
        }

        std::cout << "Successfully deleted key " << key << std::endl;
    }
}

void SkipList::displayList() const {
    std::cout << "\n*****Skip List*****\n";
    for (int i = 0; i <= level; ++i) {
        Node* node = header->forward[i].get();
        std::cout << "Level " << i << ": ";
        while (node) {
            std::cout << node->key << " ";
            node = node->forward[i].get();
        }
        std::cout << std::endl;
    }
}

int main() {
    SkipList lst(10);

    lst.insertElement(3);
    lst.insertElement(6);
    lst.insertElement(7);
    lst.insertElement(9);
    lst.insertElement(12);
    lst.insertElement(19);
    lst.insertElement(17);

    lst.displayList();
    lst.searchElement(6);
    lst.deleteElement(6);
    lst.displayList();

    return 0;
}
