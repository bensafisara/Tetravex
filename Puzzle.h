#include<vector>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include <fstream>

#ifndef PUZZLE_H 
#define PUZZLE_H
using namespace std;



struct tuile
{  int ouest;
	int nord;
	int est;
	int sud;
	int played;// 1 oui , 0 non
	
};


class Puzzle{
 	tuile *ListTuiles;
    public:
    int w;
    int h;
    Puzzle();
    tuile ***Board;
    tuile ***Board1;
    tuile ***Board2;
    tuile ***Board3;
    int sizePuzzle;
    void MethodMultithread();
    void afficherNord(tuile ***Board, int count , int i );
    void afficherEstOuest(tuile ***Board, int count , int i );
    void afficherSud(tuile ***Board, int count , int i );
    bool compareLigne(int X,int Y,int i,tuile ***Board);
    bool compareCol(int X,int Y,int i,tuile ***Board);
    bool BacktrackingSe(int X , int Y,int size,tuile ***Board);
    bool BacktrackingSe1(int X , int Y,int size,tuile ***Board);
    bool Multithreaded1(int  X, int Y , int start,tuile ***Board,bool VarBool );
    bool Multithreaded2(int  X, int Y , int start,tuile ***Board,bool VarBool );
    bool Multithreaded3(int  X, int Y , int start,tuile ***Board,bool VarBool );
    void afficherBoard(tuile ***Board);
	void AfficherListTuiles();
	void MethodSequentielle(int X , int Y,tuile ***Board);
    bool BacktrackingMultiThread(int X , int Y,int size,tuile ***Board);

    
	
	
	
};
#endif