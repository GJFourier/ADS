#include <iostream>

namespace RBTree{
    enum Color
    {
        RED,
        BLACK
    };

    struct Node
    {
        int key;
        Color color;
        Node *left, *right, *parent;
        Node(int key) : key(key), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    class RedBlackTree
    {
    public:
        long long total = 0;
        RedBlackTree() : root(nullptr) {}
        Node* find(int key){
            findNode(root, key);
        }

        /* 插入 key（注意这里没有额外判断 key 是否已经存在，默认不存在）*/
        void insert(const int &key)
        {
            Node *node = new Node(key);
            if (!root)
            {
                root = node;
                root->color = BLACK;
                return;
            }
            Node *parent = findParent(root, key);
            if (key < parent->key)
            {
                parent->left = node;
            }
            else
            {
                parent->right = node;
            }
            node->parent = parent;
            fixInsertion(node);
        }
        /* 从节点 node 开始中遍历打印红黑树 */
        void inOrderTraversal(Node *node)
        {
            if (node)
            {
                inOrderTraversal(node->left);
                std::cout << (node->color == RED? "R":"B");
                std::cout << node->key << " ";
                inOrderTraversal(node->right);
            }
        }
        /* 从根节点开始遍历打印红黑树 */
        void inOrderTraversal()
        {
            inOrderTraversal(root);
        }

    private:
        Node *root;
        /* 查找键为 key 的节点 */
        Node *findNode(Node *node, const int &key)
        {
            /* TODO: 查找结点 */
            if(key < node->key){
                findNode(node->left, key);
            }
            else if(key > node->key){
                findNode(node->right, key);
            }
            else{
                return node;
            }
        }
        /* 找到键 key 合适的父节点（仅插入时使用）*/
        Node *findParent(Node *node, const int &key)
        {
            if (key < node->key)
            {
                if (!node->left)
                    return node;
                return findParent(node->left, key);
            }
            else
            {
                if (!node->right)
                    return node;
                return findParent(node->right, key);
            }
        }
        /* 循环向上解决双红情况 */
        void fixInsertion(Node *node)
        {
//            inOrderTraversal(root);
            while (node != root && node->parent->color == RED)
            {
                if (node->parent == node->parent->parent->left)
                {
                    Node *uncle = node->parent->parent->right;
                    /* TODO: 根据叔父节点的颜色选择不同的处理方法 */
                    /* NOTE: 注意局部解决后改变 node 的值以继续循环向上 */
                    if(uncle == nullptr || uncle->color == BLACK){
                        if(node == node->parent->right) {
                            rotateLeft(node->parent);
                            node = node->left;
                        }
                        node->parent->color = BLACK;
                        node->parent->parent->color = RED;
                        rotateRight(node->parent->parent);
                    }
                    else {
                        node->parent->color = BLACK;
                        uncle->color = BLACK;
                        node->parent->parent->color = RED;
                        node = node->parent->parent;
                    }
                }
                else
                {
                    Node *uncle = node->parent->parent->left;
                    /* TODO: 根据叔父节点的颜色选择不同的处理方法 */
                    /* NOTE: 注意局部解决后改变 node 的值以继续循环向上 */
                    if(uncle == nullptr || uncle->color == BLACK){
                        if(node == node->parent->left){
                            rotateRight(node->parent);
                            node = node->right;
                        }
                        node->parent->color = BLACK;
                        node->parent->parent->color = RED;
                        rotateLeft(node->parent->parent);
                    }
                    else {
                        node->parent->color = BLACK;
                        uncle->color = BLACK;
                        node->parent->parent->color = RED;
                        node = node->parent->parent;
                    }
                }
            }
            /* 循环到根节点仍然存在双红，则树的高度 +1 */
            root->color = BLACK;
        }
        /* 左旋 */
        void rotateLeft(Node *node)
        {
            ++total;
            Node *rightChild = node->right;
            node->right = rightChild->left;
            if (rightChild->left)
            {
                rightChild->left->parent = node;
            }
            rightChild->parent = node->parent;
            if (!node->parent)
            {
                root = rightChild;
            }
            else if (node == node->parent->left)
            {
                node->parent->left = rightChild;
            }
            else
            {
                node->parent->right = rightChild;
            }
            rightChild->left = node;
            node->parent = rightChild;
        }
        /* 右旋 */
        void rotateRight(Node *node)
        {
            ++total;
            Node *leftChild = node->left;
            node->left = leftChild->right;
            if (leftChild->right)
            {
                leftChild->right->parent = node;
            }
            leftChild->parent = node->parent;
            if (!node->parent)
            {
                root = leftChild;
            }
            else if (node == node->parent->right)
            {
                node->parent->right = leftChild;
            }
            else
            {
                node->parent->left = leftChild;
            }
            leftChild->right = node;
            node->parent = leftChild;
        }
    };
}