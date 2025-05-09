#include <gtest/gtest.h>
#include "../bst.h"

TEST(Q3, Insertion) {
    BinarySearchTree t;
    EXPECT_EQ(t.insertion(2), 0);
    EXPECT_EQ(t.insertion(1), 0);
    EXPECT_EQ(t.insertion(3), 0);

    /* 
        2
       / \
      1   3
    */
    EXPECT_EQ(t.preOrder(), "2 1 3");
    EXPECT_EQ(t.inOrder(), "1 2 3");
}

TEST(Q3, InsertionExisting) {
    BinarySearchTree t;
    ASSERT_EQ(t.insertion(2), 0);
    ASSERT_EQ(t.insertion(1), 0);
    ASSERT_EQ(t.insertion(3), 0);
    
    EXPECT_EQ(t.insertion(2), -1);

    /* 
        2
       / \
      1   3
    */
    EXPECT_EQ(t.preOrder(), "2 1 3");
    EXPECT_EQ(t.inOrder(), "1 2 3");
}

TEST(Q3, DeletionLeafNode) {
    BinarySearchTree t;
    ASSERT_EQ(t.insertion(2), 0);
    ASSERT_EQ(t.insertion(1), 0);
    ASSERT_EQ(t.insertion(3), 0);

    EXPECT_EQ(t.deletion(1), 0);

    /* 
        2
       / \
      X   3
    */
    EXPECT_EQ(t.preOrder(), "2 3");
    EXPECT_EQ(t.inOrder(), "2 3");
}

TEST(Q3, DeletionOrder1NodeWithLeftChild) {
    BinarySearchTree t;
    ASSERT_EQ(t.insertion(2), 0);
    ASSERT_EQ(t.insertion(1), 0);
    ASSERT_EQ(t.insertion(5), 0);
    ASSERT_EQ(t.insertion(3), 0);

    EXPECT_EQ(t.deletion(5), 0);
    /* 
    before:
        2
       / \
      1   5
         /
        3(X)
    after:
        2
       / \
      1   3
    */

    EXPECT_EQ(t.preOrder(), "2 1 3");
    EXPECT_EQ(t.inOrder(), "1 2 3");
}

TEST(Q3, DeletionOrder1NodeWithRightChild) {
    BinarySearchTree t;
    ASSERT_EQ(t.insertion(2), 0);
    ASSERT_EQ(t.insertion(1), 0);
    ASSERT_EQ(t.insertion(5), 0);
    ASSERT_EQ(t.insertion(7), 0);

    EXPECT_EQ(t.deletion(5), 0);
    /* 
    before:
        2
       / \
      1   5 (X)
           \
            7
    after:
        2
       / \
      1   7
    */

    EXPECT_EQ(t.preOrder(), "2 1 7");
    EXPECT_EQ(t.inOrder(), "1 2 7");
}

TEST(Q3, DeletionOrder2Node) {
    BinarySearchTree t;
    ASSERT_EQ(t.insertion(2), 0);
    ASSERT_EQ(t.insertion(1), 0);
    ASSERT_EQ(t.insertion(5), 0);
    ASSERT_EQ(t.insertion(3), 0);
    ASSERT_EQ(t.insertion(7), 0);

    EXPECT_EQ(t.deletion(5), 0);
    /* 
    before:
        2
       / \
      1   5
         / \
        3   7
    after:
        2
       / \
      1   7
         /
        3  
    */

    EXPECT_EQ(t.preOrder(), "2 1 7 3");
    EXPECT_EQ(t.inOrder(), "1 2 3 7");
}

TEST(Q3, DeletionOrder2NodeLeftMostHasRightChild) {
    BinarySearchTree t;
    ASSERT_EQ(t.insertion(2), 0);
    ASSERT_EQ(t.insertion(1), 0);
    ASSERT_EQ(t.insertion(5), 0);
    ASSERT_EQ(t.insertion(3), 0);
    ASSERT_EQ(t.insertion(4), 0);
    ASSERT_EQ(t.insertion(7), 0);

    EXPECT_EQ(t.deletion(2), 0);
    /* 
    before:
        2(X)
       / \
      1   5
         / \
        3   7
         \ 
          4
    after:
        3
       / \
      1   5
         / \
        4   7
    */

    EXPECT_EQ(t.preOrder(), "3 1 5 4 7");
    EXPECT_EQ(t.inOrder(), "1 3 4 5 7");
}

TEST(Q3, DeletionNonExisting) {
    BinarySearchTree t;
    ASSERT_EQ(t.insertion(2), 0);
    ASSERT_EQ(t.insertion(1), 0);
    ASSERT_EQ(t.insertion(3), 0);

    /* 
        2
       / \
      1   3
    */
    EXPECT_EQ(t.deletion(10), -1);
}

TEST(Q3, DeletionEmptyTree) {
    BinarySearchTree t;
    EXPECT_EQ(t.deletion(10), -1);
}

TEST(Q3, Sum) {
    BinarySearchTree t;
    ASSERT_EQ(t.insertion(2), 0);
    ASSERT_EQ(t.insertion(1), 0);
    ASSERT_EQ(t.insertion(3), 0);

    /* 
        2
       / \
      1   3
    */
    EXPECT_EQ(t.sum(1), 5); // 2 + 3
}

TEST(Q3, SumLowerThanMin) {
    BinarySearchTree t;
    ASSERT_EQ(t.insertion(2), 0);
    ASSERT_EQ(t.insertion(1), 0);
    ASSERT_EQ(t.insertion(3), 0);

    /* 
        2
       / \
      1   3
    */
    EXPECT_EQ(t.sum(0), 6); // 1 + 2 + 3
}

TEST(Q3, SumLargerThanMax) {
    BinarySearchTree t;
    ASSERT_EQ(t.insertion(2), 0);
    ASSERT_EQ(t.insertion(1), 0);
    ASSERT_EQ(t.insertion(3), 0);

    /* 
        2
       / \
      1   3
    */
    EXPECT_EQ(t.sum(7), 0); // 2 + 3
}

TEST(Q3, SumEmptyTree) {
    BinarySearchTree t;
    EXPECT_EQ(t.sum(0), 0);
}

TEST(Q3, Case1) {
    BinarySearchTree t;
    EXPECT_EQ(t.insertion(4), 0);
    EXPECT_EQ(t.insertion(6), 0);
    EXPECT_EQ(t.insertion(6), -1);
    EXPECT_EQ(t.insertion(7), 0);
    EXPECT_EQ(t.deletion(7), 0);
    EXPECT_EQ(t.preOrder(), "4 6");
    EXPECT_EQ(t.inOrder(), "4 6");
}

TEST(Q3, Case2) {
    BinarySearchTree t;
    EXPECT_EQ(t.insertion(4), 0);
    EXPECT_EQ(t.insertion(2), 0);
    EXPECT_EQ(t.sum(1), 6);
    EXPECT_EQ(t.insertion(10), 0);
    EXPECT_EQ(t.insertion(9), 0);
    EXPECT_EQ(t.insertion(15), 0);
    EXPECT_EQ(t.insertion(1), 0);
    EXPECT_EQ(t.deletion(1), 0);
    EXPECT_EQ(t.deletion(4), 0);
    EXPECT_EQ(t.deletion(10), 0);
    EXPECT_EQ(t.sum(5), 24);
    EXPECT_EQ(t.preOrder(), "9 2 15");
    EXPECT_EQ(t.inOrder(), "2 9 15");
}

TEST(Q3, Case3) {
    BinarySearchTree t;
    EXPECT_EQ(t.deletion(3), -1);
    EXPECT_EQ(t.insertion(10), 0);
    EXPECT_EQ(t.deletion(10), 0);
    EXPECT_EQ(t.sum(2), 0);
    EXPECT_EQ(t.preOrder(), "");
    EXPECT_EQ(t.inOrder(), "");
}

TEST(Q3, Case4) {
    BinarySearchTree t;
    EXPECT_EQ(t.insertion(4), 0);
    EXPECT_EQ(t.insertion(6), 0);
    EXPECT_EQ(t.insertion(6), -1);
    EXPECT_EQ(t.insertion(7), 0);
    EXPECT_EQ(t.deletion(7), 0);
    EXPECT_EQ(t.sum(2), 10);
    EXPECT_EQ(t.preOrder(), "4 6");
    EXPECT_EQ(t.inOrder(), "4 6");
}