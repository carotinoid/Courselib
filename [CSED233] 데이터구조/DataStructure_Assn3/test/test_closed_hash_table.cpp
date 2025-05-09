#include <string>
#include <sstream>
#include <gtest/gtest.h>
#include "../closed_hash_function.h"
#include "../closed_hash_table.h"

std::string print_table(ClosedHashTable& t) {
    ostringstream os;
    t.print_table(os);
    return os.str();
}

TEST(Q6, Seq) {
    ClosedHashFunction hf(8);
    int d1 = 5;

    int d = hf.seq(d1, 3);
    EXPECT_EQ(d, 1);

    d = hf.seq(d, 3);
    EXPECT_EQ(d, 2);

    d = hf.seq(d, 3);
    EXPECT_EQ(d, 4);

    d = hf.seq(d, 3);
    EXPECT_EQ(d, 3);

    d = hf.seq(d, 3);
    EXPECT_EQ(d, 6);

    d = hf.seq(d, 3);
    EXPECT_EQ(d, 7);

    d = hf.seq(d, 3);
    EXPECT_EQ(d, 5);
}

TEST(Q6, Empty) {
    ClosedHashFunction hf(5);
    ClosedHashTable t(5, 3, 5, &hf);
    EXPECT_EQ(print_table(t), R"(0: EMPTY
1: EMPTY
2: EMPTY
3: EMPTY
4: EMPTY
)");
}

TEST(Q6, InsertWithoutCollision) {
    // Case 1
    ClosedHashFunction hf(4);
    ClosedHashTable t(4, 3, 2, &hf);
    t.insert(32615);
    t.insert(315);
    t.insert(6468);
    t.insert(94833);
    EXPECT_EQ(print_table(t), R"(0: 6468
1: 32615
2: 94833
3: 315
)");
}

TEST(Q6, InsertWithCollision) {
    ClosedHashFunction hf(4);
    ClosedHashTable t(4, 3, 2, &hf);
    t.insert(6468); // 0
    t.insert(103); // 0 (collision) -> 2
    EXPECT_EQ(print_table(t), R"(0: 6468
1: EMPTY
2: 103
3: EMPTY
)");
}

TEST(Q6, InsertFull) {
    // case 2
    ClosedHashFunction hf(4);
    ClosedHashTable t(4, 3, 2, &hf);
    t.insert(32615);
    t.insert(315);
    t.insert(6468);
    t.insert(94833);
    t.insert(22);
    t.insert(24); // ignore this
    EXPECT_EQ(print_table(t), R"(0: 6468
1: 32615
2: 94833
3: 315
FAIL
)");
}

TEST(Q6, InsertFailNotFull) {
    ClosedHashFunction hf(5);
    ClosedHashTable t(5, 3, 2, &hf);
    t.insert(2);
    t.insert(7);
    t.insert(11);
    t.insert(20);
    t.insert(18);
    EXPECT_EQ(print_table(t), R"(0: EMPTY
1: 11
2: 2
3: EMPTY
4: 7
FAIL
)");
}
