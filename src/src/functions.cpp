#include "structures.h"

// ==================== IMPLEMENTATION: BST ====================
BookBST::BookBST() : root(nullptr) {}
BookBST::~BookBST() { destroyTree(root); }
void BookBST::destroyTree(BSTNode* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}
BSTNode* BookBST::insertNode(BSTNode* node, Book b) {
    if (!node) return new BSTNode(b);
    if (b.id < node->data.id) node->left = insertNode(node->left, b);
    else if (b.id > node->data.id) node->right = insertNode(node->right, b);
    return node;
}
void BookBST::insert(Book b) { root = insertNode(root, b); }

BSTNode* BookBST::searchNode(BSTNode* node, int id) const {
    if (!node || node->data.id == id) return node;
    if (id < node->data.id) return searchNode(node->left, id);
    return searchNode(node->right, id);
}
BSTNode* BookBST::search(int id) const { return searchNode(root, id); }

void BookBST::inorder(BSTNode* node) const {
    if (node) {
        inorder(node->left);
        node->data.display();
        inorder(node->right);
    }
}
void BookBST::displayInOrder() const {
    if (!root) { std::cout << "Kho sach dang trong!\n"; return; }
    inorder(root);
}
void BookBST::findMostBorrowedNode(BSTNode* node, Book& maxBook) const {
    if (!node) return;
    if (node->data.borrowCount > maxBook.borrowCount) {
        maxBook = node->data;
    }
    findMostBorrowedNode(node->left, maxBook);
    findMostBorrowedNode(node->right, maxBook);
}
Book BookBST::getMostBorrowed() const {
    Book maxBook = {-1, "Chưa có", "Không có", true, -1};
    findMostBorrowedNode(root, maxBook);
    return maxBook;
}
void BookBST::saveTreeToFile(BSTNode* node, std::ofstream& outFile) const {
    if (node) {
        outFile << node->data.id << "," << node->data.title << "," 
                << node->data.author << "," << node->data.isAvailable << "," 
                << node->data.borrowCount << "\n";
        saveTreeToFile(node->left, outFile);
        saveTreeToFile(node->right, outFile);
    }
}
void BookBST::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) return;
    saveTreeToFile(root, outFile);
    outFile.close();
}
void BookBST::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) return;
    int id, borrowCount;
    bool isAvailable;
    std::string title, author, line;
    while (inFile >> id) {
        inFile.ignore(); // Bỏ dấu phẩy
        std::getline(inFile, title, ',');
        std::getline(inFile, author, ',');
        inFile >> isAvailable;
        inFile.ignore(); // Bỏ dấu phẩy
        inFile >> borrowCount;
        inFile.ignore(); // Bỏ dấu xuống dòng
        insert({id, title, author, isAvailable, borrowCount});
    }
    inFile.close();
}

// ==================== IMPLEMENTATION: QUEUE ====================
WaitingQueue::WaitingQueue() : front(nullptr), rear(nullptr) {}
WaitingQueue::~WaitingQueue() { while (!isEmpty()) dequeue(); }
void WaitingQueue::enqueue(Reader r) {
    QueueNode* newNode = new QueueNode(r);
    if (!rear) { front = rear = newNode; }
    else { rear->next = newNode; rear = newNode; }
}
Reader WaitingQueue::dequeue() {
    if (isEmpty()) return {-1, "Trống", 0};
    QueueNode* temp = front;
    Reader r = temp->reader;
    front = front->next;
    if (!front) rear = nullptr;
    delete temp;
    return r;
}
bool WaitingQueue::isEmpty() const { return front == nullptr; }
void WaitingQueue::displayQueue() const {
    if (isEmpty()) { std::cout << "Hang doi cho trong.\n"; return; }
    QueueNode* temp = front;
    while (temp) {
        std::cout << "- Doc gia: " << temp->reader.name << " (ID: " << temp->reader.id << ")\n";
        temp = temp->next;
    }
}

// ==================== IMPLEMENTATION: STACK ====================
ActionStack::ActionStack() : top(nullptr) {}
ActionStack::~ActionStack() { while (!isEmpty()) pop(); }
void ActionStack::push(std::string action) {
    StackNode* newNode = new StackNode(action);
    newNode->next = top;
    top = newNode;
}
std::string ActionStack::pop() {
    if (isEmpty()) return "Ngan xep trong";
    StackNode* temp = top;
    std::string act = temp->action;
    top = top->next;
    delete temp;
    return act;
}
bool ActionStack::isEmpty() const { return top == nullptr; }
void ActionStack::displayHistory() const {
    if (isEmpty()) { std::cout << "Chua co lich su thao tac nao.\n"; return; }
    StackNode* temp = top;
    while (temp) {
        std::cout << "[History] " << temp->action << "\n";
        temp = temp->next;
    }
}

// ==================== IMPLEMENTATION: LINKED LIST ====================
ReaderList::ReaderList() : head(nullptr) {}
ReaderList::~ReaderList() {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}
void ReaderList::addReader(Reader r) {
    ListNode* newNode = new ListNode(r);
    newNode->next = head;
    head = newNode;
}
void ReaderList::displayAll() const {
    if (!head) { std::cout << "Danh sach doc gia trong.\n"; return; }
    ListNode* temp = head;
    while (temp) {
        std::cout << "ID DG: " << temp->data.id << " | Ten: " << temp->data.name 
                  << " | So lan muon: " << temp->data.borrowCounted << "\n";
        temp = temp->next;
    }
}
Reader ReaderList::getMostActive() const {
    if (!head) return {-1, "Chưa có", 0};
    ListNode* temp = head;
    Reader maxReader = temp->data;
    while (temp) {
        if (temp->data.borrowedCount > maxReader.borrowedCount) {
            maxReader = temp->data;
        }
        temp = temp->next;
    }
    return maxReader;
}
bool ReaderList::isEmpty() const { return head == nullptr; }
