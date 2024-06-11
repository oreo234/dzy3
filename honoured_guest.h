//
// Created by Administrator on 24-6-9.
//

#ifndef HONOURED_GUEST_H
#define HONOURED_GUEST_H
#include<iostream>
using namespace std;
class honoured_guest : public buyer {
private:
    double discountRate;
public:
    honoured_guest(string n, int b, int m, int l, string a, double p) : buyer(n,m,l, b, a, p) {}
    void display() override {
        cout << "购书人姓名: " << name << "\t";
        cout << "购书人编号： " << buyerID << "\t";
        cout << "购书人为会员，折扣率为: " << discountRate * 100 << "% \n";
        cout << "地址：" << address << "\n\n";
    }
    void setPay(double p) override {
        pay += (1 - discountRate) * p;
    }
};
#endif //HONOURED_GUEST_H
