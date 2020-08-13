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

string InverseBWT(const string& bwt) {
  string text = "";

  // write your code here - ""COUNT SORT""
  string firstcol = bwt;
  sort(firstcol.begin(), firstcol.end());

  vector<int> count(5, 0);
  for(int i=0; i<bwt.size(); i++) count[lettertoindex(bwt[i])]++;

  vector<int> start(5, 0);
  for(int i=1; i<5; i++) start[i] = start[i-1] + count[i-1];

  vector<int> lasttofirst(bwt.size());
  for(int i=0; i<bwt.size(); i++) 
  	lasttofirst[i] = start[lettertoindex(bwt[i])]++;

  int index = 0;
  for(int i=0; i<bwt.size(); i++)
  {
  	text.push_back(firstcol[index]);
  	index = lasttofirst[index];
  }
  reverse(text.begin(),text.end());

  return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
