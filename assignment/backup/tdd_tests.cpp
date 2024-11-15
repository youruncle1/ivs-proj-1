//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue test suite
//
// $NoKeywords: $ivs_project_1 $tdd_tests.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2021-01-04
//============================================================================//
/**
 * @file tdd_tests.cpp
 * @author JMENO PRIJMENI
 * 
 * @brief Testy implementace prioritni fronty.
 */

#include "gtest/gtest.h"
#include "tdd_code.h"
#include <iostream>

class NonEmptyQueue : public ::testing::Test
{
protected:
    virtual void SetUp() {
        int values[] = { 10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55 };

        for(int i = 0; i < 14; ++i)
            queue.Insert(values[i]);
    }

    PriorityQueue queue;
};

class EmptyQueue : public ::testing::Test
{
protected:
    PriorityQueue queue;
};

TEST_F(NonEmptyQueue, Insert)
{
    queue.Insert(100);
    EXPECT_EQ(queue.GetHead()->value, 100);

    queue.Insert(0);
    EXPECT_EQ(queue.GetHead()->value, 100);
}

TEST_F(NonEmptyQueue, RemoveAllBackward)
{
    EXPECT_FALSE(queue.Remove(0));
    int values[] = { 5, 10, 15, 20, 30, 40, 50, 55, 60, 65, 70, 80, 85, 90 };
    for(int i = 0; i < 13; ++i)
    {
        EXPECT_TRUE(queue.Remove(values[i])) << i << "values[i]:" << values[i];
        EXPECT_EQ(queue.GetHead()->value, 90);
    }

    queue.Remove(90);
    EXPECT_TRUE(queue.GetHead() == NULL);
}

TEST_F(NonEmptyQueue, RemoveAllForward)
{
    EXPECT_FALSE(queue.Remove(0));

    int values[] = { 90, 85, 80, 70, 65, 60, 55, 50, 40, 30, 20, 15, 10, 5 };
    for(int i = 0; i < 13; ++i)
    {
        EXPECT_TRUE(queue.Remove(values[i]));
        EXPECT_EQ(queue.GetHead()->value, values[i + 1]);
    }

    queue.Remove(5);
    EXPECT_TRUE(queue.GetHead() == NULL);
}

TEST_F(NonEmptyQueue, Find)
{
    int values[] = { 5, 10, 15, 20, 30, 40, 50, 55, 60, 65, 70, 80, 85, 90 };
    for(int i = 0; i < 14; ++i)
    {
        PriorityQueue::Element_t *pElem = queue.Find(values[i]);
        ASSERT_TRUE(pElem != NULL);
        EXPECT_EQ(pElem->value, values[i]);

        EXPECT_TRUE(pElem->pNext == NULL || pElem->pNext->value <= pElem->value);
    }

    EXPECT_TRUE(queue.Find(0) == NULL);
}

TEST_F(NonEmptyQueue, Length)
{
    EXPECT_EQ(queue.Length(), 14);

    queue.Insert(100);

    EXPECT_EQ(queue.Length(), 15);

    queue.Remove(100);

    EXPECT_EQ(queue.Length(), 14);
}


TEST_F(EmptyQueue, Insert)
{
    EXPECT_TRUE(queue.GetHead() == NULL);

    queue.Insert(0);
    ASSERT_TRUE(queue.GetHead() != NULL);
    EXPECT_EQ(queue.GetHead()->value, 0);

    queue.Insert(100);
    ASSERT_TRUE(queue.GetHead() != NULL);
    EXPECT_EQ(queue.GetHead()->value, 100);
}

TEST_F(EmptyQueue, Remove)
{
    EXPECT_FALSE(queue.Remove(0));
}

TEST_F(EmptyQueue, Find)
{
    EXPECT_TRUE(queue.Find(0) == NULL);
}

TEST_F(EmptyQueue, Length)
{
    EXPECT_EQ(queue.Length(), 0);
}

/*** Konec souboru tdd_tests.cpp ***/
