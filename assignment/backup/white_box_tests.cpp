//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2021-01-04
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author JMENO PRIJMENI
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

class MatrixTest: public::testing::Test
{
protected:
    Matrix matrix1x1{};
    Matrix matrix2x2{2, 2};
    Matrix matrix2x3{2, 3};
    Matrix matrix3x2{3, 2};
    Matrix matrix3x3{3, 3};
    Matrix matrix3x4{3, 4};
    Matrix matrix4x4{4, 4};//use4deter()
};

TEST_F(MatrixTest, Constructor){
    EXPECT_NO_THROW(Matrix());

    EXPECT_ANY_THROW(Matrix(0,2));
    EXPECT_ANY_THROW(Matrix(4,0));
    EXPECT_ANY_THROW(Matrix(0,0));
    EXPECT_ANY_THROW(Matrix(-2,2));

    EXPECT_NO_THROW(Matrix(1,1));
    EXPECT_NO_THROW(Matrix(2,3));
    EXPECT_NO_THROW(Matrix(14,5));
}

TEST_F(MatrixTest, Set){
    EXPECT_FALSE(matrix1x1.set(0, 1, 50));
    EXPECT_FALSE(matrix1x1.set(1, 2, 50));
    EXPECT_FALSE(matrix2x2.set(0, 2 , 40));
    EXPECT_FALSE(matrix2x3.set(-1, 2, 0));

    EXPECT_TRUE(matrix1x1.set(0, 0, 100000));
    EXPECT_TRUE(matrix2x2.set(1, 1, 0));
    EXPECT_TRUE(matrix3x3.set(2, 0, -100000));
    EXPECT_TRUE(matrix4x4.set(3, 3, 5.103423));
}

TEST_F(MatrixTest, SetWithVector){
    std::vector<std::vector<double>> for1x1 = {{0}};
    std::vector<std::vector<double>> for2x2 = {{1, 2}, {2, 1}};
    std::vector<std::vector<double>> for3x2 = {{1, 3.3003}, {2.1,2}, {0,0.0000001}};
    std::vector<std::vector<double>> notfor2x2 = {{1, 2, 3}, {3, 2, 3, 4}};

    EXPECT_FALSE(matrix2x2.set(notfor2x2));
    EXPECT_FALSE(matrix1x1.set(for2x2));
    EXPECT_FALSE(matrix2x3.set(for3x2));

    EXPECT_TRUE(matrix1x1.set(for1x1));
    EXPECT_TRUE(matrix2x2.set(for2x2));
    EXPECT_TRUE(matrix3x2.set(for3x2));
}

TEST_F(MatrixTest, Get){
    matrix1x1.set(0, 0, 1000.5);

    EXPECT_ANY_THROW(matrix1x1.get(0, 1));
    EXPECT_ANY_THROW(matrix2x3.get(3, 2));
    EXPECT_ANY_THROW(matrix4x4.get(-4, 4));

    EXPECT_NO_THROW(matrix1x1.get(0, 0));
    EXPECT_NO_THROW(matrix2x3.get(1, 2));

    EXPECT_FLOAT_EQ(matrix1x1.get(0, 0), 1000.5);
}

TEST_F(MatrixTest, OperatorEqual){
    EXPECT_TRUE(matrix4x4.operator==(matrix4x4));
    
    Matrix m1x1_2;
    m1x1_2.set(0, 0, 5);
    EXPECT_FALSE(matrix1x1.operator==(m1x1_2));

    EXPECT_ANY_THROW(matrix3x2.operator==(matrix2x3));
    EXPECT_ANY_THROW(matrix3x3.operator==(matrix4x4));
}

TEST_F(MatrixTest, OperatorAddition){
    
    matrix2x2.set({{1.101, 0}, {0, 1.202}});
    Matrix m2x2add =  matrix2x2.operator+(matrix2x2);
    

    EXPECT_ANY_THROW(matrix1x1.operator+(matrix2x2));
    EXPECT_ANY_THROW(matrix2x3.operator+(matrix3x2));
    EXPECT_ANY_THROW(matrix4x4.operator+(matrix3x4));

    EXPECT_NO_THROW(matrix1x1.operator+(matrix1x1));
    EXPECT_NO_THROW(matrix2x2.operator+(matrix2x2));
    EXPECT_NO_THROW(matrix3x3.operator+(matrix3x3));
    EXPECT_NO_THROW(matrix4x4.operator+(matrix4x4));

    EXPECT_FLOAT_EQ(m2x2add.get(0, 0), 2.202);
    EXPECT_FLOAT_EQ(m2x2add.get(1, 1), 2.404);
    EXPECT_EQ(m2x2add.get(1, 0), 0);
    EXPECT_EQ(matrix3x3.operator+(matrix3x3).get(1,2), 0);
}

TEST_F(MatrixTest, OperatorMulFirstFunc){
    EXPECT_ANY_THROW(matrix1x1.operator*(matrix2x2));
    EXPECT_ANY_THROW(matrix1x1.operator*(matrix2x2));
    EXPECT_ANY_THROW(matrix3x4.operator*(matrix2x3));

    EXPECT_NO_THROW(matrix1x1.operator*(matrix1x1));
    EXPECT_NO_THROW(matrix2x3.operator*(matrix3x2));
    EXPECT_NO_THROW(matrix3x4.operator*(matrix4x4));

    Matrix resultmatrix;
    matrix2x2.set({{15, 5}, 
                  {10, 2.3}});
    matrix2x3.set({{1, 4.4, 2}, 
                   {6, 3, 0}});
    resultmatrix = matrix2x2.operator*(matrix2x3);
    /*
            result=
            0      1     2
        0 (45   ,  81  , 30)
        1 (23.8 , 50.9 , 20)
    */
    EXPECT_EQ(resultmatrix.get(0, 0), 45);
    EXPECT_EQ(resultmatrix.get(0, 1), 81);
    EXPECT_EQ(resultmatrix.get(0, 2), 30);
    EXPECT_FLOAT_EQ(resultmatrix.get(1, 0), 23.8);
    EXPECT_FLOAT_EQ(resultmatrix.get(1, 1), 50.9);
    EXPECT_EQ(resultmatrix.get(1, 2), 20);
}

TEST_F(MatrixTest, OperatorMulSecondFunc){
    Matrix resultmatrix;
    matrix2x2.set({{15, 5}, {10, 2.3}});
    resultmatrix = matrix2x2.operator*(0);

    for (int i = 0; i < 1; i++){
        for (int j = 0; j < 2; j++){
            EXPECT_EQ(resultmatrix.get(i,j), 0);
        }
    }
}

TEST_F(MatrixTest, SolveEquation){

    EXPECT_ANY_THROW(matrix3x2.solveEquation({1, 2}));
    EXPECT_ANY_THROW(matrix2x3.solveEquation({0, 0}));
    EXPECT_ANY_THROW(matrix1x1.solveEquation({0}));
    matrix1x1.set({{1}});
    matrix2x2.set({{2, 0},
                  {1, 4}});
    matrix3x3.set({{0, 2, 1},
                  {4.1, 0, 0},
                  {-2.5, 0, 3}});
    matrix4x4.set({{1, 0, 0, 0},
                  {0, 1, 0, 0},
                  {0, 0, 1, 0},
                  {0, 0, 0, 1}});

    std::vector<double> result1x1, result2x2, result3x3, result4x4;
    result1x1 = matrix1x1.solveEquation({1});
    result2x2 = matrix2x2.solveEquation({0, 2});
    result3x3 = matrix3x3.solveEquation({0, 3.14, 2});
    result4x4 = matrix4x4.solveEquation({0, 0, 0, 0});
    
    EXPECT_EQ(result1x1[0], 1);

    EXPECT_EQ(result2x2[0], 0);
    EXPECT_FLOAT_EQ(result2x2[1], 0.5);

    EXPECT_NEAR(result3x3[0], 0.76585365853, 0.00001);
    EXPECT_NEAR(result3x3[1], -0.65243902439, 0.00001);
    EXPECT_NEAR(result3x3[2], 1.30487804878, 0.00001);

    for(double i: result4x4)
        EXPECT_EQ(i, 0);
}

TEST_F(MatrixTest, Transpose){
    EXPECT_NO_THROW(matrix1x1.transpose());
    // EXPECT_NO_THROW(matrix1x1.transpose());
    // EXPECT_NO_THROW(matrix1x1.transpose());
    // EXPECT_NO_THROW(matrix1x1.transpose());
}

TEST_F(MatrixTest, Inverse){
    EXPECT_ANY_THROW(matrix1x1.inverse());
    EXPECT_ANY_THROW(matrix2x2.inverse());
    EXPECT_ANY_THROW(matrix3x2.inverse());
    EXPECT_ANY_THROW(matrix4x4.inverse());

    matrix2x2.set({{2,1},
                   {3,4}});
    matrix3x3.set({{2, 0, 0},
                   {0, 2, 0},
                   {0, 0, 2}});
    matrix2x2.inverse();
    matrix3x3.inverse();
}


/*** Konec souboru white_box_tests.cpp ***/
