#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>
#include"buyer.h"
#include"member.h"
#include"honoured_guest.h"
#include"book.h"
#include"order.h"
#include"global.h"
using namespace std;


int main() {
    vector<buyer *> buyers;
    vector<book *> books;
    readFromFile(buyers, books, "customers.txt", "books.txt");

    vector<Order> orders;
    int choose;
    while (true) {
        cout << "请选择功能" << endl;
        cout << "1.购买书籍算价格" << endl;
        cout << "2.增加用户" << endl;
        cout << "3.退出" << endl;
        cout << "4.更改书籍" << endl;
        cin >> choose;
        int buyerid;
        string newName;
        int newID;
        string newAddress;
        int newLeagueGrade;
        int membertype;
        int pay = 0;
        Order order1;
        switch (choose) {
            case 1: {
                while (true) {
                    cout << "请输入购书人编号（输入0退出）：";
                    cin >> buyerid;
                    if (buyerid == 0) {
                        break;
                    }

                    bool found = false;
                    for (buyer *buyer: buyers)
                        if (buyer->getID() == buyerid) {
                            found = true;
                            if (buyer->getMemberType() == 0) {
                                cout << "购书人信息：" << endl;
                                cout << "编号: " << buyer->getID() << ", 姓名: " << buyer->getBuyName()
                                        << ", 地址: " << buyer->getAddress() << ", 会员类型: 普通用户" << endl;
                            }
                            if (buyer->getMemberType() == 1) {
                                cout << "购书人信息：" << endl;
                                cout << "编号: " << buyer->getID() << ", 姓名: " << buyer->getBuyName()
                                        << ", 地址: " << buyer->getAddress() << ", 会员类型:会员 " << endl;
                                if (dynamic_cast<member *>(buyer) != nullptr) {
                                    member *mem = dynamic_cast<member *>(buyer);
                                    cout << "会员等级: " << mem->getLeagueGrade() << endl;
                                    break;
                                }
                            }
                            if (buyer->getMemberType() == 2) {
                                cout << "购书人信息：" << endl;
                                cout << "编号: " << buyer->getID() << ", 姓名: " << buyer->getBuyName()
                                        << ", 地址: " << buyer->getAddress() << ", 会员类型:荣誉会员·" << endl;
                            }
                        }
                    if (!found) {
                        cout << "编号不存在" << endl;
                        continue;
                    }

                    // 从books.txt文件中读取书籍
                    vector<book *> currentBooks;
                    readBooksFromFile(currentBooks, "books.txt");

                    cout << "当前书籍列表:\n";
                    for (const auto &book: books) {
                        book->display();
                        cout << "\n";
                    }
                    cout << "请输入要购买的书籍编号：";
                    int bookID;
                    cin >> bookID;

                    // 查找书籍
                    book *selectedBook;
                    for (const auto &b: books) {
                        if (b->getBookID() == bookID) {
                            selectedBook = b;
                            break;
                        }
                    }
                    Order newOrder(buyerid);
                    if (selectedBook != nullptr) {
                        newOrder.addBook(selectedBook->getBookID(), selectedBook->getPrice());
                        // 可以在这里添加其他相关操作，例如计算费用、显示订单等
                    } else {
                        cout << "未找到书籍编号为 " << bookID << " 的书籍。\n";
                    }

                    // 不再在控制台显示订单，而是写入文件
                    writeOrdersToFile({newOrder}, "orders.txt"); // 写入单个订单信息
                    // 清理临时加载的书籍
                    for (book *book: currentBooks) {
                        delete book;
                    }
                    vector<Order> orders = readOrdersFromFile("orders.txt");
                    for (const auto &order: orders) {
                        cout << "订单信息：" << endl;
                        cout << "买家ID：" << order.buyerID << endl;
                        cout << "总价：" << order.totalAmount << endl;
                        cout << "购买的书籍：" << endl;
                        for (const auto &item: order.items) {
                            cout << "书籍ID：" << item.first << "，价格：" << item.second << endl;
                        }
                        cout << "\n";
                    }
                }
                break;
            }
            break;

            case 2: {
                cout << "请输入新用户的姓名：";
                cin >> newName;
                cout << "请输入新用户的编号：";
                cin >> newID;
                cout << "请输入新用户的地址：";
                cin >> newAddress;
                cout << "请输入新用户的会员类型：" << endl;
                cout << "普通顾客为0\n会员为1\n荣誉会员为2" << endl;
                newLeagueGrade = 0;
                membertype = 0;
                cin >> membertype;
                if (membertype == 1) {
                    cout << "请输入新用户的会员等级：";
                    cin >> newLeagueGrade;
                }
                if (membertype == 2) {
                    cout << "该用户是荣誉会员！" << endl;
                    newLeagueGrade = 6;
                }
                // 创建新会员对象
                buyer *newMember = new member(newName, newID, membertype, newLeagueGrade, newAddress, pay);
                buyers.push_back(newMember);
                // 将新会员信息写入文件
                ofstream customerFileStream("customers.txt", ios::app);
                if (customerFileStream.is_open()) {
                    customerFileStream << newID << " " << newName << " " << newAddress << " " << membertype << " " <<
                            newLeagueGrade << " " << endl;
                    customerFileStream.close();
                    cout << "新用户已成功添加！" << endl;
                } else {
                    cerr << "无法打开或创建顾客文件!" << endl;
                }

                // 删除新创建的buyer对象，避免内存泄漏
                delete newMember;
                break;
            }
            case 3: {
                string username;
                cout << "请输入用户名：";
                cin >> username;
                vector<Order> allOrders = readOrdersFromFile("orders.txt"); // 读取所有订单
                double totalAmount = 0.0; // 初始化总金额为0

                // 筛选特定用户的订单并累加金额
                for (const Order &order: allOrders) {
                    if (findUserOrder(buyers, order.buyerID)->getBuyName() == username) {
                        // 假设 findUserOrder 函数能根据ID找到用户
                        totalAmount += order.totalAmount;
                    }
                }

                // 假设 member 类有一个 getDiscountRate 方法根据会员等级返回折扣率
                member *user = dynamic_cast<member *>(findUser(buyers, username)); // 假设 findUser 函数根据用户名查找用户
                if (user != nullptr) {
                    double discountRate = user->getDiscountRate();
                    double discountedTotal = totalAmount * (1 - discountRate);

                    cout << "用户名: " << username << endl;
                    cout << "原始总金额: " << totalAmount << endl;
                    cout << "折扣率: " << discountRate * 100 << "%" << endl;
                    cout << "折后总金额: " << discountedTotal << endl;
                } else {
                    cout << "未找到用户名为 " << username << " 的用户。" << endl;
                }
                break;
            }

            break;
            case 4: {
                cout << "请选择操作：\n";
                cout << "1. 添加书籍\n";
                cout << "2. 查看所有书籍\n";

                int subChoose;
                cin >> subChoose;

                switch (subChoose) {
                    case 1: {
                        int bookID;
                        string title, author, publisher;
                        double price;
                        cout << "请输入书号：";
                        cin >> bookID;
                        cout << "请输入书名：";
                        cin >> title;
                        cout << "请输入作者：";
                        cin >> author;
                        cout << "请输入出版社：";
                        cin >> publisher;
                        cout << "请输入价格：";
                        cin >> price;

                        // 创建并添加新书
                        books.push_back(new book(bookID, title, author, publisher, price));
                        SaveBooksToFile(books, "books.txt"); // 传递 books 参数
                        cout << "书籍已添加！\n";
                        break;
                    }
                    case 2: {
                        cout << "从books.txt文件中读取书籍列表...\n";
                        readBooksFromFile(books, "books.txt");
                        cout << "当前书籍列表:\n";
                        for (const auto &book: books) {
                            book->display();
                            cout << "\n";
                        }
                        break;
                    }
                    default:
                        cout << "无效选择！\n";
                }
                break;
            }

            default:
                cout << "无效的选择，请重新输入" << endl;
        }
        writeOrdersToFile(orders, "orders.txt"); //写入所有订单信息
    }

    for (buyer *buyer: buyers) {
        delete buyer;
    }
    for (book *book: books) {
        delete book;
    }
}
