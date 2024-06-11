//
// Created by Administrator on 24-6-9.
//

#ifndef BOOK_H
#define BOOK_H
#include<iostream>
using namespace std;
class book {
private:
    int bookID;
    string bookName;
    string author;
    string publishing;
    double price;
public:
    book(int b_id, string b_n, string au, string pu, double pr) : bookID(b_id), bookName(b_n), author(au), publishing(pu), price(pr) {}
    void display() {
        cout << "���: " << bookID << "\t";
        cout << "����: " << bookName << "\t";
        cout << "����: " << author << "\t";
        cout << "������: " << publishing << "\t";
        cout << "�۸�: " << price << "\t";
    }
    friend std::ostream& operator<<(std::ostream& os, const book& b);
    int getBookID() { return bookID; }
    double getPrice() { return price; }
};
#endif //BOOK_H
