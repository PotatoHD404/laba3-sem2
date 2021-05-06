#pragma clang diagnostic Push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
#pragma ide diagnostic ignored "modernize-use-auto"
//
// Created by korna on 30.04.2021.
//
#ifndef LABA3_NARYTREE_H
#define LABA3_NARYTREE_H

#include <iostream>
#include <cstring>
#include <sstream>
#include "ArraySequence.h"
#include "Stack.h"

using namespace std;

template<class T>
class NAryTree {
private:
    template<class T1>
    class Node;

    size_t n;
    Node<T> *root;

    template<class T1>
    class Node {
    public:
        T1 data;
        ArraySequence<Node<T1> *> children;
        Node<T1> *parent;

        Node() : Node(T1()) {}

        Node(Node<T1> const &node) : Node(&node) {}

        explicit Node(Node<T1> *input) : Node() {
            Node<T1> *res = new Node();
            Stack<Node<T1> *> s;
            Stack<Node<T1> *> s1;
            s.Push(input);
            s1.Push(this);
            while (!s.IsEmpty()) {
                Node<T1> *node = s.Pop();
                Node<T1> *tmp = s1.Pop();
                tmp->data = node->data;
                for (int i = 0; i < node->ChildrenCount(); ++i)
                    if (node->children[i] != NULL) {
                        tmp->AddChild();
                        s.Push(node->children[i]);
                        s1.Push(tmp->children[i]);
                    }
            }
        }

        template<class T2>
        explicit Node(Node<T2> *input, T1 (*mapper)(T2)) {
            Stack<Node<T2> *> s;
            Stack<Node<T1> *> s1;
            s.Push(input);
            s1.Push(this);
            while (!s.IsEmpty()) {
                Node<T2> *node = s.Pop();
                Node<T1> *tmp = s1.Pop();
                tmp->data = mapper(node->data);
                for (int i = 0; i < node->ChildrenCount(); ++i)
                    if (node->children[i] != NULL) {
                        tmp->AddChild();
                        s.Push(node->children[i]);
                        s1.Push(tmp->children[i]);
                    }
            }
        }

        explicit Node(T1 data) : Node(data, nullptr, new Node *[1], 0) {}

        Node(T1 data, Node *parent) : Node(data, parent, new Node *[1], 0) {}

        template<size_t ChildrenCount()>
        Node(T1 data, Node *parent, Node *(&children)[ChildrenCount()]):  data(data), parent(parent),
                                                                          children(children) {}

        Node(T1 data, Node *parent, ArraySequence<Node<T1> *> children, size_t ChildrenCount()) : data(data),
                                                                                                  parent(parent),
                                                                                                  children(children) {}

        T1 Reduce(T1(*f)(T1, T1), T1 const &c) {
            if (f == nullptr)
                throw std::invalid_argument("mapper is NULL");
            T res = c;
            Stack<Node<T> *> s;
            Stack<Node<T1> *> s1;
            s.Push(this);
            while (!s.IsEmpty()) {
                Node<T> *node = s.Pop();
                res = f(node->data, res);
                for (int i = 0; i < node->ChildrenCount(); ++i)
                    if (node->children[i] != NULL)
                        s.Push(node->children[i]);

            }
        }

        size_t ChildrenCount() {
            return children.GetLength();
        }

        Node *GetLastChild() {
            return children.GetLast();
        }

        void AddChild(Node *child) {
            children.Append(child);
        }

        T1 RemoveAtChild(size_t index) {
            return children.RemoveAt(index);
        }

        ~Node() {
            for (size_t i = 0; i < children.GetLength(); ++i) {
                children[i]->~Node();
            }
        }
    };

    Node<T> *GetNode(initializer_list<size_t> indexes) {
        Node<T> *res = root;
        for (size_t item : indexes)
            res = res->children[item];
        return res;
    }

    template<size_t N>
    Node<T> *GetNode(const size_t (&indexes)[N]) {
        Node<T> *res = root;
        for (size_t i = 0; i < N; ++i) {
            res = res->children[indexes[i]];
        }
        return res;
    }

    template<size_t N>
    ArraySequence<Node<T> *> GetPath(const size_t (&indexes)[N]) {
        Node<T> *tmp = root;
        ArraySequence<Node<T> *> res;
        for (size_t i = 0; i < N; ++i) {
            res.Append(tmp);
            tmp = tmp->children[indexes[i]];
        }
        return res;
    }

public:
    NAryTree() : root(nullptr), n(0) {}

    explicit NAryTree(Node<T> *root) : root(root), n(root->ChildrenCount()) {}

    NAryTree(NAryTree<T> const &tree) : root(new Node(tree.root)), n(tree.n) {}

    NAryTree(Node<T> *root, size_t n) : root(root), n(n) {}

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
        Node<T> *tmp = root;
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

    template<size_t N>
    string Order(const size_t (&indexes)[N], const string &brackets) {
        if (N != n + 1)
            throw std::runtime_error("wrong indexes: N != n + 1");
        if (root == NULL)
            throw std::runtime_error("Root is NULL");
        stringstream buffer;
        Stack<Node<T> *> s;
        s.Push(root);
        while (!s.IsEmpty()) {
            Node<T> *node = s.Pop();
            for (int i = 0; i < N; ++i)
                if (indexes[i] == N)
                    buffer << node->data << " ";
                else if (node->children != NULL && indexes[i] < node->ChildrenCount())
                    if (node->children[indexes[i]] != NULL)
                        s.Push(node->children[indexes[i]]);
        }
        string res;
        buffer >> res;
        return res;
    }
    string Order(initializer_list<size_t> const &initializerList, const string &brackets) {
        size_t indexes[n] = initializerList;
        return Order(indexes, brackets);
    }

//    string Order(initializer_list<size_t> const &initializerList, const string &brackets) {
//        size_t indexes[n] = initializerList;
//        return Order(indexes, brackets);
//    }

    string Preorder() {
        size_t indexes[n + 1];
        for (int i = 0; i < n + 1; i++)
            indexes[i] = i;
        return Order(indexes);
    }

    string Postorder() {
        size_t indexes[n + 1];
        for (int i = 0; i < n + 1; i++)
            indexes[n - i - 1] = i;
        return Order(indexes);
    }

    NAryTree<T> Subtree(initializer_list<size_t> indexes) {
        return NAryTree<T>(new Node(GetNode(indexes)));
    }

    template<size_t N>
    NAryTree<T> Subtree(const size_t (&indexes)[N]) {
        return NAryTree<T>(new Node(GetNode(indexes)));
    }

    template<typename T1>
    NAryTree<T1> Map(T1 (*mapper)(T)) {
        return NAryTree<T1>(new Node(root, mapper));
    }

    T Reduce(T (*f)(T), T const &c) {
        return root->Reduce(f, c);
    }


//    iterativePreorder(node)
//  if (node = null)
//    return
//  s ← empty stack
//  s.Push(node)
//  while (not s.isEmpty())
//    node ← s.Pop()
//    visit(node)
//    //правый потомок заносится первым, так что левый потомок обрабатывается первым
//    if (node.right ≠ null)
//      s.Push(node.right)
//    if (node.left ≠ null)
//      s.Push(node.left)

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
#pragma clang diagnostic pop