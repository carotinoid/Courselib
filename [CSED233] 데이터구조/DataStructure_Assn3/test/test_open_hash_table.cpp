#include <string>
#include <sstream>
#include <gtest/gtest.h>
#include "../open_hash_table.h"
#include "../open_hash_function.h"

std::string print_result(OpenHashTable& t) {
    ostringstream os;
    t.print_result(os);
    return os.str();
}

TEST(Q5, Empty) {
    OpenHashFunction hf(5);
    OpenHashTable t(5, &hf);

    EXPECT_EQ(print_result(t), "0 0\n");
}

TEST(Q5, Insert) {
    OpenHashFunction hf(5);
    OpenHashTable t(5, &hf);
    
    t.insert(1); // -> 1
    t.insert(10); // -> 1
    t.insert(100); // -> 1
    EXPECT_EQ(print_result(t), "2 3\n");
}

TEST(Q5, Delete) {
    OpenHashFunction hf(5);
    OpenHashTable t(5, &hf);
    
    t.insert(1); // -> 1
    t.insert(7); // -> 2
    t.insert(103); // -> 4
    t.insert(106); // -> 2
    t.insert(1006); // -> 2
    t.delete_(7);
    EXPECT_EQ(print_result(t), "2 2\n");

    t.delete_(1006);
    t.delete_(106);
    t.insert(1006);
    EXPECT_EQ(print_result(t), "2 1\n");
}

TEST(Q5, Case1) {
    OpenHashFunction hf(4);
    OpenHashTable t(4, &hf);

    t.insert(32615);
    EXPECT_EQ(print_result(t), "0 1\n");
}

TEST(Q5, Case2) {
    OpenHashFunction hf(4);
    OpenHashTable t(4, &hf);

    t.insert(32615);
    t.insert(315);
    t.insert(6468);
    t.insert(94833);
    EXPECT_EQ(print_result(t), "1 2\n");
}

TEST(Q5, Case3) {
    OpenHashFunction hf(4);
    OpenHashTable t(4, &hf);

    t.insert(32615);
    t.insert(315);
    t.insert(6468);
    t.insert(94833);
    t.delete_(32615);
    t.delete_(6468);
    EXPECT_EQ(print_result(t), "1 1\n");
}