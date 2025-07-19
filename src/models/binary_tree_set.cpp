#include "models/binary_tree_set.hpp"

#include <algorithm>
#include <cstddef>
#include <functional>

namespace models
{
template <typename T> int BinaryTreeSet<T>::findHeightRecursive(const BinaryNode<T> *node) const
{
    if (!node)
    {
        return -1;
    }

    return 1 + std::max(findHeightRecursive(node->left()), findHeightRecursive(node->right()));
}

template <typename T> int BinaryTreeSet<T>::height() const
{
    return findHeightRecursive(root);
}

template <typename T>
BinaryNode<T> *BinaryTreeSet<T>::insertValueRecursive(BinaryNode<T> *node, const T &value, bool &inserted)
{
    if (!node)
    {
        inserted = true;
        return new BinaryNode<T>(value);
    }

    if (value < node->value())
    {
        node->setLeftPtr(insertValueRecursive(node->left(), value, inserted));
    }
    else if (value > node->value())
    {
        node->setRightPtr(insertValueRecursive(node->right(), value, inserted));
    }
    //? If value equals node->data, do not insert (no duplicates)
    return node;
}

template <typename T> void BinaryTreeSet<T>::insert(const T &value)
{
    bool inserted = false;
    root = insertValueRecursive(root, value, inserted);
    if (inserted)
        tree_size++;
}

template <typename T> void BinaryTreeSet<T>::insertRange(const std::vector<T> &range)
{
    for (const auto &value : range)
    {
        insert(value);
    }
}

template <typename T> void BinaryTreeSet<T>::merge(const BinaryTreeSet<T> &set)
{
    set.traverseInorder([this](const T &value) { this->insert(value); });
}

template <typename T> bool BinaryTreeSet<T>::contains(const T &value) const
{
    const BinaryNode<T> *node = findValueRecursive(root, value);
    return node != nullptr;
}

template <typename T>
BinaryNode<T> *BinaryTreeSet<T>::findValueRecursive(const BinaryNode<T> *node, const T &value) const
{
    if (!node)
    {
        return nullptr;
    }

    if (value == node->value())
    {
        return const_cast<BinaryNode<T> *>(node);
    }
    else if (value < node->value())
    {
        return findValueRecursive(node->left(), value);
    }
    else
    {
        return findValueRecursive(node->right(), value);
    }
}

template <typename T> BinaryNode<T> *BinaryTreeSet<T>::find(const T &value) const
{
    return findValueRecursive(root, value);
}

template <typename T>
BinaryNode<T> *BinaryTreeSet<T>::removeValueRecursive(BinaryNode<T> *node, const T &value, bool &removed)
{
    if (!node)
    {
        return nullptr;
    }

    if (value < node->value())
    {
        node->setLeftPtr(removeValueRecursive(node->left(), value, removed));
    }
    else if (value > node->value())
    {
        node->setRightPtr(removeValueRecursive(node->right(), value, removed));
    }
    else
    {
        removed = true;

        //? Node with only one child or no child
        if (!node->left())
        {
            BinaryNode<T> *temp = node->right();
            delete node;
            return temp;
        }
        else if (!node->right())
        {
            BinaryNode<T> *temp = node->left();
            delete node;
            return temp;
        }

        //? Node with two children: Get the inorder successor (smallest value in the right subtree)
        BinaryNode<T> *current = node->right();
        while (current && current->left())
        {
            current = current->left();
        }

        //? Copy the inorder successor's data to this node
        node->setValue(current->value());

        //? Delete the inorder successor
        node->setRightPtr(removeValueRecursive(node->right(), current->value(), removed));
    }
    return node;
}

template <typename T> bool BinaryTreeSet<T>::erase(const T &value)
{
    bool removed = false;
    root = removeValueRecursive(root, value, removed);
    if (removed)
    {
        tree_size--;
        return true;
    }
    return false;
}

template <typename T> void BinaryTreeSet<T>::clearTreeRecursive(BinaryNode<T> *node)
{
    if (node == nullptr)
    {
        return;
    }

    clearTreeRecursive(node->left());
    clearTreeRecursive(node->right());

    //? Delete current node after its children are cleared to prevent memory leaks
    delete node;
}

template <typename T> void BinaryTreeSet<T>::clear()
{
    clearTreeRecursive(root);
    root = nullptr;
    tree_size = 0;
}

template <typename T>
void BinaryTreeSet<T>::traverseInorderRecursive(const BinaryNode<T> *node,
                                                std::function<void(const T &)> callback) const
{
    if (!node)
    {
        return;
    }

    traverseInorderRecursive(node->left(), callback);
    callback(node->value());
    traverseInorderRecursive(node->right(), callback);
}

template <typename T> void BinaryTreeSet<T>::traverseInorder(std::function<void(const T &)> callback) const
{
    traverseInorderRecursive(root, callback);
}

template <typename T>
void BinaryTreeSet<T>::traversePreorderRecursive(const BinaryNode<T> *node,
                                                 std::function<void(const T &)> callback) const
{
    if (!node)
    {
        return;
    }

    callback(node->value());
    traversePreorderRecursive(node->left(), callback);
    traversePreorderRecursive(node->right(), callback);
}

template <typename T> void BinaryTreeSet<T>::traversePreorder(std::function<void(const T &)> callback) const
{
    traversePreorderRecursive(root, callback);
}

template <typename T>
void BinaryTreeSet<T>::traversePostorderRecursive(const BinaryNode<T> *node,
                                                  std::function<void(const T &)> callback) const
{
    if (!node)
    {
        return;
    }

    traversePostorderRecursive(node->left(), callback);
    traversePostorderRecursive(node->right(), callback);
    callback(node->value());
}

template <typename T> void BinaryTreeSet<T>::traversePostorder(std::function<void(const T &)> callback) const
{
    traversePostorderRecursive(root, callback);
}
} // namespace models

// Explicit template instantiations for common types
template class models::BinaryTreeSet<int>;
template class models::BinaryTreeSet<double>;
template class models::BinaryTreeSet<std::string>;
