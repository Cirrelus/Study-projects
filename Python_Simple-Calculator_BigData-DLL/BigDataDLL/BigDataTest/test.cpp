#include "pch.h"
#include "../BigDataDLL/BigData.h"


TEST(PlusTest, OnePlusOne) {
	EXPECT_EQ(std::strcmp(Plus("1", "1"), "2"), 0);
}

TEST(PlusTest, Ten) {
	EXPECT_EQ(std::strcmp(Plus("9", "1"), "10"), 0);
}

TEST(PlusTest, DoubleIntMax) {
	EXPECT_EQ(std::strcmp(Plus("2147483647", "2147483647"), "4294967294"), 0);
}

TEST(PlusTest, FloatTest) {
	EXPECT_EQ(std::strcmp(Plus("1,1", "1,1"), "2,2"), 0);
}

TEST(PlusTest, DifferentDigitNumber) {
	EXPECT_EQ(std::strcmp(Plus("100", "10"), "110"), 0);
}

TEST(PlusTest, Zeros) {
	EXPECT_EQ(std::strcmp(Plus("000", "0"), "0"), 0);
}

TEST(MinusTest, BasicMinus) {
	EXPECT_EQ(std::strcmp(Minus("100", "10"), "90"), 0);
}

TEST(MinusTest, TwentyMinusTen) {
	EXPECT_EQ(std::strcmp(Minus("20", "10"), "10"), 0);
}

TEST(MinusTest, TwoDigitToOne) {
	EXPECT_EQ(std::strcmp(Minus("17", "9"), "8"), 0);
}

TEST(MinusTest, Negative) {
	EXPECT_EQ(std::strcmp(Minus("5", "10"), "-5"), 0);
}

TEST(MultiplyTest, BasicMultiply) {
	EXPECT_EQ(std::strcmp(Multiply("12345", "6789"), "83810205"), 0);
}

TEST(MultiplyTest, NegativeMultiply) {
	EXPECT_EQ(std::strcmp(Multiply("-9", "10"), "-90"), 0);
}

TEST(MultiplyTest, DoubleNegativeMultiply) {
	EXPECT_EQ(std::strcmp(Multiply("-9", "-9"), "81"), 0);
}

TEST(MultiplyTest, DigitMultiply) {
	EXPECT_EQ(std::strcmp(Multiply("9", "10"), "90"), 0);
}

TEST(DivisionTest, BasicDivision) {
	EXPECT_EQ(std::strcmp(Divide("90", "3"), "30"), 0);
}

TEST(DivisionTest, FirstFewer) {
	EXPECT_EQ(std::strcmp(Divide("1", "3"), "0,3"), 0);
}

TEST(DivisionTest, FirstMuchFewer) {
	EXPECT_EQ(std::strcmp(Divide("1", "100"), "0,01"), 0);
}

TEST(DivisionTest, ZeroDivision) {
	try {
		Divide("100", "0");
		EXPECT_TRUE(false);
	}
	catch (std::exception e) {
		EXPECT_TRUE(true);
	}
}

TEST(DivisionTest, FifteenByThree) {
	EXPECT_EQ(std::strcmp(Divide("15", "3"), "5"), 0);
}

TEST(DivisionTest, SixteenByThree) {
	EXPECT_EQ(std::strcmp(Divide("16", "3"), "5,3"), 0);
}