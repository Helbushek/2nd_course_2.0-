#pragma once
#include <vector>
#include <QWidget>

class Node;

class BinaryTree
{
public:
    class Node;

public:
    BinaryTree() = default;
    BinaryTree(const BinaryTree &other);

    ~BinaryTree();

    int getKey();

    Node* root();

    void clear();
    static void clear(Node* root);

    BinaryTree clone() const;
    static BinaryTree clone(Node *root);
    void operator=(const BinaryTree &other);

    bool isIdeal() const;
    bool isBalanced() const;

    Node *addNode(int key);

    void printHorizontal(int levelSpacing = 4) const;
    void printHorizontal(Node *root, int marginLeft, int levelSpacing) const;

    static void clearLeftChild(Node *root = nullptr);
    static void clearRightChild(Node *root = nullptr);
    static void clearChild(Node *root = nullptr);

    bool isEmpty() const;

    BinaryTree copyRightChild() const;
    BinaryTree copyLeftChild() const;

    int height() const;
    int height(int) const;
    int power() const;

    int max() const;
    int min() const;

    bool remove(const int key);

    BinaryTree find(const int key) const;

    void printList() const;

    operator std::vector<int>() const;
private:
    explicit BinaryTree(Node* root);
    Node *_addNode(Node *root, int key);
    Node *_clone() const;
    static Node *_clone(Node *root);

    int height(Node*) const;
    int degree(Node*) const;

    int max(Node*) const;
    int min(Node*) const;

    bool remove(Node *root);
    Node *detect(int key, Node*);

    Node *_find(const int key, Node *) const;

    void _nlrPrint(Node *) const;

    bool _isIdeal(Node *) const;
    bool _isBalanced(Node *) const;

    void vectorize(Node *root, std::vector<int>&) const;

private:
    Node *m_root = nullptr;
};


