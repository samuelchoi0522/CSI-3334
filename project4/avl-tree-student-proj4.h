/**
 * file: avl-tree-student-proj4.h
 * author: Samuel Choi
 * course: CSI 3334
 * assignment: project 4
 * due date: March 22, 2024 
 * version: 1.0
 * 
 * This file contains the definitions of the functions in avl-tree-prof-proj4.h
 */

#ifndef AVL_TREE_STUDENT_PROJ4 
#define AVL_TREE_STUDENT_PROJ4 

#include "avl-tree-prof-proj4.h"
#include <queue>

/**
 * Destructor for AVLNode
 *
 * This destructor recursively deletes the left and right subtrees of the current node.
 */
template <class Base>
AVLNode<Base>::~AVLNode(){
    delete left;
    delete right;
}

/**
 * Print Preorder
 *
 * This function prints the data of the current node followed by its left and right 
 * subtrees in preorder.
 * If either subtree is null, it prints "NULL" instead.
 * 
 * Parameters:
 *   os: Output stream to print the data
 *   indent: Indentation for the current node's data
 */
template <class Base>
void AVLNode<Base>::printPreorder(ostream &os, string indent) const{
    os << indent << data << endl;
    if(left) left->printPreorder(os, indent + "  ");
    else os << indent + "  NULL" << endl;
    if(right) right->printPreorder(os, indent + "  ");
    else os << indent + "  NULL" << endl;
}

/**
 * Find Minimum Node
 *
 * This function finds and returns the node with the minimum data value in the subtree 
 * rooted at the current node.
 * 
 * Return value: Pointer to the node with the minimum data value
 */
template <class Base>
const AVLNode<Base> *AVLNode<Base>::minNode() const{
    const AVLNode<Base> *current = this;

    while (current->getLeft()){
        current = current->getLeft();
    }

    return current;
}

/**
 * Find Maximum Node
 *
 * This function finds and returns the node with the maximum data value in the subtree 
 * rooted at the current node.
 * 
 * Return value: Pointer to the node with the maximum data value
 */
template <class Base>
const AVLNode<Base> *AVLNode<Base>::maxNode() const{
    const AVLNode<Base> *current = this;

    while (current->getRight()){
        current = current->getRight();
    }

    return current;
}

/**
 * Single Rotate Left
 *
 * This function performs a single left rotation around the current node.
 * 
 * Return value: Pointer to the new root node after rotation
 */
template <class Base>
AVLNode<Base> *AVLNode<Base>::singleRotateLeft() {
    AVLNode<Base> *rightChild = right;
    right = rightChild->left;
    rightChild->left = this;
    
    updateHeight();
    rightChild->updateHeight();
    
    return rightChild;
}

/**
 * Single Rotate Right
 *
 * This function performs a single right rotation around the current node.
 * 
 * Return value: Pointer to the new root node after rotation
 */
template <class Base>
AVLNode<Base> *AVLNode<Base>::singleRotateRight() {
    AVLNode<Base> *leftChild = left;
    left = leftChild->right;
    leftChild->right = this;
    
    updateHeight();
    leftChild->updateHeight();
    
    return leftChild;
}

/**
 * Double Rotate Left Right
 *
 * This function performs a double rotation (left-right) around the current node.
 * 
 * Return value: Pointer to the new root node after rotation
 */
template <class Base>
AVLNode<Base> *AVLNode<Base>::doubleRotateLeftRight() {
    left = left->singleRotateLeft();
    return singleRotateRight();
}

/**
 * Double Rotate Right Left
 *
 * This function performs a double rotation (right-left) around the current node.
 * 
 * Return value: Pointer to the new root node after rotation
 */
template <class Base>
AVLNode<Base> *AVLNode<Base>::doubleRotateRightLeft() {
    right = right->singleRotateRight();
    return singleRotateLeft();
}

/**
 * Insert
 *
 * This function inserts a new node with the given data into the AVL tree and 
 * rebalances if necessary.
 * 
 * Parameters:
 *   item: Data to be inserted into the AVL tree
 */
template <class Base>
void AVLTree<Base>::insert(const Base &item) {
    AVLNode<Base> *newNode = new AVLNode<Base>(item);
    if (!root) {
        root = newNode;
        return;
    }
    
    vector<AVLNode<Base> *> path;
    AVLNode<Base> *current = root;
    AVLNode<Base> *parent = nullptr;
    
    while (current) {
        path.push_back(current);
        parent = current; 
        if (item < current->data) {
            current = current->left;
        } 
        else if (current->data < item) {
            current = current->right;
        } 
        else {
            delete newNode;
            return;
        }
    }
    
    if (item < parent->data) {
        parent->left = newNode;
    } 
    else {
        parent->right = newNode;
    }
    
    rebalancePathToRoot(path);
}

/**
 * Remove
 *
 * This function removes a node with the given data from the AVL tree and 
 * rebalances if necessary.
 * 
 * Parameters:
 *   item: Data to be removed from the AVL tree
 */
template <class Base>
void AVLTree<Base>::remove(const Base &item) {
    vector<AVLNode<Base>*> path;
    AVLNode<Base> *toRemove = root;
    AVLNode<Base> *parent = nullptr;

    while (toRemove != nullptr && (toRemove->data < item || item < toRemove->data)) {
        path.push_back(toRemove);
        parent = toRemove;

        if (item < toRemove->data) {
            toRemove = toRemove->left;
        } 

        else {
            toRemove = toRemove->right;
        }

    }

    if (toRemove == nullptr) {
        return;
    }

    if (toRemove->left && toRemove->right) {
        AVLNode<Base> *leftMost = toRemove->right;
        AVLNode<Base> *leftMostParent = toRemove;
        int index = path.size();

        if (leftMost->left != nullptr) {

            while (leftMost->left != nullptr) {
                path.push_back(leftMost);
                leftMostParent = leftMost;
                leftMost = leftMost->left;
            }

            leftMostParent->left = leftMost->right;
            leftMost->right = toRemove->right;
        }

        leftMost->left = toRemove->left;

        if (parent == nullptr) {
            root = leftMost;
        } 
        
        else if (parent->left == toRemove) {
            parent->left = leftMost;
        } 
        
        else {
            parent->right = leftMost;
        }

        path.insert(path.begin() + index, leftMost);
        toRemove->left = toRemove->right = nullptr;

        delete toRemove;
    } 
    
    else if(toRemove->left || toRemove->right){
        AVLNode<Base>* child = nullptr;
        if (toRemove->left == nullptr){
            child = toRemove->right;
        }
        else{
            child = toRemove->left;
        }
        if(parent){
            if (parent->right == toRemove){
                parent->right = nullptr;
                parent->right = child;
                if(toRemove->left == child){
                    toRemove->left = nullptr;
                }
                else{
                    toRemove->right = nullptr;
                }
            }

            else{
                parent->left = nullptr;
                parent->left = child;

                if(toRemove->left == child){
                    toRemove->left = nullptr;
                }
                else{
                    toRemove->right = nullptr;
                }
            }

        }
        else{
            if(toRemove->left == child){
                toRemove->left = nullptr;
            }
            else{
                toRemove->right = nullptr;
            }
            root = child;
        }

        delete toRemove;
    }
    
    else {
        if(parent) {
            if(parent->left == toRemove) {
                parent->left = nullptr;
            } 
            
            else {
                parent->right = nullptr;
            }

        } 
        
        else {
            root = nullptr;
        }

        delete toRemove; 
    }


    for (int i = path.size() - 1; i >= 0; --i) {
        path[i]->updateHeight();
    }

    rebalancePathToRoot(path);
}

/**
 * Print Level Order
 *
 * This function prints the nodes of the AVL tree in level order.
 * 
 * Parameters:
 *   os: Output stream to print the nodes
 */
template <class Base>
void AVLTree<Base>::printLevelOrder(ostream &os) const {
    const int MAX_NODES = 20;

    if (!root) {
        os << "NULL" << endl;
        return;
    }

    queue<AVLNode<Base>*> levelQueue;
    int count = 0;
    levelQueue.push(root);

    while (!levelQueue.empty()) {
        int levelSize = levelQueue.size();
        for (int i = 0; i < levelSize; ++i) {
            AVLNode<Base>* current = levelQueue.front();
            levelQueue.pop();

            if (!current) {
                os << "NULL";
                count++;
            } 
            else {
                count++;
                os << current->data;

                if (current->left) {
                    levelQueue.push(current->left);
                } 
                else {
                    levelQueue.push(nullptr);
                }

                if (current->right) {
                    levelQueue.push(current->right);
                } 
                else {
                    levelQueue.push(nullptr);
                }
            }

            if ((i < levelSize - 1 || !levelQueue.empty()) && count < MAX_NODES) {
                os << " ";
            }

            if(count == MAX_NODES){
                os << endl;
                count = 0;
            }
        }
    }
    os << endl;
}

/**
 * Rebalance Path To Root
 *
 * This function rebalances the AVL tree along the path from the node at the end of 
 * the provided path vector up to the root.
 * 
 * Parameters:
 *   path: Vector containing the nodes along the path from the inserted/deleted node 
 * to the root
 */
template <class Base>
void AVLTree<Base>::rebalancePathToRoot(vector<AVLNode<Base> *> const &path) {
    for (int i = path.size() - 1; i >= 0; --i) {
        AVLNode<Base> *current = path[i];
        current->updateHeight();

        int balanceFactor = AVLNode<Base>::getHeight(current->left) - 
        AVLNode<Base>::getHeight(current->right);

        if (balanceFactor > 1) {
            if (AVLNode<Base>::getHeight(current->left->left) >= 
            AVLNode<Base>::getHeight(current->left->right)) {
                current = current->singleRotateRight(); 
            }
            else {
                current = current->doubleRotateLeftRight();
            }
        }
        else if (balanceFactor < -1) {
            if (AVLNode<Base>::getHeight(current->right->right) >= 
            AVLNode<Base>::getHeight(current->right->left)) {
                current = current->singleRotateLeft(); 
            }
            else {
                current = current->doubleRotateRightLeft(); 
            }
        }

        if (i > 0) {
            if (path[i - 1]->left == path[i]) {
                path[i - 1]->left = current;
            } else {
                path[i - 1]->right = current;
            }
        } else {
            root = current; 
        }
    }
}


/**
 * Encrypt
 *
 * This function encrypts the given data by traversing the BST and generating 
 * a path.
 * 
 * Parameters:
 *   item: Data to be encrypted
 * 
 * Return value: A string representing the path generated during encryption
 */
template <class Base>
string EncryptionTree<Base>::encrypt(const Base &item) const {
    const AVLNode<Base>* current = this->root;
    string path = "r";

    while (current != nullptr) {
        if (item < current->getData()) {
            current = current->getLeft();
            path += "0";
        } 

        else if (current->getData() < item) {
            current = current->getRight();
            path += "1";
        }

        else{
            return path;
        }

    }

    return "?";
}

/**
 * Decrypt
 *
 * This function decrypts the given path and retrieves the data associated with 
 * it from the BST.
 * 
 * Parameters:
 *   path: Path representing the encrypted data
 * 
 * Return value: Pointer to the decrypted data, or nullptr if the path is invalid
 */
template <class Base>
const Base* EncryptionTree<Base>::decrypt(const string &path) const {
    const AVLNode<Base>* current = this->root;

    for (unsigned int i = 1; i < path.size(); ++i) {
        char direction = path[i];

        if (current == nullptr){
            return nullptr;
        }

        if (direction == '0'){
            current = current->getLeft();
        }

        else if (direction == '1'){
            current = current->getRight();
        }

        else{
            return nullptr;
        }
    }

    if (current == nullptr){
        return nullptr;
    }

    return &(current->getData());
}



#endif
