#include"Puzzle.h"
#include"Puzzle.cpp"
#include<chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
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
#include <iostream>
using namespace std;
using namespace std::chrono;

int main()
 {

Puzzle p;

//Séquentielle
p.MethodSequentielle(0,0,p.Board);

/**********************************/

//Multithread
//p.MethodMultithread();


return 0; 

}