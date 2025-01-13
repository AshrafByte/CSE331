#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <queue>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct BTNode
{
    string value;
    BTNode *left;
    BTNode *right;
    explicit BTNode(string value) : value(value), left(nullptr), right(nullptr) {}
};

// Template class to support the tree
class BinaryTree
{
public:
    BTNode *root;

    explicit BinaryTree();

    void buildTree(const vector<string> &nodes);

    void inOrderTraverse() const;

    void postOrderTraverse() const;

    void preOrderTraverse() const;

    int evaluateBinaryTree(BTNode *start);

    int number_of_leaves();

    ~BinaryTree();

private:
    // Helper function to recursively delete nodes
    void freeTree(BTNode *node);

    void inOrderTraverse(const BTNode *start) const;

    void postOrderTraverse(const BTNode *start) const;

    void preOrderTraverse(const BTNode *start) const;

    bool isOperator(const string &nodeValue);

    int evaluate(char operation, int operand1, int operand2);

    int number_of_leaves(BTNode *start);
};

////////////////////////////////////////////// Public ////////////////////////////////////////////

// BinaryTree constructor definition
BinaryTree::BinaryTree() : root(nullptr) {}

// buildTree method definition outside of the class
void BinaryTree::buildTree(const vector<string> &nodes)
{
    if (nodes.empty())
        return;

    queue<BTNode *> parentQueue;

    // Create the root node and push it into the queue
    root = new BTNode(nodes[0]);
    parentQueue.push(root);

    int index = 1;

    // Perform level-order construction of the tree
    while (index < nodes.size())
    {
        BTNode *currentParent = parentQueue.front();
        parentQueue.pop();

        // Assign left child if available
        if (index < nodes.size() && !nodes[index].empty()) // Check if it's not an empty string
        {
            currentParent->left = new BTNode(nodes[index]);
            parentQueue.push(currentParent->left);
        }
        index++; // Move index after left assignment

        // Assign right child if available
        if (index < nodes.size() && !nodes[index].empty()) // Check if it's not an empty string
        {
            currentParent->right = new BTNode(nodes[index]);
            parentQueue.push(currentParent->right);
        }
        index++; // Move index after right assignment
    }
}

// inOrderTraverse method definition outside of the class
void BinaryTree::inOrderTraverse() const
{
    inOrderTraverse(root);
    cout << "\n";
}

void BinaryTree::postOrderTraverse() const
{
    postOrderTraverse(root);
    cout << "\n";
}

void BinaryTree::preOrderTraverse() const
{
    preOrderTraverse(root);
    cout << "\n";
}

int BinaryTree::evaluateBinaryTree(BTNode *start)
{
    if (start == nullptr)
        return 0;

    if (!isOperator(start->value))
        return stoi(start->value);

    int leftOperand = evaluateBinaryTree(start->left);
    int rightOperand = evaluateBinaryTree(start->right);
    char operation = start->value.at(0);

    return evaluate(operation, leftOperand, rightOperand);
}

inline int BinaryTree::number_of_leaves()
{
    return number_of_leaves(root);
}

// Destructor definition outside of the class
BinaryTree::~BinaryTree()
{
    freeTree(root);
}

////////////////////////////////////////////// Private ////////////////////////////////////////////
// freeTree method definition outside of the class
void BinaryTree::freeTree(BTNode *node)
{
    if (node == nullptr)
        return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

// inOrderTraverse method definition outside of the class
void BinaryTree::inOrderTraverse(const BTNode *start) const
{
    if (start == nullptr)
        return;
    inOrderTraverse(start->left);
    cout << start->value << " ";
    inOrderTraverse(start->right);
}

void BinaryTree::postOrderTraverse(const BTNode *start) const
{
    if (start == nullptr)
        return;
    postOrderTraverse(start->left);
    postOrderTraverse(start->right);
    cout << start->value << " ";
}

void BinaryTree::preOrderTraverse(const BTNode *start) const
{
    if (start == nullptr)
        return;
    cout << start->value << " ";
    preOrderTraverse(start->left);
    preOrderTraverse(start->right);
}

bool BinaryTree::isOperator(const string &nodeValue)
{
    return nodeValue == "+" || nodeValue == "-" || nodeValue == "*" || nodeValue == "/";
}

int BinaryTree::evaluate(char operation, int operand1, int operand2)
{
    switch (operation)
    {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': return operand1 / operand2;
        default: return 0;
    }
}

int BinaryTree::number_of_leaves(BTNode *start)
{
    if (start == nullptr)
        return 0;

    if (start -> left == nullptr && start -> right == nullptr)
        return 1;

    return number_of_leaves(start->left) + number_of_leaves(start -> right);
}
#endif // BINARYTREE_H
