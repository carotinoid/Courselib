#include <sstream>
#include <gtest/gtest.h>
#include "../sort.h"

TEST(Q1, Case1) {
    sortAlg s;
    s.arr[0] = 42;
    s.arr[1] = 20;
    s.arr[2] = 17;
    s.arr[3] = 13;
    s.arr[4] = 28;
    s.arr[5] = 14;
    s.arr_size = 6;

    ostringstream os;
    s.bubbleSort(os);

    EXPECT_EQ(s.arr[0], 13);
    EXPECT_EQ(s.arr[1], 14);
    EXPECT_EQ(s.arr[2], 17);
    EXPECT_EQ(s.arr[3], 20);
    EXPECT_EQ(s.arr[4], 28);
    EXPECT_EQ(s.arr[5], 42);
    EXPECT_EQ(os.str(), R"(13 42 20 17 14 28
13 14 42 20 17 28
13 14 17 42 20 28
13 14 17 20 42 28
13 14 17 20 28 42
)");
}

TEST(Q1, Length1Array) {
    sortAlg s;
    s.arr[0] = 42;
    s.arr_size = 1;

    ostringstream os;
    s.bubbleSort(os);

    EXPECT_EQ(s.arr[0], 42);
    EXPECT_TRUE(os.str().empty());
}

TEST(Q1, AlreadySorted) {
    sortAlg s;
    s.arr[0] = 13;
    s.arr[1] = 14;
    s.arr[2] = 17;
    s.arr[3] = 20;
    s.arr[4] = 28;
    s.arr[5] = 42;
    s.arr_size = 6;

    ostringstream os;
    s.bubbleSort(os);

    EXPECT_EQ(s.arr[0], 13);
    EXPECT_EQ(s.arr[1], 14);
    EXPECT_EQ(s.arr[2], 17);
    EXPECT_EQ(s.arr[3], 20);
    EXPECT_EQ(s.arr[4], 28);
    EXPECT_EQ(s.arr[5], 42);
    EXPECT_TRUE(os.str().empty());
}

TEST(Q1, Case2) {
    sortAlg s;
    s.arr[0] = 17;
    s.arr[1] = 20;
    s.arr[2] = 2;
    s.arr[3] = 21;
    s.arr[4] = 4;
    s.arr_size = 5;

    ostringstream os;
    s.bubbleSort(os);

    EXPECT_EQ(s.arr[0], 2);
    EXPECT_EQ(s.arr[1], 4);
    EXPECT_EQ(s.arr[2], 17);
    EXPECT_EQ(s.arr[3], 20);
    EXPECT_EQ(s.arr[4], 21);
    EXPECT_EQ(os.str(), R"(2 17 20 4 21
2 4 17 20 21
)");
}

TEST(Q1, Case3) {
    sortAlg s;
    s.arr[0] = 7;
    s.arr[1] = 6;
    s.arr[2] = 5;
    s.arr[3] = 4;
    s.arr[4] = 3;
    s.arr[5] = 2;
    s.arr[6] = 1;
    s.arr_size = 7;

    ostringstream os;
    s.bubbleSort(os);

    EXPECT_EQ(s.arr[0], 1);
    EXPECT_EQ(s.arr[1], 2);
    EXPECT_EQ(s.arr[2], 3);
    EXPECT_EQ(s.arr[3], 4);
    EXPECT_EQ(s.arr[4], 5);
    EXPECT_EQ(s.arr[5], 6);
    EXPECT_EQ(s.arr[6], 7);
    EXPECT_EQ(os.str(), R"(1 7 6 5 4 3 2
1 2 7 6 5 4 3
1 2 3 7 6 5 4
1 2 3 4 7 6 5
1 2 3 4 5 7 6
1 2 3 4 5 6 7
)");
}

TEST(Q2, MergeEvenEven) {
    sortAlg s;
    s.arr[0] = 4;
    s.arr[1] = 2;
    s.arr[2] = 3;
    s.arr[3] = 1;
    s.arr_size = 4;

    bool changed = false;
    s.merge(0, 2, 4, changed);

    EXPECT_EQ(s.arr[0], 4);
    EXPECT_EQ(s.arr[1], 3);
    EXPECT_EQ(s.arr[2], 2);
    EXPECT_EQ(s.arr[3], 1);
    EXPECT_TRUE(changed);
}

TEST(Q2, MergeEvenOdd) {
    sortAlg s;
    s.arr[0] = 4;
    s.arr[1] = 3;
    s.arr[2] = 2;
    s.arr[3] = 5;
    s.arr[4] = 1;
    s.arr_size = 5;

    bool changed = false;
    s.merge(0, 3, 5, changed);

    EXPECT_EQ(s.arr[0], 5);
    EXPECT_EQ(s.arr[1], 4);
    EXPECT_EQ(s.arr[2], 3);
    EXPECT_EQ(s.arr[3], 2);
    EXPECT_EQ(s.arr[4], 1);
    EXPECT_TRUE(changed);
}

TEST(Q2, MergeUnchanged) {
    sortAlg s;
    s.arr[0] = 5;
    s.arr[1] = 4;
    s.arr[2] = 3;
    s.arr[3] = 2;
    s.arr[4] = 1;
    s.arr_size = 5;

    bool changed = false;
    s.merge(0, 2, 5, changed);

    EXPECT_EQ(s.arr[0], 5);
    EXPECT_EQ(s.arr[1], 4);
    EXPECT_EQ(s.arr[2], 3);
    EXPECT_EQ(s.arr[3], 2);
    EXPECT_EQ(s.arr[4], 1);
    EXPECT_FALSE(changed);
}

TEST(Q2, MergeLenOneArray) {
    sortAlg s;
    s.arr[0] = 4;
    s.arr[1] = 5;
    s.arr_size = 2;

    bool changed = false;
    s.merge(0, 1, 2, changed);

    EXPECT_EQ(s.arr[0], 5);
    EXPECT_EQ(s.arr[1], 4);
    EXPECT_TRUE(changed);
}

TEST(Q2, EvenLenArr) {
    sortAlg s;
    s.arr[0] = 36;
    s.arr[1] = 20;
    s.arr[2] = 17;
    s.arr[3] = 13;
    s.arr[4] = 14;
    s.arr[5] = 28;
    s.arr[6] = 15;
    s.arr[7] = 23;
    s.arr_size = 8;

    ostringstream os;
    s.mergeSort(os);

    EXPECT_EQ(s.arr[0], 36);
    EXPECT_EQ(s.arr[1], 28);
    EXPECT_EQ(s.arr[2], 23);
    EXPECT_EQ(s.arr[3], 20);
    EXPECT_EQ(s.arr[4], 17);
    EXPECT_EQ(s.arr[5], 15);
    EXPECT_EQ(s.arr[6], 14);
    EXPECT_EQ(s.arr[7], 13);
    EXPECT_EQ(os.str(), R"(36 20 17 13 28 14 23 15
36 20 17 13 28 23 15 14
36 28 23 20 17 15 14 13
)");
}

TEST(Q2, OddLenArr) {
    sortAlg s;
    s.arr[0] = 36;
    s.arr[1] = 20;
    s.arr[2] = 17;
    s.arr[3] = 13;
    s.arr[4] = 14;
    s.arr[5] = 28;
    s.arr[6] = 15;
    s.arr[7] = 23;
    s.arr[8] = 32;
    s.arr_size = 9;

    ostringstream os;
    s.mergeSort(os);

    EXPECT_EQ(s.arr[0], 36);
    EXPECT_EQ(s.arr[1], 32);
    EXPECT_EQ(s.arr[2], 28);
    EXPECT_EQ(s.arr[3], 23);
    EXPECT_EQ(s.arr[4], 20);
    EXPECT_EQ(s.arr[5], 17);
    EXPECT_EQ(s.arr[6], 15);
    EXPECT_EQ(s.arr[7], 14);
    EXPECT_EQ(s.arr[8], 13);
    EXPECT_EQ(os.str(), R"(36 20 17 13 28 14 23 15 32
36 20 17 13 28 23 15 14 32
36 28 23 20 17 15 14 13 32
36 32 28 23 20 17 15 14 13
)");
}

TEST(Q2, OddLenArrLastNoChange) {
    sortAlg s;
    s.arr[0] = 36;
    s.arr[1] = 20;
    s.arr[2] = 17;
    s.arr[3] = 13;
    s.arr[4] = 14;
    s.arr[5] = 28;
    s.arr[6] = 15;
    s.arr[7] = 23;
    s.arr[8] = 1;
    s.arr_size = 9;

    ostringstream os;
    s.mergeSort(os);

    EXPECT_EQ(s.arr[0], 36);
    EXPECT_EQ(s.arr[1], 28);
    EXPECT_EQ(s.arr[2], 23);
    EXPECT_EQ(s.arr[3], 20);
    EXPECT_EQ(s.arr[4], 17);
    EXPECT_EQ(s.arr[5], 15);
    EXPECT_EQ(s.arr[6], 14);
    EXPECT_EQ(s.arr[7], 13);
    EXPECT_EQ(s.arr[8], 1);
    EXPECT_EQ(os.str(), R"(36 20 17 13 28 14 23 15 1
36 20 17 13 28 23 15 14 1
36 28 23 20 17 15 14 13 1
)");
}


TEST(Q2, OneLenArr) {
    sortAlg s;
    s.arr[0] = 1;
    s.arr_size = 1;

    ostringstream os;
    s.mergeSort(os);

    EXPECT_EQ(s.arr[0], 1);
    EXPECT_EQ(os.str(), "");
}

TEST(Q2, AlreadySorted) {
    sortAlg s;
    s.arr[0] = 42;
    s.arr[1] = 28;
    s.arr[2] = 20;
    s.arr[3] = 17;
    s.arr[4] = 14;
    s.arr[5] = 13;
    s.arr_size = 6;

    ostringstream os;
    s.mergeSort(os);

    EXPECT_EQ(s.arr[0], 42);
    EXPECT_EQ(s.arr[1], 28);
    EXPECT_EQ(s.arr[2], 20);
    EXPECT_EQ(s.arr[3], 17);
    EXPECT_EQ(s.arr[4], 14);
    EXPECT_EQ(s.arr[5], 13);
    EXPECT_TRUE(os.str().empty());
}
