//
// Created by Administrator on 24-6-9.
//

#ifndef LAYFOLK_H
#define LAYFOLK_H
#include<iostream>
using namespace std;
class layfolk : public buyer {
public:
    layfolk(string n, int b, int m, int l,string a, double p) : buyer(n,m,l, b, a, p) {}
    void display() override {
        cout << "����������: " << name << "\t";
        cout << "�����˱�ţ� " << buyerID << "\t";
        cout << "������Ϊ��ͨ�û�" << endl;
        cout << "��ַ��" << address << "\n\n";
    }
    void setPay(double p) override {
        pay += p;
    }
};
#endif //LAYFOLK_H
