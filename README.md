
# My Final SkipList Implementation in C++

This repository contains an implementation of a SkipList, a probabilistic data structure that allows fast search, insertion, and deletion operations. This implementation is written in C++ and is designed to be simple yet efficient.

## Table of Contents

- [Overview](#overview)
- [Key Features](#key-features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Compiling the Code](#compiling-the-code)
  - [Running the Program](#running-the-program)
- [Code Structure](#code-structure)
- [Usage](#usage)
  - [Inserting Elements](#inserting-elements)
  - [Searching Elements](#searching-elements)
  - [Deleting Elements](#deleting-elements)
  - [Displaying the SkipList](#displaying-the-skiplist)
- [Technical Details](#technical-details)
- [Future Enhancements](#future-enhancements)
- [Contributing](#contributing)
- [License](#license)

## Overview

SkipList is a dynamic data structure that allows efficient search, insertion, and deletion operations. It uses multiple levels of linked lists to achieve average-case time complexity similar to balanced trees, but with simpler implementation.

## Key Features

- **Fast Operations:** SkipList provides O(log n) average time complexity for search, insertion, and deletion operations.
- **Randomized Level Assignment:** The level of each node is determined randomly, ensuring probabilistic balancing.
- **Simple Implementation:** The code is designed to be easy to understand and modify.

## Getting Started

### Prerequisites

To compile and run this SkipList implementation, you need:

- A C++ compiler (GCC, Clang, or MSVC)
- A terminal or command prompt

### Compiling the Code

To compile the code, navigate to the directory containing the source file and run:

```sh
g++ -o skiplist main.cpp
```

Replace `main.cpp` with the name of your source file if it differs.

### Running the Program

After compiling, run the executable:

```
./skiplist
```

This will execute the program and showcase the basic operations of the SkipList.

## Code Structure

The implementation consists of the following classes:

- **Node:** Represents a node in the SkipList. Each node contains a key and an array of pointers (`forward`) to other nodes at different levels.
- **SkipList:** Manages the overall structure of the SkipList. It includes methods for insertion, searching, deletion, and displaying the list.

## Usage

### Inserting Elements

To insert an element into the SkipList, use the `insertElement(int key)` method. This method randomly assigns a level to the new node and inserts it at the appropriate positions in the SkipList.

Example:
```
lst.insertElement(3);
```

### Searching Elements

To search for an element, use the `searchElement(int key)` method. This method traverses the SkipList to find the node with the specified key.

Example:
```
bool found = lst.searchElement(6);
```

### Deleting Elements

To delete an element from the SkipList, use the `deleteElement(int key)` method. This method removes the node with the specified key from the list.

Example:
```
lst.deleteElement(6);
```

### Displaying the SkipList

To display the current state of the SkipList, use the `displayList()` method. This method prints the keys in the SkipList, level by level.

Example:
```
lst.displayList();
```

## Technical Details

- **Random Level Generation:** The level for each new node is generated using a random number generator. The level is incremented as long as a random binary number is 1 and the maximum level is not exceeded.
- **Memory Management:** The SkipList class manages dynamic memory allocation for nodes and ensures proper cleanup in the destructor to avoid memory leaks.

## Future Enhancements

- **Custom Comparator:** Allow customization of the comparison function for ordering elements.
- **Concurrency Support:** Implement thread-safe operations to allow concurrent access to the SkipList.
- **Persistent Storage:** Add support for persistent storage, enabling the SkipList to be saved and loaded from disk.

## Contributing

Contributions are welcome! Please fork this repository, create a new branch, and submit a pull request with your changes. Ensure that your code is well-documented and follows the existing style.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
