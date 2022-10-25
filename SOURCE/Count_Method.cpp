#include <iostream>
#include <stdint.h>
#include <vector>

using namespace std;

struct self_node
{
    int64_t value;
    uint64_t count;
    self_node* next;
};

struct self_list
{
    self_node* head;
    self_node* tail;
};

void initList(self_list &L)
{
    L.head = NULL;
    L.tail = NULL;
}

self_node* createNewNode(int64_t new_value)
{
    self_node* new_node = new self_node;
    new_node->value = new_value;
    new_node->count = 0;
    new_node->next = NULL;
    return new_node;
}

bool isEmpty(self_list L)
{
    if (L.head == NULL) return true;
    return false;
}

uint64_t numberOfItems(self_list L)
{
    uint64_t count_ = 0;
    for (self_node* p = L.head; p; p = p->next) ++count_;
    return count_;
}

bool insertNewItem(self_list &L, int64_t new_value) // Add tail
{
    self_node* node = createNewNode(new_value);
    if (node == NULL) return false;
    if (L.head == NULL) {
        L.head = node;
        L.tail = node;
        return true;
    }
    L.tail->next = node;
    L.tail = node;
    return true;
}

void removeItem(self_list &L, int64_t val)
{
    if (L.head == NULL) return;
    if (L.head == L.tail) {
        if (L.head->value == val) {
            self_node* node_temp = L.head;
            L.head = NULL;
            L.tail = NULL;
            delete node_temp;
        }
        return;
    }
    if (L.head->value == val) {
        self_node* node_temp = L.head;
        L.head = node_temp->next;
        delete node_temp;
        return;
    }
    self_node* previous = L.head;
    for (self_node* p = L.head->next; p; p = p->next) {
        if (p->value == val) {
            previous->next = p->next;
            if (p == L.tail) L.tail = previous;
            delete p;
            return;
        }
        previous = p;
    }
}

bool buildLinkedList(self_list &L, vector <int64_t> list)
{
    for (int i = 0; i < list.size(); ++i) {
        if (insertNewItem(L, list[i]) == false) return false;
    }
    return true;
}

void removeAllItems(self_list &L)
{
    self_node* Next;
    for (self_node* p = L.head; p; ) {
        Next = p->next;
        delete p;
        p = Next;
    }
    L.head = NULL;
    L.tail = NULL;
}

void update_new_position(self_list &L, self_node* &previous, self_node* &node)
{
    if (node->count < previous->count) return;
    if (node == L.tail) L.tail = previous;
    previous->next = node->next;
    if (node->count >= L.head->count) {
        node->next = L.head;
        L.head = node;
        return;
    }
    previous = L.head;
    for (self_node* p = L.head->next; p; p = p->next) {
        if (node->count >= p->count) {
            previous->next = node;
            node->next = p;
            return;
        }
        previous = p;
    }
}

bool search_self_list(self_list &L, int64_t val)
{
    if (L.head == NULL) return false;
    if (L.head->value == val) {
        ++(L.head->count);
        return true;
    }

    self_node* previous = L.head;

    for (self_node* p = L.head->next; p; p = p->next) {
        if (p->value == val) {
            ++(p->count);
            update_new_position(L, previous, p);
            return true;
        }
        previous = p;
    }

    return false;
}

void display_list(self_list L)
{
    for (self_node* p = L.head; p; p = p->next) {
        cout << '[' << p->value << ']';
        if (p->next) cout << "->";
    }
    cout << '\n';
}

int main()
{
    self_list L;
    int n;
    initList(L);

    cout << "A Self Organizing List has been initialized.\n";
    system("pause");
    system("cls");

    while (n != 8) {
        cout << "Please choose one of the following operations: \n";
        cout << "1. Test whether a linked list is empty\n";
        cout << "2. Get the number of items in a linked list\n";
        cout << "3. Insert a new item into the list (Insert to the tail of the list)\n";
        cout << "4. Remove an item from the list\n";
        cout << "5. Build a linked list from given items\n";
        cout << "6. Search an item from the list\n";
        cout << "7. Remove all items from the linked list\n";
        cout << "8. Remove all items from the linked list and stop the process\n\n";
        cout << "List: "; display_list(L);
        cout << "Your choice (Type a number): "; cin >> n;

        system("cls");

        if (n == 1) {
            if (isEmpty(L)) cout << "The list is empty\n";
            else cout << "The list is not empty\n";
        }
        else if (n == 2) {
            cout << "Number of items in the linked list: ";
            cout << numberOfItems(L);
            cout << '\n';
        }
        else if (n == 3) {
            int64_t value;
            cout << "Value of item: "; cin >> value;
            if (insertNewItem(L, value)) cout << "Insert " << value << " successful!\n";
            else cout << "Can't insert item!";
        }
        else if (n == 4) {
            int64_t value;
            cout << "Value of item: "; cin >> value;
            removeItem(L, value);
            cout << "Item " << value << " has been removed\n";
        }
        else if (n == 5) {
            if (!isEmpty(L)) {
                cout << "Can't build because the list existed.\n";
                cout << "You must delete the old list and then build the new list later.\n";
            }
            else {
                vector <int64_t> list; // Declare a vector with type int64_t
                cout << "Number of items: "; cin >> n;
                int64_t k;
                for (int i = 0; i < n; ++i) {
                    cout << "Value of item " << i + 1 << ": "; cin >> k;
                    list.push_back(k);
                }
                if (buildLinkedList(L, list)) cout << "Build successful\n";
            }
        }
        else if (n == 6) {
            int64_t value;
            cout << "Value of item: "; cin >> value;
            if (search_self_list(L, value)) cout << "Search " << value << " successful\n";
        }
        else if (n == 7) {
            removeAllItems(L);
            cout << "Remove successful\n";
        }
        else if (n == 8) {
            removeAllItems(L);
        }
        else cout << "Wrong Syntax\n";
        cout << "\nList: "; display_list(L);
        cout << '\n';
        system("pause");
        system("cls");
    }

    return 0;
}