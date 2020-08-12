#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];
	bool patternEnd;

	Node ()
	{
		fill (next, next + Letters, NA);
		patternEnd = false;
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

void insert(vector<Node> &trie, string pattern)
{
	int curr = 0;
	for (int i = 0; i < pattern.length(); i++)
	{
		if (curr >= trie.size()) trie.resize(trie.size() + 1);
		int ind = letterToIndex(pattern[i]);
		if (trie[curr].next[ind] == NA)
		{
			trie[curr].next[ind] = trie.size();
			trie.resize(trie.size()+1);
		}
		curr = trie[curr].next[ind];
	}
	trie[curr].patternEnd = true;
	return;
}

bool prefixMatch(const string& text, const vector<Node> &trie, vector<int> result)
{
	int curr = 0;
	for (int i = 0; i < text.length(); i++)
	{
		int ind = letterToIndex(text[i]);
		if (trie[curr].next[ind] == NA) break;
		curr = trie[curr].next[ind];
		if (trie[curr].patternEnd) return true;
	}
	return false;
}

vector <int> solve (string text, int n, vector <string> patterns)
{
	vector <int> result;

	// write your code here
	vector<Node> trie;
	for(int i=0; i<patterns.size(); i++)
		insert(trie, patterns[i]);

	for(int i=0; i<text.length(); i++)
		if (prefixMatch(text.substr(i), trie, result)) result.push_back(i);

	return result;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
