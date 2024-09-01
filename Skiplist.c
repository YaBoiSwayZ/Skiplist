#include <iostream>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <random>

class Node {
public:
    int key;
    Node** forward;

    explicit Node(int key, int level) {
        this->key = key;
        this->forward = new Node*[level + 1];
        std::fill_n(forward, level + 1, nullptr);
    }
};

class SkipList {
    int maxLevel;
    int level;
    Node* header;

public:
    explicit SkipList(int maxLevel) : maxLevel(maxLevel), level(0), header(new Node(INT_MIN, maxLevel)) {}

    ~SkipList() {
        Node* current = header;
        while (current != nullptr) {
            Node* next = current->forward[0];
            delete current;
            current = next;
        }
    }

    int randomLevel() {
        static std::mt19937 generator(static_cast<unsigned>(time(nullptr)));
        std::uniform_int_distribution<int> distribution(0, 1);
        int lvl = 0;
        while (distribution(generator) && lvl < maxLevel) {
            lvl++;
        }
        return lvl;
    }

    Node* createNode(int key, int level) {
        return new Node(key, level);
    }

    void insertElement(int key);
    bool searchElement(int key);
    void deleteElement(int key);
    void displayList();
};

void SkipList::insertElement(int key) {
    Node* update[maxLevel + 1] {};
    Node* current = header;

    for (int i = level; i >= 0; i--) {
        while (current->forward[i] != nullptr && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];

    if (current == nullptr || current->key != key) {
        int rlevel = randomLevel();

        if (rlevel > level) {
            for (int i = level + 1; i <= rlevel; i++) {
                update[i] = header;
            }
            level = rlevel;
        }

        Node* n = createNode(key, rlevel);

        for (int i = 0; i <= rlevel; i++) {
            n->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = n;
        }
        std::cout << "Successfully inserted key " << key << std::endl;
    }
}

bool SkipList::searchElement(int key) {
    Node* current = header;
    for (int i = level; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->key < key) {
            current = current->forward[i];
        }
    }

    current = current->forward[0];

    if (current && current->key == key) {
        std::cout << "Found key: " << key << std::endl;
        return true;
    }

    std::cout << "Key not found: " << key << std::endl;
    return false;
}

void SkipList::deleteElement(int key) {
    Node* update[maxLevel + 1] {};
    Node* current = header;

    for (int i = level; i >= 0; i--) {
        while (current->forward[i] != nullptr && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];

    if (current != nullptr && current->key == key) {
        for (int i = 0; i <= level; i++) {
            if (update[i]->forward[i] != current) break;
            update[i]->forward[i] = current->forward[i];
        }

        while (level > 0 && header->forward[level] == nullptr) {
            level--;
        }

        std::cout << "Successfully deleted key " << key << std::endl;
        delete current;
    }
}

void SkipList::displayList() {
    std::cout << "\n*****Skip List*****\n";
    for (int i = 0; i <= level; i++) {
        Node* node = header->forward[i];
        std::cout << "Level " << i << ": ";
        while (node != nullptr) {
            std::cout << node->key << " ";
            node = node->forward[i];
        }
        std::cout << std::endl;
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
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