//
//  test.cpp
//  test
//
//  Created by 贾皓翔 on 2019/8/29.
//  Copyright © 2019 贾皓翔. All rights reserved.
//

#include <stdio.h>
#include<iostream>
#include "Regex/NFA.hpp"
#include "gtest/gtest.h"
#include "Regex/Tokenizer.hpp"
#include "Regex/Parser.hpp"
using namespace std;
GTEST_TEST(NFATEST, Match)
{
    EdgePool *ep=new EdgePool();
    StatusPool *sp=new StatusPool();
    NFA a(ep,sp,"a");
    EXPECT_TRUE(a.match("a"));
    EXPECT_FALSE(a.match("b"));
    NFA b(ep,sp,"b");
    EXPECT_TRUE(b.match("b"));
    EXPECT_FALSE(b.match("a"));
    NFA c=NFAOperator::Or(a, b);
    EXPECT_TRUE(c.match("a"));
    EXPECT_TRUE(c.match("b"));
    EXPECT_FALSE(c.match("c"));
    NFA d=NFAOperator::Closure(c);
    EXPECT_TRUE(d.match("a"));
    EXPECT_TRUE(d.match("b"));
    EXPECT_TRUE(d.match("bb"));
    EXPECT_TRUE(d.match("ab"));
    EXPECT_TRUE(d.match("ba"));
    EXPECT_TRUE(d.match("aaa"));
    EXPECT_TRUE(d.match("aab"));
    EXPECT_FALSE(d.match("acb"));
    NFA e(ep,sp,"abb");
    EXPECT_TRUE(e.match("abb"));
    EXPECT_FALSE(e.match("acb"));

    NFA f=NFAOperator::Cnt(d, e);
    EXPECT_FALSE(f.match("aabaab"));
    EXPECT_TRUE(f.match("aababb"));
}
TEST(TOKENIZERTEST,Token){
    Tokenizer t(R"((fjoij4f449|43f4g5)*asdfv\n\tdaf\n\\ddaf)");
    EXPECT_TRUE(t.scan()->equal(Token(Token::Tag::SYMBOL,L"(")));
    EXPECT_TRUE(t.scan()->equal(Token(Token::Tag::STR,L"fjoij4f449")));
    EXPECT_TRUE(t.scan()->equal(Token(Token::Tag::OR,L"|")));
    EXPECT_TRUE(t.scan()->equal(Token(Token::Tag::STR,L"43f4g5")));
    EXPECT_TRUE(t.scan()->equal(Token(Token::Tag::SYMBOL,L")")));
    EXPECT_TRUE(t.scan()->equal(Token(Token::Tag::CLOSURE,L"*")));
    EXPECT_TRUE(t.scan()->equal(Token(Token::Tag::STR,L"asdfv")));
    EXPECT_TRUE(t.scan()->equal(Token(Token::Tag::CHAR,L"\n")));
    EXPECT_TRUE(t.scan()->equal(Token(Token::Tag::CHAR,L"\t")));
    EXPECT_TRUE(t.scan()->equal(Token(Token::Tag::STR,L"daf")));
    EXPECT_TRUE(t.scan()->equal(Token(Token::Tag::CHAR,L"\n")));
    EXPECT_TRUE(t.scan()->equal(Token(Token::Tag::CHAR,L"\\")));
    EXPECT_TRUE(t.scan()->equal(Token(Token::Tag::STR,L"ddaf")));
}
TEST(ParserTEST,Parser){

    EXPECT_NO_THROW(Parser(R"((joij4f449|43f4g5)*asdfv\n\tdaf\n\\ddaf)"));
    EXPECT_THROW(Parser(R"((joij4f(449|43f4g5)*asdfv\n\tdaf\n\\ddaf)"),std::runtime_error);
    EXPECT_NO_THROW(Parser(R"((joij4f4(4)9|43f4g5)*asdfv\n\tdaf\n\\ddaf)"));
    EXPECT_NO_THROW(Parser(R"((joij4f4(4|6)*9|43f4g5)*asdfv\n\tdaf\n\\ddaf)"));
    EXPECT_NO_THROW(Parser(R"((joij4f4(4*|6*)*9|43f4g5)*asdfv\n\tdaf\n\\ddaf)"));
    EXPECT_THROW(Parser(R"((joij4f4(4**|6*)*9|43f4g5)*asdfv\n\tdaf\n\\ddaf)"),std::runtime_error);

}

TEST(Regex,Function){
    BaseRegex r1("\\(\\)");
    EXPECT_TRUE(r1.match("()"));
    BaseRegex r2("hello|world");
    EXPECT_TRUE(r2.match("hello"));
    EXPECT_TRUE(r2.match("world"));
//    BaseRegex r3("nice(a*)");


}
