#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

unsigned long long factorialDivide(int num, int den){
  unsigned long long rValue = 1;
  for(int i = num; i > den; i--)
    rValue *=i;
  return rValue;
}

unsigned long long factorial(int num){
  unsigned long long rValue = 1;
  for(int i = num; i > 0; i--)
    rValue *=i;
  return rValue;
}

class Lottery {
public:
        vector<string> sortByOdds(vector<string> rules);
	unsigned long long getOdds(int choices, int blanks, char sorted, char unique);
};

unsigned long long Lottery::getOdds(int choices, int blanks, char sorted, char unique)
{
	unsigned long long odds = 0;
	if (sorted == 'T') {
		if (unique == 'T') {
			odds = factorialDivide(choices, choices - blanks) / factorial(blanks);
		} else { // T F
			odds = factorialDivide(choices + blanks - 1, choices - 1) / factorial(blanks);
		}
	} else { 
		if (unique == 'T') { // F T
			odds = factorialDivide(choices, choices - blanks);
		} else { // F F
			odds = pow(choices, blanks);
		}
	}
	return odds;
}

vector<string> Lottery::sortByOdds(vector<string> rules)
{
        vector< pair<unsigned long long, string> > game_info;
        vector<string> res;
        int input_len = rules.size();
        for(int i = 0; i < input_len; i++) {
                istringstream is(rules[i]);
                string game_name;
                int choices, blanks;
                char sorted, unique;
		// read in inputs for each case
    		getline(is,game_name, ':');
    		is>>choices>>blanks>>sorted>>unique;

		unsigned long long odds = getOdds(choices, blanks, sorted, unique);
		game_info.push_back(make_pair(odds, game_name));
        }
	sort(game_info.begin(), game_info.end());
	for( vector< pair<unsigned long long, string> >::iterator it = game_info.begin(); it != game_info.end(); ++it){
      		cout<<it->first<<","<<it->second<<endl;
      		res.push_back(it->second);
    	}
	for(vector<string>::iterator it = res.begin(); it != res.end(); ++it) {
		cout << *it << endl;
	}
        return res;
}

#define pb push_back

int main() {
        vector<string> input;
        //input.pb("INDIGO: 10 2 T F");
        input.pb("INDIGO: 93 8 T F");
        input.pb("ORANGE: 29 8 F T");
        input.pb("VIOLET: 76 6 F F");
	input.pb("BLUE: 100 8 T T");
	input.pb("RED: 99 8 T T");
	input.pb("GREEN: 78 6 F T");
	input.pb("YELLOW: 75 6 F F");
        Lottery lottery;
        lottery.sortByOdds(input);
        return 0;
}
