/**
 * file: bst-student-proj3.h
 * author: Samuel Choi
 * course: CSI 3334
 * assignment: project 3
 * due date: March 1, 2024 
 * version: 1.0
 * 
 * This file contains the declaration of the function in bst-proj-proj3.h
 */
#ifndef BST_STUDENT_PROJ3 
#define BST_STUDENT_PROJ3 

#include "bst-prof-proj3.h"

/**
 * Destructor for BSTNode
 *
 * This destructor recursively deletes the left and right subtrees 
 * of the current node.
 */
template <class Base>
BSTNode<Base>::~BSTNode(){
    delete left;
    delete right;
}

/**
 * Print Preorder
 *
 * This function prints the data of the current node followed by its left 
 * and right subtrees in preorder.
 * If either subtree is null, it prints "NULL" instead.
 * 
 * Parameters:
 *   os: Output stream to print the data
 *   indent: Indentation for the current node's data
 */
template <class Base>
void BSTNode<Base>::printPreorder(ostream &os, string indent) const{
    os << indent << data << endl;
    if(left) left->printPreorder(os, indent + "  ");
    else os << indent + "  NULL" << endl;
    if(right) right->printPreorder(os, indent + "  ");
    else os << indent + "  NULL" << endl;
}

/**
 * Find Minimum Node
 *
 * This function finds and returns the node with the minimum data value in 
 * the subtree rooted at the current node.
 * 
 * Return value: Pointer to the node with the minimum data value
 */
template <class Base>
const BSTNode<Base> *BSTNode<Base>::minNode() const{
    const BSTNode *current = this;

    while (current->getLeft()){
        current = current->getLeft();
    }

    return current;
}

/**
 * Find Maximum Node
 *
 * This function finds and returns the node with the maximum data value in the 
 * subtree rooted at the current node.
 * 
 * Return value: Pointer to the node with the maximum data value
 */
template <class Base>
const BSTNode<Base> *BSTNode<Base>::maxNode() const{
    const BSTNode *current = this;

    while (current->getRight()){
        current = current->getRight();
    }

    return current;
}

/**
 * Insert
 *
 * This function inserts a new node with the given data into the BST.
 * 
 * Parameters:
 *   item: Data to be inserted into the BST
 */
template <class Base>
void BST<Base>::insert(const Base &item) {
    if (root == nullptr) {
        root = new BSTNode<Base>(item);
    } 
    else {
        BSTNode<Base> *current = root;
        BSTNode<Base> *parent = nullptr;

        while (current) {
            parent = current;

            if (item < current->data) {
                current = current->left;
            } 
            else if (current->data < item) {
                current = current->right;
            } 
            else {
                return;
            }
        }

        if (item < parent->getData()) {
            parent->left = new BSTNode<Base>(item);
        } 
        else {
            parent->right = new BSTNode<Base>(item);
        }
    }
}

/**
 * Remove
 *
 * This function removes a node with the given data from the BST.
 * 
 * Parameters:
 *   item: Data to be removed from the BST
 */
template <class Base>
void BST<Base>::remove(const Base &item) {
    BSTNode<Base>* toRemove = root;
    BSTNode<Base>* parent = nullptr;

    while (toRemove != nullptr && (toRemove->data < item || item < toRemove->data)) {
        parent = toRemove;
        if (item < toRemove->data){
            toRemove = toRemove->left;
        }
        else {
            toRemove = toRemove->right;
        }
    }

    if (toRemove == nullptr)
        return;

    if(toRemove->left && toRemove->right){
        BSTNode<Base> *leftMost = toRemove->right;

        BSTNode<Base> *leftMostParent = toRemove;

        if (leftMost->left != nullptr) {
            while (leftMost->left) {                     
                leftMostParent = leftMost;                     
                leftMost = leftMost->left;
            }                                                         
            leftMostParent->left = leftMost->right;                       
            leftMost->right = toRemove->right;
        }                                       
                                                
        leftMost->left = toRemove->left;

        if(parent){
            if(parent->left == toRemove){
                parent->left = leftMost;
            }
            else{
                parent->right = leftMost;
            }

        }
        else{
            root = leftMost;
        }
        
        toRemove->left = toRemove->right = leftMostParent = nullptr;

        delete toRemove;
    }
    else if(toRemove->left || toRemove->right){
        BSTNode<Base>* child = nullptr;
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
    else{
        if(parent){
            if(parent->left == toRemove){
                parent->left = nullptr;
                delete toRemove;
            }
            else{
                parent->right = nullptr;
                delete toRemove;
            }
        }
        else{
            delete root;
            root = nullptr;
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
    const BSTNode<Base>* current = this->root;
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
    const BSTNode<Base>* current = this->root;

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
