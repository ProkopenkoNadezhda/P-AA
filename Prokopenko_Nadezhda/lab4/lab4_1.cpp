#include <iostream>
#include <string>
#include <vector>
using namespace std;

void prefix(vector<int> &pi, string P){
    int i = 1, j = 0;
    pi[0] = 0;
    while(i < P.length()){
        if(P[i] == P[j]){
            pi[i] = j + 1;
            i++, j++;
        } else if(j == 0){
            pi[i] = 0;
            i++;
        } else j = pi[j-1];
    }
}

void KMP(vector<int> &pi, vector<int> &result, string P, string T){
    int k = 0, l = 0;
    while(k < T.length()){
        if(T[k] == P[l]){
            k++, l++;
            if(l == P.length())
                result.push_back(k - l);
        } else if(l == 0){
            k++;
        } else l = pi[l -1];
    }
}

int main(){
  string P, T;
  getline(cin, P);
	getline(cin, T);
	vector<int> pi(P.size()), result;
	prefix(pi, P);
	KMP(pi, result, P, T);
	if(result.size() != 0){
	    for(int i = 0; i < result.size(); i++){
	        cout << result[i];
	        if(i != result.size() - 1)
	            cout <<",";
	    }
	} else cout << "-1";
	pi.clear(), result.clear(), P.clear(), T.clear();
  return 0;
}
