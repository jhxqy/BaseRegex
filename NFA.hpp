//
//  NFA.hpp
//  Regex
//
//  Created by 贾皓翔 on 2019/8/26.
//  Copyright © 2019 贾皓翔. All rights reserved.
//

#ifndef NFA_hpp
#define NFA_hpp
#include <vector>
#include <string>
#include <stdio.h>
#include <list>
#include <codecvt>
#include <locale>
#include <set>
struct MatchFactor{
    enum class Type{
        Epsilon,Character,Range
    };
    Type type_;
    wchar_t c;
    wchar_t from;
    wchar_t to;
};
class Status;
class Edge{
public:
    MatchFactor m_;
    Status *start_;
    Status *end_;
};

template<typename T>
class ObjectPool{
    std::list<T*> list_;
    ObjectPool(){}
public:
    static ObjectPool *instance(){
        static ObjectPool *p=nullptr;
        if (p==nullptr) {
            p=new ObjectPool();
        }
        return p;
    }
    T* newObject(){
        T *t=new T;
        list_.push_back(t);
        return t;
    }
    bool freeObject(T *t){
        for(auto i=list_.begin();i!=list_.end();i++){
            if (*i==t) {
                list_.erase(i);
                return true;
            }
        }
        return false;
    }
};
using EdgePool =ObjectPool<Edge>;
using StatusPool =ObjectPool<Status>;


class Status{ 
public:
    std::vector<Edge*> inEdges_;
    std::vector<Edge*> outEdges_;
    bool acceptStatus_;
    Status():acceptStatus_(false){
        
    }
};

std::wstring s2ws(const std::string& str);

std::string ws2s(const std::wstring& wstr);
class NFAOperator;
class NFA{
    std::vector<Status*> statusList_;
    Status *startStatus;
    Status *acceptStatus;
public:
    friend class NFAOperator;
    NFA(){}
    
    Edge* addEdge(Status *from,Status *to){
        Edge *e=EdgePool::instance()->newObject();
        e->start_=from;
        e->end_=to;
        from->outEdges_.push_back(e);
        to->inEdges_.push_back(e);
        e->m_.type_=MatchFactor::Type::Epsilon;
        return e;
    }
    Edge* addEdge(Status *from,Status *to,wchar_t fromC,wchar_t toC){
        Edge *e=EdgePool::instance()->newObject();
        e->start_=from;
        e->end_=to;
        from->outEdges_.push_back(e);
        to->inEdges_.push_back(e);
        e->m_.type_=MatchFactor::Type::Range;
        e->m_.from=fromC;
        e->m_.to=toC;
        return e;
    }
    Edge* addEdge(Status *from,Status *to,wchar_t c){
        Edge *e=EdgePool::instance()->newObject();
        e->start_=from;
        e->end_=to;
        from->outEdges_.push_back(e);
        to->inEdges_.push_back(e);
        e->m_.type_=MatchFactor::Type::Character;
        e->m_.c=c;
        return e;
    }
    
    Status* addStatus(){
        Status *s=StatusPool::instance()->newObject();
        statusList_.push_back(s);
        return s;
    }
    
    std::set<Status*> closure(Status *s){
        std::set<Status*> res;
        res.insert(s);
        for(auto i=s->outEdges_.begin();i!=s->outEdges_.end();i++){
            
            if ((*i)->m_.type_==MatchFactor::Type::Epsilon) {
                res.insert((*i)->end_);
            }
        }
        return res;
    }
    std::set<Status*> closure(std::set<Status*> ss){
        std::set<Status*> res;
        for(auto i=ss.begin();i!=ss.end();i++){
            res.insert(*i);
            for(auto j=(*i)->outEdges_.begin();j!=(*i)->outEdges_.end();j++){
                if ((*j)->m_.type_==MatchFactor::Type::Epsilon) {
                    res.insert((*j)->end_);
                }
            }
        }
        return res;
    }
    std::set<Status*> move(std::set<Status*> T,wchar_t a){
        std::set<Status*> res;
        for(auto i=T.begin();i!=T.end();i++){
            for(auto j=(*i)->outEdges_.begin();j!=(*i)->outEdges_.end();j++){
                switch ((*j)->m_.type_) {
                    case MatchFactor::Type::Character:
                        if (a==(*j)->m_.c) {
                            res.insert((*j)->end_);
                        }
                        break;
                    case MatchFactor::Type::Range:
                        if(a>=(*j)->m_.from&&a<=(*j)->m_.to){
                            res.insert((*j)->end_);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        return res;
    }
    
    bool match(const std::string &str){
        std::wstring ws=s2ws(str);
        std::set<Status*> S=closure(startStatus);
        for(size_t i=0;i<ws.size();i++){
            S=closure(move(S, ws[i]));
        }
        if (S.count(acceptStatus)<1) {
            return false;
        }
        return true;
    }
    
    
    NFA(const std::string &s){
        std::wstring ws=s2ws(s);
        StatusPool *statusPool=StatusPool::instance();
        EdgePool *edgePool=EdgePool::instance();
        startStatus=addStatus();
        Status *p=startStatus;
        Status *q;
        for(size_t i=0;i<ws.size();i++){
            q=addStatus();
            addEdge(p, q,ws[i]);
            p=q;
        }
        p->acceptStatus_=true;
        acceptStatus=p;
    }
};
class NFAOperator{
public:
    
    static NFA Or(const NFA &a,const NFA &b){
        NFA res;
        res.startStatus=res.addStatus();
        res.addEdge(res.startStatus, a.startStatus);
        res.addEdge(res.startStatus, b.startStatus);
        for(auto i=a.statusList_.begin();i!=a.statusList_.end();i++){
            res.statusList_.push_back(*i);
        }
        for(auto i=b.statusList_.begin();i!=b.statusList_.end();i++){
            res.statusList_.push_back(*i);
        }
        
        res.acceptStatus=res.addStatus();
        res.acceptStatus->acceptStatus_=true;
        
        res.addEdge(b.acceptStatus, res.acceptStatus);
        res.addEdge(a.acceptStatus, res.acceptStatus);
        a.acceptStatus->acceptStatus_=false;
        b.acceptStatus->acceptStatus_=false;
        
        return res;
    }
    static NFA Cnt(const NFA &a,const NFA &b){
        NFA res;
        for(auto i=a.statusList_.begin();i!=a.statusList_.end();i++){
            res.statusList_.push_back(*i);
        }
        res.startStatus=a.startStatus;
        a.acceptStatus->acceptStatus_=false;
        res.addEdge(a.acceptStatus, b.startStatus);
        for(auto i=b.statusList_.begin();i!=b.statusList_.end();i++){
            res.statusList_.push_back(*i);
        }
        res.acceptStatus=b.acceptStatus;
        return res;
    }
    
    static NFA Closure(const NFA &a){
        NFA res;
        res.startStatus=res.addStatus();
        for(auto i=a.statusList_.begin();i!=a.statusList_.end();i++){
            res.statusList_.push_back(*i);
        }
        res.acceptStatus=res.addStatus();
        res.acceptStatus->acceptStatus_=true;
        a.acceptStatus->acceptStatus_=false;
        res.addEdge(res.startStatus, a.startStatus);
        res.addEdge(res.startStatus, res.acceptStatus);
        res.addEdge(a.acceptStatus, res.acceptStatus);
        res.addEdge(a.acceptStatus, a.startStatus);
        return res;
    }
};

#endif /* NFA_hpp */
