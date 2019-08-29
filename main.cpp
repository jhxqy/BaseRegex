//
//  main.cpp
//  Regex
//
//  Created by 贾皓翔 on 2019/8/26.
//  Copyright © 2019 贾皓翔. All rights reserved.
//

#include <iostream>
#include "Regex/NFA.hpp"
#include <locale>
#include <codecvt>
using namespace std;



int main(int argc, const char * argv[]) {
    NFA a("hello");
    NFA b("nice!");
    NFA c=NFAOperator::Cnt(NFAOperator::Closure(NFA("aaa")), NFA("abb"));
    NFA d=NFAOperator::Closure(NFA("ddd"));
    NFA f=NFAOperator::Closure(NFAOperator::Or(NFA("aa"), NFA("bb")));
    cout<<f.match("aa")<<endl;
    cout<<f.match("aabb")<<endl;
    cout<<f.match("aaaa")<<endl;
    cout<<f.match("bbbb")<<endl;

    cout<<d.match("ddd")<<endl;
    cout<<d.match("dddd")<<endl;
    cout<<d.match("ddddd")<<endl;
    cout<<d.match("dddddd")<<endl;

    cout<<c.match("aaaabb")<<endl;
    cout<<c.match("aaaaaaabb")<<endl;
    cout<<c.match("aaaab")<<endl;
    return 0;
}
