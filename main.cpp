#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool search(char x, vector<char> arr) {
    for (unsigned int i = 0; i < arr.size(); i++){
        if (x == arr[i]) return true;
    }
    return false;
}

int main()
{
    fstream fileV;
    fstream fileP;
    vector<char> Vt;
    vector<char> Vn;
    vector<string> Pf;
    vector<string> Ps;
    string inp;
    string cashF;
    string cashS;
    string a;
    string b;
    bool flag;
    int type;

    fileV.open("V.txt", ios::in);
    if (!fileV){
        cout << "Error file!" << endl;
        return 1;
    }
    getline(fileV, inp);
    for (unsigned int i = 0; i < inp.length(); i++){
        Vt.push_back(inp[i]);
    }
    getline(fileV, inp);
    for (unsigned int i = 0; i < inp.length(); i++){
        Vn.push_back(inp[i]);
    }
    fileV.close();
    fileP.open("P.txt", ios::in);
    if (!fileP){
        cout << "Error file!" << endl;
        return 1;
    }
    while (getline(fileP, inp)){
        flag = false;
        cashF = "";
        cashS = "";
        for (unsigned int i = 0; i < inp.length(); i++){
            if (inp[i] == '-'){
                flag = true;
                continue;
            } else {
                if (flag){
                    cashS += inp[i];
                } else {
                    cashF += inp[i];
                }
            }
        }
        Pf.push_back(cashF);
        Ps.push_back(cashS);
    }
    fileP.close();
    type = 3;
    for (unsigned int i = 0; i < Pf.size(); i++){
        if (Pf[i] == ""){
            type = 0;
            break;
        }
        switch (type) {
        case 3:
            for (unsigned int j = 0; j < Pf[i].length(); j++){
                if (!search(Pf[i][j], Vn)) {
                    type = 1;
                    break;
                }
            }
        case 2:
            for (unsigned int j = 0; j < Pf[i].length(); j++){
                if (!search(Pf[i][j], Vn)) {
                    type = 1;
                    break;
                }
            }
        }
    }
    for (unsigned int i = 0; i < Ps.size(); i++){
        switch (type) {
        case 3:
            if (Ps[i] == ""){
                type = 2;
                break;
            }
            flag = false;
            if (search(Ps[i][0], Vn)){
                for (unsigned int j = 1; j < Ps[i].length(); j++){
                    if (flag){
                        if (!search(Ps[i][j], Vt)){
                            type = 2;
                            break;
                        }
                    }else if (!search(Ps[i][j], Vn)) flag = true;
                }
            }else if (search(Ps[i][0], Vt)){
                for (unsigned int j = 1; j < Ps[i].length(); j++){
                    if (flag){
                        if (!search(Ps[i][j], Vn)){
                            type = 2;
                            break;
                        }
                    }else if (!search(Ps[i][j], Vt)) flag = true;
                }
            }else return 2;
        case 1:
            if (Pf[i].length() > Ps[i].length()) type = 0;
        }
        if (type == 0 or type == 2) break;
    }
    cout << "Type: " << type << endl;
    return 0;
}
