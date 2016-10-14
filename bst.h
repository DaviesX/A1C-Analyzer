#ifndef BST_H
#define BST_H


#include <ostream>

template <class T>
class BST
{
        template <typename K> friend std::ostream& operator<<(std::ostream& os, const BST<K>& bst);
        template <typename K> friend void bst_inorder_print(std::ostream& os, const typename BST<K>::Node* node);

public:
        BST();
        ~BST();

        void    insert(const T& value);
        T*      find(const T& value);
        void    remove(const T& value);

private:
        struct Node {
                T   value;
                Node*           left;
                Node*           right;
        };
        Node*   root = nullptr;
};

template <class T>
BST<T>::BST()
{

}

template <class T>
BST<T>::~BST()
{
}

template <class T>
void BST<T>::insert(const T& value)
{
        // Create a new node.
        Node* new_node = new Node;
        new_node->value = value;
        new_node->left = nullptr;
        new_node->right = nullptr;

        Node* current_node = root;
        Node* old_node = nullptr;
        while (current_node != nullptr) {
                if (value <= current_node->value) {
                        old_node = current_node;
                        current_node = current_node->left;
                } else if (value > current_node->value) {
                        old_node = current_node;
                        current_node = current_node->right;
                }
        }
        // Insert to this position.
        if (old_node == nullptr)
                root = new_node;
        else {
                if (old_node->value <= value)
                        old_node->right = new_node;
                else
                        old_node->left = new_node;
        }
}

template <class T>
T* BST<T>::find(const T& value)
{
        Node* current_node = root;
        while (current_node != nullptr) {
                if (value < current_node->value) {
                        current_node = current_node->left;
                } else if (value > current_node->value) {
                        current_node = current_node->right;
                }

                if (current_node == nullptr) {
                        return nullptr;
                } else if (current_node->value == value) {
                        return &current_node->value;
                }
        }
        return nullptr;
}

template <class T>
void BST<T>::remove(const T& value)
{
        Node* current_node = root;
        Node* old_node = nullptr;
        while (current_node != nullptr) {
                if (value < current_node->value) {
                        old_node = current_node;
                        current_node = current_node->left;
                } else if (value > current_node->value) {
                        old_node = current_node;
                        current_node = current_node-> right;
                }

                // only has one child
                if (current_node->left == nullptr && current_node->right != nullptr) {
                        if (current_node->value <= old_node->value) {
                                old_node->left = current_node->right;
                        } else {old_node->right = current_node->right;}
                }
                else if (current_node->left != nullptr && current_node->right == nullptr) {
                        if (current_node->value <= old_node->value) {
                                old_node->left = current_node->left;
                        } else {old_node->right = current_node->left;}
                }

                // 2 children
                else if (current_node->left != nullptr && current_node->right != nullptr) {
                        Node* replace_node = current_node;
                        while (replace_node != nullptr) {
                                if (replace_node->left != nullptr) {
                                        replace_node = replace_node->left;
                                } else {
                                        break;
                                }
                        }
                        old_node->right = replace_node;
                        replace_node->left = current_node->left->left;
                        replace_node->right = current_node->right;
                }
                break;
        }
}

template <typename K>
void bst_inorder_print(std::ostream& os, const typename BST<K>::Node* node)
{
        if (node == nullptr) {
        } else {
                bst_inorder_print<K>(os, node->left);
                os << node->value << ",";
                bst_inorder_print<K>(os, node->right);
        }
}

template <typename K>
std::ostream& operator<<(std::ostream& os, const BST<K>& bst)
{
        os << "BST = [";
        bst_inorder_print<K>(os, bst.root);
        os << "]";
        return os;
}

#endif // BST_H
