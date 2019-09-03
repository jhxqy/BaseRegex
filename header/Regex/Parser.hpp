//
//  Parser.hpp
//  Regex
//
//  Created by 贾皓翔 on 2019/9/3.
//  Copyright © 2019 贾皓翔. All rights reserved.
//

#ifndef Parser_hpp
#define Parser_hpp

#include <stdio.h>
#include "Tokenizer.hpp"
#include <string>
#include <stdexcept>
/*
 RegexList -> Regex RegexList|ε
 Regex     -> Regex + term|term
 term      -> factor *|factor
 factor    -> (RegexList)|STR|CHAR
 */


/*
 RegexList -> Regex RegexList|ε
 Regex     -> term R'
 R'        -> + term R'|ε
 term      -> factor T'
 T'        -> *|ε
 factor    -> (RegexList)|STR|CHAR
 */



class Parser{
    Tokenizer t;
    Token *nowToken;
    void matchA(Token token){
        if(nowToken->equal(token)){
            delete nowToken;
            nowToken=t.scan();
        }else{
            throw std::runtime_error("Parser error");
        }
    }
    void matchT(Token token){
        if(nowToken->typeEqual(token)){
            delete nowToken;
            nowToken=t.scan();
        }else{
            throw std::runtime_error("Parser error");
        }
    }
    void RegexList();
    void Regex();
    void Rp();
    void term();
    void Tp();
    void factor();
    
public:
    void Start(){
        RegexList();
        if(nowToken!=nullptr){
            throw std::runtime_error("parse not end");
        }
    }
    Parser(const std::string &s):t(s){
        nowToken=t.scan();
    }
};

#endif /* Parser_hpp */
