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
#include "Regex/JRegex.hpp"
using namespace std;



int main(int argc, const char * argv[]) {
    Tokenizer t(R"((fjoij4f449|43f4g5)*asdfv\n\tdaf\n\\ddaf)");
    vector<Token*> v;
    Token* token;
    while ((token=t.scan())!=nullptr) {
        v.push_back(token);
    }
    cout<<1<<endl;
    
    return 0;
}
