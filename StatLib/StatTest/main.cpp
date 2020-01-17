#include <QCoreApplication>
#include "statlib.h"
#include <gtest/gtest.h>
#include <QDebug>


//class FooTest : public testing::Test{
//	protected:

//		FooTest()
//		{

//		}

//		virtual ~FooTest()
//		{

//		}

//		virtual void SetUp()
//		{

//		}
//		virtual void TearDown()
//		{

//		}
//	};
//TEST_F(FooTest, kek)
//{
//    int a = 1;
//    int b = 1;
//    ASSERT_EQ(a, b);
//}


TEST(Test1, StartTest)
{
    //Check
    ASSERT_EQ(1, 1);
}

TEST(Test2, Rectangular_triangle)
{
    //Input
    double x1 = 1;
    double y1 = 1;
    double x2 = 3;
    double y2 = 1;
    double x3 = 1;
    double y3 = 3;

    //Actual
    double res=0;

    //Expected
    double expected =2;
    ErrCode expCode = SUCCESS;

    //Check
    StatLib classLib;
    ErrCode code = classLib.TriangleAreaSolve(x1, y1, x2, y2, x3, y3, res);
    ASSERT_EQ(expected, res);
    ASSERT_EQ(expCode, code);
}

TEST(Test3, Int_coords_triangle)
{
    //Input
    double x1 = 3;
    double y1 = 4;
    double x2 = 9;
    double y2 = 10;
    double x3 = 20;
    double y3 = 3;

    //Actual
    double res=0;

    //Expected
    double expected =54;
    ErrCode expCode = SUCCESS;

    //Check
    StatLib classLib;
    ErrCode code = classLib.TriangleAreaSolve(x1, y1, x2, y2, x3, y3, res);
    ASSERT_EQ(expected, res);
    ASSERT_EQ(expCode, code);
}

TEST(Test4, Double_negative_coords_triangle)
{
    //Input
    double x1 = -4.5;
    double y1 = -6 ;
    double x2 = 7.5;
    double y2 = -2;
    double x3 = 6.2;
    double y3 = 8;

    //Actual
    double res=0;

    //Expected
    double expected =62.6;
    ErrCode expCode = SUCCESS;

    //Check
    StatLib classLib;
    ErrCode code = classLib.TriangleAreaSolve(x1, y1, x2, y2, x3, y3, res);
    ASSERT_EQ(expected, res);
    ASSERT_EQ(expCode, code);
}
TEST(Test5, Same_apex_in_triangle)
{
    //Input
    double x1 = -4.5;
    double y1 = -6 ;
    double x2 = -4.5;
    double y2 = -6;
    double x3 = 6.2;
    double y3 = 8;

    //Actual
    double res=0;

    //Expected
    //double expected =62.6;
    ErrCode expCode = INVALID_DATA;

    //Check
    StatLib classLib;
    ErrCode code = classLib.TriangleAreaSolve(x1, y1, x2, y2, x3, y3, res);
    //ASSERT_EQ(expected, res);
    ASSERT_EQ(expCode, code);
}

TEST(Test5, Mistake_in_expected_answer)
{
    //Input
    double x1 = -4.5;
    double y1 = -6 ;
    double x2 = 7.5;
    double y2 = -2;
    double x3 = 6.2;
    double y3 = 8;

    //Actual
    double res=0;

    //Expected
    //double expected =62.6;
    double expected =62.3;
    ErrCode expCode = SUCCESS;

    //Check
    StatLib classLib;
    ErrCode code = classLib.TriangleAreaSolve(x1, y1, x2, y2, x3, y3, res);
    ASSERT_EQ(expected, res);
    ASSERT_EQ(expCode, code);
}



int main(int argc, char *argv[])
{

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
