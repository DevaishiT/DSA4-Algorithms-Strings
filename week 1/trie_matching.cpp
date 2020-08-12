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

	Node ()
	{
		fill (next, next + Letters, NA);
	}

	bool isLeaf () const
	{
	    return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
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
	return;
}

bool prefixMatch(const string& text, const vector<Node> &trie, vector<int> result)
{
	int curr = 0;
	for (int i = 0; i < text.length(); i++)
	{
		int ind = letterToIndex(text[i]);
		//cout << ind << endl;
		if (trie[curr].next[ind] == NA) break;
		curr = trie[curr].next[ind];
		if (trie[curr].isLeaf()) return true;
	}
	return false;
}

// void display (const vector<Node> &trie, int curr, char str[], int level)
// {
// 	if (trie[curr].isLeaf())
// 	{
// 		str[level] = '\0';
// 		cout << str << endl;
// 	}

// 	if (trie[curr].next[0] != NA)  
//     { 
//         str[level] = 'A'; 
//         display(trie, trie[curr].next[0], str, level + 1); 
//     } 

//     if (trie[curr].next[1] != NA)  
//     { 
//         str[level] = 'C'; 
//         display(trie, trie[curr].next[1], str, level + 1); 
//     }

//     if (trie[curr].next[2] != NA)  
//     { 
//         str[level] = 'G'; 
//         display(trie, trie[curr].next[2], str, level + 1); 
//     }

//     if (trie[curr].next[3] != NA)  
//     { 
//         str[level] = 'T'; 
//         display(trie, trie[curr].next[3], str, level + 1); 
//     }
// }

vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
	vector <int> result;

	// write your code here
	vector<Node> trie;
	for(int i=0; i<patterns.size(); i++)
		insert(trie, patterns[i]);

	// char str[40];
	// display(trie, 0, str, 0);

	for(int i=0; i<text.length(); i++)
		if (prefixMatch(text.substr(i), trie, result)) result.push_back(i);

	// prefixMatch("AA", trie, result);

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
