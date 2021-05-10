//
// Created by korna on 08.05.2021.
//

#ifndef LABA3_BTREE_H
#define LABA3_BTREE_H

#include "NAryTree.h"
#include "ArraySequence.h"

template<typename T>
class BTree : public NAryTree<T> {
private:
    class BNode : public NAryTree<T>::template Node<T> {
    public:
        size_t n;
        const size_t t;
        bool leaf;

//        using NAryTree<T>::template Node<T>::Node;
        BNode(size_t t, bool leaf) :
                n(0), t(t), leaf(leaf),
                NAryTree<T>::template Node<T>::Node(ArraySequence<T>(2 * t - 1), nullptr,
                                                    ArraySequence<typename NAryTree<T>::template Node<T> *>(2 * t)) {}

//        BNode *Search(T k) {
//            size_t i = FindKey(k);
//
//            if (i < this->keys.Count() && this->keys[i] == k)
//                return this;
//            else if (this->IsLeaf())
//                return nullptr;
//
//            return this->GetChild(i)->Search(k);
//
//        }



// A utility function that returns the index of the first key that is
// greater than or equal to k
        size_t FindKey(T k) {
            size_t idx = 0;
            while (idx < n && this->keys[idx] < k)
                ++idx;
            return idx;
        }

// A function to remove the key k from the sub-tree rooted with this node
        void Remove(T k) {
            size_t idx = FindKey(k);

            // The key to be removed is present in this node
            if (idx < n && this->keys[idx] == k) {

                // If the node is a leaf node - removeFromLeaf is called
                // Otherwise, removeFromNonLeaf function is called
                if (leaf)
                    RemoveFromLeaf(idx);
                else
                    RemoveFromNonLeaf(idx);
            } else {

                // If this node is a leaf node, then the key is not present in tree
                if (leaf) {
                    cout << "The key " << k << " is does not exist in the tree\n";
                    return;
                }

                // The key to be removed is present in the sub-tree rooted with this node
                // The flag indicates whether the key is present in the sub-tree rooted
                // with the last child of this node
                bool flag = idx == n;

                // If the child where the key is supposed to exist has less that t keys,
                // we fill that child
                if (GetChild(idx)->n < t)
                    Fill(idx);

                // If the last child has been merged, it must have merged with the previous
                // child and so we recurse on the (idx-1)th child. Else, we recurse on the
                // (idx)th child which now has atleast t keys
                if (flag && idx > n)
                    GetChild(idx - 1)->remove(k);
                else
                    GetChild(idx)->remove(k);
            }
        }

// A function to remove the idx-th key from this node - which is a leaf node
        void RemoveFromLeaf(size_t idx) {

            // Move all the keys after the idx-th pos one place backward
            for (size_t i = idx + 1; i < n; ++i)
                this->keys[i - 1] = this->keys[i];

            // Reduce the count of keys
            n--;
        }

// A function to remove the idx-th key from this node - which is a non-leaf node
        void RemoveFromNonLeaf(size_t idx) {

            T k = this->keys[idx];

            // If the child that precedes k (C[idx]) has atleast t keys,
            // find the predecessor 'pred' of k in the subtree rooted at
            // C[idx]. Replace k by pred. Recursively delete pred
            // in C[idx]
            if (GetChild(idx)->n >= t) {
                T pred = GetPred(idx);
                this->keys[idx] = pred;
                GetChild(idx)->remove(pred);
            }

                // If the child C[idx] has less that t keys, examine C[idx+1].
                // If C[idx+1] has atleast t keys, find the successor 'succ' of k in
                // the subtree rooted at C[idx+1]
                // Replace k by succ
                // Recursively delete succ in C[idx+1]
            else if (GetChild(idx + 1)->n >= t) {
                T next = GetNext(idx);
                this->keys[idx] = next;
                GetChild(idx + 1)->Remove(next);
            }

                // If both C[idx] and C[idx+1] has less that t keys,merge k and all of C[idx+1]
                // into C[idx]
                // Now C[idx] contains 2t-1 keys
                // Free C[idx+1] and recursively delete k from C[idx]
            else {
                Merge(idx);
                GetChild(idx)->Remove(k);
            }
        }

// A function to get predecessor of keys[idx]
        T GetPred(size_t idx) {
            // Keep moving to the right most node until we reach a leaf
            BNode *cur = GetChild(idx);
            while (!cur->leaf)
                cur = cur->GetChild(cur->n);

            // Return the last key of the leaf
            return cur->keys[cur->n - 1];
        }

        T GetNext(size_t idx) {

            // Keep moving the left most node starting from C[idx+1] until we reach a leaf
            BNode *cur = GetChild(idx + 1);
            while (!cur->leaf)
                cur = cur->C[0];

            // Return the first key of the leaf
            return cur->keys[0];
        }

// A function to fill child C[idx] which has less than t-1 keys
        void Fill(size_t idx) {

            // If the previous child(C[idx-1]) has more than t-1 keys, borrow a key
            // from that child
            if (idx != 0 && GetChild(idx - 1)->n >= t)
                BorrowFromPrev(idx);

                // If the next child(C[idx+1]) has more than t-1 keys, borrow a key
                // from that child
            else if (idx != n && GetChild(idx + 1)->n >= t)
                BorrowFromNext(idx);

                // Merge C[idx] with its sibling
                // If C[idx] is the last child, merge it with with its previous sibling
                // Otherwise merge it with its next sibling
            else {
                if (idx != n)
                    Merge(idx);
                else
                    Merge(idx - 1);
            }
        }

// A function to borrow a key from C[idx-1] and insert it
// into C[idx]
        void BorrowFromPrev(size_t idx) {

            BNode *child = GetChild(idx);
            BNode *sibling = GetChild(idx - 1);

            // The last key from C[idx-1] goes up to the parent and key[idx-1]
            // from parent is inserted as the first key in C[idx]. Thus, the  loses
            // sibling one key and child gains one key

            // Moving all key in C[idx] one step ahead
            for (size_t i = child->n - 1; i >= 0; --i)
                child->keys[i + 1] = child->keys[i];

            // If C[idx] is not a leaf, move all its child pointers one step ahead
            if (!child->leaf) {
                for (size_t i = child->n; i >= 0; --i)
                    child->C[i + 1] = child->C[i];
            }

            // Setting child's first key equal to keys[idx-1] from the current node
            child->keys[0] = this->keys[idx - 1];

            // Moving sibling's last child as C[idx]'s first child
            if (!child->leaf)
                child->C[0] = sibling->C[sibling->n];

            // Moving the key from the sibling to the parent
            // This reduces the number of keys in the sibling
            this->keys[idx - 1] = sibling->keys[sibling->n - 1];

            child->n += 1;
            sibling->n -= 1;
        }

// A function to borrow a key from the C[idx+1] and place
// it in C[idx]
        void BorrowFromNext(size_t idx) {

            BNode *child = GetChild(idx);
            BNode *sibling = GetChild(idx + 1);

            // keys[idx] is inserted as the last key in C[idx]
            child->keys[(child->n)] = this->keys[idx];

            // Sibling's first child is inserted as the last child
            // into C[idx]
            if (!(child->leaf))
                child->C[(child->n) + 1] = sibling->C[0];

            //The first key from sibling is inserted into keys[idx]
            this->keys[idx] = sibling->keys[0];

            // Moving all keys in sibling one step behind
            for (size_t i = 1; i < sibling->n; ++i)
                sibling->keys[i - 1] = sibling->keys[i];

            // Moving the child pointers one step behind
            if (!sibling->leaf) {
                for (size_t i = 1; i <= sibling->n; ++i)
                    sibling->C[i - 1] = sibling->C[i];
            }

            // Increasing and decreasing the key count of C[idx] and C[idx+1]
            // respectively
            child->n += 1;
            sibling->n -= 1;
        }

// A function to merge C[idx] with C[idx+1]
// C[idx+1] is freed after merging
        void Merge(size_t idx) {
            BNode *child = GetChild(idx);
            BNode *sibling = GetChild(idx + 1);

            // Pulling a key from the current node and inserting it into (t-1)th
            // position of C[idx]
            child->keys[t - 1] = this->keys[idx];

            // Copying the keys from C[idx+1] to C[idx] at the end
            for (size_t i = 0; i < sibling->n; ++i)
                child->keys[i + t] = sibling->keys[i];

            // Copying the child pointers from C[idx+1] to C[idx]
            if (!child->leaf) {
                for (size_t i = 0; i <= sibling->n; ++i)
                    child->C[i + t] = sibling->C[i];
            }

            // Moving all keys after idx in the current node one step before -
            // to fill the gap created by moving keys[idx] to C[idx]
            for (size_t i = idx + 1; i < n; ++i)
                this->keys[i - 1] = this->keys[i];

            // Moving the child pointers after (idx+1) in the current node one
            // step before
            for (size_t i = idx + 2; i <= n; ++i)
                this->C[i - 1] = this->C[i];

            // Updating the key count of child and the current node
            child->n += sibling->n + 1;
            n--;

            // Freeing the memory occupied by sibling
            sibling->children.Clear();
            delete sibling;
        }


// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
        void InsertNonFull(T k) {
            // Initialize index as index of rightmost element
            size_t i = n - 1;

            // If this is a leaf node
            if (leaf) {
                // The following loop does two things
                // a) Finds the location of new key to be inserted
                // b) Moves all greater keys to one place ahead
                while (i >= 0 && this->keys[i] > k) {
                    this->keys[i + 1] = this->keys[i];
                    i--;
                }

                // Insert the new key at found location
                this->keys[i + 1] = k;
                n = n + 1;
            } else // If this node is not leaf
            {
                // Find the child which is going to have the new key
                while (i >= 0 && this->keys[i] > k)
                    i--;

                // See if the found child is full
                if (GetChild(i + 1)->n == 2 * t - 1) {
                    // If the child is full, then split it
                    SplitChild(i + 1, GetChild(i + 1));

                    // After split, the middle key of C[i] goes up and
                    // C[i] is splitted into two.  See which of the two
                    // is going to have the new key
                    if (this->keys[i + 1] < k)
                        i++;
                }
                GetChild(i + 1)->InsertNonFull(k);
            }
        }

// A utility function to split the child y of this node
// Note that y must be full when this function is called
        void SplitChild(size_t i, BNode *y) {
            // Create a new node which is going to store (t-1) keys
            // of y
            BNode *z = new BNode(y->t, y->leaf);
            z->n = t - 1;

            // Copy the last (t-1) keys of y to z
            for (size_t j = 0; j < t - 1; j++)
                z->keys[j] = y->keys[j + t];

            // Copy the last t children of y to z
            if (!y->leaf) {
                for (size_t j = 0; j < t; j++)
                    z->C[j] = y->C[j + t];
            }

            // Reduce the number of keys in y
            y->n = t - 1;

            // Since this node is going to have a new child,
            // create space of new child
            for (size_t j = n; j >= i + 1; j--)
                this->C[j + 1] = this->C[j];

            // Link the new child to this node
            this->C[i + 1] = z;

            // A key of y will move to this node. Find location of
            // new key and move all greater keys one space ahead
            if (n != 0)
                for (size_t j = n - 1; j >= i; j--)
                    this->keys[j + 1] = this->keys[j];

            // Copy the middle key of y to this node
            this->keys[i] = y->keys[t - 1];

            // Increment count of keys in this node
            n = n + 1;
        }

        BNode *GetChild(size_t i) {
            return static_cast<BNode *>(this->C[i]);
        }
    };


    size_t t{};

public:
    BTree() : BTree(3) {}

    explicit BTree(size_t t) : NAryTree<T>(new BNode(t, true), 2 * t), t(t) {}

    void Insert(T k) {
        if (static_cast<BNode *>(this->root)->keys.Count() == 2 * t - 1) {
            // If root is full, then tree grows in height
            // Allocate memory for new root
            BNode *s = new BNode(t, true);

            // Make old root as child of new root
            s->C[0] = this->root;

            // Split the old root and move 1 key to the new root
            s->SplitChild(0, static_cast<BNode *>(this->root));

            // New root has two C now.  Decide which of the
            // two C is going to have new key
            size_t i = 0;
            if (s->keys[0] < k)
                i++;
            s->GetChild(i)->InsertNonFull(k);

            // Change root
            this->root = s;

        } else
            static_cast<BNode *>(this->root)->InsertNonFull(k);
    }

    void Remove(T k) {

        // Call the remove function for root
        static_cast<BNode *>(this->root)->Remove(k);

        // If the root node has 0 this->keys, make its first child as the new root
        //  if it has a child, otherwise set root as NULL
        if (this->root->keys.Count() == 0) {
            BNode *tmp = static_cast<BNode *>(this->root);
            if (!static_cast<BNode *>(this->root)->IsLeaf())
                this->root = this->root->C[0];

            // Free the old root
            tmp->C.Clear();
            delete tmp;
        }
    }

    bool Search(T key) {
        return static_cast<BNode *>(this->root)->Search(key) != nullptr;
    }

    BTree(BTree<T> const &tree) : NAryTree<T>(static_cast<NAryTree<T> *>(&tree)), t(tree.t) {}


};


#endif //LABA3_BTREE_H
