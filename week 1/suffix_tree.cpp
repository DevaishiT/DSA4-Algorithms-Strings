#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;
using std::pair;
using std::make_pair;

struct Node {
	vector< Node *> next;
	vector<pair<int,int>> edges;
};

int GetCommonSubstring (const string &text, int s1, int s2, int len)
{
	int common = 0;
  	while (text[s1 + common] == text[s2 + common])
  	{
	    common++;
	    if (common == len or (s2 + common) == text.size()) break;
  	}
  	return common;
}

void InsertSuffixTree(Node *trie, const string& text, int ind)
{
	// cout << text.substr(ind) << endl;
	if (ind >= text.size()) return;

	for (int i=0; i<trie->next.size(); i++)
	{
		int st = trie->edges[i].first;
		int len = trie->edges[i].second;
		int common = GetCommonSubstring(text, st, ind, len);
		if (common > 0 and common < len)
		{
			Node *newNode = new Node;

			newNode->next.push_back(trie->next[i]);
			newNode->edges.push_back(make_pair(st+common, len-common));

			newNode->next.push_back(new Node);
			newNode->edges.push_back(make_pair(ind+common, text.size()-ind-common));

			trie->next[i] = newNode;
			trie->edges[i].second = common;
			return;
		}

		else if (common == len)
		{
			Node *nextNode = trie->next[i];
			InsertSuffixTree(nextNode, text, ind + common);
			return;
		}
	}

	Node *newNode = new Node;
	trie->next.push_back(newNode);
	trie->edges.push_back(make_pair(ind, text.size()-ind));
	return;
}

void ListSuffixTreeEdges(Node *trie, const string& text, vector<string>& result)
{
	for(int i=0; i<trie->next.size(); i++)
	{
		result.push_back(text.substr(trie->edges[i].first, trie->edges[i].second));
    	Node *nextNode = trie->next[i];
    	ListSuffixTreeEdges(nextNode, text, result);
	}
}

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
	vector<string> result;
	// Implement this function yourself

	Node *trie = new Node;
	for(int i = 0; i < text.size(); i++)
		InsertSuffixTree(trie, text, i);
	ListSuffixTreeEdges(trie, text, result);
	return result;
}

int main() 
{
	string text;
	cin >> text;

	vector<string> edges = ComputeSuffixTreeEdges(text);
	for (int i = 0; i < edges.size(); ++i)
	    cout << edges[i] << endl;
	return 0;
}
