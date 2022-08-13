#pragma once
 
#include "Graph.h"
#include "Nodes.h"
//#include "Traversals.h"

#include <iostream>

//#pragma once

 
using namespace std;

class game {
    public:
        game();
        game(int code, int player, int curr);
        game(State * start);
	~game();
        
        void cpuMove();
        void playerMove();
        void echoEndGame();
        void echoPlayerMove();
        void echoCPUMove();
        void update();
        void displayBoard();

        void process();
        bool endGame();

    private:
        int _player; //color of human player
        int _cpu;
        int _curr;  //color of current move
        stateSpace *_graph;
        State * _now;
        //int _code;
        bool _endGame; // if the game ends
        int _winner; //1-X(movevs first) 2-O(moves second) 0-no winner
};
