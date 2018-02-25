#include <iostream>
#include <string>
using namespace std;
#include "trietree.h"
void ClearScreen()
{
	cout << string(10, '\n');
};
int main()
{
	Trie trie;
	trie.Buildtrie();
	string word;
	while (1)
	{
		cout << "Nhap tu ban muon tim: ";
		getline(cin, word);
		//cin >> word;
		cout << "Searching..." << endl;
		trie.find(word);
		//system("pause");
		ClearScreen();
	}
	cin.get();
	return 0;
}
