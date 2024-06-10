//
// Created by Administrator on 24-6-9.
//

#ifndef BUYER_H
#define BUYER_H
#include<iostream>
using namespace std;
class buyer {
protected:
    string name;
    int buyerID;
    string address;
    double pay;
    int leagueGrade;
    int MemberType;
public:
    buyer(string n,int m, int l, int b, string a, double p) : name(n),MemberType(m), leagueGrade(l),buyerID(b), address(a), pay(p) {}
    string getBuyName() { return name; }
    string getAddress() { return address; }
    int getLeagueGrade() { return leagueGrade; }
    int getMemberType() { return MemberType; }
    double getPay() { return pay; }
    int getID() { return buyerID; }
    virtual void display() = 0;
    virtual void setPay(double p) = 0;
};
#endif //BUYER_H
