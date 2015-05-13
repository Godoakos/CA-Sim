#include "field.cpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace genv;
using namespace std;

/**
    2D-S CA SZIMULÁTOR FÁJLBÓL BETÖLTHETŐ SZABÁLYRENDSZERREL

    A kirajzoláshoz Flugi grafikus libjét használtam.
    Dokumentációja: http://users.itk.ppke.hu/~flugi/bevprog2_1415/graph/graphics.html

    Használat:
    Bal klikkre lerak egy loopot. Enterre elindítja/megállítja a szimulációt.
    Loopot csak álló módban lehet rakni.

    - NUMCELLS: a cellák számát adja meg egy tengelyen
    - CELLSIZE: egy cella méretét adja meg pixelben

**/

static int NUMCELLS = 128;
static int CELLSIZE = 4;

int main()
{
    Field status = Field(NUMCELLS,CELLSIZE,0);
    Rule langton;


    ifstream f;
    f.open("Langtons-Loops.table");
    string s;
    getline(f,s);
    langton.addRule(s);
    while(f.good())
    {
        getline(f,s);
        langton.addRule(s);
    }
    f.close();
    //langton.printRule();
    //langton.dumpRule();


    gout.open(NUMCELLS*CELLSIZE+1,NUMCELLS*CELLSIZE+1);
    status.draw();
    gin.timer(80);

    bool start = false;
    while(gin >> ev && ev.keycode != key_escape)
    {
        if (start)
        {
            if(ev.type==ev_timer && ev.keycode != key_escape)
            {
                for(int i=0; i<NUMCELLS; i++)
                {
                    for(int j=0; j<NUMCELLS; j++)
                    {
                        status.update(i,j,langton);
                    }
                }
                status.change();
                status.draw();
            }
            if(ev.type==ev_key && ev.keycode==key_enter)
            {
                start = false;
            }
        }

        else
        {
            if(ev.type==ev_key && ev.keycode==key_enter)
            {
                start = true;
            }
            if(ev.type==ev_mouse && ev.button==btn_left)
            {
                ifstream f;
                f.open("selfreprodloop.txt");
                status.addObject(f,ev.pos_x/CELLSIZE,ev.pos_y/CELLSIZE);
                f.close();
                status.draw();
            }
//            if(ev.type==ev_mouse && ev.button==btn_right) //Debug célból jobb klikkre kiírja egy cella kornyezetet es az update-et
//            {
//                vector<int> nhood = status.getNHood(ev.pos_x/CELLSIZE,ev.pos_y/CELLSIZE);
//                cout << ev.pos_x/2 << ";" << ev.pos_y << endl;
//                for(int i:nhood)
//                {
//                    cout << i << " ";
//                }
//                cout << "-> " << langton.update(nhood) <<  endl;
//            }
        }
    }
    return 0;
}
