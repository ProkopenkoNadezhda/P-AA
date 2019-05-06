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

void KMP(vector<int> &pi, int &res, string P, string T){
    int k = 0, l = 0;
    if(P.length() == T.length())
        while(true){
            if(k == T.length())
                k = 0;
            if(T[k] == P[l]){
                k++, l++;
                if(l == P.length()){
                    res = (l - k);
                    break;
                }
            } else if(l == 0){
                        k++;
                        if(k == T.length())
                            break;
            } else l = pi[l -1];

    }
}

int main(){
  string P, T;
  getline(cin, P);
	getline(cin, T);
	vector<int> pi(P.size());
	int res = -1;
	prefix(pi, P);
	KMP(pi, res, P, T);
	cout << res;
	pi.clear(), P.clear(), T.clear();
  return 0;
}
