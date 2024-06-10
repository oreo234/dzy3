//
// Created by Administrator on 24-6-9.
//

#ifndef LAYFOLK_H
#define LAYFOLK_H
class layfolk : public buyer {
public:
    layfolk(string n, int b, int m, int l,string a, double p) : buyer(n,m,l, b, a, p) {}
    void display() override {
        cout << "购书人姓名: " << name << "\t";
        cout << "购书人编号： " << buyerID << "\t";
        cout << "购书人为普通用户" << endl;
        cout << "地址：" << address << "\n\n";
    }
    void setPay(double p) override {
        pay += p;
    }
};
#endif //LAYFOLK_H
