//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author JMENO PRIJMENI
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

class EmptyTree : public ::testing::Test
{
protected:
    BinaryTree tree;
};

class NonEmptyTree : public ::testing::Test
{
protected:

    virtual void SetUp() {
        int values[11] = {-10000, -100, -10, -5, -1, 0, 1, 5, 10, 100, 10000};
        for(int i = 0; i < 11; i++)
            tree.InsertNode(values[i]);
    }
    
    BinaryTree tree;

};


TEST_F(EmptyTree, InsertNode){

    ASSERT_TRUE(tree.GetRoot() == NULL);

    //first node insert, value 10, should be root
    std::pair<bool, Node_t *> node = tree.InsertNode(10);
    ASSERT_TRUE(tree.GetRoot() != NULL);
    ASSERT_TRUE(node.second->pParent == NULL);
    EXPECT_TRUE(node.first);
    EXPECT_EQ(node.second->key, 10);

    //second insert with value 10(reinsert)
    std::pair<bool, Node_t *> node_reinsert = tree.InsertNode(10);
    ASSERT_EQ(node.second, node_reinsert.second);
    ASSERT_FALSE(node_reinsert.first);
    EXPECT_EQ(node_reinsert.second, node.second);
    EXPECT_EQ(node_reinsert.second->key, 10);

    //third insert with negative value, should NOT be root
    std::pair<bool, Node_t *> node2 = tree.InsertNode(-100);
    EXPECT_TRUE(node2.second->pParent != NULL);
    EXPECT_TRUE(node2.first);
    EXPECT_EQ(node2.second->key, -100);

    //fourth insert with zero value, this node should now be root
    std::pair<bool, Node_t *> node_zero = tree.InsertNode(0);
    EXPECT_EQ(node_zero.second, tree.GetRoot());
    EXPECT_TRUE(node_zero.second->pParent == NULL);
    EXPECT_TRUE(node.second->pParent != NULL);
    EXPECT_TRUE(node_zero.first);
    EXPECT_EQ(node_zero.second->key, 0);
}

TEST_F(EmptyTree, DeleteNode){
    EXPECT_FALSE(tree.DeleteNode(-10000));
    EXPECT_FALSE(tree.DeleteNode(0));
    EXPECT_FALSE(tree.DeleteNode(10000));
}

TEST_F(EmptyTree, FindNode){
    EXPECT_TRUE(tree.FindNode(-10000) == NULL);
    EXPECT_TRUE(tree.FindNode(0) == NULL);
    EXPECT_TRUE(tree.FindNode(10000) == NULL);
}

TEST_F(NonEmptyTree, DeleteNodeExisting){
    int values[11] = {-10000, -100, -10, -5, -1, 0, 1, 5, 10, 100, 10000};
    for (int i: values){
        EXPECT_TRUE(tree.DeleteNode(i));
        ASSERT_TRUE(tree.FindNode(i) == NULL);
    }
    ASSERT_TRUE(tree.GetRoot() == NULL);
}

TEST_F(NonEmptyTree, DeleteNodeNonExisting){
    int nonvalues[10] = {-9999, -99, -9, -4, -2, 2, 6, 11, 101, 10001};
    for (int i: nonvalues){
        ASSERT_FALSE(tree.DeleteNode(i));
    }
}

TEST_F(NonEmptyTree, FindNodeExisting){
    int values[11] = {-10000, -100, -10, -5, -1, 0, 1, 5, 10, 100, 10000};
    for(int i: values)
        ASSERT_EQ(tree.FindNode(i)->key, i);
}

TEST_F(NonEmptyTree, FindNodeNonExisting){
    int nonvalues[10] = {-9999, -99, -9, -4, -2, 2, 6, 11, 101, 10001};
    for(int i: nonvalues)
        ASSERT_TRUE(tree.FindNode(i) == NULL);
}

TEST_F(NonEmptyTree, InsertNode){
    int allvalues[21] = {-10000, -9999, -100, -99, -10, -9, -5, -4, -2, -1, 
                            0, 1, 2, 5, 6, 10, 11, 100, 101, 10000, 10001};
    std::pair<bool, Node_t *> node;
    for(int i: allvalues){
        node = tree.InsertNode(i);
        if(i%5 == 0 || i == 1 || i == -1){
            ASSERT_FALSE(node.first);
            ASSERT_EQ(node.second, tree.FindNode(i));
        }
        else{
            ASSERT_TRUE(node.first);
            ASSERT_EQ(node.second, tree.FindNode(i));
        }
    }
}

TEST_F(NonEmptyTree, Axiom1){
    //check each leaf node if it's color is black
    std::vector<Node_t *> outLeafNodes;
    tree.GetLeafNodes(outLeafNodes);
    for(auto *node: outLeafNodes){
        ASSERT_TRUE(node->color == BinaryTree::BLACK);
    }
}

TEST_F(NonEmptyTree, Axiom2){
    //check all non-leaf nodes - if node is red, check if it's pLeft and pRight nodes are both black 
    std::vector<Node_t *> outNonLeafNodes;
    tree.GetNonLeafNodes(outNonLeafNodes);
    for(auto *node: outNonLeafNodes){
        if (node->color == BinaryTree::RED){
            ASSERT_TRUE(node->pLeft->color == BinaryTree::BLACK);
            ASSERT_TRUE(node->pRight->color == BinaryTree::BLACK);
        }
    }
}

TEST_F(NonEmptyTree, Axiom3){
    std::vector<Node_t *> outLeafNodes;
    tree.GetLeafNodes(outLeafNodes);
    int cmp_len = 0;
    int len = 0;
    //find length to root from first leaf node
    for (Node_t *node = outLeafNodes[0]; node != tree.GetRoot(); node = node->pParent){
        if(node->color == BinaryTree::BLACK)
            cmp_len++; 
    }
    //then compare this length with all other leaf node's lengths
    for (Node_t *node: outLeafNodes){
        for(Node_t *node = outLeafNodes[1]; node != tree.GetRoot(); node = node->pParent){
            if(node->color == BinaryTree::BLACK)
                len++;
        }
        ASSERT_EQ(cmp_len, len);
        len = 0;
    }
}
//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

/*** Konec souboru black_box_tests.cpp ***/
