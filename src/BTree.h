//
// Created by korna on 08.05.2021.
//

#ifndef LABA3_BTREE_H
#define LABA3_BTREE_H

#include "NAryTree.h"

template<typename T>
class BTree : public NAryTree<T> {
private:
    class BNode : public NAryTree<T>::template Node<T> {
    public:
        using NAryTree<T>::template Node<T>::Node;

        BNode *Search(T k) {
            size_t i = FindKey(k);
            if (this->keys[i] == k)
                return this;

            if (this->IsLeaf() == true)
                return nullptr;
            return this->GetChild(i)->Search(k);

        }

        void RemoveFromLeaf(size_t idx) {
            this->keys.RemoveAt(idx);
        }

        void RemoveFromNonLeaf(size_t idx, size_t t) {
            T k = this->keys[idx];
            if (this->children[idx]->keys.Count() >= t) {
                T pred = GetPred(idx);
                this->keys[idx] = pred;
                GetChild(idx)->Remove(pred, t);
            } else if (this->children[idx + 1]->keys.Count() >= t) {
                T next = GetNext(idx);
                this->keys[idx] = next;
                GetChild(idx + 1)->Remove(next, t);
            } else {
                Merge(idx, t);
                GetChild(idx)->Remove(k, t);
            }
        }

        void Fill(size_t idx, size_t t) {
            if (idx != 0 && GetChild(idx - 1)->keys.Count() >= t)
                BorrowFromPrev(idx);
            else if (idx != this->keys.Count() && this->children[idx + 1]->keys.Count() >= t)
                BorrowFromNext(idx);
            else {
                if (idx != this->keys.Count())
                    Merge(idx, t);
                else
                    Merge(idx - 1, t);
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

            if (!child->IsLeaf()) {
//                for (size_t i = child->keys.Count(); i >= 0; --i)
//                    child->children[i + 1] = child->children[i];

            }

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

        void InsertNonFull(T k, size_t t) {
            size_t i = FindKey(k);
            if (this->IsLeaf()) {
                if (i < this->keys.Count()) {
                    if (k != this->keys[i])
                        this->keys.InsertAt(i, k);
                } else this->keys.InsertAt(i, k);
            } else {
                if (this->children[i]->keys.Count() == 2 * t - 1) {
                    SplitChild(i, this->GetChild(i), t);
                    if (this->keys[i] < k)
                        i++;
                }
                this->GetChild(i)->InsertNonFull(k, t);
            }
        }

        void Remove(size_t k, size_t t) {
            size_t idx = FindKey(k);

            // The key to be removed is present in this node
            if (idx < this->keys.Count() && this->keys[idx] == k) {

                // If the node is a leaf node - removeFromLeaf is called
                // Otherwise, removeFromNonLeaf function is called
                if (this->IsLeaf())
                    RemoveFromLeaf(idx);
                else
                    RemoveFromNonLeaf(idx, t);
            } else {

                // If this node is a leaf node, then the key is not present in tree
                if (this->IsLeaf()) {
                    cout << "The key " << k << " is does not exist in the tree\n";
                    return;
                }

                // The key to be removed is present in the sub-tree rooted with this node
                // The flag indicates whether the key is present in the sub-tree rooted
                // with the last child of this node
                bool flag = idx == this->keys.Count();

                // If the child where the key is supposed to exist has less that t this->keys,
                // we fill that child
                if (GetChild(idx)->keys.Count() < t)
                    Fill(idx, t);

                // If the last child has been merged, it must have merged with the previous
                // child and so we recurse on the (idx-1)th child. Else, we recurse on the
                // (idx)th child which now has atleast t this->keys
                if (flag && idx > this->keys.Count())
                    GetChild(idx - 1)->Remove(k, t);
                else
                    GetChild(idx)->Remove(k, t);
            }
        }

        void Merge(size_t idx, size_t t) {
            BNode *child = this->GetChild(idx);
            BNode *sibling = this->GetChild(idx + 1);
            child->keys.Append(this->keys[idx]);
            for (size_t i = 0; i < sibling->keys.Count(); ++i)
                child->keys.Append(sibling->keys[i]);
            if (!child->IsLeaf()) {
                for (size_t i = 0; i <= sibling->keys.Count(); ++i)
                    child->children.Append(sibling->children[i]);
            }
            for (size_t i = idx + 1; i < this->keys.Count(); ++i)
                this->keys[i - 1] = this->keys[i];
            this->children.RemoveAt(idx + 1);
            sibling->children.Clear();
            delete sibling;
        }

        void SplitChild(size_t i, BNode *y, size_t t) {
            BNode *z = new BNode();
            z->keys.Resize(t - 1);
            for (size_t j = 0; j < t - 1; j++)
                z->keys[j] = y->keys[j + t];

            if (!y->IsLeaf()) {
                for (size_t j = 0; j < t; j++)
                    z->children.Append(y->children[j + t]);
            }

            this->children.InsertAt(i + 1, z);
            this->keys.InsertAt(i, y->keys[t - 1]);
            y->keys.Resize(t - 1);
        }

        BNode *GetChild(size_t i) {
            return static_cast<BNode *>(this->children[i]);
        }
    };


    size_t t{};

public:
    BTree() : BTree(3) {}

    explicit BTree(size_t t) : NAryTree<T>(new BNode(), 2 * t - 1), t(t) {}

    void Insert(T k) {
        if (static_cast<BNode *>(this->root)->keys.Count() == 2 * t - 1) {
            BNode *s = new BNode();
            s->children.Append(this->root);
            s->SplitChild(0, static_cast<BNode *>(this->root), t);
            size_t i = 0;
            if (s->keys[i] < k)
                i++;
            s->GetChild(i)->InsertNonFull(k, t);

            this->root = s;
        } else
            static_cast<BNode *>(this->root)->InsertNonFull(k, t);
    }

    void Remove(T k) {

        // Call the remove function for root
        static_cast<BNode *>(this->root)->Remove(k, t);

        // If the root node has 0 this->keys, make its first child as the new root
        //  if it has a child, otherwise set root as NULL
        if (this->root->keys.Count() == 0) {
            BNode *tmp = static_cast<BNode *>(this->root);
            if (!static_cast<BNode *>(this->root)->IsLeaf())
                this->root = this->root->children[0];

            // Free the old root
            tmp->children.Clear();
            delete tmp;
        }
    }

    bool Search(T key) {
        return static_cast<BNode *>(this->root)->Search(key) != nullptr;
    }

    BTree(BTree<T> const &tree) : NAryTree<T>(static_cast<NAryTree<T> *>(&tree)), t(tree.t) {}


};


#endif //LABA3_BTREE_H
