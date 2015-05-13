#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

/**
    A szabályrendszert leíró osztály
    Egy kulcs-érték párokat tartalmazó adatszerkezetbe tölti az állapotokat és a rájuk vonatkozó választ.
**/

class Rule
{

    map<vector<int>,int> table;

public:
    ///Egy bemeneti stringet alakít szabállyá
    void addRule(string s)
    {
        vector<int> state_rot0 = vector<int>(s.length()-1,0);
        vector<int> state_rot1 = vector<int>(s.length()-1,0);
        vector<int> state_rot2 = vector<int>(s.length()-1,0);
        vector<int> state_rot3 = vector<int>(s.length()-1,0);
        int action = s[s.length()-1]-48;

        state_rot0[0] = s[0]-48;
        state_rot1[0] = s[0]-48;
        state_rot2[0] = s[0]-48;
        state_rot3[0] = s[0]-48;

        state_rot0[1] = s[1]-48;
        state_rot1[1] = s[2]-48;
        state_rot2[1] = s[3]-48;
        state_rot3[1] = s[4]-48;

        state_rot0[2] = s[2]-48;
        state_rot1[2] = s[3]-48;
        state_rot2[2] = s[4]-48;
        state_rot3[2] = s[1]-48;

        state_rot0[3] = s[3]-48;
        state_rot1[3] = s[4]-48;
        state_rot2[3] = s[1]-48;
        state_rot3[3] = s[2]-48;

        state_rot0[4] = s[4]-48;
        state_rot1[4] = s[1]-48;
        state_rot2[4] = s[2]-48;
        state_rot3[4] = s[3]-48;

        table[state_rot0] = action;
        table[state_rot1] = action;
        table[state_rot2] = action;
        table[state_rot3] = action;


    }

    ///Tesztelési célból kiírja konzolra az összes szabályt
    void printRule()
    {
        int j = 1;
        for(map<vector<int>,int>::iterator it=table.begin(); it!=table.end(); ++it)
        {
            cout << j << ": ";
            for(int i=0; i<it->first.size(); i++)
            {
                cout << it->first[i] << " ";
            }
            cout << "-> " << it->second << endl;
            j++;
        }
    }

    ///Tesztelési célból fájlba írja az összes szabályt
    void dumpRule()
    {
        ofstream dump;
        dump.open("dump.txt");
        int j = 1;
        for(map<vector<int>,int>::iterator it=table.begin(); it!=table.end(); ++it)
        {
            for(int i=0; i<it->first.size(); i++)
            {
                dump << it->first[i];
            }
            dump << it->second << endl;
            j++;
        }
        dump.close();
    }
//
//    void printRule(ofstream &f)
//    {
//        string s;
//        for(map<vector<int>,int>::iterator it=table.begin();it!=table.end();++it)
//        {
//            for(int i=0;i<it->first.size();i++)
//            {
//                s << it->first[i] << " ";
//                f.write(s);
//            }
//            s << "-> " << it->second << endl;
//            f.write(s);
//        }
//    }

    ///Egy állapothoz tartozó választ ad vissza
    int update(vector<int> state)
    {
        return table[state];
    }

};
