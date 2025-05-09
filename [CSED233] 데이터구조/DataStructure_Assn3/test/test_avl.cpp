#include <string>
#include <sstream>
#include <gtest/gtest.h>
#include "../avl.h"

std::string printInOrder(AVLTree& t) {
    std::ostringstream os;
    t.printInOrder(os);
    return os.str();
}

std::string printPreOrder(AVLTree& t) {
    std::ostringstream os;
    t.printPreOrder(os);
    return os.str();
}

std::string printFrequency(AVLTree& t) {
    std::ostringstream os;
    t.printFrequency(os);
    return os.str();
}

TEST(Q4, InsertOnce) {
    AVLTree t;
    t.insert('c');

    EXPECT_EQ(printInOrder(t), "(c, 1)\n");
    EXPECT_EQ(printPreOrder(t), "(c, 1)\n");
    EXPECT_EQ(printFrequency(t), "(c, 1)\n");
}

TEST(Q4, InsertMultiple) {
    // case 1
    AVLTree t;
    t.insert('a');
    t.insert('a');
    t.insert('b');
    t.insert('b');
    t.insert('b');
    t.insert('c');
    t.insert('c');
    t.insert('c');
    t.insert('c');

    /* 
        (3, b)
       /      \
    (2, a)    (4, c)
    */
    EXPECT_EQ(printInOrder(t), "(a, 2) (b, 3) (c, 4)\n");
    EXPECT_EQ(printPreOrder(t), "(b, 3) (a, 2) (c, 4)\n");
    EXPECT_EQ(printFrequency(t), "(c, 4) (b, 3) (a, 2)\n");
}

TEST(Q4, InsertSameFreqMultiple) {
    AVLTree t;
    t.insert('d');
    t.insert('d');
    EXPECT_EQ(printPreOrder(t), "(d, 2)\n");
    EXPECT_EQ(printInOrder(t), "(d, 2)\n");
    EXPECT_EQ(printFrequency(t), "(d, 2)\n");

    t.insert('b');
    t.insert('b');
    EXPECT_EQ(printPreOrder(t), "(d, 2) (b, 2)\n");
    EXPECT_EQ(printInOrder(t), "(b, 2) (d, 2)\n");
    EXPECT_EQ(printFrequency(t), "(d, 2) (b, 2)\n");

    t.insert('a');
    t.insert('a');
    EXPECT_EQ(printPreOrder(t), "(b, 2) (a, 2) (d, 2)\n");
    EXPECT_EQ(printInOrder(t), "(a, 2) (b, 2) (d, 2)\n");
    EXPECT_EQ(printFrequency(t), "(d, 2) (b, 2) (a, 2)\n");

    t.insert('c');
    t.insert('c');
    EXPECT_EQ(printPreOrder(t), "(b, 2) (a, 2) (d, 2) (c, 2)\n");
    EXPECT_EQ(printInOrder(t), "(a, 2) (b, 2) (c, 2) (d, 2)\n");
    EXPECT_EQ(printFrequency(t), "(d, 2) (c, 2) (b, 2) (a, 2)\n");

    t.insert('g');
    EXPECT_EQ(printPreOrder(t), "(b, 2) (a, 2) (g, 1) (d, 2) (c, 2)\n");
    EXPECT_EQ(printInOrder(t), "(g, 1) (a, 2) (b, 2) (c, 2) (d, 2)\n");
    EXPECT_EQ(printFrequency(t), "(d, 2) (c, 2) (b, 2) (a, 2) (g, 1)\n");

    t.insert('f');
    t.insert('f');
    t.insert('f');
    EXPECT_EQ(printPreOrder(t), "(b, 2) (g, 1) (a, 2) (d, 2) (c, 2) (f, 3)\n");
    EXPECT_EQ(printInOrder(t), "(g, 1) (a, 2) (b, 2) (c, 2) (d, 2) (f, 3)\n");
    EXPECT_EQ(printFrequency(t), "(f, 3) (d, 2) (c, 2) (b, 2) (a, 2) (g, 1)\n");

    t.insert('e');
    t.insert('e');
    t.insert('e');
    EXPECT_EQ(printPreOrder(t), "(b, 2) (g, 1) (a, 2) (d, 2) (c, 2) (f, 3) (e, 3)\n");
    EXPECT_EQ(printInOrder(t), "(g, 1) (a, 2) (b, 2) (c, 2) (d, 2) (e, 3) (f, 3)\n");
    EXPECT_EQ(printFrequency(t), "(f, 3) (e, 3) (d, 2) (c, 2) (b, 2) (a, 2) (g, 1)\n");
}

TEST(Q4, Case2) {
    AVLTree t;
    t.insert('a');

    /* 
        (1, a)
    */
    EXPECT_EQ(printPreOrder(t), "(a, 1)\n");
    EXPECT_EQ(printInOrder(t), "(a, 1)\n");
    EXPECT_EQ(printFrequency(t), "(a, 1)\n");
}

TEST(Q4, Case3) {
    AVLTree t;
    for (const auto& c : std::string("aabbbccccddddd")) {
        t.insert(c);
    }

    EXPECT_EQ(printPreOrder(t), "(b, 3) (a, 2) (c, 4) (d, 5)\n");
    EXPECT_EQ(printInOrder(t), "(a, 2) (b, 3) (c, 4) (d, 5)\n");
    EXPECT_EQ(printFrequency(t), "(d, 5) (c, 4) (b, 3) (a, 2)\n");
}

TEST(Q4, Case4) {
    AVLTree t;
    for (const auto& c : std::string("aaaaabbbbccccc")) {
        t.insert(c);
    }

    EXPECT_EQ(printPreOrder(t), "(a, 5) (b, 4) (c, 5)\n");
    EXPECT_EQ(printInOrder(t), "(b, 4) (a, 5) (c, 5)\n");
    EXPECT_EQ(printFrequency(t), "(c, 5) (a, 5) (b, 4)\n");
}

TEST(Q4, Case5) {
    AVLTree t;
    for (const auto& c : std::string("~")) {
        t.insert(c);
    } // No runtime error!
}

// TEST(Q4, DeleteDeg2NodeWithPlmNotItsChild) {
//     AVLTree t;
//     t.build("(1, k)[(1, b)[(1, a)][(1, c)]][(3, d)[(2, f)][(3, g)]]");
//     ASSERT_EQ(printPreOrder(t), "(k, 1) (b, 1) (a, 1) (c, 1) (d, 3) (f, 2) (g, 3)\n");
//     ASSERT_EQ(printInOrder(t), "(a, 1) (b, 1) (c, 1) (k, 1) (f, 2) (d, 3) (g, 3)\n");

//     t.insert('k');
//     EXPECT_EQ(printPreOrder(t), "(f, 2) (b, 1) (a, 1) (c, 1) (d, 3) (k, 2) (g, 3)\n");
//     EXPECT_EQ(printInOrder(t), "(a, 1) (b, 1) (c, 1) (f, 2) (k, 2) (d, 3) (g, 3)\n");
//     EXPECT_EQ(printFrequency(t), "(g, 3) (d, 3) (k, 2) (f, 2) (c, 1) (b, 1) (a, 1)\n");
// }

// TEST(Q4, DeleteDeg2NodeWithPlmNotItsChildAndHasRightSubtree) {
//     AVLTree t;
//     t.build("(1, k)[(1, b)[(1, a)][(1, c)]][(3, d)[(2, f)[][(2, h)]][(3, g)]]");
//     ASSERT_EQ(printPreOrder(t), "(k, 1) (b, 1) (a, 1) (c, 1) (d, 3) (f, 2) (h, 2) (g, 3)\n");
//     ASSERT_EQ(printInOrder(t), "(a, 1) (b, 1) (c, 1) (k, 1) (f, 2) (h, 2) (d, 3) (g, 3)\n");

//     t.insert('k');
//     EXPECT_EQ(printPreOrder(t), "(f, 2) (b, 1) (a, 1) (c, 1) (d, 3) (h, 2) (k, 2) (g, 3)\n");
//     EXPECT_EQ(printInOrder(t), "(a, 1) (b, 1) (c, 1) (f, 2) (h, 2) (k, 2) (d, 3) (g, 3)\n");
//     EXPECT_EQ(printFrequency(t), "(g, 3) (d, 3) (k, 2) (h, 2) (f, 2) (c, 1) (b, 1) (a, 1)\n");
// }

// TEST(Q4, DeleteDeg1NodeWithLeftChild) {
//     AVLTree t;
//     t.build("(2, b)[(1, a)][(3, c)[(2, d)][]]");

//     t.insert('c');
//     EXPECT_EQ(printPreOrder(t), "(b, 2) (a, 1) (d, 2) (c, 4)\n");
//     EXPECT_EQ(printInOrder(t), "(a, 1) (b, 2) (d, 2) (c, 4)\n");
//     EXPECT_EQ(printFrequency(t), "(c, 4) (d, 2) (b, 2) (a, 1)\n");
// }

// TEST(Q4, DeleteDeg1NodeWithRightChild) {
//     AVLTree t;
//     t.build("(2, b)[(1, a)][(3, c)[][(3, k)]]");

//     t.insert('c');
//     EXPECT_EQ(printPreOrder(t), "(b, 2) (a, 1) (k, 3) (c, 4)\n");
//     EXPECT_EQ(printInOrder(t), "(a, 1) (b, 2) (k, 3) (c, 4)\n");
//     EXPECT_EQ(printFrequency(t), "(c, 4) (k, 3) (b, 2) (a, 1)\n");
// }

// TEST(Q4, DeleteLLCase) {
//     AVLTree t;
//     t.build("(10, a)[(5, b)[(3, d)[][(4, h)]][(7, e)[][(9, i)]]][(20, c)[(15, f)[(13, j)][]][(25, g)]]");

//     t.insert('g');
//     EXPECT_EQ(printPreOrder(t), "(a, 10) (b, 5) (d, 3) (h, 4) (e, 7) (i, 9) (f, 15) (j, 13) (c, 20) (g, 26)\n");
//     EXPECT_EQ(printInOrder(t), "(d, 3) (h, 4) (b, 5) (e, 7) (i, 9) (a, 10) (j, 13) (f, 15) (c, 20) (g, 26)\n");
// }

// TEST(Q4, DeleteLRCase) {
//     AVLTree t;
//     t.build("(10, a)[(5, b)[(3, d)[][(4, h)]][(7, e)[][(9, i)]]][(20, c)[(15, f)[][(17, j)]][(25, g)]]");

//     t.insert('g');
//     EXPECT_EQ(printPreOrder(t), "(a, 10) (b, 5) (d, 3) (h, 4) (e, 7) (i, 9) (j, 17) (f, 15) (c, 20) (g, 26)\n");
//     EXPECT_EQ(printInOrder(t), "(d, 3) (h, 4) (b, 5) (e, 7) (i, 9) (a, 10) (f, 15) (j, 17) (c, 20) (g, 26)\n");
// }

// TEST(Q4, DeleteRLCase) {
//     AVLTree t;
//     t.build("(9, c)[(5, a)[(2, b)][(7, i)[(6, j)][]]][(11, d)[(10, e)[(9, g)][]][(15, f)[(14, h)][]]]");

//     t.insert('b');
//     EXPECT_EQ(printPreOrder(t), "(c, 9) (j, 6) (a, 5) (b, 3) (i, 7) (d, 11) (e, 10) (g, 9) (f, 15) (h, 14)\n");
//     EXPECT_EQ(printInOrder(t), "(b, 3) (a, 5) (j, 6) (i, 7) (c, 9) (g, 9) (e, 10) (d, 11) (h, 14) (f, 15)\n");
// }

// TEST(Q4, DeleteRRCase) {
//     AVLTree t;
//     t.build("(9, c)[(5, a)[(2, b)][(7, i)[][(8, j)]]][(11, d)[(10, e)[(9, g)][]][(15, f)[(14, h)][]]]");

//     t.insert('b');
//     EXPECT_EQ(printPreOrder(t), "(c, 9) (i, 7) (a, 5) (b, 3) (j, 8) (d, 11) (e, 10) (g, 9) (f, 15) (h, 14)\n");
//     EXPECT_EQ(printInOrder(t), "(b, 3) (a, 5) (i, 7) (j, 8) (c, 9) (g, 9) (e, 10) (d, 11) (h, 14) (f, 15)\n");
// }

// TEST(Q4, DeletePreferRR) {
//     AVLTree t;
//     t.build("(7, c)[(6, b)[(5, a)][]][(11, d)[(10, e)[(9, g)][]][(15, f)[(14, h)][]]]");

//     t.insert('a');
//     EXPECT_EQ(printPreOrder(t), "(d, 11) (c, 7) (b, 6) (a, 6) (e, 10) (g, 9) (f, 15) (h, 14)\n");
//     EXPECT_EQ(printInOrder(t), "(a, 6) (b, 6) (c, 7) (g, 9) (e, 10) (d, 11) (h, 14) (f, 15)\n");
// }

// TEST(Q4, DeletePreferLL) {
//     AVLTree t;
//     t.build("(10, a)[(5, b)[(3, d)[][(4, g)]][(6, e)[][(7, h)]]][(12, c)[][(13, f)]]");

//     t.insert('f');
//     EXPECT_EQ(printPreOrder(t), "(b, 5) (d, 3) (g, 4) (a, 10) (e, 6) (h, 7) (c, 12) (f, 14)\n");
//     EXPECT_EQ(printInOrder(t), "(d, 3) (g, 4) (b, 5) (e, 6) (h, 7) (a, 10) (c, 12) (f, 14)\n");
// }
