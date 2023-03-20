#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>

using namespace std;
vector<vector<int>> toatePosibilitatile = {};
string automat;
bool accepted_word = 0;
void dfs(unordered_map<int, unordered_map<char, vector<int>>> Map, int node, vector<int> res, string targetString, int lettersDone, vector<int> stari_finale){
    if(accepted_word == 1 && automat == "DFA")
        return;

    char currentLetter = targetString[lettersDone];
    if(lettersDone==targetString.length()){
        bool ok = 0;
        for(int i=0; i<stari_finale.size(); i++){
            if(node == stari_finale[i]){
                ok = 1;
                break;
            }
        }
        if(ok==1){
            toatePosibilitatile.push_back(res);
            accepted_word = 1;
        }
        return;
    }
    if(Map.find(node) != Map.end()){
        if(Map[node].find(currentLetter) != Map[node].end()){
            for(int j=0; j<Map[node][currentLetter].size(); j++){
                res.push_back(Map[node][currentLetter][j]);
                lettersDone++;
                dfs(Map, Map[node][currentLetter][j], res, targetString, lettersDone, stari_finale);
                lettersDone--;
                res.pop_back();
            }
        }
    }
}

int main() {
    ifstream f("C:\\Users\\tiril\\CLionProjects\\Tema01LFA\\input.txt");
    int numarStari, numarLitere, stare;
    char litera;
    f>>automat;
    std::string targetString;
    f>>numarStari;

    unordered_map<int, unordered_map<char, vector<int>>> Map;
    vector<int> stariFinale;
    bool stareFinala;

    for(int i=0; i<numarStari; i++){
        f>>stareFinala;
        if(stareFinala == 1){
            stariFinale.push_back(i);
        }
        f>>numarLitere;
        for(int j=0; j<numarLitere; j++){
            f>>litera;
            f>>stare;
            if(Map.find(i) == Map.end()){
                Map[i][litera] = {stare};
            }
            else {
                if(Map[i].find(litera) == Map[i].end()){
                    Map[i][litera] = {};
                    Map[i][litera].push_back(stare);
                }
                else{
                    Map[i][litera].push_back(stare);
                }
            }
        }
    }
    for(int i=0; i<stariFinale.size(); i++){
        cout<<stariFinale[i]<<endl;
    }
    vector<int> res = {0};
    f>>targetString;
    dfs(Map, 0, res, targetString, 0, stariFinale);
    if(accepted_word == 0){
        cout<<"Cuvantul nu este acceptat de acest automat!"<<endl;
    } else {
        cout<<"Cuvantul este acceptat de acest automat!"<<endl;
    }
    if(automat == "NFA" && accepted_word){
        for(int i=0; i<toatePosibilitatile.size(); i++){
            cout<<"{ ";
            for(int j=0; j<toatePosibilitatile[i].size(); j++){
                cout<<toatePosibilitatile[i][j]<<" ";
            }
            cout<<"}"<<endl;
        }
    }
    return 0;
}
