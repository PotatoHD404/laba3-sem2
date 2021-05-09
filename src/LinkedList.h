//
// Created by korna on 20.03.2021.
//
#ifndef LABA2_LINKEDLIST_H
#define LABA2_LINKEDLIST_H

#include <iostream>
#include <cstring>

using namespace std;

///
/// \tparam T - type
template<typename T>
class LinkedList {
private:
    class Node;

    size_t length;
    Node *head, *tail;

    class Node {
    public:
        T data;
        Node *next;

        Node() : Node(T(), NULL) {}

        explicit Node(T data) : Node(data, NULL) {}

        Node(T data, Node *next) : next(next), data(data) {}
    };

    ///
    /// \param index - index of node
    /// \return - posize_ter to the node of index
    Node *GetNode(size_t index) {
        Node *res = head;
        for (size_t i = 0; i < index; i++) {
            res = res->next;
        }
        return res;
    }


public:
    //Creation of the object
    /// Generates empty LinkedList
    LinkedList() : head(NULL), tail(NULL), length() {}

/// Generates LinkedList with some count of elements
/// \param count - Number of elements in List
    explicit LinkedList(size_t count) : LinkedList() {
        if (count >= 536870912)
            throw out_of_range("count < 0");
        if (count > 0) {
            head = new Node();
            Node *prev = head;
            for (size_t i = 1; i < count; ++i) {
                prev->next = new Node();
                prev = prev->next;
            }
            tail = prev;
            length = count;
        }
    }

    /// Generates LinkedList from array of items
    /// \param items - Array of elements
    /// \param count - Count of elements
    LinkedList(T *items, size_t count) : LinkedList() {
        if (count > 536870912)
            throw out_of_range("count < 0");
        if (items == NULL)
            throw invalid_argument("items is NULL");
        if (count > 0) {
            head = new Node(items[0]);
            Node *prev = head;
            for (size_t i = 1; i < count; ++i) {
                prev->next = new Node(items[i]);
                prev = prev->next;
            }
            tail = prev;
            length = count;
        }
    }

    /// Copies LinkedList
    /// \param list
    LinkedList(const LinkedList<T> &list) : LinkedList() {
        if (list.length > 0) {
            Node *tmp = list.head;
            head = new Node(tmp->data);
            Node *prev = head;
            tmp = tmp->next;
            while (tmp != NULL) {
                prev->next = new Node(tmp->data);
                prev = prev->next;
                tmp = tmp->next;
            }
            tail = prev;
            length = list.length;
        }
    }

    //Decomposition
    /// Returns first element of LinkedList
    /// \return First element
    T &GetFirst() {
        if (!head)
            throw out_of_range("");
        return head->data;
    }

    /// Returns last element of LinkedList
    /// \return Last element
    T &GetLast() {
        if (!tail)
            throw out_of_range("");
        return tail->data;
    }

    ///  Returns element with index i from LinkedList
    /// \param index
    /// \return
    T &At(size_t index) {
        if (index < 0 || index >= length)
            throw out_of_range("index < 0 or index >= length");
        if (index == 0)
            return GetFirst();
        if (index == length - 1)
            return GetLast();
        return GetNode(index)->data;
    }

    ///
    /// \param index
    /// \param value
    void Set(size_t index, T value) {
        if (index < 0 || index >= length)
            throw range_error("index < 0 or index >= length");
        At(index) = value;
    }

    ///
    /// \param startIndex
    /// \param endIndex
    /// \return
    LinkedList<T> GetSubList(size_t startIndex, size_t endIndex) {
        if (startIndex < 0 || startIndex >= length)
            throw range_error("index < 0 or index >= length");
        if (startIndex > endIndex)
            throw range_error("startIndex > endIndex");
        if (endIndex >= length)
            throw range_error("endIndex >= length");
        LinkedList<T> res;
        Node *tmp = GetNode(startIndex);
        for (size_t i = startIndex; i < endIndex + 1; ++i) {
            res.Append(tmp->data);
            tmp = tmp->next;
        }
        return res;
    }

    ///
    /// \return
    size_t GetLength() {
        return length;
    }

    ///
    /// \param index
    /// \return
    T &operator[](size_t index) { return At(index); }

    //Operations

    ///
    /// \param item
    void Append(T item) {
        Node *tmp = new Node(item);
        if (head == NULL)
            head = tmp;
        else
            tail->next = tmp;
        tail = tmp;
        ++length;
    }

    ///
    /// \param item
    void Prepend(T item) {
        Node *tmp = new Node(item);
        if (head == NULL) {
            head = tmp;
            tail = tmp;
        } else {
            tmp->next = head;
            head = tmp;
        }
        ++length;
    }

    ///
    /// \return
    T PopLast() {
        if (length < 1)
            throw range_error("length = 0");
        if (length == 1) {
            return this->PopFirst();
        }
        Node *prev = GetNode(length - 2);
        tail = prev;
        T data = prev->next->data;
        delete prev->next;
        --length;
        return data;
    }

    ///
    T PopFirst() {
        if (length < 1)
            throw range_error("length = 0");
        Node *prev = head;
        head = prev->next;
        T data = prev->data;
        delete prev;
        --length;
        if (length == 0) {
            tail = NULL;
            head = NULL;
        }
        return data;
    }

    ///
    /// \param item
    /// \param index
    void InsertAt(size_t index, T item) {
        if (index < 0 || index >= length)
            throw range_error("index < 0 or index >= length");
        if (index == length - 1) {
            this->Append(item);
            return;
        } else if (index == 0) {
            this->Prepend(item);
            return;
        }


        Node *tmp = new Node(item);
        Node *prev = GetNode(index - 1);
        Node *next = prev->next;
        prev->next = tmp;
        tmp->next = next;
        ++length;
    }

    ///
    /// \param index
    T RemoveAt(size_t index) {
        if (index < 0 || index >= length)
            throw range_error("index < 0 or index >= length");
        if (index == length - 1)
            return this->PopLast();
        else if (index == 0)
            return this->PopFirst();

        Node *prev = GetNode(index - 1);
        Node *next = (prev->next)->next;
        T data = prev->next->data;
        delete prev->next;
        prev->next = next;
        --length;
        return data;

    }

    ///
    /// \param list
    /// \return
    LinkedList<T> Concat(LinkedList<T> &list) {
        LinkedList<T> res;
        for (size_t i = 0; i < length; ++i) {
            res.Append(this->At(i));
        }
        for (size_t i = 0; i < list.length; ++i) {
            res.Append(list[i]);
        }
        return res;
    }

    ///
    /// \param list
    /// \return
    LinkedList<T> &operator=(const LinkedList<T> &list) {
        this->~LinkedList();
        if (list.length > 0) {
            Node *tmp = list.head;
            head = new Node(tmp->data);
            Node *prev = head;
            tmp = tmp->next;
            while (tmp != NULL) {
                prev->next = new Node(tmp->data);
                prev = prev->next;
                tmp = tmp->next;
            }
            tail = prev;
            length = list.length;
        } else {
            head = nullptr;
            tail = nullptr;
            length = 0;
        }
        return *this;
    }

    //Termination

    ///
    ~LinkedList() {
        while (length)
            PopFirst();
    }
};

#endif //LABA2_LINKEDLIST_H