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
        cout << "��ѡ����" << endl;
        cout << "1.�����鼮��۸�" << endl;
        cout << "2.�����û�" << endl;
        cout << "3.�˳�" << endl;
        cout << "4.�����鼮" << endl;
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
                    cout << "�����빺���˱�ţ�����0�˳�����";
                    cin >> buyerid;
                    if (buyerid == 0) {
                        break;
                    }

                    bool found = false;
                    for (buyer *buyer: buyers)
                        if (buyer->getID() == buyerid) {
                            found = true;
                            if (buyer->getMemberType() == 0) {
                                cout << "��������Ϣ��" << endl;
                                cout << "���: " << buyer->getID() << ", ����: " << buyer->getBuyName()
                                        << ", ��ַ: " << buyer->getAddress() << ", ��Ա����: ��ͨ�û�" << endl;
                            }
                            if (buyer->getMemberType() == 1) {
                                cout << "��������Ϣ��" << endl;
                                cout << "���: " << buyer->getID() << ", ����: " << buyer->getBuyName()
                                        << ", ��ַ: " << buyer->getAddress() << ", ��Ա����:��Ա " << endl;
                                if (dynamic_cast<member *>(buyer) != nullptr) {
                                    member *mem = dynamic_cast<member *>(buyer);
                                    cout << "��Ա�ȼ�: " << mem->getLeagueGrade() << endl;
                                    break;
                                }
                            }
                            if (buyer->getMemberType() == 2) {
                                cout << "��������Ϣ��" << endl;
                                cout << "���: " << buyer->getID() << ", ����: " << buyer->getBuyName()
                                        << ", ��ַ: " << buyer->getAddress() << ", ��Ա����:������Ա��" << endl;
                            }
                        }
                    if (!found) {
                        cout << "��Ų�����" << endl;
                        continue;
                    }

                    // ��books.txt�ļ��ж�ȡ�鼮
                    vector<book *> currentBooks;
                    readBooksFromFile(currentBooks, "books.txt");

                    cout << "��ǰ�鼮�б�:\n";
                    for (const auto &book: books) {
                        book->display();
                        cout << "\n";
                    }
                    cout << "������Ҫ������鼮��ţ�";
                    int bookID;
                    cin >> bookID;

                    // �����鼮
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
                        // �������������������ز��������������á���ʾ������
                    } else {
                        cout << "δ�ҵ��鼮���Ϊ " << bookID << " ���鼮��\n";
                    }

                    // �����ڿ���̨��ʾ����������д���ļ�
                    writeOrdersToFile({newOrder}, "orders.txt"); // д�뵥��������Ϣ
                    // ������ʱ���ص��鼮
                    for (book *book: currentBooks) {
                        delete book;
                    }
                    vector<Order> orders = readOrdersFromFile("orders.txt");
                    for (const auto &order: orders) {
                        cout << "������Ϣ��" << endl;
                        cout << "���ID��" << order.buyerID << endl;
                        cout << "�ܼۣ�" << order.totalAmount << endl;
                        cout << "������鼮��" << endl;
                        for (const auto &item: order.items) {
                            cout << "�鼮ID��" << item.first << "���۸�" << item.second << endl;
                        }
                        cout << "\n";
                    }
                }
                break;
            }
            break;

            case 2: {
                cout << "���������û���������";
                cin >> newName;
                cout << "���������û��ı�ţ�";
                cin >> newID;
                cout << "���������û��ĵ�ַ��";
                cin >> newAddress;
                cout << "���������û��Ļ�Ա���ͣ�" << endl;
                cout << "��ͨ�˿�Ϊ0\n��ԱΪ1\n������ԱΪ2" << endl;
                newLeagueGrade = 0;
                membertype = 0;
                cin >> membertype;
                if (membertype == 1) {
                    cout << "���������û��Ļ�Ա�ȼ���";
                    cin >> newLeagueGrade;
                }
                if (membertype == 2) {
                    cout << "���û���������Ա��" << endl;
                    newLeagueGrade = 6;
                }
                // �����»�Ա����
                buyer *newMember = new member(newName, newID, membertype, newLeagueGrade, newAddress, pay);
                buyers.push_back(newMember);
                // ���»�Ա��Ϣд���ļ�
                ofstream customerFileStream("customers.txt", ios::app);
                if (customerFileStream.is_open()) {
                    customerFileStream << newID << " " << newName << " " << newAddress << " " << membertype << " " <<
                            newLeagueGrade << " " << endl;
                    customerFileStream.close();
                    cout << "���û��ѳɹ���ӣ�" << endl;
                } else {
                    cerr << "�޷��򿪻򴴽��˿��ļ�!" << endl;
                }

                // ɾ���´�����buyer���󣬱����ڴ�й©
                delete newMember;
                break;
            }
            case 3: {
                string username;
                cout << "�������û�����";
                cin >> username;
                vector<Order> allOrders = readOrdersFromFile("orders.txt"); // ��ȡ���ж���
                double totalAmount = 0.0; // ��ʼ���ܽ��Ϊ0

                // ɸѡ�ض��û��Ķ������ۼӽ��
                for (const Order &order: allOrders) {
                    if (findUserOrder(buyers, order.buyerID)->getBuyName() == username) {
                        // ���� findUserOrder �����ܸ���ID�ҵ��û�
                        totalAmount += order.totalAmount;
                    }
                }

                // ���� member ����һ�� getDiscountRate �������ݻ�Ա�ȼ������ۿ���
                member *user = dynamic_cast<member *>(findUser(buyers, username)); // ���� findUser ���������û��������û�
                if (user != nullptr) {
                    double discountRate = user->getDiscountRate();
                    double discountedTotal = totalAmount * (1 - discountRate);

                    cout << "�û���: " << username << endl;
                    cout << "ԭʼ�ܽ��: " << totalAmount << endl;
                    cout << "�ۿ���: " << discountRate * 100 << "%" << endl;
                    cout << "�ۺ��ܽ��: " << discountedTotal << endl;
                } else {
                    cout << "δ�ҵ��û���Ϊ " << username << " ���û���" << endl;
                }
                break;
            }

            break;
            case 4: {
                cout << "��ѡ�������\n";
                cout << "1. ����鼮\n";
                cout << "2. �鿴�����鼮\n";

                int subChoose;
                cin >> subChoose;

                switch (subChoose) {
                    case 1: {
                        int bookID;
                        string title, author, publisher;
                        double price;
                        cout << "��������ţ�";
                        cin >> bookID;
                        cout << "������������";
                        cin >> title;
                        cout << "���������ߣ�";
                        cin >> author;
                        cout << "����������磺";
                        cin >> publisher;
                        cout << "������۸�";
                        cin >> price;

                        // �������������
                        books.push_back(new book(bookID, title, author, publisher, price));
                        SaveBooksToFile(books, "books.txt"); // ���� books ����
                        cout << "�鼮����ӣ�\n";
                        break;
                    }
                    case 2: {
                        cout << "��books.txt�ļ��ж�ȡ�鼮�б�...\n";
                        readBooksFromFile(books, "books.txt");
                        cout << "��ǰ�鼮�б�:\n";
                        for (const auto &book: books) {
                            book->display();
                            cout << "\n";
                        }
                        break;
                    }
                    default:
                        cout << "��Чѡ��\n";
                }
                break;
            }

            default:
                cout << "��Ч��ѡ������������" << endl;
        }
        writeOrdersToFile(orders, "orders.txt"); //д�����ж�����Ϣ
    }

    for (buyer *buyer: buyers) {
        delete buyer;
    }
    for (book *book: books) {
        delete book;
    }
}
