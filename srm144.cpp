#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
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

class Lottery
{
private:
  typedef std::pair<unsigned long long, string> LotteryOdds;

  struct LotteryOddsCompare{
    bool operator()(const LotteryOdds& left, const LotteryOdds& right){
      if(left.first == right.first)
	return left.second < right.second;
      else
	return left.first < right.first;
    }
  };

  static LotteryOdds getOdds(const string& rule){  

    // parse string
    istringstream in(rule);
    string szName;
    char cSorted, cUnique;
    int nChoices,nBlanks;

    // read in inputs for each case
    getline(in,szName, ':');
    in>>nChoices>>nBlanks>>cSorted>>cUnique;

    //Unique Permutations: n!/(n -r)!
    if(cUnique == 'T' && cSorted=='F'){
      return make_pair(factorialDivide(nChoices, nChoices - nBlanks), szName);
    }

    //Non-Unique Permutations n ^ r
    else if(cUnique == 'F'  && cSorted == 'F'){
      return make_pair(pow(nChoices, nBlanks), szName);
    }

    //Unique Combinations: n! / r! (n-r)!
    else if(cUnique=='T' && cSorted=='T'){
      unsigned long long temp = factorialDivide(nChoices, nChoices - nBlanks);
      return make_pair(temp / factorial(nBlanks), szName);
    }

    //Non-Unique Combinations: (n+r-1)! / r! (n-1)!
    else if(cUnique=='F' && cSorted=='T'){
      unsigned long long temp = factorialDivide(nChoices + nBlanks - 1,  nChoices - 1);
      return make_pair(temp / factorial(nBlanks), szName);
    } 

    //never actually hit this unless we get bad input
    return make_pair(0,"0");
  };

public:

  vector<string> sortByOdds(vector<string> rules){
    
    vector<string> rValue;
    vector<LotteryOdds> results;
    transform(rules.begin(),rules.end(), inserter(results,results.begin()),Lottery::getOdds);
    sort(results.begin(), results.end(), LotteryOddsCompare());
    for( vector<LotteryOdds>::iterator it = results.begin(); it != results.end(); ++it){
      cout<<it->first<<","<<it->second<<endl;
      rValue.push_back(it->second);
    }
    return rValue;
  }
};

int main(){
  Lottery objectTest;
  vector<string> test;
  test.push_back("INDIGO: 93 8 T F");
  test.push_back("ORANGE: 29 8 F T");
  test.push_back("VIOLET: 76 6 F F");
  test.push_back("BLUE: 100 8 T T");
  test.push_back("RED: 99 8 T T");
  test.push_back("GREEN: 78 6 F T");
  test.push_back("YELLOW: 75 6 F F");
  objectTest.sortByOdds(test);
  return 1;
}
