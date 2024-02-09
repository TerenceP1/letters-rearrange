// letters-rearrange.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
struct wTree {
    bool isW = false;
    bool hNode[26] = { false };
    wTree* btchs[26];
};
vector<string>gwds(int ltl[26], wTree* wds) {
    vector<string>res;
    if (wds->isW) {
        res.push_back("");
    }
    bool end = true;
    for (int i = 0;i < 26;i++) {
        if (ltl[i] > 0) {
            end = false;
        }
    }
    if (end) {
        return res;
    }
    for (int i = 0;i < 26;i++) {
        if (ltl[i] > 0 && wds->hNode[i]) {
            int nltl[26];
            for (int j = 0;j < 26;j++) {
                nltl[j] = ltl[j];
            }
            nltl[i]--;
            vector<string>rres = gwds(nltl, wds->btchs[i]);
            for (int j = 0;j < rres.size();j++) {
                rres[j].insert(0, 1, 'a' + i);
            }
            res.insert(res.end(), rres.begin(), rres.end());
        }
    }
    return res;
}
void wdgen(vector<string>pstw, int ltl[26], wTree* wds) {
    bool end = true;
    for (int i = 0;i < 26;i++) {
        if (ltl[i] > 0) {
            end = false;
        }
    }
    if (end) {
        for (int i = 0;i < pstw.size();i++) {
            cout << pstw[i] << ' ';
        }
        cout << endl;
    }
    else {
        vector<string> mwds = gwds(ltl, wds);
        for (int i = 0;i < mwds.size();i++) {
            int nltl[26];
            for (int j = 0;j < 26;j++) {
                nltl[j] = ltl[j];
            }
            for (int j = 0;j < mwds[i].length();j++) {
                nltl[mwds[i][j] - 'a']--;
            }
            vector<string>npstw = pstw;
            npstw.push_back(mwds[i]);
            wdgen(npstw, nltl, wds);
        }
    }
}
int main() {
    ifstream in("words.txt");
    wTree* wds = new wTree;
    string tmp;
    cout << "creating binary search tree...\nappending words to binary search tree...\nThis may take some time\n";
    int trk = 0;
    while (in >> tmp) {
        wTree* nd = wds;
        trk++;
        for (int i = 0;i < tmp.length();i++) {
            if (!nd->hNode[tmp[i] - 'a']) {
                nd->hNode[tmp[i] - 'a'] = true;
                nd->btchs[tmp[i] - 'a'] = new wTree;
            }
            nd = nd->btchs[tmp[i] - 'a'];
        }
        nd->isW = true;
        if (trk % 10000 == 0) {
            cout << "adding " << tmp << "...\n";
        }
    }
    cout << "binary search tree creation completed!\n";
    while (true) {
        cout << "type a sentance: ";
        cin.ignore();
        string st;
        getline(cin, st, '\n');
        int ltl[26] = { 0 };
        for (int i = 0;i < st.length();i++) {
            if (st[i] <= 'z' && st[i] >= 'a') {
                ltl[st[i] - 'a']++;
            }
        }
        vector<string>pstw;
        wdgen(pstw, ltl, wds);
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
