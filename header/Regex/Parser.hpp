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
 factor    -> (Regex)|STR|CHAR
 */


/*
 RegexList -> Regex RegexList|ε
 Regex     -> term R'
 R'        -> + term R'|ε
 term      -> factor T'
 T'        -> *|ε
 factor    -> (Regex)|STR|CHAR
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
    void RegexList(){
        if (nowToken==nullptr) {
            return ;
        }
        switch (nowToken->getTag()) {
            case Token::Tag::SYMBOL:
            case Token::Tag::CHAR:
            case Token::Tag::STR:
                Regex();
                RegexList();
                break;
            default:
                
                break;
        }
    }
    void Regex(){
        term();
        Rp();
    }
    void Rp(){

        if (nowToken!=nullptr&&nowToken->typeEqual(Token(Token::Tag::OR,L"|"))) {
            matchT(Token(Token::Tag::OR,L"|"));
            term();
            Rp();
        }
    }
    void term(){
        factor();
        Tp();
    }
    void Tp(){

        if(nowToken!=nullptr&&nowToken->typeEqual(Token(Token::Tag::CLOSURE,L"*"))){
            matchT(Token(Token::Tag::CLOSURE,L"*"));
        }
    }
    void factor(){
        if (nowToken==nullptr) {
            throw std::runtime_error("factor error nowToken is nullptr");
        }
        if(nowToken->equal(Token(Token::Tag::SYMBOL,L"("))){
            matchA(Token(Token::Tag::SYMBOL,L"("));
            Regex();
            matchA(Token(Token::Tag::SYMBOL,L")"));
        }else if(nowToken->typeEqual(Token(Token::Tag::STR,L""))){
            matchT(Token(Token::Tag::STR,L""));
            
        }else if(nowToken->typeEqual(Token(Token::Tag::CHAR,L""))){
            matchT(Token(Token::Tag::CHAR,L""));

        }else{
            throw std::runtime_error("factor error");
        }
    }
    
public:
    void Start(){
        RegexList();
    }
    Parser(const std::string &s):t(s){
        nowToken=t.scan();
    }
};

#endif /* Parser_hpp */
