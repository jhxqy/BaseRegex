//
//  Tokenizer.hpp
//  Regex
//
//  Created by 贾皓翔 on 2019/9/3.
//  Copyright © 2019 贾皓翔. All rights reserved.
//

#ifndef Tokenizer_hpp
#define Tokenizer_hpp

#include <stdio.h>
#include "Regex/NFA.hpp"
#include <string>
#include <stdexcept>
class Token{
public:
    enum class Tag{
        STR,SYMBOL,CHAR,AND,CLOSURE,OR
    };
    Token(Tag t,const std::wstring &s):tag_(t),lexme_(s){
        
    }
    Tag getTag()const{
        return tag_;
    }
    std::wstring getLexme()const{
        return lexme_;
    }
    bool typeEqual(const Token &t){
        return t.getTag()==tag_;
    }
    bool equal(const Token &t){
        return t.getTag()==tag_&&(lexme_.compare(t.lexme_)==0);
    }
    
private:
    std::wstring lexme_;
    Tag tag_;
};

class Tokenizer{
    std::wstring s_;
    bool eof_;
    size_t index_;
    bool eofTest(){
        if (eof_||index_>=s_.size()) {
            eof_=true;
            return false;
        }
        return true;  //可以继续则true
    }
public:
    Tokenizer(const std::string regex):index_(0),eof_(false){
        s_=s2ws(regex);
    }
    
    Token *scan(){
        std::wstring res;
        
        while (eofTest()&&s_[index_]!=L'\\'&&s_[index_]!=L'('&&s_[index_]!=L')'&&s_[index_]!=L'|'&&s_[index_]!=L'*') {
            res.push_back(s_[index_]);
            index_++;
        }
        if (res.size()!=0) {
            return new Token(Token::Tag::STR,res);
        }
        
        
        if (eofTest()&&s_[index_]==L'\\') {
            if ((index_+1)<s_.size()) {
                switch (s_[index_+1]) {
                    case L'\\':
                        index_+=2;
                        return new Token(Token::Tag::CHAR,L"\\");
                        break;
                    case L'n':
                        index_+=2;
                        return new Token(Token::Tag::CHAR,L"\n");
                        break;
                    case L't':
                        index_+=2;
                        return new Token(Token::Tag::CHAR,L"\t");
                        break;
                    case L'f':
                        index_+=2;
                        return new Token(Token::Tag::CHAR,L"\f");
                        break;
                    case L'v':
                        index_+=2;
                        return new Token(Token::Tag::CHAR,L"\v");
                        break;
                    case L'|':
                        index_+=2;
                        return new Token(Token::Tag::CHAR,L"|");
                        break;
                    case L'*':
                        index_+=2;
                        return new Token(Token::Tag::CHAR,L"*");
                        break;
                    default:
                        index_+=2;
                        return new Token(Token::Tag::CHAR,std::wstring(1,s_[index_-1]));
                        break;
                }
            }else{
                index_++;
                return new Token(Token::Tag::CHAR,std::wstring(1,s_[index_-1]));
            }
        }
        
        
        
        
        if (eofTest()&&(s_[index_]==L'('||s_[index_]==L')')) {
            Token *t=new Token(Token::Tag::SYMBOL,std::wstring(1,s_[index_]));
            index_++;
            return t;
        }
        if (eofTest()&&(s_[index_]==L'|')) {
            Token *t=new Token(Token::Tag::OR,std::wstring(1,s_[index_]));
            index_++;
            return t;
        }
        if (eofTest()&&(s_[index_]==L'*')) {
            Token*t=new Token(Token::Tag::CLOSURE,std::wstring(1,s_[index_]));
            index_++;
            return t;
        }
        if (!eofTest()) {
            return nullptr;
        }else{
            throw std::runtime_error("tokenizer error");
        }
    }
};
#endif /* Tokenizer_hpp */
