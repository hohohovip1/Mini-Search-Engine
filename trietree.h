#pragma once
#include <vector>
#include <sstream> //stringstream
#include <cctype> //tolower
#include <string>
#include <map>
#include <algorithm> //sort
#include <fstream>


const int ALPHABETS = 26;

using namespace std;
struct TrieNode
{
	TrieNode * children[ALPHABETS];
	vector<int> location;
};
struct TrieNode *getNode(void)
{
	struct TrieNode *pNode = new TrieNode;
	for (int i = 0; i < ALPHABETS; i++)
		pNode->children[i] = NULL;

	return pNode;
}
class Trie
{
protected:
	TrieNode * root;
	//vector<TrieNode*> children;
public:
	Trie()
	{
		root = getNode();
	};
	/*~Trie()
	{
	for (int i = 0; i < children.size(); i++)
	delete children[i];
	};
	*/
	void insert(string key, int ocur)
	{
		TrieNode *pCrawl = root;
		for (int i = 0; i < key.length(); i++)
		{
			int index = key[i] - 'a';
			if (pCrawl->children[index] == NULL)
			{
				pCrawl->children[index] = getNode();
			}
			pCrawl = pCrawl->children[index];
		}
		pCrawl->location.push_back(ocur);
	};
	vector<int> search(string key)
	{
		if (key == "AND")
		{
			vector<int> andvec;
			andvec.push_back(-1);
			return andvec;
		}
		if (key == "OR")
		{
			vector<int> orvec;
			orvec.push_back(-2);
			return orvec;
		}
		TrieNode *pCrawl = root;

		for (int i = 0; i < key.length(); i++)
		{
			int index = key[i] - 'a';
			if (pCrawl->children[index] == NULL)
			{
				vector<int> empty;
				return empty;
			}

			pCrawl = pCrawl->children[index];
		}
		return pCrawl->location;
	};
	void searchprint(vector<int> &document, string words)
	{
		if (!document.empty())
		{
			sort(document.begin(), document.end());
			cout << "\"" << words << "\"" << " is found in documents: ";
			for (size_t i = 0; i < document.size(); i++)
			{
				cout << " " << document[i];
			}
			cout << endl;
		}
		else
		{
			cout << "No results was found!" << endl;
		}
	};
	vector<int> findAND(vector<int> &one, vector<int> &two)
	{
		vector<int> answer;
		for (size_t i = 0; i < one.size(); i++)
		{
			for (size_t j = 0; j < two.size(); j++)
			{
				if (one[i] == two[j])
					answer.push_back(one[i]);
			}
		}
		return answer;
	};
	vector<int> findOR(vector<int> &one, vector<int> &two)
	{
		vector<int> answer;
		for (size_t i = 0; i < one.size(); i++)
		{
			answer.push_back(one[i]);
		}
		for (size_t i = 0; i < two.size(); i++)
		{
			if (std::find(one.begin(), one.end(), two[i]) != one.end())
			{
			}
			else
			{
				answer.push_back(two[i]);
			}
		}
		return answer;
	};
	vector<int> phaseMatching(vector<int> &one, vector<int> &two)
	{
		vector<int> answer;
		for (size_t i = 0; i < one.size(); i++)
		{
			for (size_t j = 0; j < two.size(); j++)
			{
				if (one[i] == two[j]+1)
					answer.push_back(one[i]);
			}
		}
		return answer;
	};
	void find(string words)
	{
		vector<string> wordvector;
		string buffer;
		stringstream ss(words);
		while (ss >> buffer)
		{
			wordvector.push_back(buffer);
		}
		vector<vector<int> > allthelocations;
		for (int i = 0; i < wordvector.size(); i++)
		{
			allthelocations.push_back(search(wordvector[i]));
		}
		vector<int> x = recursivesearch(allthelocations);
		searchprint(x, words);
	};
	vector<int> recursivesearch(vector< vector<int> > x)
	{
		int size = x.size();
		if (size % 2 == 0 && size > 2)
		{
			vector<int> empty;
			return empty;
		}
		if (size == 1)
			return x[0];
		if (size == 2)
		{
			return phaseMatching(x[0], x[1]);
		}
		if (size == 3)
		{
			if (x[1][0] == -1)
			{
				return findAND(x[0], x[2]);
			}
			if (x[1][0] == -2)
			{
				return findOR(x[0], x[2]);
			}
			else
			{
				vector<int> empty;
				return empty;
			}
		}
		else 
		{
			vector<vector<int>> t;
			for (int i = 2; i < size; i++)
			{
				t.push_back(x[i]);
			}
			if (x[1][0] == -1)
			{
				vector<int> h = recursivesearch(t);
				return findAND(x[0], h);
			}
			if (x[1][0] == -2)
			{
				vector<int> h = recursivesearch(t);
				return findOR(x[0], h);
			}
			else
			{
				vector<int> empty;
				return empty;
			}
		}
		/*int mid = size / 2;
		vector<vector<int>> y;
		for (int i = 0; i < mid; i++)
		{
			y.push_back(x[i]);
		}
		vector<vector<int>> z;
		for (int i = mid + 1; i < size; i++)
		{
			z.push_back(x[i]);
		}
		if (x[mid][0] == -1)
		{
			vector<int> a = recursivesearch(y);
			vector<int> b = recursivesearch(z);
			return findAND(a, b);
		}
		if (x[mid][0] == -2)
		{
			vector<int> a = recursivesearch(y);
			vector<int> b = recursivesearch(z);
			return findOR(a, b);
		}
		else
		{
			vector<int> empty;
			return empty;
		}*/
	};
	void Buildtrie()
	{
		ifstream input;
		string common = "doc/text000";
		string word;
		Trie trie;
		for (int number = 1; number <= 6; number++)
		{
			if (number > 9)
			{
				common = "doc/text00";
			}
			stringstream ss;
			ss << common << number;
			string filename = ss.str();

			input.open(filename.c_str());
			if (input.fail())
			{
				cout << "Failed to open document" << number << endl;
				cin.get();
				return;
			}
			/*ostringstream convert;
			convert << number;
			string documentNumber = convert.str();
			*/
			while (!input.eof())
			{
				input >> word;
				if (word[0] != '<' && word != "\0" && word[0]!='.')
				{
					if (word[0] == '.' || word[0] == ',')
					{
						word.erase(0, 1);
					}
					else if (word[word.size() - 1] == '.' || word[word.size() - 1] == ',')
					{
						word.erase(word.size() - 1);
					}
					for (int i = 0; i < word.length(); i++)
					{
						tolower(word[i]);
					}
					insert(word, number);
				}
			}

			input.close();
		}
		/*string words[] = { "foo", "bar", "baz", "barz" };
		for (int i = 0; i < 4; i++)
		{
		insert(words[i]);
		}*/

	};
};