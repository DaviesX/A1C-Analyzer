#ifndef LINKEDLinkedBST_H
#define LINKEDLinkedBST_H

#include "linkedlist.h"


template <class T>
class LinkedBST
{
        template <typename K> friend std::ostream& operator<<(std::ostream& os, const LinkedBST<K>& bst);
        template <typename K> friend void bst_inorder_print(std::ostream& os, const typename LinkedBST<K>::Node* node);

public:
        LinkedBST();
        ~LinkedBST();

        void            insert(const T& value);
        LinkedList<T>*  find(const T& value);
        void            remove(const T& value);

private:
        struct Node
        {
                LinkedList<T>   value;
                Node*           left;
                Node*           right;

               bool operator < (const T& value)
               {
                       return *this->value.front() < value;
               }

               bool operator > (const T& value)
               {
                       return *this->value.front() > value;
               }
        };

        Node*   root = nullptr;
};

template <class T>
LinkedBST<T>::LinkedBST()
{

}

template <class T>
LinkedBST<T>::~LinkedBST()
{
}

template <class T>
void LinkedBST<T>::insert(const T& value)
{
        Node* current_node = root;
        Node* old_node = nullptr;
        while (current_node != nullptr) {
                if (*current_node > value) {
                        old_node = current_node;
                        current_node = current_node->left;
                } else if (*current_node < value) {
                        old_node = current_node;
                        current_node = current_node->right;
                } else {
                        // Insert to this position.
                        current_node->value.push_front(value);
                        return ;
                }
        }
        // Insert to a new position.
        // Since the node doesn't exit, create a new node.
        Node* new_node = new Node;
        new_node->value.push_front(value);
        new_node->left = nullptr;
        new_node->right = nullptr;
        if (old_node == nullptr)
                root = new_node;
        else {
                if (*old_node < value)
                        old_node->right = new_node;
                else
                        old_node->left = new_node;
        }
}

template <class T>
LinkedList<T>* LinkedBST<T>::find(const T& value)
{
        Node* current_node = root;
        while (current_node != nullptr) {
                if (*current_node > value) {
                        current_node = current_node->left;
                } else if (*current_node < value) {
                        current_node = current_node->right;
                } else {
                        return &current_node->value;
                }
        }
        return nullptr;
}

template <typename K>
void linked_bst_inorder_print(std::ostream& os, const typename LinkedBST<K>::Node* node)
{
        if (node == nullptr) {
        } else {
                ::linked_bst_inorder_print<K>(os, node->left);
                os << node->value << ",";
                ::linked_bst_inorder_print<K>(os, node->right);
        }
}

template <typename K>
std::ostream& operator<<(std::ostream& os, const LinkedBST<K>& lbst)
{
        os << "LinkedBST = [";
        ::linked_bst_inorder_print<K>(os, lbst.root);
        os << "]";
        return os;
}

#endif // LINKEDLinkedBST_H
