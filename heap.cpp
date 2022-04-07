#include "MinHeap.h"
#include "gtest/gtest.h"
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <vector>

using namespace std;

/*
These tests are only usable if you used a vector<pair<T, int>> container to store the heap.

The tests below use a very simple vec() function for every MinHeap, which is implemented
in the public members of the MinHeap.h file. This function should just return the heap vector.

Please remember to delete your vec() function after running the tests, as it should NOT
be included in the final submission.
*/

TEST(HeapTest, EmptyRemove) {
    MinHeap<string> test(3);
    EXPECT_THROW(test.remove(), std::out_of_range);
}

TEST(HeapTest, EmptyPeek) {
    MinHeap<string> test(5);
    EXPECT_THROW(test.peek(), std::out_of_range);
}

TEST(HeapTest, AddNominal1) {  // Testing add 3-ary.
    MinHeap<string> test(3);
    test.add("nona", 1);
    test.add("lisa", 6);
    test.add("mika", 5);
    test.add("jenny", 3);
    test.add("billy", 4);
    test.add("ryan", 2);

    vector<pair<string, int>> sample;
    pair<string, int> nona;
    nona.first = "nona";
    nona.second = 1;

    pair<string, int> ryan;
    ryan.first = "ryan";
    ryan.second = 2;

    pair<string, int> jenny;
    jenny.first = "jenny";
    jenny.second = 3;

    pair<string, int> billy;
    billy.first = "billy";
    billy.second = 4;

    pair<string, int> mika;
    mika.first = "mika";
    mika.second = 5;

    pair<string, int> lisa;
    lisa.first = "lisa";
    lisa.second = 6;

    sample.push_back(nona);
    sample.push_back(ryan);
    sample.push_back(mika);
    sample.push_back(jenny);
    sample.push_back(lisa);
    sample.push_back(billy);

    EXPECT_EQ(sample, test.vec());
}

TEST(HeapTest, AddNominal2) {  // Testing add 5-ary.
    MinHeap<string> test(5);
    test.add("ryan", 2);
    test.add("lisa", 6);
    test.add("mika", 5);
    test.add("jenny", 3);
    test.add("billy", 4);
    test.add("lou", 7);
    test.add("nona", 1);

    vector<pair<string, int>> sample;
    pair<string, int> nona;
    nona.first = "nona";
    nona.second = 1;

    pair<string, int> ryan;
    ryan.first = "ryan";
    ryan.second = 2;

    pair<string, int> jenny;
    jenny.first = "jenny";
    jenny.second = 3;

    pair<string, int> billy;
    billy.first = "billy";
    billy.second = 4;

    pair<string, int> mika;
    mika.first = "mika";
    mika.second = 5;

    pair<string, int> lisa;
    lisa.first = "lisa";
    lisa.second = 6;

    pair<string, int> lou;
    lou.first = "lou";
    lou.second = 7;

    sample.push_back(nona);
    sample.push_back(ryan);
    sample.push_back(mika);
    sample.push_back(jenny);
    sample.push_back(billy);
    sample.push_back(lou);
    sample.push_back(lisa);

    EXPECT_EQ(sample, test.vec());
}

TEST(HeapTest, AddNominal3) {  // Testing add 5-ary with two values of same priority.
    MinHeap<string> test(5);
    test.add("ryan", 2);
    test.add("lisa", 6);
    test.add("mika", 5);
    test.add("jenny", 3);
    test.add("billy", 4);
    test.add("lou", 7);
    test.add("nona", 1);
    test.add("moon", 1);

    vector<pair<string, int>> sample;
    pair<string, int> nona;
    nona.first = "nona";
    nona.second = 1;

    pair<string, int> moon;
    moon.first = "moon";
    moon.second = 1;

    pair<string, int> ryan;
    ryan.first = "ryan";
    ryan.second = 2;

    pair<string, int> jenny;
    jenny.first = "jenny";
    jenny.second = 3;

    pair<string, int> billy;
    billy.first = "billy";
    billy.second = 4;

    pair<string, int> mika;
    mika.first = "mika";
    mika.second = 5;

    pair<string, int> lisa;
    lisa.first = "lisa";
    lisa.second = 6;

    pair<string, int> lou;
    lou.first = "lou";
    lou.second = 7;

    // Tie breaks so that items of same priority get sorted FIFO.
    // Change the sample push_backs to reflect your implementation of the tie break.

    sample.push_back(nona);   // 1
    sample.push_back(moon);   // 1
    sample.push_back(mika);   // 5
    sample.push_back(jenny);  // 3
    sample.push_back(billy);  // 4
    sample.push_back(lou);    // 7
    sample.push_back(lisa);   // 6
    sample.push_back(ryan);   // 2

    EXPECT_EQ(sample, test.vec());
}

TEST(HeapTest, RemoveNominal) {  // Testing delete.
    MinHeap<string> test(3);
    test.add("nona", 1);
    test.add("lisa", 6);
    test.add("mika", 5);
    test.add("jenny", 3);
    test.add("billy", 4);
    test.add("ryan", 2);

    for (int i = 0; i < 6; i++) {
        test.remove();
    }

    vector<pair<string, int>> sample;

    EXPECT_EQ(sample, test.vec());
}

TEST(HeapTest, EmptyFalse) {
    MinHeap<string> test(4);
    test.add("nona", 1);
    test.add("lisa", 6);
    test.add("mika", 5);
    test.add("jenny", 3);
    test.add("billy", 4);
    test.add("ryan", 2);

    for (int i = 0; i < 6; i++) {
        test.remove();
    }

    EXPECT_EQ(true, test.isEmpty());
}

TEST(HeapTest, EmptyTrue) {
    MinHeap<string> test(4);
    test.add("nona", 1);
    test.add("lisa", 6);
    test.add("mika", 5);
    test.add("jenny", 3);
    test.add("billy", 4);
    test.add("ryan", 2);

    for (int i = 0; i < 5; i++) {
        test.remove();
    }

    EXPECT_EQ(false, test.isEmpty());
}

TEST(HeapTest, Peek) {
    MinHeap<string> test(5);
    test.add("ryan", 2);
    test.add("lisa", 6);
    test.add("mika", 5);
    test.add("jenny", 3);
    test.add("billy", 4);
    test.add("lou", 7);
    test.add("nona", 1);

    vector<pair<string, int>> sample;
    pair<string, int> nona;
    nona.first = "nona";
    nona.second = 1;

    pair<string, int> ryan;
    ryan.first = "ryan";
    ryan.second = 2;

    pair<string, int> jenny;
    jenny.first = "jenny";
    jenny.second = 3;

    pair<string, int> billy;
    billy.first = "billy";
    billy.second = 4;

    pair<string, int> mika;
    mika.first = "mika";
    mika.second = 5;

    pair<string, int> lisa;
    lisa.first = "lisa";
    lisa.second = 6;

    pair<string, int> lou;
    lou.first = "lou";
    lou.second = 7;

    for (int i = 0; i < 4; i++) {
        test.remove();
    }

    EXPECT_EQ("mika", test.peek());
}

TEST(HeapTest, Peek2) {
    MinHeap<string> test(5);
    test.add("ryan", 2);
    test.add("lisa", 6);
    test.add("mika", 5);
    test.add("jenny", 3);
    test.add("billy", 4);
    test.add("lou", 7);
    test.add("nona", 1);
    test.add("moon", 1);

    vector<pair<string, int>> sample;
    pair<string, int> nona;
    nona.first = "nona";
    nona.second = 1;

    pair<string, int> moon;
    moon.first = "moon";
    moon.second = 1;

    pair<string, int> ryan;
    ryan.first = "ryan";
    ryan.second = 2;

    pair<string, int> jenny;
    jenny.first = "jenny";
    jenny.second = 3;

    pair<string, int> billy;
    billy.first = "billy";
    billy.second = 4;

    pair<string, int> mika;
    mika.first = "mika";
    mika.second = 5;

    pair<string, int> lisa;
    lisa.first = "lisa";
    lisa.second = 6;

    pair<string, int> lou;
    lou.first = "lou";
    lou.second = 7;

    test.remove();

    // Tie breaks so that items of same priority get sorted FIFO.
    // Change the expected string output to reflect your implementation of the tie break.

    EXPECT_EQ("moon", test.peek());
}

TEST(HeapTest, Stress) {
    srand(time(0));

    MinHeap<int> test(20);

    int min;
    int secondMin;
    int thirdMin;

    // First input.
    int num = rand() % 1000;
    test.add(num, num);
    min = num;

    // Second.
    num = rand() % 1000;
    if (num < min) {
        secondMin = min;
        min = num;
    } else {
        secondMin = num;
    }
    test.add(num, num);

    // Third.
    num = rand() % 1000;
    if (num > min && num > secondMin) {
        thirdMin = num;
    } else if (num > min && num < secondMin) {
        thirdMin = secondMin;
        secondMin = num;
    } else if (num < min && num < secondMin) {
        thirdMin = secondMin;
        secondMin = min;
        min = num;
    }
    test.add(num, num);

    // Adding more numbers.
    for (int i = 0; i < 300; i++) {
        int num = rand() % 1000;

        if (num < min) {
            thirdMin = secondMin;
            secondMin = min;
            min = num;
        } else if (num < secondMin) {
            thirdMin = secondMin;
            secondMin = num;
        } else if (num < thirdMin) {
            thirdMin = num;
        }

        test.add(num, num);
    }

    test.remove();
    test.remove();

    EXPECT_EQ(thirdMin, test.peek());
}