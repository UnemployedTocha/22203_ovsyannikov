#include "HashTable.h"
#include <gtest/gtest.h>


TEST(TestValue, Equality){
    Value A;
    Value B(10, 24);
    A = B;
    EXPECT_EQ(A, B);
}

TEST(TestHashTable, Insert) { 
    HashTable A;
    
    for (size_t i = 0; i < 1000; ++i) {
        Value Data(12, 38);
        std::string key = std::to_string(i);
        A.Insert(std::to_string(i), Data);
        EXPECT_FALSE(A.Insert(key, Data));
    }
    A.Clear();
    for (size_t i = 0; i < 1000; ++i) { 
        Value Data;
        std::string key = std::to_string(i);
        EXPECT_TRUE(A.Insert(key, Data));
    }
    
    HashTable B = A;
    for (size_t i = 0; i < 1000; ++i) { 
        Value Data;
        std::string key = std::to_string(i);
        EXPECT_FALSE(B.Insert(key, Data));
    }

    
}

TEST(TestHashTable, OperatorSquareBrackets) {
    
    HashTable A;
    for (int i = 0; i < 1000; ++i) { 
        Value Data(i, i);
        std::string key = std::to_string(i);
        A.Insert(key, Data);
        EXPECT_EQ(A[std::to_string(i)], Data);
    }

    A.Clear();
    for (int i = 1000; i > 0; --i) { 
        Value Data(i, i);
        std::string key = std::to_string(i);
        A.Insert(key, Data);
        EXPECT_EQ(A[std::to_string(i)], Data);
    }
    
}

TEST(TestHashTable, Erase) {
    HashTable A;
    
    for (int i = 0; i < 1000; ++i) {
        Value Data(12, 38);
        A.Insert(std::to_string(i), Data);
    }
    for(int i = 999; i >= 0; --i){
        EXPECT_TRUE(A.Erase(std::to_string(i)));
    }
}


TEST(TestHashTable, At) {
    
    HashTable A;
    for (int i = 0; i < 1000; ++i) { 
        Value Data(i, i);
        std::string key = std::to_string(i);
        A.Insert(key, Data);
        EXPECT_EQ(A.At(std::to_string(i)), Data);
    }

    A.Clear();
    for (int i = 1000; i > 0; --i) { 
        Value Data(i, i);
        std::string key = std::to_string(i);
        A.Insert(key, Data);
        EXPECT_EQ(A.At(std::to_string(i)), Data);
    }
    
}



TEST(TestHashTable, Contains) { 
    HashTable A;
    for(int i = 0; i < 100; ++i) EXPECT_FALSE(A.Contains(std::to_string(i)));
    
    for (size_t i = 0; i < 1000; ++i) { 
        Value Data;
        std::string key = std::to_string(i);
        A.Insert(key, Data);
    }
    for(int i = 999; i >= 0; --i) {
        EXPECT_TRUE(A.Contains(std::to_string(i)));
    }
}


TEST(TestHashTable, Equality) {
    HashTable A;
    for (size_t i = 0; i < 1000; ++i) { 
        Value Data;
        std::string key = std::to_string(i);
        EXPECT_TRUE(A.Insert(key, Data));
    }

    HashTable B;
    for (int i = 0; i < 2000; ++i) {
        Value Data;
        std::string key = std::to_string(i);
        EXPECT_TRUE(B.Insert(key, Data));
    }
    for(int i = 1000; i < 2000; ++i) {
        EXPECT_TRUE(B.Erase(std::to_string(i)));
    }

    EXPECT_EQ(A, B);
 }

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
