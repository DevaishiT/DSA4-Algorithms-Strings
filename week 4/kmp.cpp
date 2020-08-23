#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> compute_prefix_function(const string& str)
{
	int len = str.length();
	vector<int> result(len, 0);

	int border = 0;
	for(int i=1; i<len; i++)
	{
		while(border > 0 and str[i] != str[border])
			border = result[border-1];

		if (str[i] == str[border]) border++;
		else border = 0;

		result[i] = border;
	}

	return result;
}

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.
vector<int> find_pattern(const string& pattern, const string& text) {
  vector<int> result;
  // Implement this function yourself

  string combined = pattern + '$' + text;
  // cout << combined << endl;

  vector<int> prefix_func = compute_prefix_function(combined);
  
  int P = pattern.length();
  for(int i = P+1; i<combined.length(); i++)
  	if(prefix_func[i] == P) result.push_back(i - 2*P);
  
  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
