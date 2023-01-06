#include <iostream>
#include "Trie.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");
	TrieNode* root = getNewNode(); // создаем корень дерева словаря

	//добавляем слова в словарь
	insert(root, "slovo");
	insert(root, "monstr");
	insert(root, "cool");
	insert(root, "cold");
	insert(root, "coler");
	insert(root, "colobok");
	while (true) {
		string key;
		string d;
		int e = 0;
		int command = 0;
		cout << "Введите желаемую операцию: \n 1 - ввести словов словарь.\n 2 поиск.\n 0 - выход." << endl;
		cin >> command;
		if (command != 1 && command != 2 && command !=0) {
			cout << "Вы ввели неверную команду!" << endl;
			continue;
		}
		if (command == 0) { break; }
		if (command == 1 || command == 2|| command==0) {
			switch (command) {

			case 1:
			{//Добавление слова в словарь
				cout << "Введите слово: " << endl;

				getline(cin, d, '\n');
				getline(cin, d, '\n');

				insert(root, d);

				break;
			}

			case 2:
				//поиск слова в словаре по ключу
				cout << "Введите ключ для поиска: " << endl;
				getline(cin, d, '\n');
				getline(cin, key, '\n');
				find_words(root, key);
				break;

			default:
				cout << "Неверная команда" << endl;
				break;
			}
		}
	}
	cout << "Досвидания!" << endl;

	return 0;
}
