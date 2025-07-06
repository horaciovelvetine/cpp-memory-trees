#include <gtest/gtest.h>
#include <string>
#include "models/binary_node.hpp"

using namespace models;

class BinaryNodeTest : public ::testing::Test
{
};

// Test construction with different data types
TEST(BinaryNodeTest, ConstructorWithInt)
{
  BinaryNode<int> node(42);
  EXPECT_EQ(node.value(), 42) << "Default integer constructor failed";
  EXPECT_EQ(node.left(), nullptr);
  EXPECT_EQ(node.right(), nullptr);

  BinaryNode<int> node0(0);
  EXPECT_EQ(node0.value(), 0) << "Constructor integer w/ 0 value failed";

  BinaryNode<int> nodeNeg(-1);
  EXPECT_EQ(nodeNeg.value(), -1) << "Constructor integer w/ negative value failed";
}

TEST(BinaryNodeTest, ConstructorWithDouble)
{
  BinaryNode<double> node(3.14);
  EXPECT_DOUBLE_EQ(node.value(), 3.14) << "Default double constructor failed";
  EXPECT_EQ(node.left(), nullptr);
  EXPECT_EQ(node.right(), nullptr);

  BinaryNode<double> node0(0.00);
  EXPECT_DOUBLE_EQ(node0.value(), 0.00) << "Constructor double w/ 0.00 value failed";

  BinaryNode<double> nodeNeg(-1.11);
  EXPECT_DOUBLE_EQ(nodeNeg.value(), -1.11) << "Constructor double w/ negative value failed";
}

TEST(BinaryNodeTest, ConstructorWithString)
{
  BinaryNode<std::string> node("test");
  EXPECT_EQ(node.value(), "test") << "Default string constructor 'test' failed";
  EXPECT_EQ(node.left(), nullptr);
  EXPECT_EQ(node.right(), nullptr);

  EXPECT_ANY_THROW(BinaryNode<std::string> emptyNode("")) << "Constructor with empty string did not throw as expected";
}

TEST(BinaryNodeTest, SetAndGetValue)
{
  BinaryNode<int> node(42);
  EXPECT_EQ(node.setValue(24), 24) << "setValue() should return new value";
  EXPECT_EQ(node.value(), 24) << "value() should return updated value after setValue()";

  BinaryNode<std::string> strNode("hello");
  EXPECT_EQ(strNode.setValue("world"), "world");
  EXPECT_EQ(strNode.value(), "world");

  EXPECT_ANY_THROW(strNode.setValue("")) << "Setting empty string should throw";
}

TEST(BinaryNodeTest, SetAndGetLeftRight)
{
  BinaryNode<int> root(1);
  BinaryNode<int> left(2);
  BinaryNode<int> right(3);

  //? Test setting nodes directly
  root.setLeft(left);
  root.setRight(right);

  EXPECT_EQ(root.left()->value(), 2) << "Left node value incorrect";
  EXPECT_EQ(root.right()->value(), 3) << "Right node value incorrect";

  //? Test setting via values
  root.setLeft(4);
  root.setRight(5);

  EXPECT_EQ(root.left()->value(), 4) << "Left node value incorrect after setLeft(value)";
  EXPECT_EQ(root.right()->value(), 5) << "Right node value incorrect after setRight(value)";

  //? Test chaining
  root.setLeft(6)->setRight(7);
  EXPECT_EQ(root.left()->value(), 6) << "Left node value incorrect after chaining";
  EXPECT_EQ(root.right()->value(), 7) << "Right node value incorrect after chaining";

  //? Test with string nodes
  BinaryNode<std::string> strRoot("root");
  strRoot.setLeft("left");
  strRoot.setRight("right");

  EXPECT_EQ(strRoot.left()->value(), "left");
  EXPECT_EQ(strRoot.right()->value(), "right");

  EXPECT_ANY_THROW(strRoot.setLeft("")) << "Setting empty string as left should throw";
  EXPECT_ANY_THROW(strRoot.setRight("")) << "Setting empty string as right should throw";
}

TEST(BinaryNodeTest, StringNodeSpecialCases)
{
  BinaryNode<std::string> node("test");

  //? Test special characters
  EXPECT_NO_THROW(node.setValue("!@#$%^&*()")) << "Setting special characters should not throw";
  EXPECT_EQ(node.value(), "!@#$%^&*()") << "Node value should match special characters that were set";

  EXPECT_NO_THROW(node.setValue("Hello世界")) << "Setting Unicode characters should not throw";
  EXPECT_EQ(node.value(), "Hello世界") << "Node value should match Unicode string that was set";

  //? Test single space character
  EXPECT_NO_THROW(node.setValue(" ")) << "Setting single space character should not throw";
  EXPECT_EQ(node.value(), " ") << "Node value should match single space character that was set";

  //? Test setting children with special characters
  EXPECT_NO_THROW(node.setLeft("$%^")) << "Setting left child with special characters should not throw";
  EXPECT_EQ(node.left()->value(), "$%^") << "Left child value should match special characters that were set";

  EXPECT_NO_THROW(node.setRight(" ")) << "Setting right child with space character should not throw";
  EXPECT_EQ(node.right()->value(), " ") << "Right child value should match space character that was set";
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}