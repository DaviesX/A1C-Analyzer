#ifndef BST_H
#define BST_H


template <class T>
class BST
{
public:
        BST();
        ~BST();

        void    insert(const T& value);
        T&      find(const T& value);
        void    remove(const T& value);
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
void insert(const T& value)
{
}

template <class T>
T& find(const T& value)
{
}

template <class T>
void remove(const T& value)
{
}


#endif // BST_H
