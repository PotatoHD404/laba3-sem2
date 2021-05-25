//
// Created by korna on 08.05.2021.
//

#ifndef LABA3_BTREE_HPP
#define LABA3_BTREE_HPP

#include "NAryTree.hpp"
#include "Pair.hpp"
#include "Stack.hpp"

template<typename T>
class BTree : public NAryTree<T> {
private:
    class BNode : public NAryTree<T>::template Node<T> {
    public:
        using NAryTree<T>::template Node<T>::Node;

        BNode *Search(T k) {
            size_t i = FindKey(k);

            if (i < this->keys.Count() && this->keys[i] == k)
                return this;
            else if (this->IsLeaf())
                return nullptr;

            return this->GetChild(i)->Search(k);

        }

        bool RemoveFromLeaf(size_t idx) {
            if (idx < this->keys.Count()) {
                this->keys.RemoveAt(idx);
                return true;
            }
            return false;
        }

        bool RemoveFromNonLeaf(size_t idx, size_t _t) {
            T k = this->keys[idx];
            if (this->children[idx]->keys.Count() >= _t) {
                T pred = GetPred(idx);
                this->keys[idx] = pred;
                GetChild(idx)->Remove(pred, _t);
                return true;
            } else if (this->children[idx + 1]->keys.Count() >= _t) {
                T next = GetNext(idx);
                this->keys[idx] = next;
                GetChild(idx + 1)->Remove(next, _t);
                return true;
            } else {
                Merge(idx);
                GetChild(idx)->Remove(k, _t);
                return true;
            }
        }

        void Fill(size_t idx, size_t _t) {
            if (idx != 0 && GetChild(idx - 1)->keys.Count() >= _t)
                BorrowFromPrev(idx);
            else if (idx != this->keys.Count() && this->children[idx + 1]->keys.Count() >= _t)
                BorrowFromNext(idx);
            else {
                if (idx != this->keys.Count())
                    Merge(idx);
                else
                    Merge(idx - 1);
            }
        }

// A function to borrow a key from this->children[idx-1] and insert it
// into GetChild(idx)
        void BorrowFromPrev(size_t idx) {
            BNode *child = GetChild(idx);
            BNode *sibling = GetChild(idx - 1);

            child->keys.Prepend(T());
//            for (size_t i = child->keys.Count() - 1; i >= 0; --i)
//                child->keys[i + 1] = child->keys[i];

//            if (!child->IsLeaf()) {
////                for (size_t i = child->keys.Count(); i >= 0; --i)
////                    child->children[i + 1] = child->children[i];
//
//            }

            child->keys.Prepend(this->keys[idx - 1]);

//            if (!child->leaf)
//                child->children[0] = sibling->children[sibling->keys.Count()];
            if (!child->IsLeaf())
                this->children.Prepend(sibling->children[sibling->keys.Count()]);


            this->keys[idx - 1] = sibling->keys.PopLast();
        }

// A function to borrow a key from the this->children[idx+1] and place
// it in GetChild(idx)
        void BorrowFromNext(size_t idx) {

            BNode *child = GetChild(idx);
            BNode *sibling = GetChild(idx + 1);

            // this->keys[idx] is inserted as the last key in GetChild(idx)
            child->keys.Append(this->keys[idx]);

            // Sibling's first child is inserted as the last child
            // into GetChild(idx)
            if (!(child->IsLeaf()))
                child->children.Append(sibling->children[0]);

            //The first key from sibling is inserted into this->keys[idx]
            this->keys[idx] = sibling->keys[0];

            // Moving all this->keys in sibling one step behind
            sibling->keys.PopFirst();

            // Moving the child pointers one step behind
            if (!sibling->IsLeaf()) {
//                for (size_t i = 1; i <= sibling->keys.Count() + 1; ++i)
//                    sibling->children[i - 1] = sibling->children[i];
                sibling->children.PopFirst();
            }

        }

        // A function to get predecessor of this->keys[idx]
        T GetPred(size_t idx) {
            // Keep moving to the right most node until we reach a leaf
            BNode *cur = GetChild(idx);
            while (!cur->IsLeaf())
                cur = cur->GetChild(cur->keys.Count());

            // Return the last key of the leaf
            return cur->keys[cur->keys.Count() - 1];
        }

        T GetNext(size_t idx) {
            // Keep moving the left most node starting from this->children[idx+1] until we reach a leaf
            BNode *cur = GetChild(idx + 1);
            while (!cur->IsLeaf())
                cur = cur->GetChild(0);

            // Return the first key of the leaf
            return cur->keys[0];
        }


        size_t FindKey(T k) {
            size_t res = 0;
            while (res < this->keys.Count() && this->keys[res] < k)
                ++res;
            return res;
        }

        bool InsertNonFull(T k, size_t _t) {
            size_t i = FindKey(k);
            if (this->IsLeaf()) {
                if (this->keys.Count() == i || (i < this->keys.Count() && k != this->keys[i])) {
                    this->keys.InsertAt(i, k);
                    return true;
                }
                return false;
            } else {
                if (this->children[i]->keys.Count() == 2 * _t - 1) {
                    SplitChild(i, this->GetChild(i), _t);
                    if (this->keys[i] < k)
                        i++;
                }
                return this->GetChild(i)->InsertNonFull(k, _t);
            }
        }

        bool Remove(T k, size_t _t) {
            size_t idx = FindKey(k);

            // The key to be removed is present in this node
            if (idx < this->keys.Count() && this->keys[idx] == k) {

                // If the node is a leaf node - removeFromLeaf is called
                // Otherwise, removeFromNonLeaf function is called
                if (this->IsLeaf()) {
                    return RemoveFromLeaf(idx);
                } else
                    return RemoveFromNonLeaf(idx, _t);
            } else {

                // If this node is a leaf node, then the key is not present in tree
                if (this->IsLeaf()) {
//                    cout << "The key " << k << " is does not exist in the tree\n";
                    return false;
                }

                // The key to be removed is present in the sub-tree rooted with this node
                // The flag indicates whether the key is present in the sub-tree rooted
                // with the last child of this node
                bool flag = idx == this->keys.Count();

                // If the child where the key is supposed to exist has less that _t this->keys,
                // we fill that child
                if (GetChild(idx)->keys.Count() < _t)
                    Fill(idx, _t);

                // If the last child has been merged, it must have merged with the previous
                // child and so we recurse on the (idx-1)th child. Else, we recurse on the
                // (idx)th child which now has atleast _t this->keys
                if (flag && idx > this->keys.Count())
                    GetChild(idx - 1)->Remove(k, _t);
                else
                    GetChild(idx)->Remove(k, _t);
                return true;
            }
        }

        void Merge(size_t idx) {
            BNode *child = this->GetChild(idx);
            BNode *sibling = this->GetChild(idx + 1);
            child->keys.Append(this->keys[idx]);
            for (size_t i = 0; i < sibling->keys.Count(); ++i)
                child->keys.Append(sibling->keys[i]);
            if (!child->IsLeaf()) {
                for (size_t i = 0; i <= sibling->keys.Count(); ++i)
                    child->children.Append(sibling->children[i]);
            }
//            for (size_t i = idx + 1; i < this->keys.Count(); ++i)
//                this->keys[i - 1] = this->keys[i];
            this->keys.RemoveAt(idx);
            this->children.RemoveAt(idx + 1);
            sibling->children.Clear();
            delete sibling;
        }

        void SplitChild(size_t i, BNode *y, size_t _t) {
            BNode *z = new BNode();
//            z->keys.Resize(_t - 1);
            for (size_t j = 0; j < _t - 1; j++)
//                z->keys[j] = y->keys[j + _t];
                z->keys.Prepend(y->keys.PopLast());

            if (!y->IsLeaf()) {
                for (size_t j = 0; j < _t; j++)
                    z->children.Prepend(y->children.PopLast());
            }

            this->children.InsertAt(i + 1, z);
            this->keys.InsertAt(i, y->keys.PopLast());
//            y->keys.Resize(_t - 1);
        }

        BNode *GetChild(size_t i) {
            return static_cast<BNode *>(this->children[i]);
        }
    };


    size_t t{};

public:
    BTree() : BTree(3) {}

    ArraySequence<T> ToArraySequence() {
        ArraySequence<T> res;
        if (this->root == NULL)
            throw runtime_error("Root is NULL");

        function<void(BNode *)> VisitNode = [&](BNode *node) {
            size_t length = node->keys.Count();
            for (size_t i = 0; i < length; ++i) {
                if (!node->IsLeaf())
                    VisitNode(node->GetChild(i));
                res.Append(node->keys[i]);
            }
            if (!node->IsLeaf())
                VisitNode(node->GetChild(length));
        };
        VisitNode(static_cast<BNode *>(this->root));
        return res;
    }

    BTree<T> &operator=(BTree<T> &&list) noexcept {
        this->~BTree();
        this->n = list.n;
        this->count = list.count;
        t = list.t;
        this->root = new BNode(*static_cast<BNode *>(list.root));
        return *this;
    }

//    bool operator==(BTree<T>& list) noexcept {
//        return *list.root == *this->root;
//    }

//    BTree<T> &operator=(NAryTree<T> &&list) {
//        this->~BTree();
//
//        this->n = list.GetN();
//        count = list.Count();
//        t = list.t;
//        this->root = new BNode(*list.root);
//        return *this;
//    }

    string AscendingOrder() {
        if (this->root == NULL)
            throw runtime_error("Root is NULL");
        stringstream buffer;
        Stack<Pair<BNode *, size_t>> stack;
        stack.Push(Pair(static_cast<BNode *>(this->root), (size_t) 0));
        size_t length = this->count;
        while (!stack.IsEmpty()) {
            if (!stack.Top().first->IsLeaf()) {
                if (stack.Top().first->ChildrenCount() == stack.Top().second)
                    stack.Pop();
                else {

                    if (stack.Top().second != 0) {
                        buffer << stack.Top().first->keys[stack.Top().second - 1];
                        length--;
                        if (length != this->count && length)
                            buffer << " ";
                    }

                    stack.Push(Pair(stack.Top().first->GetChild(stack.Top().second++), (size_t) 0));
                }
            } else {
                size_t len = stack.Top().first->keys.Count();
                length -= len;
                for (size_t i = 0; i < len; ++i) {
                    buffer << stack.Top().first->keys[i];
                    if (i != len - 1)
                        buffer << " ";
                }
                stack.Pop();
                if (length != this->count && length)
                    buffer << " ";
            }

//            else {
//                int i = 0;
//                buffer << i;
//            }
        }
//        function<void(BNode *)> VisitNode = [&](BNode *node) {
//            size_t length = node->keys.Count();
//            for (size_t i = 0; i < length; ++i) {
//                if (!node->IsLeaf())
//                    VisitNode(node->GetChild(i));
//                res.Append(node->keys[i]);
//            }
//            if (!node->IsLeaf())
//                VisitNode(node->GetChild(length));
//        };
//        VisitNode(this->root);
        return buffer.str();
    }

    explicit BTree(size_t t) : NAryTree<T>(new BNode(), 2 * t, 0), t(t) {}

    void Insert(T k) {
        if (static_cast<BNode *>(this->root)->keys.Count() == 2 * t - 1) {
            BNode *s = new BNode();
            s->children.Append(this->root);
            s->SplitChild(0, static_cast<BNode *>(this->root), t);
            size_t i = 0;
            if (s->keys[i] < k)
                i++;

            if (s->InsertNonFull(k, t))
                this->count++;
            this->root = s;
        } else {
            if (static_cast<BNode *>(this->root)->InsertNonFull(k, t))
                this->count++;
        }
    }

    T GetMin() {
        BNode *tmp = static_cast<BNode *>(this->root);
        while (!tmp->IsLeaf())
            tmp = static_cast<BNode *>(tmp->children.GetFirst());
        return tmp->keys.GetFirst();
    }

    T GetMax() {
        BNode *tmp = static_cast<BNode *>(this->root);
        while (!tmp->IsLeaf())
            tmp = tmp->children.GetLast();
        return tmp->keys.GetLast();
    }

    T Pop() {
        T res = GetMin();
        Remove(res);
        return res;
    }

    void Remove(T k) {

        // Call the remove function for root
        if (static_cast<BNode *>(this->root)->Remove(k, t)) {
            this->count--;
        }

        // If the root node has 0 this->keys, make its first child as the new root
        //  if it has a child, otherwise BTree root as NULL
        if (this->root->keys.Count() == 0 && !static_cast<BNode *>(this->root)->IsLeaf()) {
            BNode *tmp = static_cast<BNode *>(this->root);
//            if (!static_cast<BNode *>(this->root)->IsLeaf())
                this->root = this->root->children[0];

            // Free the old root
            tmp->children.Clear();
            delete tmp;
        }
    }

    bool Contains(T key) {
        return static_cast<BNode *>(this->root)->Search(key) != nullptr;
    }

    BTree(BTree<T> &tree) : NAryTree<T>(static_cast<NAryTree<T> &>(tree)), t(tree.t) {}

};


#endif //LABA3_BTREE_HPP
