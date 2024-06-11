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
        cout << "订单信息：\n";
        cout << "购书人编号：" << buyerID << endl;
        cout << "总金额：" << totalAmount << endl;
        cout << "购买书籍：\n";
        for (const auto& item : items) {
            cout << "书号：" << item.first << ", 价格：" << item.second << endl;
        }
    }
};
#endif //ORDER_H
