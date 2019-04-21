#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>
#include <cmath>
#define N 26
using namespace std;
typedef struct Priority{
    vector<int> resultat;
    double prior;
    int var_evristic;
} Priority;

bool operator < (const Priority &com_ver_1, const Priority &com_ver_2){
    return com_ver_1.prior > com_ver_2.prior;
}

class Graf{
private:
    double **graf;
    vector<int> str;
    double weight_from[N];
    double finish_way;
public:
    Graf(int start){
        str.push_back(start);
        graf = new double *[N];
        for(int i = 0; i < N; i++)
            graf[i] = new double[N];
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++)
                graf[i][j] = 0;
        }
    }
    ~Graf(){
        for(int i = 0; i < N; i++)
            delete[] graf[i];
        delete[] graf;
        str.clear();
    }
    void matrix(char i, char j, double weight){
        graf[i][j] = weight;
    }
    void Display(){
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                cout << graf[i][j] << " ";
            cout << endl;
    }
    void print_path(int first, int finish){
        bool admissible = 1;
        bool monotonic = 1;
        int i = 0;
        while(str[i] != finish){
            admissible = is_admissible(finish, str[i])  && admissible ? 1 : 0;
            i++;
            monotonic = is_monotonic(finish, str[i - 1], str[i]) && monotonic ? 1 : 0;
        }
        for(i = 0; i < str.size() ; i++)
            cout << char(str[i] + 'a');
        if(admissible)
            cout << endl << "Эвристика допустима" << endl;
        else
            cout << endl << "Эвристика не допустима" << endl;
        if(monotonic)
            cout << "Эвристика монотонна" << endl;
        else
            cout << "Эвристика не монотонна" << endl;
    }
    double evristic(int i, int j){
        return abs(i - j);
    }
    bool is_admissible(int finish, int ver){
        return finish_way - weight_from[ver] >= evristic(finish, ver);
    }
    bool is_monotonic(int finish, int ver1, int ver2){
        return graf[ver1][ver2] >= evristic(finish, ver1) - evristic(finish, ver2);
    }
    void min_way_A_star(int first, int finish, priority_queue <Priority> &queue, double way){
        vector<int> str1;
        weight_from[first] = 0;
        int first_prior = evristic(finish, first);
        while(true){
            for(int j = 0; j < N; j++)
                if(graf[first][j] != 0){
                    Priority elem;
                    elem.var_evristic = evristic(finish, j);
                    elem.prior = graf[first][j] + way + elem.var_evristic;
                    for(auto i : str1)
                        elem.resultat.push_back(i);
                    elem.resultat.push_back(j);
                    queue.push(elem);
                }
            if(queue.empty())
                break;
            if(!queue.empty()){
                Priority popped;
                popped = queue.top();
                queue.pop();
                first = popped.resultat[popped.resultat.size() - 1];
                str1 = popped.resultat;
                way = popped.prior - popped.var_evristic;
                first_prior = popped.var_evristic + first_prior - popped.var_evristic;
                weight_from[first] = way + first_prior;
            }
            if(str1[str1.size() - 1] == finish){
                if(str.size()){
                    for(auto i : str1)
                        str.push_back(i);
                    finish_way = weight_from[first]  ;
                    print_path(str[0], str[str.size() - 1]);
                    break;
                }
                else cout << "нет пути";
            }
        }
    }
};

int main(){
    char start, the_end, from, to;
    double weight;
    cin >> start >> the_end;
    priority_queue <Priority> queue;
    Graf matr(start - 'a');
    while(cin >> from >> to >> weight){
        matr.matrix(from - 'a', to - 'a', weight);
    }
    //  matr.Display();
    matr.min_way_A_star(start - 'a', the_end - 'a', queue, 0);
    return 0;
}
