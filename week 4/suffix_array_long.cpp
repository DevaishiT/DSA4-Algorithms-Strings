#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

int lettertoindex (char letter)
{
  switch (letter)
  {
    case '$': return 0; break;
    case 'A': return 1; break;
    case 'C': return 2; break;
    case 'G': return 3; break;
    case 'T': return 4; break;
    default: return -1;
  }
}

vector<int> SortCharacters(const string& text)
{
	int len = text.length();
	vector<int> order(len);

	// Alphabets possible $, A, C, G, T
	vector<int> count(5, 0);

	for(int i=0; i<len; i++)
		count[lettertoindex(text[i])]++;

	// for(int i=0; i<5; i++) cout << count[i] << " ";
	// cout << endl;

	for(int i=1; i<5; i++)
		count[i] = count[i] + count[i-1];

	int idx;
	for(int i=len-1; i>=0; i--)
	{
		idx = --count[lettertoindex(text[i])];
		order[idx] = i;
	}

	return order;
}

vector<int> ComputeCharClasses(const string& text, const vector<int>& order)
{
	int len = text.length();
	vector<int> eqclass(len);

	eqclass[order[0]] = 0;
	for(int i=1; i<len; i++)
	{
		if (text[order[i]] != text[order[i-1]])
			eqclass[order[i]] = eqclass[order[i-1]] + 1;
		else eqclass[order[i]] = eqclass[order[i-1]];
	}

	return eqclass;
}

vector<int> SortDoubledStrings(const string& text, int l, 
	const vector<int>& order, const vector<int>& eqclass)
{
	int len = text.length();
	vector<int> newOrder(len);
	vector<int> count(len, 0);

	for(int i=0; i<len; i++) count[eqclass[i]]++;

	for(int i=1; i<len; i++)
		count[i] = count[i] + count[i-1];

	int start;
	for(int i=len-1; i>=0; i--)
	{
		start = (order[i] - l + len) % len;
		count[eqclass[start]]--;
		newOrder[count[eqclass[start]]] = start;
	}

	return newOrder;
}

vector<int> UpdateClasses(int l, const vector<int>& order, 
	const vector<int>& eqclass)
{
	int size = order.size();
	vector<int> newEqclass(size);

	newEqclass[order[0]] = 0;
	int curr, prev, mid, midprev;
	for(int i=1; i<size; i++)
	{
		curr = order[i];
		prev = order[i-1];
		mid = (curr + l) % size;
		midprev = (prev + l) % size;

		if (eqclass[curr] != eqclass[prev] or eqclass[mid] != eqclass[midprev])
			newEqclass[curr] = newEqclass[prev] + 1;

		else newEqclass[curr] = newEqclass[prev];
	}

	return newEqclass;
}

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(const string& text) {
  // Implement this function yourself
  int len = text.length();
  vector<int> result(len);
  vector<int> eqclass(len);

  if (len == 0) return result;
  if (len == 1)
  {
  	result[0] = 1;
  	return result;
  }
  
  result = SortCharacters(text);
  eqclass = ComputeCharClasses(text, result);

  for(int i=1; i<len; i*=2)
  {
  	result = SortDoubledStrings(text, i, result, eqclass);
  	eqclass = UpdateClasses(i, result, eqclass);
  }

  return result;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
