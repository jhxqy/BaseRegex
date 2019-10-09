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
 RegexList -> Regex RegexList|ε      RegexList.val=Regex.val + RegexList | ε
 Regex     -> term R'
 R'        -> + term R'|ε
 term      -> factor T'
 T'        -> *|ε
 factor    -> (RegexList)|STR|CHAR
 */

/*
RegexList -> Regex RegexList1|ε     RegexList.val=Regex.val con RegexList1.val | ε
Regex     -> term R'                R'.inh=term.val;
                                    Regex.val=R'.val
                                
R'        -> + term R'1|ε           Rp1.inh=rp.inh + term.val;
                                    Rp.val= rp1.val
                                    if Rp==ε , Rp.val=Rp.inh
term      -> factor T'              Tp.inh=factor.val
                                    term.value=tp.val
T'        -> *|ε                    if(tp==*) tp.val=(tp.inh*)
                                    if(tp==ε) tp.val=tp.inh
factor    -> (RegexList)|STR|CHAR   factor.val=(RegexList)|STR|CHAR
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
    void RegexList(NFA &val);
    void Regex(NFA &val);
    void Rp(NFA &val,NFA inh);
    void term(NFA &val);
    void Tp(NFA &val,NFA inh);
    void factor(NFA &val);
    
public:
    NFA Start(){
        NFA nfa;
        RegexList(nfa);
        if(nowToken!=nullptr){
            throw std::runtime_error("parse not end");
        }
        return nfa;
    }
    Parser(const std::string &s):t(s){
        nowToken=t.scan();
    }
};

#endif /* Parser_hpp */
