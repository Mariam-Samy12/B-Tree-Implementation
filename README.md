# B-Tree Implementation

A C++ implementation of the **B-Tree data structure**, developed as part of the **Advanced Data Structures** course.

This project implements the fundamental operations of a B-Tree using C++ templates, inheritance, and dynamic memory allocation.

## Project Overview

A B-Tree is a self-balancing multiway search tree designed to maintain sorted data and support efficient searching, insertion, and deletion.

Unlike a Binary Search Tree, a B-Tree node can store multiple keys and have multiple children. All leaf nodes remain at the same depth, ensuring that the tree stays balanced.

The implementation is based on the **order `m`** of the B-Tree.

For a B-Tree of order `m`:

- Each node can contain at most `m - 1` keys.
- Each internal node can have at most `m` children.
- Every non-root node contains at least `ceil(m / 2) - 1` keys.
- Every non-root internal node has at least `ceil(m / 2)` children.
- A node containing `k` keys has `k + 1` children if it is an internal node.
- All leaf nodes appear at the same level.
- Keys within each node are stored in sorted order.

## Features

The project supports four main operations:

### 1. Insertion

Inserts a new key into the B-Tree while maintaining its sorted and balanced structure.

When a node exceeds its maximum allowed number of keys, it is split and the appropriate middle key is promoted to its parent.

### 2. Deletion

Removes a key from the B-Tree while preserving the B-Tree properties.

The deletion algorithm handles cases such as:

- Deleting a key from a leaf node.
- Deleting a key from an internal node.
- Borrowing a key from a sibling.
- Merging nodes when necessary.
- Updating the root when the tree height decreases.

### 3. Searching

Searches for a specified key by comparing it with the keys stored in each node and following the appropriate child pointer.

### 4. Display All (Depth-First Traversal)

Traverses the B-Tree recursively and displays its stored keys using depth-first traversal.

## Data Structures

The implementation uses four primary structures.

| Structure | Description |
|---|---|
| `Node<Type, ord>` | Base node containing the keys, key count, and leaf indicator |
| `InternalNode<Type, ord>` | Inherits from `Node` and stores pointers to child nodes |
| `LeafNode<Type, ord>` | Inherits from `Node` and represents a node without children |
| `Btree<Type, ord>` | Represents the complete B-Tree and stores its root pointer |

### Templates

The implementation uses C++ templates to support different key data types and B-Tree orders.

For example:

```cpp
Btree<int, 5> tree{};
```

This declares an integer B-Tree of order 5.

## Project Structure

```text
B-Tree-Implementation/
│
├── README.md
│
└── BTreeImplementation/
    ├── BTreeImplementation.sln
    ├── .gitignore
    │
    └── BTreeImplementation/
        ├── BTree.h
        ├── main.cpp
        ├── BTreeImplementation.vcxproj
        └── BTreeImplementation.vcxproj.filters
```

## Console Menu

The application provides a menu-driven interface:

```text
========== B-Tree Menu ==========
1. Insert
2. Delete
3. Search
4. Display All (Depth First)
5. Exit

Enter your choice:
```

Users select an operation by entering the corresponding number.

## How to Run

### Requirements

- Microsoft Visual Studio 2022 with C++ development tools
- C++ compiler
- Git (optional)

### Installation

**1. Clone the repository**

```bash
git clone https://github.com/Mariam-Samy12/B-Tree-Implementation.git
```

**2. Open the project**

Open `BTreeImplementation.sln` in Microsoft Visual Studio 2022.

**3. Build the project**

Use `Ctrl + Shift + B` to build the solution.

**4. Run the application**

Use `Ctrl + F5` to run the console application.

## Time Complexity

The expected time complexities for a balanced B-Tree are:

| Operation | Time Complexity |
|---|---|
| Insertion | O(log n) |
| Deletion | O(log n) |
| Searching | O(log n) |
| Depth-First Traversal | O(n) |

These bounds assume a fixed B-Tree order and count work in terms of the number of stored keys.

## Development Status

The project is under development. The B-Tree structures and console menu form the initial foundation, while the required algorithms will be integrated and tested.

## Team Collaboration

This project is developed by a team for the Advanced Data Structures course.

Each team member contributes to the implementation, testing, debugging, or integration of the required B-Tree operations.

## Course Information

**Course:** Advanced Data Structures  
**Assignment:** Assignment 1 — B-Tree Implementation  
**Programming Language:** C++  
**Development Environment:** Microsoft Visual Studio 2022

## License

This project is intended for educational and academic purposes.
