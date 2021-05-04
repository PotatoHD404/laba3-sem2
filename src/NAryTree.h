//
// Created by korna on 30.04.2021.
//
#ifndef LABA3_NARYTREE_H
#define LABA3_NARYTREE_H

#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;

template<class T>
class NAryTree {
private:
    class Node;

    size_t n;
    Node *root;

    class Node {
    public:
        T data;
        Node **children;
        Node *parent;
        size_t children_count;


        Node() : Node(T()) {} // NOLINT(cppcoreguidelines-pro-type-member-init)

        explicit Node(T data) : Node(data, nullptr, new Node *[1],
                                     0) {} // NOLINT(cppcoreguidelines-pro-type-member-init)

        Node(T data, Node *parent) : // NOLINT(cppcoreguidelines-pro-type-member-init)
                Node(data, parent, new Node *[1], 0) {}

        template<size_t children_count>
        Node(T data, Node *parent, Node *(&children)[children_count]) // NOLINT(cppcoreguidelines-pro-type-member-init)
                : Node(data, parent, children, children_count) {}

        Node(T data, Node *parent, Node **children, size_t children_count) :
                data(data),
                parent(parent),
                children(children),
                children_count(children_count) {}

        void Resize(size_t newSize) {
            for (size_t i = newSize; i < children_count; ++i) {
                children[i]->~Node();
            }
            Node **newArr;
            if (newSize != 0) {
                newArr = new Node *[newSize];
                size_t old_size = old_size <= newSize ? children_count : newSize;
                memcpy(newArr, children, old_size * sizeof(Node));
            } else {
                newArr = new Node *[1];
            }
            children_count = newSize;
            delete[] children;
            children = newArr;
        }

        Node *GetLastChild() {
            return children[children_count - 1];
        }

        void AddChild(Node *child) {
            Resize(children_count + 1);
            child->parent = this;
            children[children_count - 1] = child;
        }

        T RemoveAtChild(size_t index) {
            T res = children[index]->data;
            memcpy(children + index, children + index + 1, children_count - index);
            Resize(children_count - 1);
            return res;
        }

        ~Node() {
            for (size_t i = 0; i < children_count; ++i) {
                children[i]->~Node();
            }
            delete[] children;
        }
    };

    Node *GetNode(initializer_list<size_t> indexes) {
        Node *res = root;
        for (size_t item : indexes)
            res = res->children[item];
        return res;
    }

    template<size_t N>
    Node *GetNode(size_t (&indexes)[N]) {
        Node *res = root;
        for (size_t i = 0; i < N; ++i) {
            res = res->children[indexes[i]];
        }
        return res;
    }

public:
    NAryTree() : root(nullptr), n(0) {}

    explicit NAryTree(const string &input) : NAryTree() {
        // "123 + 3232 32 123 - 32"

        size_t plusPos = input.find(" + ");
        size_t minusPos = input.find(" - ");
        size_t currentPos = 0;
        size_t length = 0;
        string current = input.substr(currentPos, minusPos < plusPos ? minusPos : plusPos);

        stringstream ss(current);
        T t;
        ss >> t;
        root = new Node(t);
        while (ss >> t) {
            ++length;
            root->AddChild(new Node(t));
        }
        n = length;
        length = 0;
        Node *tmp = root;
        while (currentPos < input.length()) {
            if (plusPos < minusPos) {
                tmp = tmp->GetLastChild();
                currentPos = plusPos + 3;
            } else {
                tmp = tmp->parent;
                currentPos = minusPos + 3;
            }
            current = input.substr(currentPos, input.length());
            plusPos = current.find(" + ");
            minusPos = current.find(" - ");
            current = input.substr(currentPos, minusPos < plusPos ? minusPos : plusPos);
            ss = stringstream(current);
            while (ss >> t) {
                ++length;
                root->AddChild(new Node(t));
            }
            if (length > n)
                n = length;
        }
    }

//    explicit NAryTree(size_t count) : NAryTree() {
//        if (count >= 536870912)
//            throw out_of_range("count < 0");
//        if (count > 0) {
//            head = new Node();
//            Node * prev = head;
//            for (size_t i = 1; i < count; ++i) {
//                prev->next = new Node();
//                prev = prev->next;
//            }
//            tail = prev;
//            length = count;
//        }
//    }
//
//    NAryTree(T *items, size_t count) : NAryTree() {
//        if (count > 536870912)
//            throw out_of_range("count < 0");
//        if (items == NULL)
//            throw invalid_argument("items is NULL");
//        if (count > 0) {
//            head = new Node(items[0]);
//            Node * prev = head;
//            for (size_t i = 1; i < count; ++i) {
//                prev->next = new Node(items[i]);
//                prev = prev->next;
//            }
//            tail = prev;
//            length = count;
//        }
//    }
//
//    NAryTree(const NAryTree<T> &list) : NAryTree() {
//        if (list.length > 0) {
//            Node * tmp = list.head;
//            head = new Node(tmp->data);
//            Node * prev = head;
//            tmp = tmp->next;
//            while (tmp != NULL) {
//                prev->next = new Node(tmp->data);
//                prev = prev->next;
//                tmp = tmp->next;
//            }
//            tail = prev;
//            length = list.length;
//        }
//    }
//
//    T &GetFirst() {
//        if (!head)
//            throw out_of_range("");
//        return head->data;
//    }
//
//    T &GetLast() {
//        if (!tail)
//            throw out_of_range("");
//        return tail->data;
//    }
//
//    T &At(size_t index) {
//        if (index < 0 || index >= length)
//            throw out_of_range("index < 0 or index >= length");
//        if (index == 0)
//            return GetFirst();
//        if (index == length - 1)
//            return GetLast();
//        return GetNode(index)->data;
//    }
//
//    void Set(size_t index, T value) {
//        if (index < 0 || index >= length)
//            throw range_error("index < 0 or index >= length");
//        At(index) = value;
//    }
//
//    NAryTree<T> GetSubList(size_t startIndex, size_t endIndex) {
//        if (startIndex < 0 || startIndex >= length)
//            throw range_error("index < 0 or index >= length");
//        if (startIndex > endIndex)
//            throw range_error("startIndex > endIndex");
//        if (endIndex >= length)
//            throw range_error("endIndex >= length");
//        NAryTree<T> res;
//        Node * tmp = GetNode(startIndex);
//        for (size_t i = startIndex; i < endIndex + 1; ++i) {
//            res.Append(tmp->data);
//            tmp = tmp->next;
//        }
//        return res;
//    }
//
//    size_t GetLength() {
//        return length;
//    }
//
//    T &operator[](size_t index) { return At(index); }
//
//    //Operations
//
//    void Append(T item) {
//        Node * tmp = new Node(item);
//        if (head == NULL)
//            head = tmp;
//        else
//            tail->next = tmp;
//        tail = tmp;
//        ++length;
//    }
//
//    void Prepend(T item) {
//        Node * tmp = new Node(item);
//        if (head == NULL) {
//            head = tmp;
//            tail = tmp;
//        } else {
//            tmp->next = head;
//            head = tmp;
//        }
//        ++length;
//    }
//
//    T PopLast() {
//        if (length < 1)
//            throw range_error("length = 0");
//        if (length == 1) {
//            return this->PopFirst();
//        }
//        Node * prev = GetNode(length - 2);
//        tail = prev;
//        T data = prev->next->data;
//        delete prev->next;
//        --length;
//        return data;
//    }
//
//    T PopFirst() {
//        if (length < 1)
//            throw range_error("length = 0");
//        Node * prev = head;
//        head = prev->next;
//        T data = prev->data;
//        delete prev;
//        --length;
//        if (length == 0) {
//            tail = NULL;
//            head = NULL;
//        }
//        return data;
//    }
//
//    void InsertAt(T item, size_t index) {
//        if (index < 0 || index >= length)
//            throw range_error("index < 0 or index >= length");
//        if (index == length - 1) {
//            this->Append(item);
//            return;
//        } else if (index == 0) {
//            this->Prepend(item);
//            return;
//        }
//
//        Node * tmp = new Node(item);
//        Node * prev = GetNode(index - 1);
//        Node * next = prev->next;
//        prev->next = tmp;
//        tmp->next = next;
//        ++length;
//    }
//
//    void RemoveAt(size_t index) {
//        if (index < 0 || index >= length)
//            throw range_error("index < 0 or index >= length");
//        if (index == length - 1) {
//            this->PopLast();
//            return;
//        } else if (index == 0) {
//            this->PopFirst();
//            return;
//        }
//
//        Node * prev = GetNode(index - 1);
//        Node * next = (prev->next)->next;
//        delete prev->next;
//        prev->next = next;
//        --length;
//    }
//
//    NAryTree<T> Concat(NAryTree<T> &list) {
//        NAryTree<T> res;
//        for (size_t i = 0; i < length; ++i) {
//            res.Append(this->At(i));
//        }
//        for (size_t i = 0; i < list.length; ++i) {
//            res.Append(list[i]);
//        }
//        return res;
//    }
//
//    NAryTree<T> &operator=(const NAryTree<T> &list) {
//        this->~NAryTree();
//        if (list.length > 0) {
//            Node * tmp = list.head;
//            head = new Node(tmp->data);
//            Node * prev = head;
//            tmp = tmp->next;
//            while (tmp != NULL) {
//                prev->next = new Node(tmp->data);
//                prev = prev->next;
//                tmp = tmp->next;
//            }
//            tail = prev;
//            length = list.length;
//        } else {
//            head = nullptr;
//            tail = nullptr;
//            length = 0;
//        }
//        return *this;
//    }
//
//    //Termination
//
//    ~NAryTree() {
//        while (length)
//            PopFirst();
//    }
};

#endif //LABA3_NARYTREE_H