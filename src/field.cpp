#include "graphics.hpp"
#include "rule.cpp"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
using namespace genv;

/**
    A Field osztály tartalmazza az állapotmező leírását egy NxN-es mátrixban
     - current és next: a mostani és a következő állapot
     - numcells: sejtek száma egy tengelyen (így current és a next mérete numcells*numcells)
     - cellsize: egy sejt mérete pixelben (a kirajzolást segíti)
     - boundcond: a határfeltétel változtatására szolgál (TRUE: konstans - FALSE: periodikus)
     - boundary: a konstans határfeltétel értéke
**/

class Field
{

private:
    vector<vector<int> > current;
    vector<vector<int> > next;
    int numcells;
    int cellsize;
    bool boundcond;
    int boundary = 0; ///TRUE: konst. -- FALSE: periodikus

public:

    ///A kétargumentumos konstruktoron keresztül automatikusan kosntans 0 határfeltétel érvényesül
    ///Az első argumentum a mátrix méretét határozza meg, a második a kirajzoláskor szükséges cellaméretet
    Field(int a, int b)
    {
        numcells = a;
        cellsize = b;
        current = vector<vector<int> >(numcells,vector<int>(numcells,0));
        next = current;
        boundcond = 0;
    }

    ///A háromargumentumos konstruktorban választhatunk a határfeltételtípusok közt
    Field(int a, int b, int c)
    {
        numcells = a;
        cellsize = b;
        current = vector<vector<int> >(numcells,vector<int>(numcells,0));
        next = current;
        boundcond= c;
    }

    ///A négyargumentumossal pedig a határértékeket is állíthatjuk
    Field(int a, int b, int c, int d)
    {
        numcells = a;
        cellsize = b;
        current = vector<vector<int> >(numcells,vector<int>(numcells,0));
        next = current;
        boundcond= c;
        boundary = d;
    }

    ///A kirajzolást végzi és a színeket határozza meg
    void draw()
    {
        for(int x=0; x<numcells; x++)
        {
            for(int y=0; y<numcells; y++)
            {
                switch (current[x][y])
                {
                case 0:
                    gout << color(48,48,48);
                    break;
                case 1:
                    gout << color(0,0,255);
                    break;
                case 2:
                    gout << color(255,0,0);
                    break;
                case 3:
                    gout << color(0,255,0);
                    break;
                case 4:
                    gout << color(255,255,0);
                    break;
                case 5:
                    gout << color(255,0,255);
                    break;
                case 6:
                    gout << color(255,255,255);
                    break;
                case 7:
                    gout << color(0,255,255);
                    break;
                }

                gout << move_to(x*cellsize,y*cellsize) << box_to((x+1)*cellsize,(y+1)*cellsize);
            }
        }
        gout << refresh;
    }

    ///Egy pont Neumann-környezetét adja vissza
    vector<int> getNHood(int i, int j)
    {
        vector<int> nhood = vector<int>(5,boundary);
        nhood[0]=(current[i][j]);
        if(boundcond)
        {
            if(!j-1<0) nhood[1]=(current[i][j-1]);
            if(i+1<numcells) nhood[2]=(current[i+1][j]);
            if(j+1<numcells) nhood[3]=(current[i][j+1]);
            if(!i-1<0) nhood[4]=(current[i-1][j]);
        }
        else
        {
            if(!j-1<0) nhood[1]=(current[i][j-1]);
            else nhood[1]=(current[i][numcells-1]);
            if(i+1<numcells) nhood[2]=(current[i+1][j]);
            else nhood[2]=(current[0][j]);
            if(j+1<numcells) nhood[3]=(current[i][j+1]);
            else nhood[3]=(current[i][0]);
            if(!i-1<0) nhood[4]=(current[i-1][j]);
            else nhood[4]=(current[numcells-1][j]);
        }
        return nhood;
    }

    ///Egy pont új állapotát adja meg egy szabályrendszer függvényében
    void update(int x,int y,Rule &rule)
    {
        next[x][y] = rule.update(getNHood(x,y));
    }

    ///Az állapotfrissítést végzi
    void change()
    {
        current = next;
    }

    ///Külső fájlból tölthetünk be vele objektumot
    void addObject(ifstream &f,int posx,int posy)
    {
        int sizex;
        int sizey;
        int a;
        f >> sizex;
        f >> sizey;
        if(posx+sizex<numcells && posy+sizey<numcells)
        {
            while(f.good())
            {
                for(int j=0; j<sizey; j++)
                {
                    for(int i=0; i<sizex; i++)
                    {
                        f >> current[posx+i][posy+j];
                    }
                }
            }
        }


    }



};
