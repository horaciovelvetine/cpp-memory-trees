#include "models/binary_node.hpp"
#include <gtest/gtest.h>
#include <string>

using namespace models;

class BinaryNodeTest : public ::testing::Test
{
};

// Test construction with different data types
TEST(BinaryNodeTest, ConstructorWithInt)
{
    BinaryNode<int> node(42);
    EXPECT_EQ(node.value(), 42) << "Default integer constructor failed";
    const BinaryNode<int> &constNode = node;
    EXPECT_EQ(constNode.left(), nullptr);
    EXPECT_EQ(constNode.right(), nullptr);

    BinaryNode<int> node0(0);
    EXPECT_EQ(node0.value(), 0) << "Constructor integer w/ 0 value failed";

    BinaryNode<int> nodeNeg(-1);
    EXPECT_EQ(nodeNeg.value(), -1) << "Constructor integer w/ negative value failed";
}

TEST(BinaryNodeTest, ConstructorWithDouble)
{
    BinaryNode<double> node(3.14);
    EXPECT_DOUBLE_EQ(node.value(), 3.14) << "Default double constructor failed";
    const BinaryNode<double> &constNode = node;
    EXPECT_EQ(constNode.left(), nullptr);
    EXPECT_EQ(constNode.right(), nullptr);

    BinaryNode<double> node0(0.00);
    EXPECT_DOUBLE_EQ(node0.value(), 0.00) << "Constructor double w/ 0.00 value failed";

    BinaryNode<double> nodeNeg(-1.11);
    EXPECT_DOUBLE_EQ(nodeNeg.value(), -1.11) << "Constructor double w/ negative value failed";
}

TEST(BinaryNodeTest, ConstructorWithString)
{
    BinaryNode<std::string> node("test");
    EXPECT_EQ(node.value(), "test") << "Default string constructor 'test' failed";
    const BinaryNode<std::string> &constNode = node;
    EXPECT_EQ(constNode.left(), nullptr);
    EXPECT_EQ(constNode.right(), nullptr);

    EXPECT_ANY_THROW(BinaryNode<std::string> emptyNode(""))
        << "Constructor with empty string did not throw as expected";
}

TEST(BinaryNodeTest, ReadOnlyAccess)
{
    BinaryNode<int> node(42);

    EXPECT_EQ(node.value(), 42) << "value() should return the stored value";

    const BinaryNode<int> &constNode = node;
    EXPECT_EQ(constNode.left(), nullptr) << "left() should return nullptr for new node";
    EXPECT_EQ(constNode.right(), nullptr) << "right() should return nullptr for new node";

    EXPECT_EQ(constNode.value(), 42) << "const value() should work";
    EXPECT_EQ(constNode.left(), nullptr) << "const left() should work";
    EXPECT_EQ(constNode.right(), nullptr) << "const right() should work";
}

TEST(BinaryNodeTest, StringNodeSpecialCases)
{
    BinaryNode<std::string> node("test");

    EXPECT_NO_THROW(BinaryNode<std::string> specialNode("!@#$%^&*()"))
        << "Constructor with special characters should not throw";
    EXPECT_NO_THROW(BinaryNode<std::string> unicodeNode("Hello世界"))
        << "Constructor with Unicode characters should not throw";
    EXPECT_NO_THROW(BinaryNode<std::string> spaceNode(" ")) << "Constructor with space character should not throw";

    BinaryNode<std::string> specialNode("!@#$%^&*()");
    EXPECT_EQ(specialNode.value(), "!@#$%^&*()") << "Node value should match special characters";

    BinaryNode<std::string> unicodeNode("Hello世界");
    EXPECT_EQ(unicodeNode.value(), "Hello世界") << "Node value should match Unicode string";

    BinaryNode<std::string> spaceNode(" ");
    EXPECT_EQ(spaceNode.value(), " ") << "Node value should match space character";
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}