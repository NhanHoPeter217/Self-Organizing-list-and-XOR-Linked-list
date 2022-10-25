#include <iostream>
#include <fstream>
#include <string>

// XOR linked list
struct Node 
{
    int val;
    Node *link;
    Node() : val(0), link(nullptr) {}
    Node(int v) : val(v), link(nullptr) {}
};

Node* XOR(Node* a, Node* b) 
{
    return (Node*) ((uintptr_t) a ^ (uintptr_t) b);
}

struct List 
{
    Node* head;
    Node* tail;
    int size;
    List() : head(nullptr), tail(nullptr), size(0) {}
    ~List()
    {
        Node* prev = nullptr, *curr = head, *next = nullptr; 
        while(curr != nullptr)
        {
            next = XOR(prev, curr->link);
            delete prev;
            size--;
            prev = curr;
            curr = next;
        }
        delete prev;
        // delete head; // C++: lol r u ded yet?
        // delete tail; // also C++: pretty sure lol.
        head = tail = nullptr;
    }
    // List(Node* h = nullptr, Node* t = nullptr, int s = 0) : head(h), tail(t), size(s) {}
    bool empty() { return head == nullptr; }
    int size() 
    { 
        int s = 0;  
        Node* curr = head, *next = nullptr, *prev = nullptr;
        while(curr != nullptr)
        {
            next = XOR(prev, curr->link);
            s++;
            prev = curr;
            curr = next;
        }
        return s;
    }
    void push_head(int v)
    {
        Node* n = new Node(v);
        if(empty()) // 0 nodes
        {
            head = n;
            tail = n;
        } 
        else if(head->link == nullptr) // 1 node
        {
            head->link = n;
            n->link = head;
            head = n;
            tail = n->link;
        } 
        else 
        {
            head->link = XOR(head->link, n);
            n->link = head;
            head = n;
        }
        size++;
    }
    void push_tail(int v)
    {
        Node* n = new Node(v);
        if(empty()) // 0 nodes
        {
            head = n;
            tail = n;
        } 
        else if(tail->link == nullptr) // 1 node = head
        {
            tail->link = n;
            n->link = tail;
            tail = n;
            head = n->link;
        } 
        else 
        {
            tail->link = XOR(tail->link, n);
            n->link = tail;
            tail = n;
        }
        size++;
    }
    void insert(int v, int index)
    {
        Node* n = new Node(v);
        if(empty())
        {
            head = n;
            tail = n;
        } 
        else if(index == 0)
        {
            push_head(v);
        } 
        else if(index == size)
        {
            push_tail(v);
        } 
        else if(index > size)
        {
            return;
        }
        else
        {
            Node* prev = nullptr, *curr = head, *next = head->link;
            for(int i = 0; i < index; i++)
            {
                next = XOR(prev, curr->link);
                prev = curr;
                curr = next;
            }
            n->link = XOR(prev, curr);
            curr->link = XOR(XOR(curr->link, prev), n);
            prev->link = XOR(XOR(prev->link, curr), n);
        }
        size++;
    }
    void pop_head()
    {
        if(empty())
        {
            return;
        } 
        else if(head->link == nullptr)
        {
            delete head;
            head = tail = nullptr;
        } 
        else
        {
            Node* n = head;
            head = head->link;
            head->link = XOR(head->link, n);
            delete n;
        }
        size--;
    }
    void pop_tail()
    {
        if(empty())
        {
            return;
        }
        else if(tail->link == nullptr)
        {
            delete tail;
            head = tail = nullptr;
        }
        else
        {
            Node* n = tail;
            tail = tail->link;
            tail->link = XOR(tail->link, n);
            delete n;
        }
        size--;
    }
    void remove(int index)
    {
        if(empty())
        {
            return;
        } 
        else if(index == 0)
        {
            pop_head();
        } 
        else if(index == size - 1)
        {
            pop_tail();
        } 
        else if(index > size - 1)
        {
            return;
        }
        else
        {
            Node* prev = nullptr, *curr = head, *next = head->link;
            for(int i = 0; i < index; i++)
            {
                next = XOR(prev, curr->link);
                prev = curr;
                curr = next;
            }
            next = XOR(prev, curr->link);
            prev->link = XOR(XOR(prev->link, curr), next);
            next->link = XOR(XOR(next->link, curr), prev);
            // curr->link = XOR(XOR(curr->link, prev), XOR(curr->link, curr));
            delete curr;
            size--;
        }
    }
    void readFile(std::string filename)
    { 
        std::ifstream file(filename);
        int n;
        while(file >> n)
        {
            push_tail(n);
        }
        file.close();
    }
    void writeFile(std::string filename)
    {
        std::ofstream file(filename);
        Node* prev = nullptr, *curr = head, *next = head->link;
        while(curr != nullptr)
        {
            file << curr->val << " ";
            next = XOR(prev, curr->link);
            prev = curr;
            curr = next;
        }
        file.close();
    }
    void print()
    {
        Node* prev = nullptr, *curr = head, *next = nullptr; 
        while(curr != nullptr)
        {
            std::cout << curr->val << " ";
            next = XOR(prev, curr->link);
            prev = curr;
            curr = next;
        }
        std::cout << std::endl;
    }
};

int main()
{
    List l;
    for(int i = 0; i < 10; i++)
    {
        l.push_head(i);
    }
    l.print();
    l.remove(3);
    l.print();
    l.insert(99, 9); // 0-indexed
    l.print();
    return 0;
}

// insertion(build) and removal(s): o(n)
// check empty o(1)
// tell size o(n)

// =========

// The underlying principle of the XOR linked list can be applied to any reversible binary operation, such as addition or subtraction.
// The same concept can be applied to XOR BSTs, allowing 2 directional traversal in the BSTs

// =========

// gần y chang doubly linked list, khác mỗi cái thay vì doubly có 2 biến *prev *next thì thằng này gói trong 1 biến link = &prev ^ &next

// =========
// sôt: https://en.wikipedia.org/wiki/XOR_linked_list https://www.geeksforgeeks.org/xor-linked-list-a-memory-efficient-doubly-linked-list-set-1/