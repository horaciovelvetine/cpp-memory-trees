#include <gtest/gtest.h>
#include "models/binary_tree_set.hpp"
#include <vector>
#include <string>
#include <algorithm>

using namespace models;

class BinaryTreeSetTests : public ::testing::Test
{
protected:
    BinaryTreeSet<int> tree;

    void SetUp() override {}
    void TearDown() override
    {
        tree.clear();
    }
};

//? Test construction and basic properties
TEST_F(BinaryTreeSetTests, DefaultConstructor)
{
    BinaryTreeSet<int> defaultTree;
    EXPECT_EQ(defaultTree.size(), 0) << "Default constructor should create empty tree";
    EXPECT_TRUE(defaultTree.empty()) << "Default constructor should create empty tree";
    EXPECT_EQ(defaultTree.getRoot(), nullptr) << "Default constructor should have null root";
    EXPECT_EQ(defaultTree.height(), -1) << "Empty tree should have height -1";
}

TEST_F(BinaryTreeSetTests, DestructorAndClear)
{
    BinaryTreeSet<int> *treePtr = new BinaryTreeSet<int>();
    treePtr->insert(1);
    treePtr->insert(2);
    treePtr->insert(3);
    EXPECT_EQ(treePtr->size(), 3) << "Tree should have 3 elements before deletion";

    delete treePtr; //? Should call destructor which calls clear()
    //? No memory leaks should occur
}

//? Test insertion operations
TEST_F(BinaryTreeSetTests, SingleInsert)
{
    tree.insert(42);
    EXPECT_EQ(tree.size(), 1) << "Size should be 1 after single insert";
    EXPECT_FALSE(tree.empty()) << "Tree should not be empty after insert";
    EXPECT_EQ(tree.getRoot()->value(), 42) << "Root value should match inserted value";
    EXPECT_EQ(tree.height(), 0) << "Single node tree should have height 0";
}

TEST_F(BinaryTreeSetTests, MultipleInserts)
{
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);

    EXPECT_EQ(tree.size(), 5) << "Tree should have 5 elements after multiple inserts";
    EXPECT_EQ(tree.getRoot()->value(), 50) << "Root should be first inserted value";
    EXPECT_EQ(tree.getRoot()->left()->value(), 30) << "Left child should be 30";
    EXPECT_EQ(tree.getRoot()->right()->value(), 70) << "Right child should be 70";
}

TEST_F(BinaryTreeSetTests, DuplicateInsertPrevention)
{
    tree.insert(42);
    tree.insert(42); //? Duplicate insert
    tree.insert(42); //? Another duplicate

    EXPECT_EQ(tree.size(), 1) << "Size should remain 1 after duplicate inserts";
    EXPECT_TRUE(tree.contains(42)) << "Tree should still contain the value";
}

TEST_F(BinaryTreeSetTests, InsertRange)
{
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    tree.insertRange(values);

    EXPECT_EQ(tree.size(), 7) << "Tree should have 7 elements after insertRange";
    for (int value : values)
    {
        EXPECT_TRUE(tree.contains(value)) << "Tree should contain value: " << value;
    }
}

TEST_F(BinaryTreeSetTests, InsertRangeWithDuplicates)
{
    tree.insert(50);
    std::vector<int> values = {30, 50, 70, 30, 50}; //? Contains duplicates
    tree.insertRange(values);

    EXPECT_EQ(tree.size(), 3) << "Tree should have 3 unique elements after insertRange with duplicates";
    EXPECT_TRUE(tree.contains(30)) << "Tree should contain 30";
    EXPECT_TRUE(tree.contains(50)) << "Tree should contain 50";
    EXPECT_TRUE(tree.contains(70)) << "Tree should contain 70";
}

TEST_F(BinaryTreeSetTests, InsertRangeEmptyVector)
{
    std::vector<int> emptyVec;
    tree.insertRange(emptyVec);

    EXPECT_EQ(tree.size(), 0) << "Tree size should remain 0 after empty range insert";
    EXPECT_TRUE(tree.empty()) << "Tree should remain empty";
}

//? Test search operations
TEST_F(BinaryTreeSetTests, ContainsExistingValue)
{
    tree.insert(42);
    tree.insert(30);
    tree.insert(70);

    EXPECT_TRUE(tree.contains(42)) << "Tree should contain root value";
    EXPECT_TRUE(tree.contains(30)) << "Tree should contain left child value";
    EXPECT_TRUE(tree.contains(70)) << "Tree should contain right child value";
}

TEST_F(BinaryTreeSetTests, ContainsNonExistentValue)
{
    tree.insert(42);
    tree.insert(30);
    tree.insert(70);

    EXPECT_FALSE(tree.contains(100)) << "Tree should not contain non-existent value";
    EXPECT_FALSE(tree.contains(0)) << "Tree should not contain non-existent value";
    EXPECT_FALSE(tree.contains(-1)) << "Tree should not contain non-existent value";
}

TEST_F(BinaryTreeSetTests, ContainsEmptyTree)
{
    EXPECT_FALSE(tree.contains(42)) << "Empty tree should not contain any value";
    EXPECT_FALSE(tree.contains(0)) << "Empty tree should not contain any value";
}

TEST_F(BinaryTreeSetTests, FindExistingValue)
{
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);

    BinaryNode<int> *found = tree.find(30);
    EXPECT_NE(found, nullptr) << "Find should return non-null for existing value";
    EXPECT_EQ(found->value(), 30) << "Found node should have correct value";

    found = tree.find(50);
    EXPECT_NE(found, nullptr) << "Find should return non-null for root value";
    EXPECT_EQ(found->value(), 50) << "Found node should have correct value";
}

TEST_F(BinaryTreeSetTests, FindNonExistentValue)
{
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);

    EXPECT_EQ(tree.find(100), nullptr) << "Find should return null for non-existent value";
    EXPECT_EQ(tree.find(0), nullptr) << "Find should return null for non-existent value";
}

TEST_F(BinaryTreeSetTests, FindEmptyTree)
{
    EXPECT_EQ(tree.find(42), nullptr) << "Find should return null in empty tree";
}

//? Test removal operations
TEST_F(BinaryTreeSetTests, EraseLeafNode)
{
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);

    EXPECT_TRUE(tree.erase(30)) << "Erase should return true for existing leaf node";
    EXPECT_EQ(tree.size(), 2) << "Size should decrease by 1";
    EXPECT_FALSE(tree.contains(30)) << "Tree should not contain erased value";
    EXPECT_TRUE(tree.contains(50)) << "Tree should still contain other values";
    EXPECT_TRUE(tree.contains(70)) << "Tree should still contain other values";
}

TEST_F(BinaryTreeSetTests, EraseNodeWithOneChild)
{
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);

    EXPECT_TRUE(tree.erase(30)) << "Erase should return true for node with one child";
    EXPECT_EQ(tree.size(), 3) << "Size should decrease by 1";
    EXPECT_FALSE(tree.contains(30)) << "Tree should not contain erased value";
    EXPECT_TRUE(tree.contains(20)) << "Left subtree should be preserved";
}

TEST_F(BinaryTreeSetTests, EraseNodeWithTwoChildren)
{
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    EXPECT_TRUE(tree.erase(50)) << "Erase should return true for node with two children";
    EXPECT_EQ(tree.size(), 6) << "Size should decrease by 1";
    EXPECT_FALSE(tree.contains(50)) << "Tree should not contain erased value";
    //? Root should be replaced with inorder successor (60)
    EXPECT_EQ(tree.getRoot()->value(), 60) << "Root should be replaced with inorder successor";
}

TEST_F(BinaryTreeSetTests, EraseRootOnly)
{
    tree.insert(42);

    EXPECT_TRUE(tree.erase(42)) << "Erase should return true for root-only tree";
    EXPECT_EQ(tree.size(), 0) << "Size should be 0 after erasing root";
    EXPECT_TRUE(tree.empty()) << "Tree should be empty";
    EXPECT_EQ(tree.getRoot(), nullptr) << "Root should be null";
    EXPECT_EQ(tree.height(), -1) << "Height should be -1 for empty tree";
}

TEST_F(BinaryTreeSetTests, EraseNonExistentValue)
{
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);

    EXPECT_FALSE(tree.erase(100)) << "Erase should return false for non-existent value";
    EXPECT_EQ(tree.size(), 3) << "Size should remain unchanged";
    EXPECT_TRUE(tree.contains(50)) << "Tree should still contain all original values";
    EXPECT_TRUE(tree.contains(30)) << "Tree should still contain all original values";
    EXPECT_TRUE(tree.contains(70)) << "Tree should still contain all original values";
}

TEST_F(BinaryTreeSetTests, EraseEmptyTree)
{
    EXPECT_FALSE(tree.erase(42)) << "Erase should return false for empty tree";
    EXPECT_EQ(tree.size(), 0) << "Size should remain 0";
    EXPECT_TRUE(tree.empty()) << "Tree should remain empty";
}

//? Test clear operation
TEST_F(BinaryTreeSetTests, ClearPopulatedTree)
{
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);

    tree.clear();

    EXPECT_EQ(tree.size(), 0) << "Size should be 0 after clear";
    EXPECT_TRUE(tree.empty()) << "Tree should be empty after clear";
    EXPECT_EQ(tree.getRoot(), nullptr) << "Root should be null after clear";
    EXPECT_EQ(tree.height(), -1) << "Height should be -1 after clear";
}

TEST_F(BinaryTreeSetTests, ClearEmptyTree)
{
    tree.clear();

    EXPECT_EQ(tree.size(), 0) << "Size should remain 0 after clearing empty tree";
    EXPECT_TRUE(tree.empty()) << "Tree should remain empty";
    EXPECT_EQ(tree.getRoot(), nullptr) << "Root should remain null";
    EXPECT_EQ(tree.height(), -1) << "Height should remain -1";
}

//? Test merge operation
TEST_F(BinaryTreeSetTests, MergeTwoTrees)
{
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);

    BinaryTreeSet<int> otherTree;
    otherTree.insert(20);
    otherTree.insert(40);
    otherTree.insert(60);
    otherTree.insert(80);

    tree.merge(otherTree);

    EXPECT_EQ(tree.size(), 7) << "Merged tree should have 7 elements";
    EXPECT_EQ(otherTree.size(), 4) << "Original tree should remain unchanged";

    //? Check all values are present
    std::vector<int> expectedValues = {20, 30, 40, 50, 60, 70, 80};
    for (int value : expectedValues)
    {
        EXPECT_TRUE(tree.contains(value)) << "Merged tree should contain value: " << value;
    }
}

TEST_F(BinaryTreeSetTests, MergeWithDuplicates)
{
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);

    BinaryTreeSet<int> otherTree;
    otherTree.insert(30);
    otherTree.insert(50);
    otherTree.insert(80);

    tree.merge(otherTree);

    EXPECT_EQ(tree.size(), 4) << "Merged tree should have 4 unique elements";
    EXPECT_TRUE(tree.contains(30)) << "Tree should contain 30";
    EXPECT_TRUE(tree.contains(50)) << "Tree should contain 50";
    EXPECT_TRUE(tree.contains(70)) << "Tree should contain 70";
    EXPECT_TRUE(tree.contains(80)) << "Tree should contain 80";
}

TEST_F(BinaryTreeSetTests, MergeEmptyTree)
{
    tree.insert(50);
    tree.insert(30);

    BinaryTreeSet<int> emptyTree;
    tree.merge(emptyTree);

    EXPECT_EQ(tree.size(), 2) << "Tree size should remain unchanged after merging empty tree";
    EXPECT_TRUE(tree.contains(50)) << "Tree should still contain original values";
    EXPECT_TRUE(tree.contains(30)) << "Tree should still contain original values";
}

TEST_F(BinaryTreeSetTests, MergeIntoEmptyTree)
{
    BinaryTreeSet<int> otherTree;
    otherTree.insert(50);
    otherTree.insert(30);
    otherTree.insert(70);

    tree.merge(otherTree);

    EXPECT_EQ(tree.size(), 3) << "Empty tree should gain 3 elements from merge";
    EXPECT_TRUE(tree.contains(50)) << "Tree should contain merged values";
    EXPECT_TRUE(tree.contains(30)) << "Tree should contain merged values";
    EXPECT_TRUE(tree.contains(70)) << "Tree should contain merged values";
}

//? Test traversal operations
TEST_F(BinaryTreeSetTests, InorderTraversal)
{
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    std::vector<int> visited;
    tree.traverseInorder([&visited](const int &value)
                         { visited.push_back(value); });

    std::vector<int> expected = {20, 30, 40, 50, 60, 70, 80};
    EXPECT_EQ(visited, expected) << "Inorder traversal should visit nodes in ascending order";
}

TEST_F(BinaryTreeSetTests, PreorderTraversal)
{
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);

    std::vector<int> visited;
    tree.traversePreorder([&visited](const int &value)
                          { visited.push_back(value); });

    std::vector<int> expected = {50, 30, 20, 40, 70};
    EXPECT_EQ(visited, expected) << "Preorder traversal should visit root, left subtree, then right subtree";
}

TEST_F(BinaryTreeSetTests, PostorderTraversal)
{
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);

    std::vector<int> visited;
    tree.traversePostorder([&visited](const int &value)
                           { visited.push_back(value); });

    std::vector<int> expected = {20, 40, 30, 70, 50};
    EXPECT_EQ(visited, expected) << "Postorder traversal should visit left subtree, right subtree, then root";
}

TEST_F(BinaryTreeSetTests, TraversalEmptyTree)
{
    std::vector<int> visited;

    tree.traverseInorder([&visited](const int &value)
                         { visited.push_back(value); });
    EXPECT_TRUE(visited.empty()) << "Inorder traversal of empty tree should not call callback";

    visited.clear();
    tree.traversePreorder([&visited](const int &value)
                          { visited.push_back(value); });
    EXPECT_TRUE(visited.empty()) << "Preorder traversal of empty tree should not call callback";

    visited.clear();
    tree.traversePostorder([&visited](const int &value)
                           { visited.push_back(value); });
    EXPECT_TRUE(visited.empty()) << "Postorder traversal of empty tree should not call callback";
}

//? Test height calculation
TEST_F(BinaryTreeSetTests, HeightSingleNode)
{
    tree.insert(42);
    EXPECT_EQ(tree.height(), 0) << "Single node tree should have height 0";
}

TEST_F(BinaryTreeSetTests, HeightBalancedTree)
{
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    EXPECT_EQ(tree.height(), 2) << "Balanced tree with 7 nodes should have height 2";
}

TEST_F(BinaryTreeSetTests, HeightUnbalancedTree)
{
    tree.insert(50);
    tree.insert(40);
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);

    EXPECT_EQ(tree.height(), 4) << "Unbalanced left-heavy tree should have height 4";
}

TEST_F(BinaryTreeSetTests, HeightRightHeavyTree)
{
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);

    EXPECT_EQ(tree.height(), 4) << "Unbalanced right-heavy tree should have height 4";
}

//? Test with different data types
TEST_F(BinaryTreeSetTests, StringTree)
{
    BinaryTreeSet<std::string> stringTree;

    stringTree.insert("banana");
    stringTree.insert("apple");
    stringTree.insert("cherry");
    stringTree.insert("date");

    EXPECT_EQ(stringTree.size(), 4) << "String tree should have 4 elements";
    EXPECT_TRUE(stringTree.contains("apple")) << "String tree should contain 'apple'";
    EXPECT_TRUE(stringTree.contains("banana")) << "String tree should contain 'banana'";
    EXPECT_FALSE(stringTree.contains("grape")) << "String tree should not contain 'grape'";

    std::vector<std::string> visited;
    stringTree.traverseInorder([&visited](const std::string &value)
                               { visited.push_back(value); });

    std::vector<std::string> expected = {"apple", "banana", "cherry", "date"};
    EXPECT_EQ(visited, expected) << "String tree inorder traversal should be alphabetical";
}

TEST_F(BinaryTreeSetTests, DoubleTree)
{
    BinaryTreeSet<double> doubleTree;

    doubleTree.insert(3.14);
    doubleTree.insert(2.71);
    doubleTree.insert(1.41);
    doubleTree.insert(2.23);

    EXPECT_EQ(doubleTree.size(), 4) << "Double tree should have 4 elements";
    EXPECT_TRUE(doubleTree.contains(3.14)) << "Double tree should contain 3.14";
    EXPECT_TRUE(doubleTree.contains(2.71)) << "Double tree should contain 2.71";
    EXPECT_FALSE(doubleTree.contains(1.0)) << "Double tree should not contain 1.0";

    std::vector<double> visited;
    doubleTree.traverseInorder([&visited](const double &value)
                               { visited.push_back(value); });

    std::vector<double> expected = {1.41, 2.23, 2.71, 3.14};
    EXPECT_EQ(visited, expected) << "Double tree inorder traversal should be in ascending order";
}

//? Test edge cases and stress tests
TEST_F(BinaryTreeSetTests, LargeTreeOperations)
{
    //? Insert many elements
    for (int i = 0; i < 100; ++i)
    {
        tree.insert(i);
    }

    EXPECT_EQ(tree.size(), 100) << "Tree should have 100 elements";

    //? Remove half the elements
    for (int i = 0; i < 50; ++i)
    {
        EXPECT_TRUE(tree.erase(i)) << "Should successfully erase element: " << i;
    }

    EXPECT_EQ(tree.size(), 50) << "Tree should have 50 elements after removal";

    //? Verify remaining elements
    for (int i = 50; i < 100; ++i)
    {
        EXPECT_TRUE(tree.contains(i)) << "Tree should still contain element: " << i;
    }

    for (int i = 0; i < 50; ++i)
    {
        EXPECT_FALSE(tree.contains(i)) << "Tree should not contain removed element: " << i;
    }
}

TEST_F(BinaryTreeSetTests, RepeatedInsertAndRemove)
{
    //? Insert and remove the same element multiple times
    for (int i = 0; i < 10; ++i)
    {
        tree.insert(42);
        EXPECT_EQ(tree.size(), 1) << "Size should remain 1 after duplicate inserts";
        EXPECT_TRUE(tree.erase(42)) << "Should successfully erase element";
        EXPECT_EQ(tree.size(), 0) << "Size should be 0 after removal";
        EXPECT_TRUE(tree.empty()) << "Tree should be empty after removal";
    }
}

TEST_F(BinaryTreeSetTests, ComplexTreeStructure)
{
    //? Create a complex tree structure
    tree.insert(50);
    tree.insert(25);
    tree.insert(75);
    tree.insert(12);
    tree.insert(37);
    tree.insert(62);
    tree.insert(87);
    tree.insert(6);
    tree.insert(18);
    tree.insert(31);
    tree.insert(43);
    tree.insert(56);
    tree.insert(68);
    tree.insert(81);
    tree.insert(93);

    EXPECT_EQ(tree.size(), 15) << "Complex tree should have 15 elements";
    EXPECT_EQ(tree.height(), 3) << "Complex tree should have height 3";

    //? Test removal of nodes with different configurations
    EXPECT_TRUE(tree.erase(25)) << "Should remove node with two children";
    EXPECT_EQ(tree.size(), 14) << "Size should decrease by 1";
    EXPECT_FALSE(tree.contains(25)) << "Tree should not contain removed value";

    EXPECT_TRUE(tree.erase(50)) << "Should remove root node";
    EXPECT_EQ(tree.size(), 13) << "Size should decrease by 1";
    EXPECT_FALSE(tree.contains(50)) << "Tree should not contain removed root";

    //? Verify tree structure is maintained
    EXPECT_TRUE(tree.contains(12)) << "Tree should still contain left subtree elements";
    EXPECT_TRUE(tree.contains(75)) << "Tree should still contain right subtree elements";
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}