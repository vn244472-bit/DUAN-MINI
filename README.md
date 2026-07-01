##📚 Hệ thống Quản lý Thư viện

##🛠️ Cấu trúc dữ liệu áp dụng
Binary Search Tree (BST): Lưu trữ danh mục sách giúp tối ưu hóa việc tìm kiếm từ dữ liệu lớn chỉ mất 
O
(
log
⁡
n
)
.


Queue (Hàng đợi đơn): Lưu hàng chờ của độc giả khi một đầu sách mong muốn đã bị mượn hết sạch.
Stack (Ngăn xếp): Theo vết lịch sử hành vi để cung cấp tính năng Undo (Hoàn tác).

Linked List: Danh sách liên kết tuyến tính giúp quản lý danh sách độc giả động một cách mềm dẻo.

##🚀 Hướng dẫn Biên dịch & Chạy ứng dụng

Biên dịch Chương trình chính:
Chạy lệnh sau trên terminal/cmd tại thư mục src/:

===== tack======
#ifndef TASK_H
#define TASK_H

#include <string>
#include <iostream>

// Định nghĩa Cấu trúc Task
struct Task {
    int id;
    std::string title;
    int priority; // 1: Cao, 2: Trung bình, 3: Thấp

    void display() const {
        std::cout << "[" << id << "] " << title << " (Ưu tiên: " << priority << ")\n";
    }
};

// 1. Linked List: Quản lý danh sách toàn bộ Task
struct ListNode {
    Task data;
    ListNode* next;
    ListNode(Task t) : data(t), next(nullptr) {}
};

class TaskList {
private:
    ListNode* head;
public:
    TaskList();
    ~TaskList();
    void addTask(Task t);
    void displayAll() const;
    bool isEmpty() const;
};

// 2. Queue: Hàng đợi xử lý Task theo cơ chế FIFO
struct QueueNode {
    Task data;
    QueueNode* next;
    QueueNode(Task t) : data(t), next(nullptr) {}
};

class TaskQueue {
private:
    QueueNode* front;
    QueueNode* rear;
public:
    TaskQueue();
    ~TaskQueue();
    void enqueue(Task t);
    Task dequeue();
    bool isEmpty() const;
    void displayQueue() const;
};

// 3. Stack: Lịch sử thao tác hoàn tác (Undo)
struct StackNode {
    std::string action;
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

// 4. Binary Search Tree (BST): Tìm kiếm Task theo ID nhanh chóng
struct BSTNode {
    Task data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(Task t) : data(t), left(nullptr), right(nullptr) {}
};

class TaskBST {
private:
    BSTNode* root;
    BSTNode* insertNode(BSTNode* node, Task t);
    BSTNode* searchNode(BSTNode* node, int id) const;
    void inorder(BSTNode* node) const;
    void destroyTree(BSTNode* node);
public:
    TaskBST();
    ~TaskBST();
    void insert(Task t);
    BSTNode* search(int id) const;
    void displayInOrder() const;
};

#endif
