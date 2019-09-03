//
//  Parser.cpp
//  Regex
//
//  Created by 贾皓翔 on 2019/9/3.
//  Copyright © 2019 贾皓翔. All rights reserved.
//

#include "Parser.hpp"
void Parser::RegexList(){
    if (nowToken==nullptr) {
        return ;
    }
    switch (nowToken->getTag()) {
        case Token::Tag::CHAR:
        case Token::Tag::STR:
            Parser::Regex();
            Parser::RegexList();
            break;
        default:
            if(nowToken->equal(Token(Token::Tag::SYMBOL,L"("))){
                Parser::Regex();
                Parser::RegexList();
            }
            break;
    }
}
void Parser::Regex(){
    Parser::term();
    Parser::Rp();
}
void Parser::Rp(){
    
    if (nowToken!=nullptr&&nowToken->typeEqual(Token(Token::Tag::OR,L"|"))) {
        Parser::matchT(Token(Token::Tag::OR,L"|"));
        Parser::term();
        Parser::Rp();
    }
}

void Parser::term(){
    Parser::factor();
    Parser::Tp();
}
void Parser::Tp(){
    
    if(nowToken!=nullptr&&nowToken->typeEqual(Token(Token::Tag::CLOSURE,L"*"))){
        Parser::matchT(Token(Token::Tag::CLOSURE,L"*"));
    }
}

void Parser::factor(){
    if (nowToken==nullptr) {
        throw std::runtime_error("factor error nowToken is nullptr");
    }
    if(nowToken->equal(Token(Token::Tag::SYMBOL,L"("))){
        Parser::matchA(Token(Token::Tag::SYMBOL,L"("));
        Parser::RegexList();
        if (nowToken==nullptr) {
            throw std::runtime_error("factor error nowToken is nullptr");
        }else{
            Parser::matchA(Token(Token::Tag::SYMBOL,L")"));
        }
    }else if(nowToken->typeEqual(Token(Token::Tag::STR,L""))){
        Parser::matchT(Token(Token::Tag::STR,L""));
        
    }else if(nowToken->typeEqual(Token(Token::Tag::CHAR,L""))){
        Parser::matchT(Token(Token::Tag::CHAR,L""));
        
    }else{
        throw std::runtime_error("factor error");
    }
}
