#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

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

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_count_before.
int CountOccurrences(const string& pattern, 
                     const string& bwt, 
                     map<char, int>& starts, 
                     map<char, vector<int> >& occ_count_before) {
  
  // Implement this function yourself
  int top = 0;
  int bottom = bwt.size() - 1;
  int lastindex = pattern.length() - 1;

  char symbol;
  while (top <= bottom)
  {
    if (lastindex < 0) return bottom - top + 1;
    symbol = pattern[lastindex--];
    top = starts[symbol] + occ_count_before[symbol][top];
    bottom = starts[symbol] + occ_count_before[symbol][bottom+1] - 1;
  }

  return 0;
}
     

int main() {
  string bwt;
  cin >> bwt;
  int pattern_count;
  cin >> pattern_count;
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
  for (int pi = 0; pi < pattern_count; ++pi) {
    string pattern;
    cin >> pattern;
    int occ_count = CountOccurrences(pattern, bwt, starts, occ_count_before);
    printf("%d ", occ_count);
  }
  printf("\n");
  return 0;
}
