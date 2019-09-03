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
    Parser p(R"((joij4f449|43f4g5)*asdfv\n\tdaf\n\\ddaf)");
    p.Start();
    
    return 0;
}
