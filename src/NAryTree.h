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
#include <regex>
#include "ArraySequence.h"
#include "Stack.h"
#include "Pair.h"

using namespace std;

template<class T>
class NAryTree {
private:
//    friend class BTree<T>;
    template<class T1>
    class Node {
    private:
        ArraySequence<T1> data;
        ArraySequence<Node<T1> *> children;
        Node<T1> *parent;
    public:
        friend class NAryTree;

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
                tmp->data = node->data.Map(mapper);
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
                data({data}), parent(parent), children(children) {}

        T1 Reduce(T1(*f)(T1, T1), T1 const &c) {
            if (f == nullptr)
                throw invalid_argument("mapper is NULL");
            T res = c;
            Stack<Node<T> *> s;
            Stack<Node<T1> *> s1;
            s.Push(this);
            while (!s.IsEmpty()) {
                Node<T> *node = s.Pop();
                res = node->data.Reduce(f, res);
                for (int i = 0; i < node->ChildrenCount(); ++i)
                    if (node->children[i] != NULL)
                        s.Push(node->children[i]);

            }
        }

        size_t ChildrenCount() {
            return children.GetLength();
        }

        bool IsLeaf() {
            return children.GetLength() == 0;
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
            for (size_t i = 0; i < children.GetLength(); ++i) {
                delete children[i];
            }
        }
    };

    size_t n;
    Node<T> *root;

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
    NAryTree() : NAryTree(new Node<T>(), 0) {}

    explicit NAryTree(Node<T> *root) : root(root), n(root->ChildrenCount()) {}

    NAryTree(NAryTree<T> const &tree) : root(new Node<T>(tree.root)), n(tree.n) {}

    NAryTree(Node<T> *root, size_t n) : root(root), n(n) {}

    explicit NAryTree(const string &input) : NAryTree() {
        // "123 123 + 3232 32 123 - 32"

        size_t plusPos = input.find(" + ");
        size_t minusPos = input.find(" - ");
        size_t currentPos = 0;
        size_t length = 0;
        string current = input.substr(currentPos,
                                      minusPos == plusPos == string::npos ? input.length() : minusPos < plusPos
                                                                                             ? minusPos : plusPos);

        stringstream ss(current);
        currentPos = current.find(' ');
        T t;
        ss >> t;

        current = ss.str().substr(currentPos, ss.str().length() - 1);
        root = new Node<T>(t);
        Node<T> *tmp = root;
        while (currentPos < input.length()) {
            ss = stringstream(current);
            currentPos += current.length();
            while (ss >> t) {
                tmp->AddChild(new Node<T>(t));
                length = tmp->ChildrenCount();
            }
            if (!(plusPos == minusPos && plusPos == string::npos)) {
                if (plusPos <= minusPos) {
                    tmp = tmp->GetLastChild();
                    currentPos = plusPos + 3;
                } else {
                    tmp = tmp->parent;
                    currentPos = minusPos + 3;
                }
            }
            plusPos = current.find(" + ");
            minusPos = current.find(" - ");
            current = input.substr(currentPos, minusPos == plusPos == string::npos ? input.length() : minusPos < plusPos
                                                                                                      ? minusPos
                                                                                                      : plusPos);
            if (length > n)
                n = length;
            if (current.length() == 0)
                break;

        }
    }

//{1}({2})[{3}({4})[{7}]] recompile pls)
    NAryTree(const string &str, const string &br) {

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
                    ss >> node->data[0];
                    while (ss >> d) {
                        node->data.Append(d);
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

    string Order(const string &str) {
        regex word_regex(R"(([^\dK])((\d)+|(K))([^\dK]))");
        auto words_begin = sregex_iterator(str.begin(), str.end(), word_regex);
        auto words_end = sregex_iterator();
        const size_t length = distance(words_begin, words_end);
        if (length != n + 1 || !regex_search(str, regex(R"(^(([^\dK])((\d)+|(K))([^\dK]))+$)")))
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
        if (length != n + 1)
            throw runtime_error("wrong indexes: N != n + 1");
        if (root == NULL)
            throw runtime_error("Root is NULL");
        stringstream buffer;
        function<void(Node<T> *, size_t)> VisitNode = [&](Node<T> *node, size_t br) {
            if (br != -1)
                buffer << brackets[indexes[br]][0];
            for (int i = 0; i < length; ++i)
                if (indexes[i] == n) {
                    buffer << brackets[n][0];
                    for (int k = 0; k < node->data.GetLength(); ++k) {
                        buffer << node->data[k];
                        if (k != node->data.GetLength() - 1)
                            buffer << " ";
                    }
                    buffer << brackets[n][1];
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