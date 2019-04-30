#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct edge{
    char beg;
    char end;
    int heft;
    int forward;
    int back;
    bool doubl;
};

bool compare(edge first, edge second){
    if(first.beg == second.beg)
        return first.end < second.end;
    return first.beg < second.beg;
}

class Graph{
private:
    vector <edge> graph;
    char source;
    char estuary;
    int N, maxFlow;
    vector <char> viewingpoint;
    vector <char> result;
public:
    Graph(): maxFlow(0){
        cin >> N >> source >> estuary;
        for(int i = 0; i < N; i++){
                      edge element;
            cin >> element.beg >> element.end >> element.heft;
            element.forward = element.heft;
            element.back = 0;
            element.doubl = false;
            bool flag = true;
            for(int i = 0; i < graph.size(); i++){
                if(graph[i].beg == element.end && graph[i].end == element.beg){
                    graph[i].back += element.forward;
                    flag = false;
                    graph[i].doubl = true;
                    break;
                }
            }
            if(!flag)
                continue;
            graph.push_back(element);
        }
    }
    bool isViewing(char value){
        for(size_t i = 0; i < viewingpoint.size(); i++)
            if(viewingpoint[i] == value)
                return true;
        return false;
    }
    bool Search(char value, int& min){
         if(value == estuary){
            result.push_back(value);
            return true;
        }
        viewingpoint.push_back(value);
        for(size_t i(0); i < graph.size(); i++){
            if(value == graph[i].beg){
                if(isViewing(graph[i].end) || graph[i].forward == 0)
                    continue;
                result.push_back(graph[i].beg);
                bool flag = Search(graph[i].end, min);
                if(flag){
                   if(graph[i].forward < min)
                       min = graph[i].forward;
                   return true;
                }
                result.pop_back();
            }
            if(value == graph[i].end){
                if(isViewing(graph[i].beg) || graph[i].back == 0)
                    continue;
                result.push_back(graph[i].end);
                bool flag = Search(graph[i].beg, min);
                if(flag){
                   if(graph[i].back < min)
                        min = graph[i].back;
                   return true;
                }
                result.pop_back();
            }
        }
        return false;
    }
    void FordFalk(){
        int min = INT_MAX;
        while(Search(source, min)){
            for(int i = 1; i < result.size(); i++){
                for(int j = 0; j < graph.size(); j++){
                    if(graph[j].beg == result[i-1] && graph[j].end == result[i]){
                        graph[j].forward -= min;
                        graph[j].back += min;
                    }
                    if(graph[j].end == result[i-1] && graph[j].beg == result[i]){
                        graph[j].forward += min;
                        graph[j].back -= min;
                    }
                }
            }
            maxFlow += min;
            viewingpoint.clear();
            result.clear();
            min = INT_MAX;
        }
    }
    void print(){
        sort(graph.begin(), graph.end(), compare);
        cout << maxFlow << endl;
        for(int i = 0; i < graph.size(); i++){
            int value = max(graph[i].heft - graph[i].forward, 0 - graph[i].back);
            if(graph[i].doubl == true){
                if(value < 0)
                    value = 0;
                cout << graph[i].beg << " " << graph[i].end << " " << value << endl;
                swap(graph[i].beg, graph[i].end);
                swap(graph[i].back, graph[i].forward);
                graph[i].doubl = false;
                sort(graph.begin(), graph.end(), compare);
                i--;
            }
            else{
                cout << graph[i].beg << " " << graph[i].end << " " << value << endl;
            }
        }
    }
};

int main(){
    Graph element;
    element.FordFalk();
    element.print();
    return 0;
}
