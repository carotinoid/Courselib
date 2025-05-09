#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tree.h"


TEST(BinaryTree, PrintNodeAndChildren) {
    BinaryTree t;
    t.buildFromString("A(B(D)())(C)");
    EXPECT_EQ(t.printNodeAndChildren(), "A2B1D0C0");

    BinaryTree t2;
    t.buildFromString("A(B)(C()(D))");
    EXPECT_EQ(t.printNodeAndChildren(), "A2B0C1D0");

    BinaryTree t3;
    t.buildFromString("A(B(C()(D()(E)))(F))()");
    EXPECT_EQ(t.printNodeAndChildren(), "A1B2C1D1E0F0");
}

TEST(BinaryTree, PrintNodeAndChildrenEmptyTree) {
    BinaryTree t;
    t.buildFromString("");
    EXPECT_EQ(t.printNodeAndChildren(), "");
}

TEST(BinaryTree, PrintNodeAndChildrenRootOnly) {
    BinaryTree t;
    t.buildFromString("A");
    EXPECT_EQ(t.printNodeAndChildren(), "A0");
}

TEST(BinaryTree, FindHeightOfNode) {
    BinaryTree t;
    t.buildFromString("A(B(D)())(C)");
    EXPECT_EQ(t.findHeightOfNode(t.getRoot(), 'A'), 2);
    EXPECT_EQ(t.findHeightOfNode(t.getRoot(), 'B'), 1);
    EXPECT_EQ(t.findHeightOfNode(t.getRoot(), 'C'), 0);
    EXPECT_EQ(t.findHeightOfNode(t.getRoot(), 'D'), 0);

    BinaryTree t2;
    t2.buildFromString("1(2)(3)");
    EXPECT_EQ(t2.findHeightOfNode(t2.getRoot(), '2'), 0);

    BinaryTree t3;
    t3.buildFromString("1(2()(4))(3()(5))");
    EXPECT_EQ(t3.findHeightOfNode(t3.getRoot(), '1'), 2);
}

TEST(BinaryTree, FindHeightOfNodeNotFound) {
    BinaryTree t;
    t.buildFromString("A(B(D)())(C)");
    EXPECT_EQ(t.findHeightOfNode(t.getRoot(), 'Z'), -1);

    BinaryTree t4;
    t4.buildFromString("4(2(3)(1))(6(5))");
    EXPECT_EQ(t4.findHeightOfNode(t4.getRoot(), '8'), -1);
}

TEST(BinaryTree, FindLevelOfNode) {
    BinaryTree t;
    t.buildFromString("A(B(D)())(C)");
    EXPECT_EQ(t.findLevelOfNode(t.getRoot(), 'A'), 0);
    EXPECT_EQ(t.findLevelOfNode(t.getRoot(), 'B'), 1);
    EXPECT_EQ(t.findLevelOfNode(t.getRoot(), 'C'), 1);
    EXPECT_EQ(t.findLevelOfNode(t.getRoot(), 'D'), 2);

    BinaryTree t2;
    t2.buildFromString("1(2)(3)");
    EXPECT_EQ(t2.findLevelOfNode(t2.getRoot(), '2'), 1);

    BinaryTree t3;
    t3.buildFromString("1(2()(4))(3()(5))");
    EXPECT_EQ(t3.findLevelOfNode(t3.getRoot(), '1'), 0);
}

TEST(BinaryTree, FindLevelOfNodeNotFound) {
    BinaryTree t;
    t.buildFromString("A(B(D)())(C)");
    EXPECT_EQ(t.findLevelOfNode(t.getRoot(), 'Z'), -1);

    BinaryTree t4;
    t4.buildFromString("4(2(3)(1))(6(5))");
    EXPECT_EQ(t4.findLevelOfNode(t4.getRoot(), '8'), -1);
}

TEST(BinaryTree, LevelOrder) {
    BinaryTree t;
    t.buildFromString("A(B(D)())(C)");
    EXPECT_EQ(t.levelOrder(), "A B C D ");

    BinaryTree t2;
    t2.buildFromString("1(2)(3)");
    EXPECT_EQ(t2.levelOrder(), "1 2 3 ");

    BinaryTree t3;
    t3.buildFromString("1(2()(4))(3()(5))");
    EXPECT_EQ(t3.levelOrder(), "1 2 3 4 5 ");

    BinaryTree t4;
    t4.buildFromString("4(2(3)(1))(6(5))");
    EXPECT_EQ(t4.levelOrder(), "4 2 6 3 1 5 ");
}

// TEST(BinaryTree, LevelOrderEmpty) {
//     BinaryTree t;
//     t.buildFromString("");
//     EXPECT_EQ(t.levelOrder(), "");
// }

TEST(BinaryTree, LeafCount) {
    BinaryTree t;
    t.buildFromString("A(B(D)())(C)");
    EXPECT_EQ(t.leafCount(), "2");

    BinaryTree t2;
    t2.buildFromString("1(2(4)(5))(3(6))");
    EXPECT_EQ(t2.leafCount(), "3");
}

// TEST(BinaryTree, LeafCountEmpty) {
//     BinaryTree t;
//     t.buildFromString("");
//     EXPECT_EQ(t.leafCount(), "0");
// }

TEST(BinaryTree, LeafCountRootOnly) {
    BinaryTree t;
    t.buildFromString("A");
    EXPECT_EQ(t.leafCount(), "1");
}

TEST(BinaryTree, GetWidth) {
    BinaryTree t;
    t.buildFromString("A(B(D)())(C)");
    EXPECT_EQ(t.leafCount(), "2");

    BinaryTree t2;
    t2.buildFromString("1(2)(3)");
    EXPECT_EQ(t2.getWidth(), "2");

    BinaryTree t3;
    t3.buildFromString("1(2(4(7))(5))(3(6))");
    EXPECT_EQ(t3.getWidth(), "3");
}

// TEST(BinaryTree, GetWidthEmpty) {
//     BinaryTree t;
//     t.buildFromString("");
//     EXPECT_EQ(t.getWidth(), "-1");
// }

TEST(BinaryTree, GetWidthRootOnly) {
    BinaryTree t;
    t.buildFromString("A");
    EXPECT_EQ(t.getWidth(), "1");
}