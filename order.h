//
// Created by Administrator on 24-6-9.
//

#ifndef ORDER_H
#define ORDER_H
class Order {
public:
    int buyerID;
    double totalAmount;
    vector<pair<int, double>> items;
    Order(){};
    Order(int id) : buyerID(id), totalAmount(0) ,items(){}

    void addBook(int bookID, double price) {
        items.push_back(make_pair(bookID, price));
        totalAmount += price;
    }

    void display() {
        cout << "������Ϣ��\n";
        cout << "�����˱�ţ�" << buyerID << endl;
        cout << "�ܽ�" << totalAmount << endl;
        cout << "�����鼮��\n";
        for (const auto& item : items) {
            cout << "��ţ�" << item.first << ", �۸�" << item.second << endl;
        }
    }
};
#endif //ORDER_H
