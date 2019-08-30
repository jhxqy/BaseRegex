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
using namespace std;

TEST(NFATEST,HandlerTrueReturn)
{
    NFA a("a");
    EXPECT_TRUE(a.match("a"));
    EXPECT_FALSE(a.match("b"));
    NFA b("b");
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

    NFA e("abb");
    
    EXPECT_TRUE(e.match("abb"));
    EXPECT_FALSE(e.match("acb"));

    NFA f=NFAOperator::Cnt(d, e);
    EXPECT_FALSE(f.match("aabaab"));
    EXPECT_TRUE(f.match("aababb"));

}
