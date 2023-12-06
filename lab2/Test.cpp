#include <gtest/gtest.h>
#include "Interpreter.h"
#include "Utility.h"
#include "Factory.h"
#include "StringOutput.h"
#include "Command.h"
#include <sstream>

TEST(TestInterpretator, TestBigger) {
    Interpreter H;
    std::string out;
    std::istringstream in("1 2 > .");

    H.TextProccesing(in, out);
    EXPECT_EQ(out, "0");

}

TEST(TestInterpretator, TestLess) {
    Interpreter H;
    std::string out;
    std::istringstream in("1 2 < .");

    H.TextProccesing(in, out);
    EXPECT_EQ(out, "1");

}

TEST(TestInterpretator, TestCr) {
    Interpreter H;
    std::string out;
    std::istringstream in("cr cr cr");

    H.TextProccesing(in, out);
    EXPECT_EQ(out, "\n\n\n");
    out.clear();
}

TEST(TestInterpretator, TestDiv) {
    Interpreter H;
    std::string out;
    std::istringstream in1("1 2 / .");

    H.TextProccesing(in1, out);
    EXPECT_EQ(out, "0");
    out.clear();

    std::istringstream in2("5 2 / .");
    H.TextProccesing(in2, out);
    EXPECT_EQ(out, "2");
    out.clear();

    std::istringstream in3("100 0 / .");
    EXPECT_THROW(H.TextProccesing(in3, out), std::runtime_error);
    out.clear();

    std::istringstream in4("1000 / .");
    EXPECT_THROW(H.TextProccesing(in4, out), std::underflow_error);
    out.clear();
}

TEST(TestInterpretator, TestDrop) {
    Interpreter H;
    std::string out;
    std::istringstream in("10 20 30 drop . .");

    H.TextProccesing(in, out);
    EXPECT_EQ(out, "20 10");
    out.clear();
}

TEST(TestInterpretator, TestDup) {
    Interpreter H;
    std::string out;
    std::istringstream in("10 20 300 dup . .");

    H.TextProccesing(in, out);
    EXPECT_EQ(out, "300 300");
    out.clear();
}

TEST(TestInterpretator, TestEmit) {
    Interpreter H;
    std::string out;
    std::istringstream in("79 emit");

    H.TextProccesing(in, out);
    EXPECT_EQ(out, "O");
    out.clear();
}

TEST(TestInterpretator, TestEquality) {
    Interpreter H;
    std::string out;
    std::istringstream in("1400 1400 = .");

    H.TextProccesing(in, out);
    EXPECT_EQ(out, "1");
    out.clear();
}

TEST(TestInterpretator, TestIf) {
    Interpreter H;
    std::string out;

    std::istringstream in1("0 if 4 5 + . else 40 50 + . then ;");
    H.TextProccesing(in1, out);
    EXPECT_EQ(out, "90");
    out.clear();

    std::istringstream in2("1 if 4 5 + . else 40 50 + . then ;");
    H.TextProccesing(in2, out);
    EXPECT_EQ(out, "9");
    out.clear();

    std::istringstream in3("0 if if 1 2 + . else 2 3 + then ; else if 10 20 + . else 20 30 + . then ; then ;");
    H.TextProccesing(in3, out);
    EXPECT_EQ(out, "50");
    out.clear();

    std::istringstream in200("1 if if 1 2 + . else 2 3 + then ; else if 10 20 + . else 20 30 + . then ; then ;");
    H.TextProccesing(in200, out);
    EXPECT_EQ(out, "3");
    out.clear();

    std::istringstream in4("0 if 1 2 + else else 2 3 +");
    EXPECT_THROW(H.TextProccesing(in4, out), std::runtime_error);
    out.clear();

    std::istringstream in5("1 if 1 2 + else else 2 3 +");
    EXPECT_THROW(H.TextProccesing(in5, out), std::runtime_error);
    out.clear();

    std::istringstream in6(" 0 if 1 2 + else 2 3 + then");
    EXPECT_THROW(H.TextProccesing(in6, out), std::runtime_error);
    out.clear();

    std::istringstream in100(" 0 if 1 2 + 2 3 + then");
    EXPECT_THROW(H.TextProccesing(in100, out), std::runtime_error);
    out.clear();

    std::istringstream in300(" 0 if 1 2 + 2 3 + then ;");
    H.TextProccesing(in300, out);
    EXPECT_EQ(out, "");
    out.clear();

    std::istringstream in7("1 if 1 2 + then ");
    EXPECT_THROW(H.TextProccesing(in7, out), std::runtime_error);
    out.clear();

    std::istringstream in8("1 if 1 2 + else then");
    EXPECT_THROW(H.TextProccesing(in8, out), std::runtime_error);
    out.clear();

    std::istringstream in9("1 if DAAAA + else 2 3 + then");
    EXPECT_THROW(H.TextProccesing(in9, out), std::runtime_error);
    out.clear();

    std::istringstream in10("1 if 1 2 + else DAAAA then");
    EXPECT_THROW(H.TextProccesing(in10, out), std::runtime_error);
    out.clear();

    std::istringstream in11("0 if DAAAA + else 2 3 + then");
    EXPECT_THROW(H.TextProccesing(in11, out), std::runtime_error);
    out.clear();

    std::istringstream in12("0 if 1 2 + else DAAAA then");
    EXPECT_THROW(H.TextProccesing(in12, out), std::runtime_error);
    out.clear();

    std::istringstream in13("1 if 1 2 + else 1 2 3 4 5 +");
    EXPECT_THROW(H.TextProccesing(in13, out), std::runtime_error);
    out.clear();

    std::istringstream in14("0 if 1 2 3 4 5 +");
    EXPECT_THROW(H.TextProccesing(in14, out), std::runtime_error);
    out.clear();

    std::istringstream in15("1 if ");
    EXPECT_THROW(H.TextProccesing(in15, out), std::runtime_error);
    out.clear();

    std::istringstream in16("1 if 100 200 300 + then ;");
    H.TextProccesing(in16, out);
    EXPECT_EQ(out, "");
    out.clear();

    std::istringstream in17("0 if if if 1 . then ; then ; else then ;");
    H.TextProccesing(in17, out);
    EXPECT_EQ(out, "");
    out.clear();

    std::istringstream in18("1 if 500 10 / . else if  else if if 1 . then ; then ; then ; then ;");
    H.TextProccesing(in18, out);
    EXPECT_EQ(out, "50");
    out.clear();

    std::istringstream in19("1 if  else if if if then ; else else then ; then;");
    EXPECT_THROW(H.TextProccesing(in19, out), std::runtime_error);
    out.clear();

    std::istringstream in20("0 if if if SUDO CHMOD if then ; else then ; else then;");
    EXPECT_THROW(H.TextProccesing(in20, out), std::runtime_error);
    out.clear();

    std::istringstream in21("0 if if else SUDO then ; if if then ; else then ; then;");
    EXPECT_THROW(H.TextProccesing(in21, out), std::runtime_error);
    out.clear();

    std::istringstream in22("0 if if if else 2 3 + .");
    EXPECT_THROW(H.TextProccesing(in22, out), std::runtime_error);
    out.clear();
}

TEST(TestInterpretator, TestLoop) {
    Interpreter H;
    std::string out;
    std::istringstream in("10 0 do i . loop ;");

    H.TextProccesing(in, out);
    EXPECT_EQ(out, "0 1 2 3 4 5 6 7 8 9");
    out.clear();

    std::istringstream in2("11 1 do 7 . loop ;");
    H.TextProccesing(in2, out);
    EXPECT_EQ(out, "7 7 7 7 7 7 7 7 7 7");
    out.clear();

    std::istringstream in3("20 0 do 1 2 loop ; 0 if do do 21 . loop ; loop ; else 200 . then ;");
    H.TextProccesing(in3, out);
    EXPECT_EQ(out, "200");
    out.clear();

    std::istringstream in4("20 0 do 1 2 loop ; 0 if do do DAAA loop ; loop ; else 200 . then ;");
    EXPECT_THROW(H.TextProccesing(in4, out), std::runtime_error);
    out.clear();

    std::istringstream in5("20 0 do 1 2 loop ; 0 if do do 5 . ");
    EXPECT_THROW(H.TextProccesing(in5, out), std::runtime_error);
    out.clear();

    std::istringstream in6("10 0 do OOP 1 2 loop ;");
    EXPECT_THROW(H.TextProccesing(in6, out), std::runtime_error);
    out.clear();

    std::istringstream in7("10 0 do 1 2 ");
    EXPECT_THROW(H.TextProccesing(in7, out), std::runtime_error);
    out.clear();
}

TEST(TestInterpretator, TestMod) {
    Interpreter H;
    std::string out;
    std::istringstream in("21 2 mod .");

    H.TextProccesing(in, out);
    EXPECT_EQ(out, "1");
    out.clear();
}

TEST(TestInterpretator, TestMul) {
    Interpreter H;
    std::string out;
    std::istringstream in("7 3 * .");

    H.TextProccesing(in, out);
    EXPECT_EQ(out, "21");
    out.clear();
}

TEST(TestInterpretator, TestOver) {
    Interpreter H;
    std::string out;
    std::istringstream in("7 3 over .");

    H.TextProccesing(in, out);
    EXPECT_EQ(out, "7");
    out.clear();
}

TEST(TestInterpretator, TestRot) {
    Interpreter H;
    std::string out;
    std::istringstream in("10 20 30 rot . . .");

    H.TextProccesing(in, out);
    EXPECT_EQ(out, "30 10 20");
    out.clear();
}

TEST(TestInterpretator, TestStringOutput) {
    Interpreter H;
    std::string out;
    std::istringstream in("0 if .\" DAAA\" else .\" NEEET\" then ;");

    H.TextProccesing(in, out);
    EXPECT_EQ(out, "NEEET");
    out.clear();

    std::istringstream in2("0 if .\" DAAA else .\" NEEET\" then ;");
    EXPECT_THROW(H.TextProccesing(in2, out), std::runtime_error);
    out.clear();

    std::istringstream in3("0 if .\" DAAA\" else .\" NEEET then ;");
    EXPECT_THROW(H.TextProccesing(in3, out), std::runtime_error);
    out.clear();
}

TEST(TestInterpretator, TestSub) {
    Interpreter H;
    std::string out;
    std::istringstream in("100 90 - .");

    H.TextProccesing(in, out);
    EXPECT_EQ(out, "10");
    out.clear();
}

TEST(TestInterpretator, TestSwap) {
    Interpreter H;
    std::string out;
    std::istringstream in("250 500 swap . .");

    H.TextProccesing(in, out);
    EXPECT_EQ(out, "250 500");
    out.clear();
}

TEST(TestInterpretator, TestSum) {
    Interpreter H;
    std::string out;
    std::istringstream in("-500 -500 + .");

    H.TextProccesing(in, out);
    EXPECT_EQ(out, "-1000");
    out.clear();
}

TEST(TestInterpretator, TestUtility) {
    std::string out;
    Tokens tokens;

    EXPECT_EQ(isNumber(out), false);
    out.clear();

    tokens.Push("qwerty");
    tokens.Push("12345");
    EXPECT_THROW(CheckSemicolon(tokens), std::runtime_error);
}

TEST(TestInterpretator, TestCommand) {
    Command command;
    Operands operands;
    Tokens tokens;
    std::string output;
    std::istringstream in("123");
    Reader reader(in);

    command.Execute(operands, tokens, output, reader);
    command.Check(tokens, reader);
}

TEST(TestInterpretator, TestInterprerator) {
    Interpreter H;
    std::string out;
    std::istringstream in("QWERTY");

    EXPECT_THROW(H.TextProccesing(in, out), std::runtime_error);
    out.clear();
}


Command *createStringOutput() {
    return new StringOutput();
}
TEST(TestInterpretator, TestFactory) {
    auto pFactory = Factory<Command, std::string, Command*(*)()>::getInstance();
    auto p = std::unique_ptr<Command>(createStringOutput());
    EXPECT_EQ(pFactory->regist3r("if", createStringOutput), false);
    EXPECT_EQ(pFactory->complexFuncRegist3r("if", createStringOutput), false);
}

TEST(TestInterpretator, TestOperands) {
    Operands operands;

    EXPECT_THROW(operands.Top(), std::underflow_error);
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}