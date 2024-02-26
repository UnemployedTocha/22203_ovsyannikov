#include "HashTable.h"
#include <gtest/gtest.h>

TEST(TestValue, Equality){
    Value A(10, 24);
    Value B(10, 24);
    EXPECT_EQ(A == B, true);

    Value C;
    Value D(0, 0);
    EXPECT_EQ(C == D, true);
    EXPECT_EQ(A == D, false);
}
TEST(TestList, OperatorEquality){
    List A;
    Value data;

    for(size_t i = 0; i < 1000; ++i){
        std::string key = std::to_string(i);
        A.Push(key, data);
    }
    List B;
    B = A;

    EXPECT_EQ(A, B);
    EXPECT_EQ(B, A);

    A = A;
    EXPECT_EQ(A, A);

    A.Push("qwerty", data);
    EXPECT_NE(A, B);
}


TEST(TestHashTable, Constructors){
    HashTable A;
    for(size_t i = 0; i < 1000; ++i){
        Value data;
        std::string key = std::to_string(i);
        A.Insert(key, data);
    }
    HashTable B = A;

    EXPECT_EQ(A, B);
    EXPECT_EQ(B, A);

}

TEST(TestHashTable, Insert) {
    HashTable A;

    for (size_t i = 0; i < 1000; ++i) {
        Value data(12, 38);
        std::string key = std::to_string(i);
        A.Insert(key, data);
        EXPECT_FALSE(A.Insert(key, data));
    }
    A.Clear();
    for (size_t i = 0; i < 1000; ++i) {
        Value Data;
        std::string key = std::to_string(i);
        EXPECT_TRUE(A.Insert(key, Data));
    }

    HashTable B;
    B = A;
    for (size_t i = 0; i < 1000; ++i) {
        Value data;
        std::string key = std::to_string(i);
        EXPECT_FALSE(B.Insert(key, data));
    }

    for (size_t i = 0; i < 1000; ++i) {
        EXPECT_TRUE(B.Contains(std::to_string(i)));
    }
}

TEST(TestHashTable, MoveConstructor) {
    HashTable A;
    for (int i = 100; i > 0; --i) {
        std::string key = std::to_string(i);
        Value data;
        A.Insert(key, data);
    }
    HashTable B = A;
    HashTable C = std::move(B);
    EXPECT_EQ(A, C);
}

TEST(TestHashTable, Swap) {
    HashTable A;
    for (int i = 100; i > 0; --i) {
        std::string key = std::to_string(i);
        Value data;
        A.Insert(key, data);
    }
    HashTable C = A;
    HashTable B;
    for (int i = 200; i > 100; --i) {
        std::string key = std::to_string(i);
        Value data;
        B.Insert(key, data);
    }
    HashTable D = B;
    A.Swap(B);
    EXPECT_EQ(A, D);
    EXPECT_EQ(B, C);
}

TEST(TestHashTable, OperatorSquareBrackets) {

    HashTable A;
    for (int i = 0; i < 1000; ++i) {
        Value data(i, i);
        std::string key = std::to_string(i);
        A.Insert(key, data);
        EXPECT_EQ(A[std::to_string(i)], data);
    }

    A.Clear();
    for (int i = 1000; i > 0; --i) {
        Value data(i, i);
        std::string key = std::to_string(i);
        A.Insert(key, data);
        EXPECT_EQ(A[std::to_string(i)], data);
    }

    A.Clear();
    for (int i = 1000; i > 0; --i) {
        std::string key = std::to_string(i);
        Value data;
        EXPECT_EQ(A[std::to_string(i)], data);
    }
}
TEST(TestHashTable, Erase) {
    HashTable A;

    for (int i = 0; i < 1000; ++i) {
        Value data(12, 38);
        A.Insert(std::to_string(i), data);
    }
    for(int i = 999; i >= 0; --i){
        EXPECT_TRUE(A.Erase(std::to_string(i)));
    }
    EXPECT_FALSE(A.Erase("qwerty"));

    HashTable C;
    Value data;
    C.Insert("alt+f3", data);
    C.Insert("alt+f4", data);
    EXPECT_FALSE(C.Erase("qwerty3"));
    EXPECT_FALSE(C.Erase("qwerty4"));
}
TEST(TestHashTable, At) {

    HashTable A;
    for (int i = 0; i < 1000; ++i) {
        Value data(i, i);
        std::string key = std::to_string(i);
        A.Insert(key, data);
        EXPECT_EQ(A.At(key), data);
    }

    for(size_t i = 1000; i < 2000; ++i){
        std::string key = std::to_string(i);
        EXPECT_THROW(A.At(key), std::runtime_error);
    }


    const HashTable B = A;
    for (int i = 0; i < 1000; ++i) {
        Value data(i, i);
        EXPECT_EQ(B.At(std::to_string(i)), data);
    }
    for(size_t i = 1000; i < 2000; ++i){
        std::string key = std::to_string(i);
        EXPECT_THROW(B.At(key), std::runtime_error);
    }

}
TEST(TestHashTable, Contains) {
    HashTable A;
    for(int i = 0; i < 100; ++i) EXPECT_FALSE(A.Contains(std::to_string(i)));

    for (size_t i = 0; i < 1000; ++i) {
        Value data;
        std::string key = std::to_string(i);
        A.Insert(key, data);
    }
    for(int i = 999; i >= 0; --i) {
        EXPECT_TRUE(A.Contains(std::to_string(i)));
    }
}

TEST(TestHashTable, Empty_Size_Clear) {
    HashTable A;
    for (size_t i = 0; i < 1000; ++i) {
        Value data(i, i);
        std::string key = std::to_string(i);
        A.Insert(key, data);
    }
    EXPECT_EQ(A.Size(), 1000);
    A.Clear();
    EXPECT_EQ(A.Empty(), true);
    EXPECT_EQ(A.Size(), 0);
}

TEST(TestHashTable, Equality) {
    HashTable A;
    for (size_t i = 0; i < 1000; ++i) {
        Value data;
        std::string key = std::to_string(i);
        EXPECT_TRUE(A.Insert(key, data));
    }

    HashTable B;
    for (int i = 0; i < 2000; ++i) {
        Value data;
        std::string key = std::to_string(i);
        EXPECT_TRUE(B.Insert(key, data));
    }
    for(int i = 1000; i < 2000; ++i) {
        EXPECT_TRUE(B.Erase(std::to_string(i)));
    }

    EXPECT_EQ(A == B, true);

    A = A;
    EXPECT_EQ(A == A, true);

    Value Data;
    A.Insert("qwerty", Data);
    EXPECT_EQ(A == B, false);

    A.Erase("qwerty");
    A.Erase("0");
    A.Insert("UNIQUE_KEY", Data);
    EXPECT_EQ(A == B, false);
}

TEST(TestHashTable, Inequality) {
    HashTable A;
    for (size_t i = 0; i < 1000; ++i) {
        Value data;
        std::string key = std::to_string(i);
        EXPECT_TRUE(A.Insert(key, data));
    }

    HashTable B;
    for (int i = 0; i < 2000; ++i) {
        Value data;
        std::string key = std::to_string(i);
        EXPECT_TRUE(B.Insert(key, data));
    }
    for(int i = 1000; i < 2000; ++i) {
        EXPECT_TRUE(B.Erase(std::to_string(i)));
    }

    EXPECT_EQ(A != B, false);
}
int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
