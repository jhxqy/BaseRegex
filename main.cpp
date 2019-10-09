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
#include <vector>
#include "Regex/Tokenizer.hpp"
#include "Regex/Parser.hpp"
using namespace std;



int main(int argc, const char * argv[]) {
    BaseRegex regex("\\(\\)");
    cout<<regex.match("()")<<endl;
    cout<<regex.match("hell")<<endl;

    return 0;
}
