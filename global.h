//
// Created by Administrator on 24-6-9.
//

#ifndef GLOBAL_H
#define GLOBAL_H
#include<iostream>
using namespace std;

std::ostream &operator<<(std::ostream &os, const book &b) {
    os << b.bookID << " "
            << b.bookName << " "
            << b.author << " "
            << b.publishing << " "
            << b.price << " ";
    return os;
}

void readFromFile(vector<buyer *> &buyers, vector<book *> &books, const string &customersFile,
                  const string &booksFile) {
    ifstream customerStream(customersFile);
    ifstream bookStream(booksFile);

    string line;
    while (getline(customerStream, line)) {
        istringstream iss(line);
        int buyerID, leagueGrade, MemberType;
        string name, address;
        double pay;
        iss >> buyerID >> name >> address >> MemberType >> leagueGrade;
        cout << buyerID << name << address << MemberType << leagueGrade << endl;
        if (iss.fail()) {
            cerr << "Invalid customer data." << endl;
            continue;
        }
        buyers.push_back(new member(name, buyerID, MemberType, leagueGrade, address, pay));
    }

    while (getline(bookStream, line)) {
        istringstream iss(line);
        int bookID;
        string bookName, author, publishing;
        double price;
        iss >> bookID >> bookName >> author >> publishing >> price;
        if (iss.fail()) {
            cerr << "Invalid book data." << endl;
            continue;
        }
        books.push_back(new book(bookID, bookName, author, publishing, price));
    }

    customerStream.close();
    bookStream.close();
}

void writeToFile(const vector<Order> &orders, const string &outputFile) {
    ofstream orderStream(outputFile);
    for (const auto &order: orders) {
        orderStream << order.buyerID << " " << order.totalAmount << " ";
        for (const auto &item: order.items) {
            orderStream << item.first << " " << item.second << " ";
        }
        orderStream << endl;
    }
    orderStream.close();
}

void SaveBooksToFile(const std::vector<book *> &books, const std::string &filename) {
    std::ofstream outputFile(filename, std::ios_base::app);

    if (outputFile.is_open()) {
        std::cout << "正在将书籍信息保存到文件...\n";
        for (const auto &book: books) {
            outputFile << *book << "\n"; // 假设 book 类重载了 << 运算符
        }
        outputFile.close();
        std::cout << "书籍信息已成功保存到文件！\n";
    } else {
        std::cout << "无法打开文件！\n";
    }
}

void readBooksFromFile(vector<book *> &books, const string &booksFile) {
    ifstream bookStream(booksFile);

    string line;
    while (getline(bookStream, line)) {
        istringstream iss(line);
        int bookID;
        string bookName, author, publishing;
        double price;
        iss >> bookID >> bookName >> author >> publishing >> price;
        if (iss.fail()) {
            cerr << "Invalid book data." << endl;
            continue;
        }
        books.push_back(new book(bookID, bookName, author, publishing, price));
    }

    bookStream.close();
}

void writeOrdersToFile(const vector<Order> &orders, const string &outputFile) {
    ofstream orderStream(outputFile, ios_base::app);
    for (const auto &order: orders) {
        orderStream << order.buyerID << " " << order.totalAmount << " ";
        for (const auto &item: order.items) {
            orderStream << item.first << " " << item.second << " ";
        }
        orderStream << endl;
    }
    orderStream.close();
}

void displayAllBooks(const vector<book *> &books) {
    cout << "当前书籍列表:\n";
    for (const auto &book: books) {
        book->display();
        cout << "\n";
    }
}

vector<Order> readOrdersFromFile(const string &ordersFile) {
    vector<Order> orders;
    ifstream orderStream(ordersFile);

    if (orderStream.is_open()) {
        string line;
        while (getline(orderStream, line)) {
            istringstream iss(line);
            int buyerID, bookID;
            double totalAmount, itemPrice;

            iss >> buyerID >> totalAmount;
            Order *order = new Order(buyerID);
            while (iss >> bookID >> itemPrice) {
                order->addBook(bookID, itemPrice);
            }

            // 假设 Order 可以通过买家ID、总价和物品列表构建
            orders.push_back(*order);
            delete order;
        }
        orderStream.close();
    } else {
        cerr << "无法打开订单文件！" << endl;
    }

    return orders;
}

// 修改函数以接受const vector<Order>&并返回Order const*
const Order *findUserOrder(const vector<Order> &orders, int buyerID) {
    for (const auto &order: orders) {
        // 这里也修改为const auto&
        if (order.buyerID == buyerID) {
            return &order; // 现在可以安全返回Order const*，因为order是const的
        }
    }
    return nullptr;
}

buyer *findUser(const vector<buyer *> &buyers, const string &username) {
    for (auto &buyerPtr: buyers) {
        if (buyerPtr->getBuyName() == username) {
            return buyerPtr; // 找到了匹配的用户，返回指向它的指针
        }
    }
    return nullptr; // 如果没有找到，返回nullptr
}

buyer *findUserOrder(const vector<buyer *> &buyers, int buyerID) {
    for (buyer *buyerPtr: buyers) {
        if (buyerPtr->getID() == buyerID) {
            return buyerPtr; // 找到了匹配的买家，返回指向它的指针
        }
    }
    return nullptr; // 如果没有找到匹配的买家，返回nullptr
}
#endif //GLOBAL_H
