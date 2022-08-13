#pragma once
#include <vector>
#include <utility>
#include <unordered_set>
#include <set>
#include <list>
#include <cmath>
#include <unordered_map>
//#include <boost/functional/hash.hpp>
#include "Nodes.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
#include <bits/stdc++.h>
using namespace std;

class stateSpace {

    public:
        stateSpace();
        stateSpace(State& start);
        //void render();
        ~stateSpace();
        void deleteHelper(State* s);

        void render(State& start);

        static int toInt(string str);
        static std::string toString(int value);
        static std::string toString9(int value);
        static int DecToTer(int n);
        static int TerToDec(int s);
        static int** getBoard(int code);
        static void deleteBroad(int** a);
        static void drawBoard(int code);
        static std::set<pair<int, int> > * allValidMoveNode(int code, int color);
        static bool isMovePhase(int code);
        static std::set<pair<int, int> >* allEmptyPosition(int code);
        static bool intheBound(int x_Coor, int y_Coor);
        static bool checkPositionValid(int code, int x_Coor, int y_Coor);
        static std::set<pair<int, int> > * validNextMove(int code, int x, int y);
        static int checkEndGame(int code);
        static int addOneStepADD(int code, int x_Coor, int y_Coor, int color);
        static int addOneStepMOVE(int code, pair<int, int> from, pair<int, int> to);
        static std::set<int> * getNextSteps(int code, int color);
        static int bestMove(int code, int color);
        static int minimax(pair<int, int> state, int mycolor, int depth,int alpha,int beta);
        static int getBoardScore(int code, int color);
        static pair<int, int> sameColorneighber(int code, int x, int y, int color, bool isVertical);
        static int criticalPoint(int code, int color); // 得分就不加自由度
        static int badPositionPoint(int code, int color); //得分就不加自由度
        static int freedPoint(int code, int color);
        static pair<int, int> isAddCritical(int code, int color);
        static string drawP(int num);

        //void growFrom(State& start);
        //static void growFrom2(stateSpace&, State& start);
        //static void growFrom2(State start, set<pair<int,int> >& nodeList, map<pair<int, int>, int>& edgeList);
        static void growFrom2(stateSpace& space, pair<int, int> start);
        void insertNode(pair<int,int>, State * s);
        void initi();
        void insertEdge(pair<int,int> edge, int color);
        map<pair<int,int>, State * > * getNodeList(); 
        map<pair<int, int>, int> * geteEdgeList();
        void putStart(State * s);
        State * getStart();

        int score(State* s, int depth, int Xscore, int Oscore);

        void pageRank();

        

    private:
        // std::unordered_map<int, State, stateHash> nodeList {{-9841, State(-9841)}, {-19682, State(-19682)}, {0, State(0)}};
        // std::unordered_map<std::pair<int, int>, int, pairHash> edgeList;
        State * start_;
        bool isInit;
        map<pair<int,int>, State* > * nodeList; 
        map<pair<int, int>, int> * edgeList; 

};

class spaceTraversal {
    public:
        class Iterator : std::iterator<std::forward_iterator_tag, State> {
        public:
            Iterator();
            Iterator(stateSpace graph_);
            Iterator(spaceTraversal* traversal_, State* state_);
            Iterator & operator++();
            State operator*();
            bool operator!=(const Iterator &other);

        private:
            spaceTraversal* traversal;
            State* current;  
        };

        virtual Iterator begin() = 0;
        virtual Iterator end() = 0;
        virtual void add(State& state) = 0;
        virtual State* pop() = 0;
        virtual State* peek() const = 0;
        virtual bool empty() const = 0;

    //private:
        //const bool a;
        State* start_;
        set<int> visitedStates; 
        set<pair<int, int> > visitedEdges; 
        list<State*> states;
};

 
// #include <string>
// #include <set>
// #include "Nodes.h"

// using namespace std;

// void makeFromCertainState(int s, std::set<int> nodesSet, std::set<std::pair <int,int> >); //pairs from->to 

// void makeFromEmptyState(std::set<int> nodesSet, std::set<std::pair <int,int> >);