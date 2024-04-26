#include <iostream>
#include <fstream>

using namespace std;

struct tree {
    int i_val;
    tree* left;
    tree* right;
};

tree* F_T_CRreateNode(int a) // Создание узла
{
    tree* T = new tree;
    T->i_val = a;
    T->left = T->right = NULL;
    return T;

}

void push(tree*& root, tree* node)
{
    if (root) // Если дерево существует
    {
        if (node->i_val <= root->i_val) // Сравнение узла с корнем
            push(root->left, node);
        else
            push(root->right, node);
    }
    else
        root = node; // Корень делаем узлом
}

tree* F_T_ReadTree(const char* filename) // Чтение файла
{
    tree* T = NULL;

    ifstream file;
    file.open(filename);

    int a;

    while (!file.eof()) // Создание дерева (запись из файла)
    {
        file >> a;
        push(T, F_T_CRreateNode(a));

    }

    file.close();

    return T;
}

void F_V_WriteNodeInOrder(ofstream& fout, tree* node) // Вывод в файл + операция inOrder (симметричный обход)
{
    if (node)
    {

        F_V_WriteNodeInOrder(fout, node->left);
        fout << abs(node->i_val) << " ";
        F_V_WriteNodeInOrder(fout, node->right);
    }
}


void F_V_WriteTree(const char* filename, tree* T) // Запись в файл
{
    ofstream fout;
    fout.open(filename);

    F_V_WriteNodeInOrder(fout, T);

    fout.close();


}

void F_V_DelTree(tree*& node) // Удаление узлов (дерева)
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
