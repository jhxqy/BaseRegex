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
#include "Regex/BaseRegex.hpp"
using namespace std;



int main(int argc, const char * argv[]) {
    BaseRegex regex("(hello*)world|nice!");
    cout<<boolalpha<<regex.match("helloworld")<<endl;
    cout<<boolalpha<<regex.match("hellohelloworld")<<endl;
    cout<<boolalpha<<regex.match("nice!")<<endl;
    cout<<boolalpha<<regex.match("world")<<endl;
    cout<<boolalpha<<regex.match("worl")<<endl;


    return 0;
}
