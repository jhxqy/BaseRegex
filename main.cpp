//
//  main.cpp
//  Regex
//
//  Created by 贾皓翔 on 2019/8/26.
//  Copyright © 2019 贾皓翔. All rights reserved.
//

#include <iostream>
#include "NFA.hpp"
#include <locale>
#include <codecvt>
using namespace std;



int main(int argc, const char * argv[]) {
    NFA a("hello");
    NFA b("nice!");
    NFA c=NFAOperator::Cnt(a, b);
    
    cout<<1<<endl;
    return 0;
}
