#pragma once
#include <stdexcept>
#include <string>

namespace models
{
// Forward declaration for friend class
template <typename U> class BinaryTreeSet;

/**
 * @brief A node in a binary tree set
 *
 * @tparam T The type of data stored in the node (supports int, double, std::string)
 *
 * This class represents a single node in a binary tree set, containing:
 * - data: The value stored in the node
 * - left: Pointer to left child node (contains values less than current node)
 * - right: Pointer to right child node (contains values greater than current node)
 *
 * This class is designed to prevent accidental modification of tree structure.
 * Only read-only access to node values and child pointers is provided to users.
 * Tree modification operations are restricted to the BinaryTreeSet class.
 */
template <typename T> class BinaryNode
{
  private:
    T data;
    BinaryNode *left_, *right_;

    // Private methods for BinaryTreeSet to use internally
    // These methods are not available to users to prevent tree structure corruption

    /**
     * @brief Set a new value for this node (private - only for BinaryTreeSet)
     *
     * @param value The new value to store in this node
     * @return T The new value that was set
     *
     * This method validates the new value before updating the node's data:
     * - For std::string: throws std::invalid_argument if the string is empty
     * - For primitive types (int, double): accepts any value
     */
    T setValue(const T &value);

    /**
     * @brief Set the left child pointer directly (private - only for BinaryTreeSet)
     *
     * @param node Pointer to the node to set as the left child
     */
    void setLeftPtr(BinaryNode<T> *node);

    /**
     * @brief Set the right child pointer directly (private - only for BinaryTreeSet)
     *
     * @param node Pointer to the node to set as the right child
     */
    void setRightPtr(BinaryNode<T> *node);

    /**
     * @brief Get the left child node (non-const version - private for BinaryTreeSet)
     *
     * @return BinaryNode<T>* Pointer to the left child node, or nullptr if no left child exists
     */
    BinaryNode<T> *left();

    /**
     * @brief Get the right child node (non-const version - private for BinaryTreeSet)
     *
     * @return BinaryNode<T>* Pointer to the right child node, or nullptr if no right child exists
     */
    BinaryNode<T> *right();

  public:
    /**
     * @brief Construct a new BinaryNode with the given value
     *
     * @param value The value to store in this node
     * @throws std::invalid_argument if the value is invalid (e.g., empty string for std::string)
     *
     * This constructor validates the input value:
     * - For std::string: throws if the string is empty
     * - For primitive types (int, double): accepts any value
     */
    BinaryNode(const T &value);

    /**
     * @brief Get the value stored in this node
     *
     * @return const T The value stored in this node
     */
    const T value() const;

    /**
     * @brief Get the left child node (read-only access)
     *
     * @return const BinaryNode<T>* Pointer to the left child node, or nullptr if no left child exists
     */
    const BinaryNode<T> *left() const;

    /**
     * @brief Get the right child node (read-only access)
     *
     * @return const BinaryNode<T>* Pointer to the right child node, or nullptr if no right child exists
     */
    const BinaryNode<T> *right() const;

    // Make BinaryTreeSet a friend class to access private members for tree operations
    template <typename U> friend class BinaryTreeSet;
};

//? Implementation
//? Implementation
//? Implementation

/**
 * @brief Construct a new BinaryNode with the given value
 *
 * @tparam T The type of data stored in the node
 * @param value The value to store in this node
 *
 * Initializes a new BinaryNode with the specified value and sets both
 * left and right child pointers to nullptr.
 */
template <typename T> BinaryNode<T>::BinaryNode(const T &value) : data(value), left_(nullptr), right_(nullptr)
{
}

/**
 * @brief Template specialization for std::string constructor
 *
 * @param value The string value to store in this node
 * @throws std::invalid_argument if the string is empty
 *
 * This specialization adds validation to ensure that string values
 * cannot be empty, maintaining data integrity for the binary tree.
 */
template <>
inline BinaryNode<std::string>::BinaryNode(const std::string &value) : data(value), left_(nullptr), right_(nullptr)
{
    if (value.empty())
    {
        throw std::invalid_argument("String value cannot be empty");
    }
}

/**
 * @brief Get the value stored in this node
 *
 * @tparam T The type of data stored in the node
 * @return const T The value stored in this node
 *
 * Returns a const reference to the data stored in this node.
 */
template <typename T> const T BinaryNode<T>::value() const
{
    return data;
}

/**
 * @brief Set a new value for this node (private method for BinaryTreeSet)
 *
 * @tparam T The type of data stored in the node
 * @param value The new value to store in this node
 * @return T The new value that was set
 *
 * Updates the node's data with the new value and returns it.
 * This method is private and only accessible by BinaryTreeSet to prevent
 * accidental modification of node values that could break BST properties.
 */
template <typename T> T BinaryNode<T>::setValue(const T &value)
{
    data = value;
    return value;
}

/**
 * @brief Template specialization for std::string setValue
 *
 * @param value The new string value to store in this node
 * @return std::string The new value that was set
 * @throws std::invalid_argument if the string is empty
 *
 * This specialization adds validation to ensure that string values
 * cannot be set to empty strings.
 */
template <> inline std::string BinaryNode<std::string>::setValue(const std::string &value)
{
    if (value.empty())
    {
        throw std::invalid_argument("String value cannot be set to empty ('')");
    }
    data = value;
    return value;
}

/**
 * @brief Get the left child node (const version)
 *
 * @tparam T The type of data stored in the node
 * @return const BinaryNode<T>* Pointer to the left child node, or nullptr if no left child exists
 *
 * Returns a const pointer to the left child node, allowing read-only access.
 */
template <typename T> const BinaryNode<T> *BinaryNode<T>::left() const
{
    return left_;
}

/**
 * @brief Get the right child node (const version)
 *
 * @tparam T The type of data stored in the node
 * @return const BinaryNode<T>* Pointer to the right child node, or nullptr if no right child exists
 *
 * Returns a const pointer to the right child node, allowing read-only access.
 */
template <typename T> const BinaryNode<T> *BinaryNode<T>::right() const
{
    return right_;
}

/**
 * @brief Get the left child node (non-const version - private for BinaryTreeSet)
 *
 * @tparam T The type of data stored in the node
 * @return BinaryNode<T>* Pointer to the left child node, or nullptr if no left child exists
 *
 * Returns a non-const pointer to the left child node for internal tree operations.
 * This method is private and only accessible by BinaryTreeSet to prevent
 * accidental modification of tree structure.
 */
template <typename T> BinaryNode<T> *BinaryNode<T>::left()
{
    return left_;
}

/**
 * @brief Get the right child node (non-const version - private for BinaryTreeSet)
 *
 * @tparam T The type of data stored in the node
 * @return BinaryNode<T>* Pointer to the right child node, or nullptr if no right child exists
 *
 * Returns a non-const pointer to the right child node for internal tree operations.
 * This method is private and only accessible by BinaryTreeSet to prevent
 * accidental modification of tree structure.
 */
template <typename T> BinaryNode<T> *BinaryNode<T>::right()
{
    return right_;
}

/**
 * @brief Set the left child pointer directly (private method for BinaryTreeSet)
 *
 * @tparam T The type of data stored in the node
 * @param node Pointer to the node to set as the left child
 *
 * Sets the left child pointer to the provided node without creating
 * a copy. This is useful for tree restructuring operations.
 * This method is private and only accessible by BinaryTreeSet to prevent
 * accidental modification of tree structure.
 */
template <typename T> void BinaryNode<T>::setLeftPtr(BinaryNode<T> *node)
{
    left_ = node;
}

/**
 * @brief Set the right child pointer directly (private method for BinaryTreeSet)
 *
 * @tparam T The type of data stored in the node
 * @param node Pointer to the node to set as the right child
 *
 * Sets the right child pointer to the provided node without creating
 * a copy. This is useful for tree restructuring operations.
 * This method is private and only accessible by BinaryTreeSet to prevent
 * accidental modification of tree structure.
 */
template <typename T> void BinaryNode<T>::setRightPtr(BinaryNode<T> *node)
{
    right_ = node;
}

// Explicit template instantiations for supported types
template class BinaryNode<int>;
template class BinaryNode<double>;
template class BinaryNode<std::string>;

} // namespace models