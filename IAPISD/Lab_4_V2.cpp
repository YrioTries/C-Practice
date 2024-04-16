#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

struct tree {
    int i_val;
    tree* left;
    tree* right;
    tree(int x) : i_val(x), left(NULL), right(NULL) {}
};

void insert(tree*& root, int i_val) {
    if (root == NULL) {
        root = new tree(i_val);
        return;
    }
    if (i_val < root->i_val) {
        insert(root->left, i_val);
    }
    else {
        insert(root->right, i_val);
    }
}

tree* F_T_ReadTree(const char* filename)
{
    tree* T = NULL;

    ifstream file;
    file.open(filename);

    int a;

    while (!file.eof())
    {
        file >> a;
        insert(T, abs(a));

    }

    file.close();

    return T;
}

void F_V_WriteNodeInOrder(ofstream& fout, tree* node)
{
    if (node)
    {
        F_V_WriteNodeInOrder(fout, node->left);
        fout << node->i_val << " ";
        F_V_WriteNodeInOrder(fout, node->right);
    }
}

void F_V_WriteTree(const char* filename, tree* T)
{
    ofstream fout;
    fout.open(filename);

    F_V_WriteNodeInOrder(fout, T);

    fout.close();
}

void F_V_DelTree(tree*& node)
{
    if (node)
    {
        F_V_DelTree(node->left);
        F_V_DelTree(node->right);
        delete node;
    }
}

int main()
{
    tree* T;

    T = F_T_ReadTree("input.txt");

    F_V_WriteTree("output.txt", T);

    F_V_DelTree(T);
}
