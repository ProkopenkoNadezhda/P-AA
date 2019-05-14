#include <iostream>
#include <map>
#include <vector>
using namespace std;
struct bohr_vertex {
    bool flag;
    int obraz;//номер образца
    int suff_link;//суффиксная ссылка
    int par;//вершина-отец в дереве
    char symb; //символ на ребре от par к этой вершине
    map<char,int> edge;//номер вершины, в которую мы придем по символу с номером i в алфавите
    map<char,int> auto_move;//auto_move - запоминание перехода автомата
    bohr_vertex(int m_par, char m_symb): par(m_par), symb(m_symb) {
        flag = false;
        obraz = 0;
        suff_link = -1;//изначально - суф. ссылки нет
    }
};
class Aho_Karasik{
    vector<bohr_vertex> bohr;
    vector <string> patterns;
    int counter;//счетчик узлов бора
public:
    Aho_Karasik(){//создание корня бора
        counter = 1;
        bohr.push_back(bohr_vertex(0, 0));
    }
    void add_string_to_bohr(string& s, int str){//добавление строки-образца в бор
        int n = 0;//начинаем с корня
        patterns.push_back(s);
        for(int i = 0; i < s.length(); i++){
            if(bohr[n].edge.find(s[i]) == bohr[n].edge.end()){//если от вершины нет путей в искомую
                bohr.push_back(bohr_vertex(n, s[i]));
                bohr[n].edge[s[i]] = counter++;
            }
            n = bohr[n].edge[s[i]];
        }
        bohr[n].flag = true;//n - конечная вершина
        bohr[n].obraz = patterns.size();
    }
    int get_suff_link(int v){//возвращает индекс суффиксной ссылки
        if(bohr[v].suff_link == -1){//если еще не считали
            if (v == 0 || bohr[v].par == 0) //если v - корень или предок v - корень
                bohr[v].suff_link = 0;
            else
                bohr[v].suff_link = get_auto_move(get_suff_link(bohr[v].par), bohr[v].symb);
        }
        return bohr[v].suff_link;
    }
    int get_auto_move(int v, char symbol){//переходы автомата
        if(bohr[v].auto_move.find(symbol) == bohr[v].auto_move.end())
            if(bohr[v].edge.find(symbol) != bohr[v].edge.end())
                bohr[v].auto_move[symbol] = bohr[v].edge[symbol];
            else
                if (v == 0)//если v - корень
                    bohr[v].auto_move[symbol] = 0;
                else
                    bohr[v].auto_move[symbol] = get_auto_move(get_suff_link(v), symbol);
        return bohr[v].auto_move[symbol];
    }
    void check(int v, int i) {  //хождение по хорошим суффиксальнм ссылкам из текущей позиции, учитывая, что эта позиция оканчивается на символ i
        for (int u = v; u != 0; u = get_suff_link(u))
            if (bohr[u].flag)
                cout<< i - patterns[bohr[u].obraz - 1].size() + 2 << " " << bohr[u].obraz << endl;
    }
    void find_all_pos(string s) {
        int u = 0;
        for (int i = 0; i < s.length(); i++) {
            u = get_auto_move(u, s[i]);
            check(u, i);
        }
    }
};
int main(){
    Aho_Karasik ah;
    string text, pattern;
    int num;
    cin >> text >> num;
    for(int i = 0; i < num; i++){
        cin >> pattern;
        ah.add_string_to_bohr(pattern, i + 1);
    }
    ah.find_all_pos(text);
    return 0;
}
