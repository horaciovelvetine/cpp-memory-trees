#pragma once

#include "binary_node.hpp"

#include <functional>
#include <cstddef>
#include <vector>

namespace models
{

  template <typename T>
  class BinaryTreeSet
  {
  private:
    BinaryNode<T> *root;
    size_t tree_size;

    //? Recursive helpers & primary logic
    int findHeightRecursive(const BinaryNode<T> *node) const;
    BinaryNode<T> *insertValueRecursive(BinaryNode<T> *node, const T &value, bool &inserted);
    BinaryNode<T> *findValueRecursive(const BinaryNode<T> *node, const T &value) const;
    BinaryNode<T> *removeValueRecursive(BinaryNode<T> *node, const T &value, bool &removed);
    void clearTreeRecursive(BinaryNode<T> *node);

    //? traversal helpers...
    void traverseInorderRecursive(const BinaryNode<T> *node, std::function<void(const T &)> callback) const;
    void traversePreorderRecursive(const BinaryNode<T> *node, std::function<void(const T &)> callback) const;
    void traversePostorderRecursive(const BinaryNode<T> *node, std::function<void(const T &)> callback) const;

  public:
    BinaryTreeSet() : root(nullptr), tree_size(0) {}
    ~BinaryTreeSet() { clear(); }

    //
    //! ACCESSORS/GETTERS/FIELDS
    //

    /**
     * @brief Get the root node of the binary tree with read-only access
     *
     * @return const BinaryNode<T>* Pointer to the root node that cannot be modified
     *
     * This method provides read-only access to the root node and its children. For write access use the non-const overload instead
     */
    const BinaryNode<T> *getRoot() const { return root; }

    /**
     * @brief Get the root node of the binary tree with write access
     *
     * @return BinaryNode<T>* Pointer to the root node that can be modified
     *
     * This method provides direct access to modify the root node and its children. For read-only access use the const overload instead
     */
    BinaryNode<T> *getRoot() { return root; }

    /**
     * @brief Get the total number of nodes in the binary tree
     *
     * @return size_t The number of nodes currently in the tree
     */
    size_t size() const { return tree_size; }

    /**
     * @brief Check if the binary tree is empty (the root node pointer is a nullptr)
     *
     * @return true if the tree contains no nodes
     * @return false if the tree contains at least one node
     */
    bool empty() const { return root == nullptr; }

    /**
     * @brief Get the height of the binary tree
     *
     * @return int The height of the tree (number of edges in longest path from root to leaf)
     *
     * The height is defined as the number of edges in the longest path from the root to any leaf.
     * - An empty tree has height -1
     * - A tree with only a root node has height 0
     * - Otherwise, height is max(left_subtree_height, right_subtree_height) + 1
     */
    int height() const;

    //
    //! MODIFICATION OPERATIONS
    //

    /**
     * @brief Insert the provided value into the tree
     *
     * @param value The value to insert into the binary search tree
     *
     * This method inserts a new node with the given value into the binary search tree,
     * maintaining the tree property where:
     * - All values in the left subtree are less than the current node
     * - All values in the right subtree are greater than the current node
     *
     * If the value already exists in the tree, it will not be inserted again.
     * The tree_size is incremented only when a new value is successfully inserted.
     */
    void insert(const T &value);

    /**
     * @brief Inserts a copy of each element in the range if and only if there is no element with that value already present.
     *
     * @param range A vector containing elements to insert into the set
     * @return void
     *
     * @note If the range is null, this method will return without doing anything
     * @see https://en.cppreference.com/w/cpp/container/set/insert_range.html
     *
     * This method attempts to insert each element from the input range into the set.
     * Elements that already exist in the set will be skipped.
     */
    void insertRange(const std::vector<T> &range);

    /**
     * @brief Merges another binary tree set into this one
     *
     * @param set The binary tree set to merge into this one
     *
     * This method takes all values from the input set and inserts them into the current set.
     * If a value from the input set already exists in the current set, it will be skipped.
     * The input set remains unchanged after the merge operation.
     *
     * The tree_size will increase by the number of new unique values that were merged in.
     */
    void merge(const BinaryTreeSet<T> &set);

    /**
     * @brief Searches the tree for a node with the given value.
     *
     * @param value The value to search for in the tree
     * @return true if the value is found in the tree
     * @return false if the value is not found in the tree
     *
     */
    bool contains(const T &value) const;

    /**
     * @brief Searches for and returns a node containing the specified value
     *
     * @param value The value to search for in the tree
     * @return BinaryNode<T>* Pointer to the node containing the value if found, nullptr otherwise
     *
     * This method traverses the binary search tree to find a node containing the given value.
     * If a matching node is found, a pointer to that node is returned.
     * If no node contains the value, nullptr is returned.
     */
    BinaryNode<T> *find(const T &value) const;

    /**
     * @brief Removes a node with the specified value from the binary search tree
     *
     * @param value The value to remove from the tree
     * @return true if a node containing the value was found and removed
     * @return false if the value was not found in the tree
     *
     * This method searches for and removes a node containing the given value from the tree,
     * maintaining the binary search tree property where:
     * - All values in the left subtree are less than the current node
     * - All values in the right subtree are greater than the current node
     *
     * When removing a node with two children, it is replaced with its in-order successor
     * (the smallest value in its right subtree).
     *
     * The tree_size is decremented when a value is successfully removed.
     */
    bool erase(const T &value);

    /**
     * @brief Removes all nodes from the binary search tree
     *
     * This method deletes all nodes in the tree and sets the root to nullptr.
     * After calling clear(), the tree will be empty and tree_size will be 0.
     * All memory used by the tree nodes will be properly deallocated.
     */
    void clear();

    //
    //! TRAVERSAL OPERATIONS
    //

    /**
     * Runs the callback in ascending order on every node in the tree:
     * ==> Left recursively first
     * ==> Node (self) second
     * ==> Right recursively last
     */
    /**
     * @brief Performs an inorder traversal of the binary tree, executing a callback on each node
     *
     * @param callback A function to execute on each node's value during traversal
     *
     * Visits the nodes in the following order:
     * 1. Recursively traverse the left subtree
     * 2. Visit the current node (execute callback)
     * 3. Recursively traverse the right subtree
     *
     * This traversal visits nodes in ascending order for a binary search tree.
     */
    void traverseInorder(std::function<void(const T &)> callback) const;

    /**
     * @brief Performs a preorder traversal of the binary tree, executing a callback on each node
     *
     * @param callback A function to execute on each node's value during traversal
     *
     * Visits the nodes in the following order:
     * 1. Visit the current node (execute callback)
     * 2. Recursively traverse the left subtree
     * 3. Recursively traverse the right subtree
     *
     * This traversal visits the root before its children, making it useful for copying/cloning trees
     * or generating prefix expressions.
     */
    void traversePreorder(std::function<void(const T &)> callback) const;

    /**
     * @brief Performs a postorder traversal of the binary tree, executing a callback on each node
     *
     * @param callback A function to execute on each node's value during traversal
     *
     * Visits the nodes in the following order:
     * 1. Recursively traverse the left subtree
     * 2. Recursively traverse the right subtree
     * 3. Visit the current node (execute callback)
     *
     * This traversal visits all children before their parent nodes, making it useful for operations
     * that require processing child nodes first, such as deletion or calculating expression trees.
     */
    void traversePostorder(std::function<void(const T &)> callback) const;
  };
}