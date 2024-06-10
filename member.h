//
// Created by Administrator on 24-6-9.
//

#ifndef MEMBER_H
#define MEMBER_H
#include<iostream>
using namespace std;
class member : public buyer {
public:
    member(string n, int b,int m, int l, string a, double p) : buyer(n,m,l, b, a, p){}
    void display() override {
        cout << "购书人姓名: " << name << "\t";
        cout << "购书人编号： " << buyerID << "\t";
        cout << "购书人为会员，级别: " << leagueGrade << "\t";
        cout << "地址：" << address << "\t";
    }
    void setPay(double p) override {
        if (leagueGrade >= 1 && leagueGrade <= 5) {
            pay += (1 - (leagueGrade - 1) / 10) * p;
        } else {
            cout << "级别错误" << endl;
        }
    }
    double getDiscountRate() const {
        if (leagueGrade >= 1 && leagueGrade <= 5) {
            return (5 - leagueGrade) / 10.0; // 调整以直接返回折扣率，注意这里的计算逻辑需根据实际需求调整
        } else {
            return 0.0; // 如果等级不在范围内，不给予折扣
        }
    }

};
#endif //MEMBER_H
