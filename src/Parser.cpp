//
//  Parser.cpp
//  Regex
//
//  Created by 贾皓翔 on 2019/9/3.
//  Copyright © 2019 贾皓翔. All rights reserved.
//

#include "Parser.hpp"
void Parser::RegexList(NFA &val){
    if (nowToken==nullptr) {
        return ;
    }
    NFA RegexVal(ep,sp),RegexListVal(ep,sp);
    switch (nowToken->getTag()) {
        case Token::Tag::CHAR:
        case Token::Tag::STR:
            Parser::Regex(RegexVal);
            Parser::RegexList(RegexListVal);
            val=NFAOperator::Cnt(RegexVal, RegexListVal);
            break;
        default:
            if(nowToken->equal(Token(Token::Tag::SYMBOL,L"("))){
                  Parser::Regex(RegexVal);
                          Parser::RegexList(RegexListVal);
                          val=NFAOperator::Cnt(RegexVal, RegexListVal);
            }else{
                val=NFA(ep,sp);

            }
            break;
    }
}
void Parser::Regex(NFA &val){
    NFA termVal(ep,sp);
    Parser::term(termVal);
    Parser::Rp(val,termVal);
    
}
void Parser::Rp(NFA &val,NFA inh){
    NFA termVal(ep,sp);
    if (nowToken!=nullptr&&nowToken->typeEqual(Token(Token::Tag::OR,L"|"))) {
        Parser::matchT(Token(Token::Tag::OR,L"|"));
        Parser::term(termVal);
        Parser::Rp(val,NFAOperator::Or(inh, termVal));
    }else{
        val=inh;
    }
}

void Parser::term(NFA &val){
    NFA factorVal(ep,sp);
    Parser::factor(factorVal);
    Parser::Tp(val,factorVal);
}
void Parser::Tp(NFA &val,NFA inh){
    
    if(nowToken!=nullptr&&nowToken->typeEqual(Token(Token::Tag::CLOSURE,L"*"))){
        Parser::matchT(Token(Token::Tag::CLOSURE,L"*"));
        val=NFAOperator::Closure(inh);
    }else{
        val=inh;
    }
}

void Parser::factor(NFA &val){
    if (nowToken==nullptr) {
        throw std::runtime_error("factor error nowToken is nullptr");
    }
    if(nowToken->equal(Token(Token::Tag::SYMBOL,L"("))){
        Parser::matchA(Token(Token::Tag::SYMBOL,L"("));
        Parser::RegexList(val);
        if (nowToken==nullptr) {
            throw std::runtime_error("factor error nowToken is nullptr");
        }else{
            Parser::matchA(Token(Token::Tag::SYMBOL,L")"));
        }
    }else if(nowToken->typeEqual(Token(Token::Tag::STR,L""))){
        val=NFA(ep,sp,ws2s(nowToken->getLexme()));

        Parser::matchT(Token(Token::Tag::STR,L""));
    }else if(nowToken->typeEqual(Token(Token::Tag::CHAR,L""))){
        val=NFA(ep,sp,ws2s(nowToken->getLexme()));
        Parser::matchT(Token(Token::Tag::CHAR,L""));
        
    }else{
        throw std::runtime_error("factor error");
    }
}
