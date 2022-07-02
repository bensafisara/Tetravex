#include "Puzzle.h"
#include <fstream>
#include <string>
#include <iostream>
#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <thread>
#include <vector>
#include <mutex>
#include <iostream>
using namespace std;




Puzzle::Puzzle(){
std::ifstream fichier("7x7.txt");


fichier >>w;
fichier >>h;

sizePuzzle=w*h;
ListTuiles = new tuile[sizePuzzle];



Board = new tuile**[w];	
Board1= new tuile**[w]; 
Board2 = new tuile**[w]; 
Board3 = new tuile**[w]; 


for(int i=0;i<w;i++)
{
Board[i] = new tuile*[h];
Board1[i] = new tuile*[h];
Board2[i] = new tuile*[h];
Board3[i] = new tuile*[h];
}


for (int i = 0; i < w*h; ++i){

int ouest,nord,est,sud;
fichier >>ouest >>nord >> est >>sud;


ListTuiles[i].ouest=ouest;
ListTuiles[i].nord=nord;
ListTuiles[i].est=est;
ListTuiles[i].sud=sud;
ListTuiles[i].played=0;

  }

}

/*  Fonctions d'affichage*/

void Puzzle::afficherNord(tuile ***Board, int count , int i ){


for (int j = 0; j < count; ++j)
{
  cout <<" "<<Board[i][j]->nord<<"    ";
}


}

void Puzzle::afficherEstOuest(tuile ***Board, int count , int i ){


for (int j = 0; j < count; ++j)
{
  cout <<Board[i][j]->ouest<<"  "<<Board[i][j]->est<<"  ";
}


}


void Puzzle::afficherSud(tuile ***Board, int count , int i ){


for (int j = 0; j < count; ++j)
{
  cout <<" "<<Board[i][j]->sud<<"    ";
}


}

void Puzzle::afficherBoard(tuile ***Board){
int cpt =0;
for (int i = 0; i < w; i++)
        {
           



afficherNord(Board, h , i );
cout <<"\n";
afficherEstOuest(Board, h , i );
cout <<"\n";
afficherSud(Board, h , i );
cout <<"\n";


           
           }

         }

/* Fonction pour afficher l'ensemble des tuiles lu par le programme
void Puzzle::AfficherListTuiles()
{
 
for (int i = 0; i < h*w; i++)
        {
          
           		
           			cout <<"  "<< ListTuiles[i].ouest<<" \n"<<ListTuiles[i].nord<<"   "<<ListTuiles[i].est<<"\n"<<" "<<ListTuiles[i].sud<<endl;
           		
           }

}

*/

//Fonction pour comparer les tuiles
bool Puzzle::compareLigne(int X,int Y,int i,tuile ***Board){
 
if(X!=0){
//la comparaison : si je ne suis pas sur la premiere ligne 
//cad je compare le le numéro nord de la tuile au numéro sud de la pice déja placé 
//si cela ne correspond pad pas je retourne false la piece n'est pas adéquate et si je suis 
  //sur la premiere ligne je retourne directement true càd on est au début pas beoin de comparer  
      if(Board[X - 1][Y]->sud != ListTuiles[i].nord){
       
        return false;

      }
}

return true;
}


bool Puzzle::compareCol(int X,int Y,int i,tuile ***Board){

if(Y!=0){
   //la comparaison : si je ne suis pas sur la premiere colonne 
//cad je compare le numéro est de la tuile au numéro ouest de la piece déja placé
//si cela ne correspond pad pas je retourne false la piece n'est pas adéquate et si je suis 
  //sur la premiere colonne je retourne directement true càd on est au début      
 if(Board[X ][Y-1]->est != ListTuiles[i].ouest){
      
        return false;

      }
    }

return true;
}


  



        

/******************Séquentielle***********************/


bool Puzzle::BacktrackingSe(int X , int Y,int size,tuile ***Board){
int nx, ny;
if(X==size){
   cout<<"affichage Board"<<endl;
       afficherBoard(Board);
    return true;

}



for (int i = 0; i < size*size; i++) {
   
    //on prend une tuile on vérifier qu'elle est pas jouer
    if(ListTuiles[i].played==0){
    

   
//si les deux condition vérifier, on place la tuile sinon on remonte à l'appel précedent
    if (compareLigne(X,Y,i,Board)&&compareCol(X,Y,i,Board)){

    Board[X][Y] = &ListTuiles[i];
    ListTuiles[i].played = 1;
    nx=X;
    ny=Y+1;

    if(ny==size){nx=X+1; ny=0;};
    
    if (BacktrackingSe(nx, ny,size,Board)) {
                return true;
                }
     
      ListTuiles[i].played = 0;
    }
  
  }


}

return false;
}






void Puzzle::MethodSequentielle(int X, int Y,tuile ***Board) {
  auto start = chrono::high_resolution_clock::now();  
  BacktrackingSe(X, Y,h,Board);  
  auto end = chrono::high_resolution_clock::now(); 
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
int seconds = duration / 1000;
    int milisec = duration - seconds * 1000;
    int minutes = seconds / 60;
    seconds = seconds - minutes * 60;
    cout << "Partie Séquentielle :" << endl << "Time = " << minutes << "m" << seconds << "."
             << milisec << endl; 
}





/******************MultiThread***********************/

bool Puzzle::Multithreaded1(int  X, int Y , int start,tuile ***Board,bool VarBool ){

int nx, ny;
if(X==h){
   
  cout<<"Thread 1  finished " << endl; 
  
    return true;
}

if(VarBool==true){


if(ListTuiles[start].played==0){
    
   //je ne suis pas sur la ligne des X
    
    if (compareLigne(X,Y,start,Board)&&compareCol(X,Y,start,Board)){

    Board[X][Y] = &ListTuiles[start];
    ListTuiles[start].played = 1;
    nx=X;
    ny=Y+1;

    if(ny==h){nx=X+1; ny=0;};
  

    if(Multithreaded1(nx, ny,0,Board ,false)){
                return true;}




}}}else{
 

for (int i = 0; i < h*w; i++) {
   
    //on prend une tuile on vérifier qu'elle est pas jouer
    if(ListTuiles[i].played==0){
    
   //je ne suis pas sur la ligne des X
    
    if (compareLigne(X,Y,i,Board)&&compareCol(X,Y,i,Board)){

    Board[X][Y] = &ListTuiles[i];
    ListTuiles[i].played = 1;
    nx=X;
    ny=Y+1;

    if(ny==h){nx=X+1; ny=0;};
  

    
if(Multithreaded1(nx, ny,0,Board ,false)){
                return true;}


    }
    }
ListTuiles[i].played = 0;
}
}

return false;




}


bool Puzzle::Multithreaded2(int  X, int Y , int start,tuile ***Board,bool VarBool ){


int nx, ny;
if(X==h){
  cout<<"Thread 2 finished\n"<<endl;
 
    return true;
}

if(VarBool==true){


if(ListTuiles[start].played==0){
    
   //je ne suis pas sur la ligne des X
    
    if (compareLigne(X,Y,start,Board)&&compareCol(X,Y,start,Board)){

    Board[X][Y] = &ListTuiles[start];
    ListTuiles[start].played = 1;
    nx=X;
    ny=Y+1;

    if(ny==h){nx=X+1; ny=0;};
  

    if(Multithreaded2(nx, ny,0,Board ,false)){
                return true;}




}}}else{

for (int i = 0; i < h*w; i++) {
   
    //on prend une tuile on vérifier qu'elle est pas jouer
    if(ListTuiles[i].played==0){
    
   //je ne suis pas sur la ligne des X
    
    if (compareLigne(X,Y,i,Board)&&compareCol(X,Y,i,Board)){

    Board[X][Y] = &ListTuiles[i];
    ListTuiles[i].played = 1;
    nx=X;
    ny=Y+1;

    if(ny==h){nx=X+1; ny=0;};
  

  
if(Multithreaded1(nx, ny,0,Board ,false)){
                return true;}


    }
    }
ListTuiles[i].played = 0;
}
}

return false;




}



bool Puzzle::Multithreaded3(int  X, int Y , int start,tuile ***Board,bool VarBool ){


int nx, ny;
if(X==h){
  cout<<"Thread 3 finished  "<<endl;
  
    return true;
}

if(VarBool==true){


if(ListTuiles[start].played==0){
    
   //je ne suis pas sur la ligne des X
    
    if (compareLigne(X,Y,start,Board)&&compareCol(X,Y,start,Board)){

    Board[X][Y] = &ListTuiles[start];
    ListTuiles[start].played = 1;
    nx=X;
    ny=Y+1;

    if(ny==h){nx=X+1; ny=0;};
  

    if(Multithreaded3(nx, ny,0,Board ,false)){
                return true;}




}}}else{

for (int i = 0; i < h*w; i++) {
   
    //on prend une tuile on vérifier qu'elle est pas jouer
    if(ListTuiles[i].played==0){
    
   //je ne suis pas sur la ligne des X
    
    if (compareLigne(X,Y,i,Board)&&compareCol(X,Y,i,Board)){

    Board[X][Y] = &ListTuiles[i];
    ListTuiles[i].played = 1;
    nx=X;
    ny=Y+1;

    if(ny==h){nx=X+1; ny=0;};
  

    
   
if(Multithreaded1(nx, ny,0,Board ,false)){
                return true;}



    }
    }
ListTuiles[i].played = 0;
}
}

return false;




}



void Puzzle::MethodMultithread() {
//les deux thread vont effectuer les combinaison en parallèle
const clock_t deb = clock();  
std::thread t1(&Puzzle::Multithreaded1,this,0, 0 , 0,Board1,true);
   
std::thread t2(&Puzzle::Multithreaded2,this,0, 0 , 5,Board2,true );

std::thread t3(&Puzzle::Multithreaded3,this,0, 0 , 24,Board3,true );


t1.join();
t2.join();
t3.join();


cout<<"\nthread 1 "<<endl;
afficherBoard(Board1);
cout<<"\nthread 2 "<<endl;
afficherBoard(Board2);
cout<<"\nthread 3"<<endl;
afficherBoard(Board3);

float dur2= float( clock () - deb ) /  CLOCKS_PER_SEC;
}






























