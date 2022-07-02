#include<vector>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include <fstream>

#ifndef ThrPool_H 
#define ThrPool_H
using namespace std;



struct tuile
{  int ouest;
	int nord;
	int est;
	int sud;
	int played;// 1 oui , 0 non
	
};


class thrPool{
    
    
    
    
    public:
    tuile *ListTuiles;
    tuile ***Board;
    mutex m;
    condition_variable cv;
    vector<thread> threads;
    queue<int> Taches;
    int h;
    int w;
    bool finish = false;
    thrPool();
    ~thrPool();
    void afficherNord(tuile ***Board, int count , int i );
    void afficherEstOuest(tuile ***Board, int count , int i );
    void afficherSud(tuile ***Board, int count , int i );
    bool compareLigne(int X,int Y,int i,tuile ***Board);
    bool compareCol(int X,int Y,int i,tuile ***Board);
    bool BacktrackingSe1(int X , int Y,int size,tuile ***Board);
    void afficherBoard(tuile ***Board);
    void start();
    void taches();
	
	
	
	
};
#endif