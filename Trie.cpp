#include <iostream>
//#include <bits/stdc++.h>
#include "Trie.h"

using namespace std;

// Возвращет новый узел с пустыми детьми
TrieNode* getNewNode(void)
{
    // Выделяем память по новый узел
    struct TrieNode* pNode = new TrieNode;

    // устанавливаем флаг конца слова в false
    pNode->isEndOfWord = false;

    // инициализируем детей нулевым уазателем
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}


// Вставляет ключ в дерево, если его нет, 
// иначе если ключ явлется префксом узла дерева 
// помечает вкачестве литового т.е. конец слова
void insert(TrieNode* root, string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // вычисляем индекс в алфите через смещение отнситьельно первой буквы
        int index = key[i] - 'a';

        // если указатель пустрой, т.е. детей с таким префиксом нет
        // создаем новый узел
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }

    // помечаем последний узлел как лист, т.е. конец слова
    node->isEndOfWord = true;
    //  cout << key << " ";
}

// Возврашает true если ключ есть в дереве, иначе false 
bool  search(struct TrieNode* root, string key)
{
    struct TrieNode* node = root;
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return false;
        node = node->children[index];
    }
    return (node != nullptr && node->isEndOfWord);
}

bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// Рекурсивная функция удаления ключа из дерева 
TrieNode* remove(TrieNode* root, string key, int depth)
{
    // Если дерево пустое 
    if (!root)
        return nullptr;

    // если дошли до конца ключа 
    if (depth == key.size()) {

        // Этот узел больше не конец слова 
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // Если ключ не евляется префиксом, удаляем его
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }
        return root;
    }
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }
    return root;
}

// вывод окончания слов по ключу
void find_end(TrieNode* root, char buf[], int ind, string& res, string key) {
    TrieNode* node = root;
    ind++;
    if (node->isEndOfWord == true && isEmpty(node)) {
        cout << key;
        for (int i = 0; i < ind; i++) {
            
            cout << buf[i];
        }
        cout << endl;
    }
    if (node->isEndOfWord == true && !isEmpty(node)) {
        {cout << key;
            for (int i = 0; i < ind; i++) {
                cout << buf[i];
            }
            cout << endl;
        }
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != nullptr) {
                char b = 'a' + i;
                buf[ind] = b;
                find_end(node->children[i], buf, ind, res, key);
                continue;
            }
        }
    }

    if (node->isEndOfWord == false) {
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != nullptr) {
                char b = 'a' + i;

                buf[ind] = b;

                find_end(node->children[i], buf, ind, res, key);
                continue;
            }
        }
    }
}


//вывод слов из словаря по ключу
void find_words(TrieNode* root, string key) {

    if (key == "") { 
        cout << "Вы не ввели ключ для поиска!" << endl;
        return ;
    }
    struct TrieNode* node = root;
    int y = 0;
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (node->children[index] == nullptr) {
            cout << "Нет слова с таким ключем в словаре!" << endl;
            break;
        }
        if (node->children[index]) {
            node = node->children[index];
            y++;
        }
    }
    if (y== key.length()) {
        char buf[10];
        int ind = -1;
        string res;
        find_end(node, buf, ind, res, key);
    }
}
