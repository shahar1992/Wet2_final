//
// Created by edri6 on 05/01/2018.
//

#ifndef WET2_FINAL_SPLAYTREE_H
#define WET2_FINAL_SPLAYTREE_H

#include <iostream>
#include <functional>
#include <new>

#define nullptr 0

template<class T, typename GetScore>
class SplayTree {
    template<class P, typename GetScore1>
    class Node {
        friend class SplayTree<T, GetScore1>;

        P data;
        Node<P, GetScore1> *left;
        Node<P, GetScore1> *right;
        Node<P, GetScore1> *parent;
        GetScore1 getScore;
        int right_tree_size;
        int left_tree_size;
        int right_tree_sum;
        int left_tree_sum;

        /**
         * The function constructs a new node with the given data.
         * next and previous fields are initialized to NULL.
         * @param data - the data for the new node
         */
        Node<P, GetScore1>(const P &data, const GetScore1 &getScore) :
                data(data), left(), right(), parent(), getScore(getScore),
                right_tree_size(0), left_tree_size(0),
                right_tree_sum(0), left_tree_sum(0) {}

        /**
         * Constructor
         */
        Node<P, GetScore1>(const GetScore1 &getScore) :
                data(), left(), right(), parent(), getScore(getScore),
                right_tree_size(0), left_tree_size(0),
                right_tree_sum(0), left_tree_sum(0) {}


        /**
         * recursive function that updates all the ancestors invariants
         * of the given node
         * @param node - the node to update his ancestors
         * @param size_to_change - the size to increase/decrease
         * @param sum_to_change - the sum to increase/decrease
         */
        void updateParents(Node<P, GetScore1> *node, int size_to_change,
                           int sum_to_change) {
            if (!(node->parent))
                return;
            if (node->parent->right == node) {
                node->parent->right_tree_size =
                        node->parent->right_tree_size + size_to_change;
                node->parent->right_tree_sum =
                        node->parent->right_tree_sum + sum_to_change;
                updateParents(node->parent, size_to_change, sum_to_change);
            } else {
                node->parent->left_tree_size =
                        node->parent->left_tree_size + size_to_change;
                node->parent->left_tree_sum =
                        node->parent->left_tree_sum + sum_to_change;
                updateParents(node->parent, size_to_change, sum_to_change);
            }
        }

        /**
          * Set function to set the given Node as left child
          */
        void setLeft(Node<P,GetScore1>* Left) {
            left = Left;
            if (left) left->parent = this;
        }

        /**
         * Set function to set the given Node as right child
         */
        void setRight(Node<P, GetScore1> *Right) {
            right = Right;
            if (Right) right -> parent = this;
        }
    }; //---------------END OF NODE-------------------------------
    //-------------PRIVATE FUNCTIONS OF SPLAY TREE----------------
    /**
    * The function rotates the tree with a zig rotation
    * A - is the root
    * B - is a son of A
    */
    void zig(Node<T, GetScore> *A, Node<T, GetScore> *B) {
        if (B == A->left) {
            A->setLeft(B->right);
            B->parent = nullptr;
            B->setRight(A);
            this->root = B;
            A->left_tree_size = B->right_tree_size;
            A->left_tree_sum = B->right_tree_sum;
            B->right_tree_size = B->right_tree_size + A->right_tree_size + 1;
            B->right_tree_sum = B->right_tree_sum + A->right_tree_sum + getScore(A->data);
        } else {         //in case B == A -> right
            A->setRight(B->left);
            B->parent = nullptr;
            B->setLeft(A);
            this->root = B;
            A->right_tree_size = B->left_tree_size;
            A->right_tree_sum = B->left_tree_sum;
            B->left_tree_size = B->left_tree_size + A->left_tree_size + 1;
            B->left_tree_sum = B->left_tree_sum + A->left_tree_sum + getScore(A->data);
        }
    }

    /**
     * The function rotates the tree with a zig-zig rotation
     * A - is a left or right son
     * B - is the left or the right son of A
     */
    void zig_zig(Node<T, GetScore> *A, Node<T, GetScore> *B) {
        if (A->parent->parent && A->parent->parent->left == A->parent)
            A->parent->parent->setLeft(B);
        else if (A->parent->parent && A->parent->parent->right == A->parent)
            A->parent->parent->setRight(B);
        else if (A->parent == root) {
            this->root = B;
            B->parent = nullptr;
        }
        if (A->parent->left == A && A->left == B)    //left left case
        {
            A->parent->setLeft(A->right);
            A->setRight(A->parent);
            A->setLeft(B->right);
            B->setRight(A);
            A->right->left_tree_size = A->right_tree_size;
            A->right->left_tree_sum = A->right_tree_sum;
            A->right_tree_size =
                    A->right_tree_size + A->right->right_tree_size + 1;
            A->right_tree_sum = A->right_tree_sum + A->right->right_tree_sum +
                    getScore(A->right->data);
            A->left_tree_size = B->right_tree_size;
            A->left_tree_sum = B->right_tree_sum;
            B->right_tree_size =
                    B->right_tree_size + A->right_tree_size + 1;
            B->right_tree_sum = B->right_tree_sum + A->right_tree_sum +
                                getScore(A->data);
        } else {                                          // right right case
            A->parent->setRight(A->left);
            A->setLeft(A->parent);
            A->setRight(B->left);
            B->setLeft(A);
            A->left->right_tree_size = A->left_tree_size;
            A->left->right_tree_sum = A->left_tree_sum;
            A->left_tree_size =
                    A->left_tree_size + A->left->left_tree_size + 1;
            A->left_tree_sum = A->left_tree_sum + A->left->left_tree_sum +
                                getScore(A->left->data);
            A->right_tree_size = B->left_tree_size;
            A->right_tree_sum = B->left_tree_sum;
            B->left_tree_size =
                    B->left_tree_size + A->left_tree_size + 1;
            B->left_tree_sum = B->left_tree_sum + A->left_tree_sum +
                                getScore(A->data);
        }
    }

    /**
     * The function rotates the tree with a zig-zag rotation
     * A - is a left or a right son
     * B - is the right or the left son of A
     */
    void zig_zag(Node<T, GetScore> *A, Node<T, GetScore> *B) {
        if (A->parent->parent && A->parent->parent->left == A->parent)
            A->parent->parent->setLeft(B);
        else if (A->parent->parent && A->parent->parent->right == A->parent)
            A->parent->parent->setRight(B);
        else if (A->parent == root) {
            this->root = B;
            B->parent = nullptr;
        }
        if (A->parent->left == A)    //left right case
        {
            A -> parent -> setLeft(B -> right);
            A -> setRight(B -> left);
            B -> setRight(A -> parent);
            B -> setLeft(A);
            A->right_tree_size = B->left_tree_size;
            A->right_tree_sum = B->left_tree_sum;
            B->right->left_tree_size = B->right_tree_size;
            B->right->left_tree_sum = B->right_tree_sum;
            B->left_tree_size = A->left_tree_size + A->right_tree_size + 1;
            B->left_tree_sum = A->left_tree_sum + A->right_tree_sum +
                    getScore(A->data);
            B->right_tree_size = B->right->left_tree_size +
                    B->right->right_tree_size + 1;
            B->right_tree_sum = B->right->left_tree_sum +
                    B->right->right_tree_sum + getScore(B->right->data);
        } else                                          // right left case
        {
            A -> parent -> setRight(B -> left);
            A -> setLeft(B -> right);
            B -> setLeft(A -> parent);
            B -> setRight(A);
            A->left_tree_size = B->right_tree_size;
            A->left_tree_sum = B->right_tree_sum;
            B->left->right_tree_size = B->left_tree_size;
            B->left->right_tree_sum = B->left_tree_sum;
            B->right_tree_size = A->right_tree_size + A->left_tree_size + 1;
            B->right_tree_sum = A->right_tree_sum + A->left_tree_sum +
                               getScore(A->data);
            B->left_tree_size = B->left->left_tree_size +
                                 B->left->right_tree_size + 1;
            B->left_tree_sum = B->left->left_tree_sum +
                                B->left->right_tree_sum + getScore(B->left->data);
        }
    }

    /**
     * The function splays the Tree according to the given node X
     */
    void splay(Node<T, GetScore> *X) {
        while (X != root) {
            if (X->parent == root)
                zig(X->parent, X);
            else if ((X->parent->left == X &&
                      X->parent->parent->left == X->parent) ||
                     (X->parent->right == X &&
                      X->parent->parent->right == X->parent))
                zig_zig(X->parent, X);
            else
                zig_zag(X->parent, X);
        }
    }

    /**
     * The function joins two given trees into one
     *  known that this < T2 for each element.
     */
    void join(SplayTree<T, GetScore> *T2) {
        this->find_max();
        if (this->root){
            this->root->setRight(T2->root);
            if(this->root->right) {
                this->root->right_tree_size =
                        this->root->right->right_tree_size +
                        this->root->right->left_tree_size + 1;
                this->root->right_tree_sum = this->root->right->right_tree_sum +
                                             this->root->right->left_tree_sum +
                                             getScore(this->root->right->data);
            } else {
                this->root->right_tree_size = 0;
                this->root->right_tree_sum = 0;
            }
        }
        else
            this->root = T2->root;
        T2->root = nullptr;
    }

public:
    //--------------SPLAY TREE FIELDS-----------------------------
    Node<T, GetScore> *root;
    int size;
    GetScore getScore;

    /**
    * Constructs a new Splay Tree.
    */
    SplayTree<T, GetScore>(const GetScore& getScore) : root(nullptr),
                                               size(0), getScore(getScore) {
        root = nullptr;
        size = 0;
    };

    /**
     * Distructor
     */
    ~SplayTree() {
        deleteTree(this->root);
    }

    /**
     * help function to delete the tree recursively
     * @param X - the node to delete
     */
    void deleteTree(Node<T, GetScore>* X){
        if (!X) return;
        deleteTree(X->left);
        deleteTree(X->right);
        delete X;
    }

    /**
     * The function finds a given node in the tree and splays him
     * @param predicate - a function that compares the nodes on the tree
     * in order to find a given node
     * @return - pointer to the found data or nullptr if not found
     */
    template<typename Predicate>
    T *find(const Predicate &predicate) {
        if (root == nullptr)
            return nullptr;
        Node<T, GetScore> *X = root;
        int not_found = 0;
        while (X != nullptr && predicate(X->data) && !not_found) {
            if (predicate(X->data) == 1)
                if (X->left != nullptr)
                    X = X->left;
                else
                    not_found = 1;
            else if (X->right != nullptr)
                X = X->right;
            else
                not_found = 1;
        }
        splay(X);
        if (not_found)
            return nullptr;
        return &(X->data);
    }

    /**
     * The function finds the min node in the tree
     */
    T find_min() {
        Node<T, GetScore> *X = root;
        if (X == nullptr)
            return nullptr;
        while (X->left != nullptr) {
            X = X->left;
        }
        splay(X);
        return X->data;
    }

    /**
     * The function finds the max node
     */
    T *find_max() {
        Node<T, GetScore> *X = root;
        if (X == nullptr)
            return nullptr;
        while (X->right != nullptr) {
            X = X->right;
        }
        splay(X);
        return &X->data;
    }

    /**
     * This function inserts the given node to the tree
     * The predicate function helps to find the right place to insert the new node
     */
    template<typename Predicate>
    void insert(const Predicate &predicate, T data) {
        try {
            Node<T, GetScore> *X = new Node<T, GetScore>(data, getScore);
            if (!this->root)
                root = X;
            else if (find(predicate) != nullptr)
                return;
            else if (predicate(root->data) < 0) {
                X->setLeft(root);
                X->setRight(root->right);
                X->right_tree_size = root->right_tree_size;
                X->right_tree_sum = root->right_tree_sum;
                if (X->left != nullptr) {
                    X->left->right = nullptr;
                    X->left->right_tree_size = 0;
                    X->left->right_tree_sum = 0;
                }
                X->left_tree_size = root->left_tree_size + 1;
                X->left_tree_sum = root->left_tree_sum + getScore(root->data);
                root = X;
            } else {
                X->setRight(root);
                X->setLeft(root->left);
                X->left_tree_size = root->left_tree_size;
                X->left_tree_sum = root->left_tree_sum;
                if (X->right != nullptr) {
                    X->right->left = nullptr;
                    X->right->left_tree_size = 0;
                    X->right->left_tree_sum = 0;
                }
                X->right_tree_size = root->right_tree_size + 1;
                X->right_tree_sum = root->right_tree_sum + getScore(root->data);
                root = X;
            }
            this->size++;
        } catch (const std::bad_alloc &e) {
            throw e;
        }
    }

    /**
     * the function removes a given node by the predicate function
     */
    template<typename Predicate>
    void remove(const Predicate &predicate) {
        if (this->find(predicate) == nullptr)
            return;
        Node<T, GetScore> *X = this->root;
        SplayTree *Y = new SplayTree(getScore);
        Y->root = this->root->right;
        if (Y->root) {
            Y->root->parent = nullptr;
            X->right_tree_size = 0;
            X->right_tree_sum = 0;
        }
        this->root = this->root->left;
        if (this->root)
            this->root->parent = nullptr;
        delete X;
        this->join(Y);
        delete Y;
        this->size--;
    }

    /**
     * The function returns the sum of the K left elements score
     * @param k - number of elements to calculate
     * @return sum of K left elements scores
     */
    int getSumKLeftElements(int k){
        if(k == 1)
            return getScore(*find_max());
        else {
            Node<T, GetScore> *X = root;
            int num_greater_elements = X->left_tree_size;
            int sum_greater_elememts = X->left_tree_sum;
            while ((k < num_greater_elements || k > (num_greater_elements+1))) {
                if(k < num_greater_elements){
                    X = X->left;
                    num_greater_elements = num_greater_elements - 1 -
                            X->right_tree_size;
                    sum_greater_elememts = sum_greater_elememts -
                            getScore(X->data) - X->right_tree_sum;
                } else {
                    X = X->right;
                    num_greater_elements = num_greater_elements + 1 +
                            X->left_tree_size;
                    sum_greater_elememts = sum_greater_elememts +
                            getScore(X->parent->data) + X->left_tree_sum;
                }
            }
            if(k == num_greater_elements)
                return sum_greater_elememts;
            else //if(k == (num_greater_elements+1))
                return sum_greater_elememts + getScore(X->data);
        }
    }

    /**
     * The function goes over the tree in order and operates a given function
     * on any node in the tree
     */
    template<typename Function>
    void inOrder(Node<T, GetScore> *X, const Function &function) {
        if (X == nullptr)
            return;
        inOrder(X->left, function);
        function(X->data);
        inOrder(X->right, function);
    }

    /**
     * The function goes over the tree in reverse order and operates a
     * given function on any node in the tree
     */
    template<typename Function>
    void inOrderReverse(Node<T, GetScore> *X, const Function &function) {
        if (X == nullptr)
            return;
        inOrderReverse(X->right, function);
        function(X->data);
        inOrderReverse(X->left, function);
    }

    /**
     * The function goes over the tree in pre order and operates a given function
     * on any node in the tree
     * @param X - the root of the tree
     * @param function
     */
    template<typename Function>
    void preOrder(Node<T, GetScore> *X, const Function &function) {
        if (X == nullptr)
            return;
        function(X->data);
        inOrder(X->left, function);
        inOrder(X->right, function);
    }

    //-------------------HELP FUNCTIONS-----------------------------

    /**
     * The function goes over the tree in order and prints
     * any node in the tree
     */
    void inOrderPrint(Node<T, GetScore> *X) {
        if (X == nullptr)
            return;
        inOrderPrint(X->left);
        std::cout << getScore(X->data) << " left size-" << X->left_tree_size
                  << " left sum-" << X->left_tree_sum
                  << " right size-" << X->right_tree_size << " right sum-"
                  << X->right_tree_sum << std::endl;
        inOrderPrint(X->right);
    }
};

#endif //WET2_FINAL_SPLAYTREE_H
