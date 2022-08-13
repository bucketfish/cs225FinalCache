#include <iostream>
#include <utility>
#include <vector>
#include <set>
#include <cmath>
#include <sstream>
#include <string>
#include <iomanip>
#include <bits/stdc++.h>
#include "Nodes.h"
//#include "Graph.h"

using namespace std;


State::State() {
    _color = 1;
    _code = 0;
    _score = 0;
    _parents = 0;
    _rank = 1;
    codeColor = pair<int, int>(0,1);
    possibleNext = new std::set<State *>();
}


State::State(int code, int color) { //输入code永远为10进制！

    _code = code;
    _color = color;
    _score = 0;
    _parents = 0;
    _rank = 1;
    int nextColor = 0;
    if (color == 1) {
        nextColor = 2;
    } else {
        nextColor = 1;
    }
    codeColor = pair<int, int>(code,color);
    possibleNext = new std::set<State *>();
    
    //_score = compScore()

}

State::State(const State& other) {
    _code = other.getCode();
    _color = other.getColor();
    _score = other.getScore();
    _parents = other.numOfParents();
    _rank = other.getRank();
    int nextColor = 0;
    if (_color == 1) {
        nextColor = 2;
    } else {
        nextColor = 1;
    }
    codeColor = pair<int, int>(other.getCode(),other.getColor());
    possibleNext = other.getNext();
}

State::~State() {
    for (std::set<State *>::iterator it=possibleNext->begin(); it!=possibleNext->end(); ++it) {
        if (*it != NULL) {
            delete *it;
        }
    }
    delete possibleNext;
}


bool State::operator== (const State& other) {
    return (this->_code == other._code);
}

bool State::operator!= (const State& other) {
    return (this->_code != other._code);
}

void State::operator= (const State& other) {
    _code = other.getCode();
    _color = other.getColor();
}

void State::putNext(State * s) {
    possibleNext->insert(s);
}

std::set<State *> * State::getNext() const {
    return possibleNext;
}

pair<int, int> State::getcc() {
    return codeColor;
}



int** State::deRenderCode(int code) { //十进制转board
    int** board;
    int factor = 8;

    //反向操作
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = code / pow(3, factor);
            code = code % int(pow(3, factor));
            factor--;
        }
    }

    return board;
}

int State::getCode() const{
    return _code;
}

int State::getColor() const {
    return _color;
}


void State::deleteBroad(int** a) {
    for (int i = 0; i < 3; i++) {
        delete[] a[i];
    }
    delete[] a;
}

int State::getScore() const {
    return _score;
}

void State::setScore(int score) {
    _score = score;
}

double State::numOfParents() const {
    return _parents;
}

void State::increNumOfParents() {
    _parents+=1;
}

double State::getRank() const {
    return _rank;
}

void State::setRank(double rank) {
    _rank = rank;
} 

bool State::important() {
    return (_rank >= .00001 && _rank <= .0001);
}

