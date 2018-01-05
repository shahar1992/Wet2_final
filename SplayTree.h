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
        void setLeft(Node<P, GetScore1> *Left) {
            if (Left) {
                int size_change =
                        Left->left_tree_size + Left->right_tree_size + 1;
                int sum_change =
                        Left->left_tree_sum + Left->right_tree_sum +
                        getScore(Left->data);
                updateParents(Left, -size_change, -sum_change);
                if (Left->parent) {
                    if (Left->parent->right == Left)
                        Left->parent->right = nullptr;
                    else
                        Left->parent->left = nullptr;
                }
                if (this->left)
                    left->parent = nullptr;
            }
            left = Left;
            left_tree_size = 0;
            left_tree_sum = 0;
            if (left) {
                int size_change =
                        left->left_tree_size + left->right_tree_size + 1;
                int sum_change =
                        left->left_tree_sum + left->right_tree_sum +
                        getScore(left->data);
                if (this->parent == left)
                    this->parent = nullptr;
                left->parent = this;
                updateParents(left, size_change, sum_change);
            }
        }

        /**
         * Set function to set the given Node as right child
         */
        void setRight(Node<P, GetScore1> *Right) {
            if (Right) {
                int size_change =
                        Right->left_tree_size + Right->right_tree_size + 1;
                int sum_change =
                        Right->left_tree_sum + Right->right_tree_sum +
                        getScore(Right->data);
                updateParents(Right, -size_change, -sum_change);
                if (Right->parent) {
                    if (Right->parent->right == Right)
                        Right->parent->right = nullptr;
                    else
                        Right->parent->left = nullptr;
                }
                if (this->right)
                    right->parent = nullptr;
            }
            right = Right;
            right_tree_size = 0;
            right_tree_sum = 0;
            if (right) {
                int size_change =
                        right->left_tree_size + right->right_tree_size + 1;
                int sum_change =
                        right->left_tree_sum + right->right_tree_sum +
                        getScore(right->data);
                if (this->parent == right)
                    this->parent = nullptr;
                right->parent = this;
                updateParents(right, size_change, sum_change);
            }
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
        } else {         //in case B == A -> right
            A->setRight(B->left);
            B->parent = nullptr;
            B->setLeft(A);
            this->root = B;
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
        } else {                                          // right right case
            A->parent->setRight(A->left);
            A->setLeft(A->parent);
            A->setRight(B->left);
            B->setLeft(A);
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
            A->parent->setLeft(B->right);
            Node<T, GetScore> *tmp = A->parent;
            A->parent = nullptr;
            A->setRight(B->left);
            B->setRight(tmp);
            B->setLeft(A);
        } else                                          // right left case
        {
            A->parent->setRight(B->left);
            Node<T, GetScore> *tmp = A->parent;
            A->parent = nullptr;
            A->setLeft(B->right);
            B->setLeft(tmp);
            B->setRight(A);
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
        if (this->root)
            this->root->setRight(T2->root);
        else
            this->root = T2->root;
        T2->root = nullptr;
    }


//---################################split doesn't support the invariants#####################---------------
    /**
     * The function splits a given tree into two trees according to the
     * given predicate function (with given node to compare to)
     * T1 will get all the lower or equal values
     * T2 will get all the higher values
     */
    template<typename Predicate>
    void split(const Predicate &predicate, SplayTree<T, GetScore> &T1,
               SplayTree<T, GetScore> &T2) {
        this->find(predicate);
        if (predicate(root) >= 0) {
            T1.root = root;
            T1.root->right = nullptr;
            T2.root = root->right;
            T2.root->parent = nullptr;
        } else {
            T1.root = root->left;
            T1.root->parent = nullptr;
            T2.root = root;
            T2.root->left = nullptr;
        }
    }

public:
    //--------------SPLAY TREE FIELDS-----------------------------
    Node<T, GetScore> *root;
    int size;
    GetScore getScore;

    /**
    * Constructs a new Splay Tree.
    */
    SplayTree<T, GetScore>() : root(), size() {};

    /**
     * Distructor
     */
    ~SplayTree() {
        int index = 0;
        Node<T, GetScore> **nodes = new Node<T, GetScore> *[this->size];
        convertTreeToNodesArray(root, &index, nodes);
        for (int i = 0; i < this->size; i++)
            delete nodes[i];
        delete[] nodes;
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
                if (X->left != nullptr) {
                    X->left->right = nullptr;
                    X->left->right_tree_size = 0;
                    X->left->right_tree_sum = 0;
                }
                root = X;
            } else {
                X->setRight(root);
                X->setLeft(root->left);
                if (X->right != nullptr) {
                    X->right->left = nullptr;
                    X->right->left_tree_size = 0;
                    X->right->left_tree_sum = 0;
                }
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


    /**
* function that converts a given tree into array of Nodes<T> pointers
* @param node - the root of the tree to convert
* @param index - the current index of the given "root"
* @param array  - the array to insert the nodes to
*/
    static void convertTreeToNodesArray(Node<T, GetScore> *node, int *index,
                                        Node<T, GetScore> **array) {
        if (!node) return;
        convertTreeToNodesArray(node->left, index, array);
        array[*index] = node;
        (*index)++;
        convertTreeToNodesArray(node->right, index, array);
    }

    /**
     * function that converts a given tree into array of the data in the tree
     * @param node - the root of the tree to convert
     * @param index - the current index of the given "root"
     * @param array  - the array to insert the data to
     */
    void convertTreeToDataArray(Node<T, GetScore> *node, int *index, T *array) {
        if (!node) return;
        convertTreeToDataArray(node->right, index, array);
        array[*index] = node->data;
        (*index)++;
        convertTreeToDataArray(node->left, index, array);
    }


    /**
     * Ths function merges two arrays into one ordered array with the given
     * Compare function
     * @param merged - an array to insert the ordered array
     * @param changed - one of the arrays to merge
     * @param changed_i - number of elements in the changed array
     * @param orig - one of the arrays to merge
     * @param orig_i - number of elements in the orig array
     * @param compare - the function to compare with
     */
    template<typename Compare>
    void mergeArrays(T **merged, T **changed, int changed_i,
                     T **orig, int orig_i, Compare &compare) {
        int i = 0, oi = 0, ci = 0;
        while (oi < orig_i && ci < changed_i) {
            if (compare((*changed)[ci], (*orig)[oi])) {
                (*merged)[i] = (*changed)[ci++];
            } else {
                (*merged)[i] = (*orig)[oi++];
            }
            i++;
        }
        while (ci < changed_i) {
            (*merged)[i++] = (*changed)[ci++];
        }
        while (oi < orig_i) {
            (*merged)[i++] = (*orig)[oi++];
        }
    }

    //-------------------HELP FUNCTIONS-----------------------------
    /**
    * function object that inserts an array values into a given tree
    */
    class InsertArrayToTree {
        Node<T, GetScore> **nodes;
        int index;
    public:
        explicit InsertArrayToTree(Node<T, GetScore> **nodes) : nodes(nodes),
                                                                index(0) {}

        void operator()(T data) {
            data = *(nodes[index++])->data;
        }
    };

    /**
     * function that updates the tree values with Update function if the
     * Condition is true
     * @param update - update function
     * @param condition - condition function
     * @param compare - compare data function
     */
    template<typename Update, typename Condition, typename Compare>
    void conditionedUpdate(const Update &update,
                           const Condition &condition,
                           const Compare &compare) {
        Node<T, GetScore> **nodes = new Node<T, GetScore> *[this->size];
        T *changed, *orig;

        int ind = 0;
        convertTreeToNodesArray(root, &ind, nodes);
        changed = new T[this->size];
        orig = new T[this->size];
        int orig_i = 0, changed_i = 0;
        for (int i = 0; i < this->size; i++) {
            if (condition(nodes[i]->data)) {
                update(nodes[i]->data);
                changed[changed_i++] = nodes[i]->data;
            } else {
                orig[orig_i++] = nodes[i]->data;
            }
        }
        T *merged = new T[this->size];
        mergeArrays(&merged, &changed, changed_i, &orig, orig_i, compare);
        for (int i = 0; i < this->size; i++) {
            nodes[i]->data = merged[i];
        }
        delete[] changed;
        delete[] orig;
        delete[] nodes;
        delete[] merged;
    }

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
