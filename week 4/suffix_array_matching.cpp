#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>

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

char indextoletter (int index)
{
  switch (index)
  {
    case 0: return '$'; break;
    case 1: return 'A'; break;
    case 2: return 'C'; break;
    case 3: return 'G'; break;
    case 4: return 'T'; break;
    default: return ' ';
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

vector<int> BuildSuffixArray(const string& text) {
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

string BwtFast(const string& text, const vector<int>& order)
{
  int size = order.size();

  string bwt = "";
  for(int i=0; i<size; i++)
  	bwt += text[(order[i] - 1 + size) % size];

  return bwt;
}

// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position 
//       of this character in the sorted array of 
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
void PreprocessBWT(const string& bwt, 
                   map<char, int>& starts, 
                   map<char, vector<int> >& occ_count_before) {
  
  // Implement this function yourself

  vector<int> v(bwt.size()+1, 0);
  for(int i=0; i<5; i++) occ_count_before[indextoletter(i)] = v;

  for(int i=1; i<=bwt.size(); i++)
  {
    for(int j=0; j<5; j++)
    {
      if (j == lettertoindex(bwt[i-1])) 
        occ_count_before[bwt[i-1]][i] = occ_count_before[bwt[i-1]][i-1] + 1;
      else 
        occ_count_before[indextoletter(j)][i] = occ_count_before[indextoletter(j)][i-1];
    }
  }

  vector<int> start(5, 0);
  for(int i=0; i<5; i++) 
  {
    if (i != 0) start[i] = start[i-1] + occ_count_before[indextoletter(i-1)][bwt.size()];
    starts[indextoletter(i)] = start[i];
  }

  // map<char,vector<int> >::iterator it1;
  // for(it1=occ_count_before.begin();it1!=occ_count_before.end();++it1){
  //   cout<<it1->first<<": ";
  //   for(int i=0;i<it1->second.size();i++){
  //     cout<<it1->second[i]<<",";
  //   }
  //   cout<<endl;
  // }
  // cout << endl << endl;
  // map<char,int>::iterator it2;
  // for(it2=starts.begin();it2!=starts.end();++it2){
  //   cout<<it2->first<<": "<<it2->second<<endl;
  // }
  // cout << endl << endl;

}

vector<int> FindOccurrences(const string& pattern, const string& bwt, 
	const vector<int>& suffix_array, map<char, int>& starts, 
    map<char, vector<int> >& occ_count_before) {
  vector<int> result;

  // write your code here
  int top = 0;
  int bottom = bwt.size() - 1;
  int lastindex = pattern.length() - 1;

  char symbol;
  while (top <= bottom)
  {
    if (lastindex < 0) 
    {
    	for (int i = top; i <= bottom; i++) 
    		result.push_back(suffix_array[i]);

    	return result;
    }
    symbol = pattern[lastindex--];
    top = starts[symbol] + occ_count_before[symbol][top];
    bottom = starts[symbol] + occ_count_before[symbol][bottom+1] - 1;
  }
  return result;
}

int main() {

  char buffer[100001];
  scanf("%s", buffer);
  string text = buffer;
  text += '$';

  vector<int> suffix_array = BuildSuffixArray(text);

  string bwt = BwtFast(text, suffix_array);
  // cout << bwt << endl;

  // Start of each character in the sorted list of characters of bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, int> starts;
  // Occurrence counts for each character and each position in bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, vector<int> > occ_count_before;
  // Preprocess the BWT once to get starts and occ_count_before.
  // For each pattern, we will then use these precomputed values and
  // spend only O(|pattern|) to find all occurrences of the pattern
  // in the text instead of O(|pattern| + |text|).
  PreprocessBWT(bwt, starts, occ_count_before);

  int pattern_count;
  scanf("%d", &pattern_count);
  vector<bool> occurs(text.length(), false);
  for (int pattern_index = 0; pattern_index < pattern_count; ++pattern_index) {
    scanf("%s", buffer);
    string pattern = buffer;
    vector<int> occurrences = FindOccurrences(pattern, bwt, 
    	suffix_array, starts, occ_count_before);
    for (int j = 0; j < occurrences.size(); ++j) {
      occurs[occurrences[j]] = true;
    }
  }
  for (int i = 0; i < occurs.size(); ++i) {
    if (occurs[i]) {
      printf("%d ", i);
    }
  }
  printf("\n");
  return 0;
}
