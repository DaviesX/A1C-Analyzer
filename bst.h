#ifndef BST_H
#define BST_H


#include <ostream>
#include <vector>

template <class T>
class BST
{
        template <typename K> friend std::ostream& operator<<(std::ostream& os, const BST<K>& bst);
        template <typename K> friend void bst_inorder_print(std::ostream& os, const typename BST<K>::Node* node);

public:
        BST();
        ~BST();

        void            insert(const T& value);
        T*              find(const T& value);
        void            remove(const T& value);
        void            extract(std::vector<T>& values) const;
        void            clear();
        int        size() const;

        //struct Iterator {
        //        std::vector<Node*>      stack;
        //        Node*                   node;

        //        void            init(Node* root);
        //        void            has_next();
        //        T&              next();
        //};

private:
        void            destroy_subtree(typename BST<T>::Node* node);
        void            copy_nodes(std::vector<T>& values, const typename BST<T>::Node* node) const;

        struct Node
        {
                Node(const T& value):
                        value(value), left(nullptr), right(nullptr)
                {
                }

                T               value;
                Node*           left;
                Node*           right;
        };

        Node*           root = nullptr;
        int        n_nodes = 0;
};

// Iterator
//template <class T>
//void BST<T>::Iterator::init(Node* node)
//{
//        stack.clear();
//        this->node = node;
//        stack.push_back(node);
//}

//template <class T>
//void BST<T>::Iterator::has_next()
//{
//        return !stack.empty();
//}
//
//template <class T>
//T& BST<T>::Iterator::next()
//{
//}

// Class
template <class T>
BST<T>::BST()
{
}

template <class T>
BST<T>::~BST()
{
        clear();
}

template <class T>
void BST<T>::insert(const T& value)
{
        Node* current_node = root;
        Node* old_node = nullptr;
        while (current_node != nullptr) {
                if (value < current_node->value) {
                        old_node = current_node;
                        current_node = current_node->left;
                } else if (value > current_node->value) {
                        old_node = current_node;
                        current_node = current_node->right;
                } else {
                        current_node->value = value;
                        return ;
                }
        }

        // Insert to this position.
        // Create a new node.
        Node* new_node = new Node(value);

        if (old_node == nullptr)
                root = new_node;
        else {
                if (value < old_node->value)
                        old_node->left = new_node;
                else
                        old_node->right = new_node;
        }
        n_nodes ++;
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
                } else {
                        return &current_node->value;
                }
        }
        return nullptr;
}

template <class T>
int BST<T>::size() const
{
        return n_nodes;
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

template <class T>
void BST<T>::copy_nodes(std::vector<T>& values, const typename BST<T>::Node* node) const
{
        if (node == nullptr)
                return;
        else {
                copy_nodes(values, node->left);
                values.push_back(node->value);
                copy_nodes(values, node->right);
        }
}

template <class T>
void BST<T>::extract(std::vector<T>& values) const
{
        values.reserve(n_nodes);
        copy_nodes(values, root);
}

template<class T>
void BST<T>::destroy_subtree(typename BST<T>::Node* node)
{
        if (node == nullptr)
                return;
        else {
                destroy_subtree(node->left);
                destroy_subtree(node->right);
                delete node;
        }
}

template <class T>
void BST<T>::clear()
{
        destroy_subtree(root);
        root = nullptr;
        n_nodes = 0;
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
