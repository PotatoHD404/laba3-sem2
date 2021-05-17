//
// Created by korna on 30.04.2021.
//
#ifndef LABA3_NARYTREE_H
#define LABA3_NARYTREE_H

#include <iostream>
#include <cstring>
#include <sstream>
#include <regex>
#include "ArraySequence.h"
#include "Stack.h"
#include "Pair.h"

using namespace std;

template<class T>
class NAryTree {
protected:
    template<class T1>
    class Node {
    public:
        ArraySequence<T1> keys;
        ArraySequence<Node<T1> *> children;
        Node<T1> *parent;

        Node() : keys(), children(ArraySequence<Node<T1> *>()), parent(nullptr) {}

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
                tmp->keys = node->keys;
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
                tmp->keys = node->keys.Map(mapper);
                for (int i = 0; i < node->ChildrenCount(); ++i)
                    if (node->children[i] != NULL) {
                        tmp->AddChild();
                        s.Push(node->children[i]);
                        s1.Push(tmp->children[i]);
                    }
            }
        }

        explicit Node(T1 data) : Node(data, nullptr, ArraySequence<Node<T1> *>()) {}

        Node(T1 data, Node<T1> *parent) : Node(data, parent, ArraySequence<Node<T1> *>()) {}

        template<size_t children_count>
        Node(T1 data, Node<T1> *parent, Node<T1> *(&children)[children_count]):
                Node(data, parent, ArraySequence<Node<T1> *>(children)) {}

        Node(T1 data, Node<T1> *parent, ArraySequence<Node<T1> *> children) :
                keys({data}), parent(parent), children(children) {}

        Node(ArraySequence<T1> keys, Node<T1> *parent, ArraySequence<Node<T1> *> children) :
                keys(keys), parent(parent), children(children) {}

        T1 Reduce(T1(*f)(T1, T1), T1 const &c) {
            if (f == nullptr)
                throw invalid_argument("mapper is NULL");
            T res = c;
            Stack<Node<T> *> s;
            Stack<Node<T1> *> s1;
            s.Push(this);
            while (!s.IsEmpty()) {
                Node<T> *node = s.Pop();
                res = node->keys.Reduce(f, res);
                for (int i = 0; i < node->ChildrenCount(); ++i)
                    if (node->children[i] != NULL)
                        s.Push(node->children[i]);

            }
        }


        size_t ChildrenCount() {
            return children.Count();
        }

        bool IsLeaf() {
            return children.Count() == 0;
        }

        Node<T1> *GetLastChild() {
            return children.GetLast();
        }

        void AddChild(Node<T1> *child) {
            child->parent = this;
            children.Append(child);
        }

        void AddChild() {
            Node<T1> *child = new Node<T1>();
            child->parent = this;
            children.Append(child);
        }

        ~Node() {
            for (size_t i = 0; i < children.Count(); ++i) {
                delete children[i];
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

    size_t n;
    Node<T> *root;
    size_t count;

public:


    NAryTree() : NAryTree(new Node<T>(), 0, 0) {}

    explicit NAryTree(Node<T> *root, size_t count) : root(root), n(root->ChildrenCount()), count(count) {}

    NAryTree(NAryTree<T> const &tree) : root(new Node<T>(tree.root)), n(tree.n), count(tree.count) {}

    NAryTree(Node<T> *root, size_t n, size_t count) : n(n), root(root), count(count) {}

    NAryTree(const string &str, const string &br) {
        count = 0;
        regex word_regex(R"(([^\dK])((\d)+|(K))([^\dK]))");
        auto words_begin = sregex_iterator(br.begin(), br.end(), word_regex);
        auto words_end = sregex_iterator();
        const size_t length = distance(words_begin, words_end);
        n = length - 1;
        string check;
        char brackets[length][2];
        size_t indexes[length];
        int j = 0;
        for (sregex_iterator i = words_begin; i != words_end; ++i) {
            smatch match = *i;
            string match_str = match.str();
            size_t num;
            if (match_str[1] == 'K')
                num = length;
            else {
                stringstream s(match_str.substr(1, match_str.size() - 2));
                s >> num;
            }
            num -= 1;
            if (num >= length)
                throw runtime_error("wrong input");
            indexes[j] = num;
            if (check.find(match_str[0]) != string::npos || check.find(match_str[match_str.size() - 1]) != string::npos)
                throw runtime_error("wrong input(brackets)");
            brackets[num][0] = match_str[0];
            brackets[num][1] = match_str[match_str.size() - 1];
            check += string(1, brackets[num][0]) + string(1, brackets[num][1]);
            ++j;
        }
        check = "";
        string openBr;
        string closeBr;
        string rootBr = string(1, brackets[n][0]) + string(1, brackets[n][1]);
        for (int i = 0; i < n; ++i) {
            openBr += string(1, brackets[i][0]);
            closeBr += string(1, brackets[i][1]);
        }
        size_t len = str.length();

        Stack<char> bracketSequence;
        root = new Node<T>();
        Node<T> *node = root;
        size_t tmp;
        for (int i = 0; i < len; ++i) {
            size_t found1 = openBr.find(str[i]);
            size_t found2 = closeBr.find(str[i]);
            if (found1 != string::npos) {
                bracketSequence.Push(str[i]);
                while (node->ChildrenCount() <= found1)
                    node->AddChild();
                node = node->children[found1];
            } else if (rootBr[0] == str[i]) {
                bracketSequence.Push(str[i]);
                tmp = i;
            } else if (found2 != string::npos) {
                if (bracketSequence.Pop() != openBr[found2])
                    throw std::runtime_error("Wrong input");
                node = node->parent;
            } else if (rootBr[1] == str[i]) {
                if (bracketSequence.Pop() != rootBr[0])
                    throw std::runtime_error("Wrong input");
                try {
                    stringstream ss(str.substr(tmp + 1, i));
                    T d;
                    ss >> node->keys[0];
                    while (ss >> d) {
                        count++;
                        node->keys.Append(d);
                    }

                }
                catch (const std::exception &) {
                    throw std::runtime_error("Wrong input type");
                }
            }
        }
        if (!bracketSequence.IsEmpty())
            throw std::runtime_error("Wrong input");
    }

    NAryTree<T> &operator=(const NAryTree<T> &list) {
        this->~NAryTree();
        n = list.n;
        root = new Node<T>(*list.root);
        return *this;
    }


//    ArraySequence<T> ToArraySequence() {
//        if (root == NULL)
//            throw runtime_error("Root is NULL");
//        stringstream buffer;
//        function<void(Node<T> *, long long)> VisitNode = [&](Node<T> *node, long long br) {
//            if (br != -1)
//                buffer << brackets[indexes[br]][0];
//            for (size_t i = 0; i < length; ++i)
//                if (indexes[i] == length - 1) {
//                    buffer << brackets[length - 1][0];
//                    for (size_t k = 0; k < node->keys.Count(); ++k) {
//                        buffer << node->keys[k];
//                        if (k != node->keys.Count() - 1)
//                            buffer << " ";
//
//                    }
//                    buffer << brackets[length - 1][1];
//                } else if (indexes[i] < node->ChildrenCount())
//                    VisitNode(node->children[indexes[i]], i);
//            if (br != -1)
//                buffer << brackets[indexes[br]][1];
//        };
//        VisitNode(root, -1);
//        return buffer.str();
//    }

    size_t Count() { return count; }

    string Order(const string &str) {
        regex word_regex(R"(([^\dK])((\d)+|(K))([^\dK]))");
        auto words_begin = sregex_iterator(str.begin(), str.end(), word_regex);
        auto words_end = sregex_iterator();
        size_t length = distance(words_begin, words_end);
        if (!regex_search(str, regex(R"(^(([^\dK])((\d)+|(K))([^\dK]))+$)")))
            throw runtime_error("wrong input");
//        cout << length << endl;
        char brackets[length][2];
        size_t indexes[length];
        int j = 0;
        for (sregex_iterator i = words_begin; i != words_end; ++i) {
            smatch match = *i;
            string match_str = match.str();
            size_t num;
            if (match_str[1] == 'K')
                num = length;
            else {
                stringstream s(match_str.substr(1, match_str.size() - 2));
                s >> num;
            }
            num -= 1;
            if (num >= length)
                throw runtime_error("wrong input");
            indexes[j] = num;
            brackets[num][0] = match_str[0];
            brackets[num][1] = match_str[match_str.size() - 1];
            ++j;
        }
//        if (length >= n) {
//            indexes[length - 1] = n;
//            brackets[n][0] = brackets[--length][0];
//            brackets[n][1] = brackets[length][1];
//            length = n + 1;
//        }
//        if (length != n + 1)
//            throw runtime_error("wrong indexes: N != n + 1");
        if (root == NULL)
            throw runtime_error("Root is NULL");
        stringstream buffer;
        function<void(Node<T> *, long long)> VisitNode = [&](Node<T> *node, long long br) {
            if (br != -1)
                buffer << brackets[indexes[br]][0];
            for (size_t i = 0; i < length; ++i)
                if (indexes[i] == length - 1) {
                    buffer << brackets[length - 1][0];
                    for (size_t k = 0; k < node->keys.Count(); ++k) {
                        buffer << node->keys[k];
                        if (k != node->keys.Count() - 1)
                            buffer << " ";

                    }
                    buffer << brackets[length - 1][1];
                } else if (indexes[i] < node->ChildrenCount())
                    VisitNode(node->children[indexes[i]], i);
            if (br != -1)
                buffer << brackets[indexes[br]][1];
        };
        VisitNode(root, -1);
        return buffer.str();
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

    ~NAryTree() {
        delete root;
    }
};

#endif //LABA3_NARYTREE_H