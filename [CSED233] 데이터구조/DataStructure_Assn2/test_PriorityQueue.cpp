#include <gtest/gtest.h>
#include "heap.h"

TEST(PriorityQueue, DefaultConstructor) {
    PriorityQueue q;
    EXPECT_TRUE(q.empty());
}

TEST(PriorityQueue, Insert) {
    PriorityQueue q;

    q.insert(100, 100);
    EXPECT_FALSE(q.empty());
    EXPECT_EQ(q.printPQ(), "100 ");

    q.insert(300, 300);
    q.insert(200, 200);
    EXPECT_EQ(q.printPQ(), "300 100 200 ");
}

TEST(PriorityQueue, InsertDuplicate) {
    PriorityQueue q;

    q.insert(1, 1);
    q.insert(2, 2);
    q.insert(0, 0);
    ASSERT_EQ(q.printPQ(), "2 1 0 ");

    EXPECT_FALSE(q.insert(1, 1));
    EXPECT_EQ(q.printPQ(), "2 1 0 ");
}

// TEST(PriorityQueue, InsertFull) {
//     PriorityQueue q;

//     for (int i = 0; i < MAX_SIZE; ++i) {
//         q.insert(i, i);
//     }

//     EXPECT_FALSE(q.insert(101, 101));
// }

TEST(PriorityQueue, RemoveMax) {
    PriorityQueue q;
    q.insert(1, 1);
    q.insert(2, 2);
    q.insert(0, 0);
    ASSERT_EQ(q.printPQ(), "2 1 0 ");

    q.removeMax(); // remove 2
    EXPECT_EQ(q.printPQ(), "1 0 ");

    q.removeMax(); // remove 1
    EXPECT_EQ(q.printPQ(), "0 ");

    q.removeMax(); // remove 0
    EXPECT_EQ(q.printPQ(), "");
}

TEST(PriorityQueue, RemoveMaxEmpty) {
    PriorityQueue q;
    EXPECT_FALSE(q.removeMax());
}

TEST(PriorityQueue, GetMax) {
    PriorityQueue q;
    q.insert(1, 1);
    q.insert(2, 2);
    q.insert(0, 0);

    auto m = q.getMax();
    EXPECT_EQ(m.priority, 2);
    EXPECT_EQ(m.value, 2);
}

TEST(PriorityQueue, ChangeMax) {
    PriorityQueue q;
    q.insert(1, 1);
    q.insert(2, 2);
    q.insert(0, 0);

    q.changeMax(0); // 0 -> 3
    EXPECT_EQ(q.printPQ(), "3 1 2 ");
    auto m = q.getMax();
    EXPECT_EQ(m.priority, 3);
    EXPECT_EQ(m.value, 3);
}

TEST(PriorityQueue, ChangeMaxNotFound) {
    PriorityQueue q;
    q.insert(1, 1);
    q.insert(2, 2);
    q.insert(0, 0);

    EXPECT_FALSE(q.changeMax(100));
    EXPECT_EQ(q.printPQ(), "2 1 0 ");
}

TEST(PriorityQueue, ChangeMaxOfMax) {
    PriorityQueue q;
    q.insert(1, 1);
    q.insert(2, 2);
    q.insert(0, 0);

    EXPECT_TRUE(q.changeMax(2));
    auto m = q.getMax();
    EXPECT_EQ(m.value, 3);
    EXPECT_EQ(m.priority, 3);
    EXPECT_EQ(q.printPQ(), "3 1 0 ");
}