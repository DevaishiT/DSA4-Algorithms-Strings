#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string BWT(const string& text) {
  string result = "";

  // write your code here
  	vector<string> rotations;

  	string temp;
  	for (int i=0; i<text.size(); i++)
    {
	  	temp = "";
	  	for (int j=0; j<text.size(); j++)
		  	temp += text[(i+j)%text.size()];
		rotations.push_back(temp);
    }

    sort(rotations.begin(), rotations.end());

    for(int i=0; i<text.size(); i++)
    	result += rotations[i][text.size() - 1];

  	return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}