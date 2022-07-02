#include <iostream>
#include <vector>
#include <fstream>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <cassert>
#include <condition_variable>
#include <mutex>
#include <queue>
#include "ThreadPool_.h"
std::mutex m1;
bool cp=true;
using namespace std;


//Constructeur	
thrPool::thrPool(){
	//Lire Fichier et construire board 
	        std::ifstream fichier("8x8.txt");
			fichier >>w;
			fichier >>h;
			ListTuiles = new tuile[w*h];
		    Board = new tuile**[w];

			for(int i=0;i<w;i++)
			{
			Board[i] = new tuile*[h];
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
	
			//Initialiser le nombre de taches	
				for (int i = 0; i < w; ++i)
				{
					for (int j = 0; j < w; ++j){   

						Taches.push(i*j);
					}
		           }
}


//Fonction de compraraisons
bool thrPool::compareLigne(int X,int Y,int i,tuile ***Board){

	if(X!=0){  
	      if(Board[X - 1][Y]->sud != ListTuiles[i].nord){
	       
	        return false;

	      }
	}

	return true;
}


bool thrPool::compareCol(int X,int Y,int i,tuile ***Board){

	if(Y!=0){
	      
	 if(Board[X ][Y-1]->est != ListTuiles[i].ouest){
	      
	        return false;

	      }
	    }

	return true;
}


void thrPool::afficherNord(tuile ***Board, int count , int i ){


for (int j = 0; j < count; ++j)
{
  cout <<" "<<Board[i][j]->nord<<"    ";
}


}


//Fonctions Affichage
void thrPool::afficherEstOuest(tuile ***Board, int count , int i ){


for (int j = 0; j < count; ++j)
{
  cout <<Board[i][j]->ouest<<"  "<<Board[i][j]->est<<"  ";
}


}


void thrPool::afficherSud(tuile ***Board, int count , int i ){


for (int j = 0; j < count; ++j)
{
  cout <<" "<<Board[i][j]->sud<<"    ";
}


}

void thrPool::afficherBoard(tuile ***Board){
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



 //FonctionBacktracking      
bool thrPool::BacktrackingSe1(int X , int Y,int size,tuile ***Board){
   int nx, ny;
   
	if(X==size&&cp==true){
	  cout<<"affichage Board"<<endl;
       afficherBoard(Board);
       cp=false;
	    return true;
	}

	for (int i = 0; i < size*size; i++) {
	   
	    //on prend une tuile on vérifier qu'elle est pas jouer
	    if(ListTuiles[i].played==0){
	    
	   //je ne suis pas sur la ligne des X
	    
	    if (compareLigne(X,Y,i,Board)&&compareCol(X,Y,i,Board)){

	    Board[X][Y] = &ListTuiles[i];
	    ListTuiles[i].played = 1;
	    nx=X;
	    ny=Y+1;
        
	    if(ny==size){nx=X+1; ny=0;};
	   
	    if (BacktrackingSe1(nx, ny,size,Board)) {
	                return true;
	    }
	   
	    }
	    }
	ListTuiles[i].played = 0;
	}
  return false;}

//Création des threads et affectation de la tache à effectuer

void thrPool::start(){
		for (int i = 0; i < 6 ; ++i)
		{  
			threads.push_back(std::thread(&thrPool::taches,this));
			
		}
	}






//j'appelle mes threads dans cette fonction, tant que un thread n'a pas trouver la solution ou la liste des tache pas vide je continuer a exécuter 
void thrPool::taches(){
		
while(!finish){
	  unique_lock<mutex> ul(m);
	  cv.wait(ul, [&]{return !Taches.empty() || finish;});
				if (finish){break;}
				 Taches.front();
	             Taches.pop();

             m1.lock();
			if(BacktrackingSe1(0, 0,h,Board)){
				finish = true;}
             m1.unlock();

			cv.notify_one();
		}
	}




thrPool::~thrPool(){
	//Notifier tout les thread 
		finish = true;
		cv.notify_all();

		for(auto& thread : threads){
			if (thread.joinable())
			{
				thread.join();
			}
		}
	}




int main()
{
//executer thread Pool
thrPool thr;
thr.start();
return 0; 
    }

    

   
  
