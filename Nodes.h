#pragma once
#include <iostream>
#include <utility>
#include <vector>
#include <set>

using namespace std;

class State {

    public:
        State();
        State(int code, int color);
        State(const State& other); 
        ~State();

        bool operator== (const State& other);
        bool operator!= (const State& other);
        void operator= (const State& other);

        int** deRenderCode(int code);
        int getCode() const;
        int getColor() const;
        void deleteBroad(int** a);
        std::set<State *> * getNext() const;
        void putNext(State * s);
        pair<int, int> getcc();

        int getScore() const;
        void setScore(int score);
        //int compScore(State* s, int depth, int Bscore, int Wscore);

        double numOfParents() const;
        void increNumOfParents();

        double getRank() const;
        void setRank(double rank);
        bool important();

    private:
        int _code; 
        int _color; //1黑 2白
        pair<int, int> codeColor;
        std::set<State *> * possibleNext;
        int _score;
        double _rank;
        double _parents;
}; 
