#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <iostream>
#include <fstream>
#include <limits>

// --- Định nghĩa thực thể ---
struct Book {
    int id;
    std::string title;
    std::string author;
    bool isAvailable; // true: Sách sẵn sàng, false: Đã bị mượn
    int borrowCount;  // Thống kê số lần mượn

    void display() const {
        std::cout << "ID: " << id << " | Ten sach: " << title 
                  << " | Tac gia: " << author 
                  << " | Trang thai: " << (isAvailable ? "San sang" : "Da duoc muon")
                  << " | Luot muon: " << borrowCount << "\n";
    }
};

struct Reader {
    int id;
    std::string name;
    int borrowedCount; // Số sách tích cực mượn
};

// --- 1. BST (Binary Search Tree): Quản lý & tìm kiếm sách theo ID ---
struct BSTNode {
    Book data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(Book b) : data(b), left(nullptr), right(nullptr) {}
};

class BookBST {
private:
    BSTNode* root;
    BSTNode* insertNode(BSTNode* node, Book b);
    BSTNode* searchNode(BSTNode* node, int id) const;
    void inorder(BSTNode* node) const;
    void destroyTree(BSTNode* node);
    void findMostBorrowedNode(BSTNode* node, Book& maxBook) const;
    void saveTreeToFile(BSTNode* node, std::ofstream& outFile) const;
public:
    BookBST();
    ~BookBST();
    void insert(Book b);
    BSTNode* search(int id) const;
    void displayInOrder() const;
    Book getMostBorrowed() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

// --- 2. Queue (Hàng đợi đơn): Danh sách chờ mượn khi sách hết ---
struct QueueNode {
    Reader reader;
    QueueNode* next;
    QueueNode(Reader r) : reader(r), next(nullptr) {}
};

class WaitingQueue {
private:
    QueueNode* front;
    QueueNode* rear;
public:
    WaitingQueue();
    ~WaitingQueue();
    void enqueue(Reader r);
    Reader dequeue();
    bool isEmpty() const;
    void displayQueue() const;
};

// --- 3. Stack (Ngăn xếp): Lịch sử thao tác phục vụ chức năng Undo ---
struct StackNode {
    std::string action; // Mô tả hành động để hiển thị hoặc hoàn tác
    StackNode* next;
    StackNode(std::string act) : action(act), next(nullptr) {}
};

class ActionStack {
private:
    StackNode* top;
public:
    ActionStack();
    ~ActionStack();
    void push(std::string action);
    std::string pop();
    bool isEmpty() const;
    void displayHistory() const;
};

// --- 4. Linked List (Danh sách liên kết): Quản lý độc giả toàn thư viện ---
struct ListNode {
    Reader data;
    ListNode* next;
    ListNode(Reader r) : data(r), next(nullptr) {}
};

class ReaderList {
private:
    ListNode* head;
public:
    ReaderList();
    ~ReaderList();
    void addReader(Reader r);
    void displayAll() const;
    Reader getMostActive() const;
    bool isEmpty() const;
};

#endif
