# SkipList Implementation

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Class Structure](#class-structure)
  - [Node Class](#node-class)
  - [SkipList Class](#skiplist-class)
- [Key Functions](#key-functions)
  - [insertElement(int key)](#insertelementint-key)
  - [searchElement(int key) const](#searchelementint-key-const)
  - [deleteElement(int key)](#deleteelementint-key)
  - [displayList() const](#displaylist-const)
- [Usage](#usage)
- [How It Works](#how-it-works)
- [License](#license)

## Overview

This is a SkipList data structure in C++. SkipLists are a type of data structure that allow fast search, insertion, and deletion operations within an ordered sequence of elements, using a hierarchy of linked lists. This script makes use of smart pointers (`std::unique_ptr`) for automatic memory management, ensuring safe and efficient resource handling.

## Features

- **Smart Pointers:** `std::unique_ptr` for all dynamic memory management, making the code more robust by avoiding manual memory management and potential memory leaks.
- **Randomized Levels:** The SkipList is built using a randomized level structure, which offers an average time complexity of O(log n) for search, insertion, and deletion operations.
- **Automatic Level Management:** The SkipList automatically adjusts its level as new elements are added.

## Class Structure

### Node Class

```
class Node {
public:
    int key;
    std::unique_ptr<std::unique_ptr<Node>[]> forward;

    explicit Node(int key, int level);
};
```

- **`key`:** Stores the key value of the node.
- **`forward`:** An array of smart pointers pointing to the next nodes at various levels.

### SkipList Class

```
class SkipList {
    int maxLevel;
    int level;
    std::unique_ptr<Node> header;

public:
    explicit SkipList(int maxLevel);
    int randomLevel() const;
    std::unique_ptr<Node> createNode(int key, int level);
    void insertElement(int key);
    bool searchElement(int key) const;
    void deleteElement(int key);
    void displayList() const;
};
```

- **`maxLevel`:** The maximum level a node can have.
- **`level`:** The current level of the SkipList.
- **`header`:** A header node to represent the start of the SkipList.

## Key Functions

### `insertElement(int key)`
Inserts a new key into the SkipList.

### `searchElement(int key) const`
Searches for a key in the SkipList. Returns `true` if the key is found, otherwise `false`.

### `deleteElement(int key)`
Deletes a key from the SkipList.

### `displayList() const`
Displays the entire SkipList, showing the elements at each level.

## Usage

Here is a simple example of how to use the SkipList:

```
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
```

This example demonstrates inserting elements into the SkipList, searching for an element, deleting an element, and displaying the SkipList at different stages.

## How It Works

1. **Random Level Generation:** The `randomLevel()` function generates a level for a new node using a random number generator, where each level has a 50% chance of being incremented.
  
2. **Insertion:** The `insertElement()` method inserts the new node at the appropriate position in the SkipList. If the generated level is higher than the current level of the SkipList, the level of the SkipList is updated.

3. **Search:** The `searchElement()` method navigates through the levels starting from the highest and progressively moving down to locate the key.

4. **Deletion:** The `deleteElement()` method removes the specified key from the SkipList and adjusts the pointers accordingly.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

Feel free to contribute to this project by submitting issues or pull requests!
