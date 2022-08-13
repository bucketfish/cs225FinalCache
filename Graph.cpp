//#include <vector>
#include <utility>
#include <set>
#include <map>
#include <unordered_set>
#include "Graph.h"
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <queue>
#include <iomanip>
#include <tuple>
#include <bits/stdc++.h>
#include <climits>
using namespace std;

stateSpace::stateSpace() {
    
}

stateSpace::stateSpace(State& start) {
    start_ = &start;
    isInit = false;
    nodeList = NULL;
    edgeList = NULL;
}

stateSpace::~stateSpace() {
    //delete start_;
    if (isInit) {
        delete nodeList;
        delete edgeList;
    }
    // deleteHelper(start_);  

    // delete nodeList;
    // delete edgeList;

}


void stateSpace::initi() {
    
    isInit = true;
    nodeList = new map<pair<int, int>, State*>;
    edgeList = new map<pair<int, int>, int>;
}

void stateSpace::drawBoard(int code) {
    int** a = getBoard(code);
    cout <<"    " << "0 1 2"<<endl<<endl;
    cout <<"0)  " << drawP(a[0][0]) << " " << drawP(a[0][1]) << " "<< drawP(a[0][2]) << " " << endl;
    cout << "1)  "<<drawP(a[1][0]) << " " <<drawP(a[1][1]) << " "<< drawP(a[1][2]) << " " << endl;
    cout << "2)  "<<drawP(a[2][0]) << " " << drawP(a[2][1]) << " "<<drawP( a[2][2]) << " " << endl;
    deleteBroad(a);
}

string stateSpace::drawP(int num) {
    if (num == 1) {
        return "O";
    } else if (num == 0) {
        return "-";
    } else {
        return "X";
    }
}

void stateSpace::deleteHelper(State* s) {
    if (!(s->getNext())->empty()) {
        for (State* n : *(s->getNext())) {
            deleteHelper(n);
        }
    }

    delete s;
}

map<pair<int,int>, State*> * stateSpace::getNodeList() {
    return nodeList; 
} 

map<pair<int, int>, int> * stateSpace::geteEdgeList() {
    return edgeList;
}

State * stateSpace::getStart() {
    return start_;
}

int stateSpace::toInt(string str) {
    int num; 
    stringstream ss;  
    ss << str;  
    ss >> num;  
    return num;
}

std::string stateSpace::toString(int value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

std::string stateSpace::toString9(int value) { //保证返回来的是9位数的string，是001002001，而不是1002001！
    std::ostringstream os;
    os << setw(9) << setfill('0') << value << setw(9) << setfill('0');
    return os.str();
}

int stateSpace::DecToTer(int n) {
    //std::string str_ret;
    if (n==0) return 0;
    if (n<0) n = 0 - n;
    int ret=0;
    int mul=1;
    while(n>0) 
    {
       int digitofternary=n%3;
       n/=3;
       ret += mul * digitofternary;
       mul *= 10;
       //std::string str= stateSpace::toString(digitofternary);
       //str_ret.append(str); 
       
    }
    return ret;
    //reverse(str_ret.begin(), str_ret.end());
    //cout << str_ret << endl;
    // return stateSpace::toInt(str_ret);
}

int stateSpace::TerToDec(int s) { 
    int multiplier=1, result=0;
    if (s == 0) {
        return 0;
    }
    if (s<0) s = 0 - s;
    while(s>0)
    {
        result=result+s%10*multiplier;
        multiplier=multiplier*3;
        s=s/10;
    }
    return result;
}

int** stateSpace::getBoard(int code) { //十进制转三进制再转board//每一次getBoard请务必记得delete。
    int** a = new int*[3];
    for (int i = 0; i < 3; ++i) {
        a[i] = new int[3];
    }
    int one = DecToTer(code);
    string codeStr = toString9(one);
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            a[j][k] = toInt(codeStr.substr(0,1));
            codeStr = codeStr.substr(1);
        }
    }
    return a;
}

void stateSpace::deleteBroad(int** a) {
    for (int i = 0; i < 3; i++) {
        delete[] a[i];
    }
    delete[] a;
}

bool stateSpace::intheBound(int x_Coor, int y_Coor) {
    if (x_Coor < 0 || x_Coor > 2 ||y_Coor < 0 || y_Coor > 2) {
        return false;
    }
    return true;
}



std::set<pair<int, int> > * stateSpace::allValidMoveNode(int code, int color) { //调用后一定要delete。
    set<pair<int, int> >* theSet = new set<pair<int, int> >; 
    int** a = stateSpace::getBoard(code);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (a[i][j] == color) {
                theSet->insert(make_pair(i, j));
            }
        }
    }
    stateSpace::deleteBroad(a);
    return theSet;
}

std::set<pair<int, int> >* stateSpace::allEmptyPosition(int code) {
    set<pair<int, int> > * emptyPos = new set<pair<int, int> >;
    int** a = getBoard(code);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (a[i][j] == 0) {
                emptyPos->insert(make_pair(i, j));
            }
        }
    }
    deleteBroad(a);
    return emptyPos;
}

bool stateSpace::isMovePhase(int code) {
    int count = 0;
    int terCode = stateSpace::DecToTer(code);
    string codeStr = stateSpace::toString9(terCode);
    for (std::string::size_type i = 0; i < codeStr.size(); ++i) {
        if (codeStr[i] == '0') {
            count++;
        }
    }
    if (count == 3) {
        return true;
    } else {
        return false;
    }
}

bool stateSpace::checkPositionValid(int code, int x_Coor, int y_Coor) {
    if (!intheBound(x_Coor, y_Coor)) {
        //std::cout << "invalid position - out of bound" << endl;
        return false;
    }
    int terCode = stateSpace::DecToTer(code);
    string codeStr = stateSpace::toString9(terCode);
    if (codeStr.at(x_Coor * 3 + y_Coor) != '0') {
        //std::cout << codeStr.at(x_Coor * 3 + y_Coor) << endl;
        return false;
    }
    return true;
}

std::set<pair<int, int> > * stateSpace::validNextMove(int code, int x, int y) {
    set<pair<int, int> > * neighbors = new set<pair<int, int> >;
    if (((x == 1 && y == 1) || (x == 2 && y == 2)) && checkPositionValid(code, x - 1, y - 1)) {
        neighbors->insert( pair<int,int>(x - 1, y - 1));
    }
    if (checkPositionValid(code, x - 1, y)) {
        neighbors->insert(pair<int,int>(x - 1, y));
    }
    if (((x == 1 && y == 1) || (x == 2 && y == 0)) && checkPositionValid(code, x - 1, y + 1)) {
        neighbors->insert( pair<int,int>(x - 1, y + 1));
    }
    if (checkPositionValid(code, x, y - 1)) {
        neighbors->insert( pair<int,int>(x, y - 1));
    }
    if (checkPositionValid(code, x, y + 1)) {
        neighbors->insert( pair<int,int>(x, y + 1));
    }
    if (((x == 1 && y == 1) || (x == 0 && y == 2)) && checkPositionValid(code, x + 1, y - 1)) {
        neighbors->insert( pair<int,int>(x + 1, y - 1));
    }
    if (checkPositionValid(code, x + 1, y)) {
        neighbors->insert( pair<int,int>(x + 1, y));
    }
    if (((x == 1 && y == 1) || (x == 0 && y == 0)) && checkPositionValid(code, x + 1, y + 1)) {
        neighbors->insert( pair<int,int>(x + 1, y + 1));
    }
    return neighbors;
}

int stateSpace::checkEndGame(int code) {
    int** _board = stateSpace::getBoard(code);
    int _endGame = 0;
    for (int i = 0; i < 3; i++) {
        int y0 = _board[i][0];
        int y1 = _board[i][1];
        int y2 = _board[i][2];
        if (y0 == y1 && y1 == y2 && y0 != 0) {
            //_endGame = y0;
            if (y0 == 1) _endGame = 1;
            if (y0 == 2) _endGame = -1;
            deleteBroad(_board);
            return _endGame;
        }

        int x0 = _board[0][i];
        int x1 = _board[1][i];
        int x2 = _board[2][i];

        if (x0 == x1 && x1 == x2 && x0 != 0) {
            //_endGame = x0;
            if (x0 == 1) _endGame = 1;
            if (x0 == 2) _endGame = -1;
            deleteBroad(_board);
            return _endGame;
        }               
    }

    // check cross
    int c00 = _board[0][0];
    int c22 = _board[2][2];
    int c11 = _board[1][1];   

    int c20 = _board[2][0];
    int c02 = _board[0][2];
    if (c00 == c11 && c11 == c22 && c00 != 0) {
        if (c00 == 1) _endGame = 1;
        if (c00 == 2) _endGame = -1;
        deleteBroad(_board);
        //_endGame = c00;
        return _endGame;
    }
    if (c20 == c11 && c11 == c02 && c20 != 0) {
        //_endGame = c20;
        if (c20 == 1) _endGame = 1;
        if (c20 == 2) _endGame = -1;
        deleteBroad(_board);
        return c20;
    }
    
    
    deleteBroad(_board);
    return 0;
}

int stateSpace::addOneStepADD(int code, int x_Coor, int y_Coor, int color) {
    if (x_Coor < 0 || x_Coor > 2 ||y_Coor < 0 || y_Coor > 2) {
        //std::cout << "invalid position - out of bound" << endl;
        return code;
    }
    string newCodeStr;
    if (stateSpace::checkEndGame(code) == 0) {
        int tre = stateSpace::DecToTer(code);
        string codeStr = stateSpace::toString9(tre);
        int position = x_Coor *3 + y_Coor; 

        if (codeStr.at(position) == '0') {
            newCodeStr.append(codeStr.substr(0, position));
            newCodeStr.append(toString(color));
            newCodeStr.append(codeStr.substr(position+1));
        } else {
            //std::cout << "invalid postion - already have node here" << std::endl;
            return code;
        }

    } else {
        //std::cout << "Game already over!" << std::endl;
        return code;
    }
    return stateSpace::TerToDec(stateSpace::toInt(newCodeStr));
}

int stateSpace::addOneStepMOVE(int code, pair<int, int> from, pair<int, int> to) {
    int tre = stateSpace::DecToTer(code);
    string codeStr = stateSpace::toString9(tre);
    int position = from.first *3 + from.second; 
    string thecolor;
    thecolor.push_back(codeStr.at(position));
    int color = toInt(thecolor);
    string newCodeStr;
    newCodeStr.append(codeStr.substr(0, position));
    newCodeStr.append("0");
    newCodeStr.append(codeStr.substr(position+1));
    int newcode = stateSpace::TerToDec(toInt(newCodeStr));
    return stateSpace::addOneStepADD(newcode, to.first, to.second, color);
    
}

std::set<int> * stateSpace::getNextSteps(int code, int color) { 
    set<int> * nextStep = new set<int>; //toreturn
    if (isMovePhase(code)){ //移棋状态
        set<pair<int, int> > * moveNode = stateSpace::allValidMoveNode(code, color); //找出所有可能挪动的棋子（全部黑棋，全部白棋）
        for (std::set<pair<int, int> >::iterator it=moveNode->begin(); it!=moveNode->end(); ++it) {//对于每一个可能挪动棋子
            pair<int, int> from = make_pair(it->first, it->second);
            std::set<pair<int, int> > * validNextPoint = stateSpace::validNextMove(code, it->first, it->second);//找出每个可能挪动棋子的下一步可能移动坐标
            //生成可能状态并储存
            for (std::set<pair<int, int> >::iterator it2=validNextPoint->begin(); it2!=validNextPoint->end(); ++it2) {
                nextStep->insert(addOneStepMOVE(code, from, make_pair(it2->first, it2->second)));
            }
            delete validNextPoint;
        }
        delete moveNode;
    } else { //下棋状态
        set<pair<int, int> > * addNode = stateSpace::allEmptyPosition(code); //找出所有可能下棋的位置（全部空白）
        //生成可能状态并储存
        for (std::set<pair<int, int> >::iterator it=addNode->begin(); it!=addNode->end(); ++it) { //有没有可能在这一步就避免对称呢？ 没有
            nextStep->insert(stateSpace::addOneStepADD(code, it->first, it->second, color));
        }
        delete addNode;
    }
    return nextStep;
    
}

void stateSpace::putStart(State * s) {
    start_ = s;
}

void stateSpace::insertNode(pair<int,int> node, State * s) {
    nodeList->insert( pair<pair<int, int>, State*> (node, s) );
} 

void stateSpace::insertEdge(pair<int,int> edge, int color) {
    (*edgeList)[edge] = color;
}

void stateSpace::growFrom2(stateSpace& space, pair<int, int> start) {
    /*
    stateSpace空的nodelist
        在nodelist里面放入-9841（1赢），-19682（2赢）这两种状态
    stateSpace空的edgelist
    给定空的queue
    1. 给定一个状态放queue
    2. while
    取第一个
    get所有nextstep
    对于这些nextstep
        如果1赢：生成新的edge，放入edgelist，（不放入新node，不加入queue）
        如果2赢：生成新的edge，放入edgelist，

        如果nodeset里面有这个step，
            生成新的edge，放入edgelist，生成对应state（不放入新node，不加入queue）
        否则如果没有这个nodestep
            将本step加入nodeset，生成新的edge，放入edgelist，生成对应state，加入queue
    
    结果：private variable被initialize. nodelist，edgelist
    */
<<<<<<< HEAD

=======
>>>>>>> 043f995019bdce0780c18358b5680a0a3961cb7b
    space.initi();
    State * Bwin = new State(-9481, 1); //?
    State * Wwin = new State(-19682, 2);
    space.insertNode(pair<int,int>(-9841,0), Bwin);
    space.insertNode(pair<int,int>(-19682,0), Wwin);
    
    std::queue<State * > q;

    if (checkEndGame(start.first) == 0) {
        State * st = new State(start.first, start.second);
        space.putStart(st);
        q.push(st);
        space.insertNode(pair<int,int>(start.first,start.second),st);
        
    }
    
    // int i = 0; //change i in the while loop to change num of steps
    while (! q.empty()) { //&& i < 2000) {//&& i<6
        State * s = q.front();
        q.pop();

        int nextColor = 0; 
        if (s->getColor() == 1) {
            nextColor = 2;
        } else {
            nextColor = 1;
        }
        
        std::set<int> * possibleSet = stateSpace::getNextSteps(s->getCode(), nextColor);
        
        for (std::set<int>::iterator it=possibleSet->begin(); it!=possibleSet->end(); ++it) {
            //State * stNext = new State(*it, nextColor);
            //s->putNext(stNext);

            if (checkEndGame(*it) == 1) {
                State * stNext = new State(*it, nextColor);
                stNext->putNext(Bwin);
                s->putNext(stNext);
                Bwin->increNumOfParents();
                stNext->increNumOfParents();
                pair<int, int> transit(s->getCode(), *it);
                space.insertEdge(transit, nextColor);
                pair<int, int> transit2(s->getCode(), -9841);
                space.insertEdge(transit2, nextColor);
            } else if (checkEndGame(*it) == 2) {
                State * stNext = new State(*it, nextColor);
                stNext->putNext(Wwin);
                s->putNext(stNext);
                Wwin->increNumOfParents();
                stNext->increNumOfParents();
                pair<int, int> transit(s->getCode(), *it);
                space.insertEdge(transit, nextColor);
                pair<int, int> transit2(s->getCode(), -19682);
                space.insertEdge(transit2, nextColor);
            } else {
                std::map<pair<int,int>, State* >::iterator it2 = (space.getNodeList())->find( pair<int,int>(*it,nextColor) );
                if (it2 != (space.getNodeList())->end()) { //在next中
                    pair<int, int> transit(s->getCode(), *it); 
                    space.insertEdge(transit, nextColor);

                    s->putNext(it2->second);
                    (it2->second)->increNumOfParents();
                    //delete stNext;

                } else {
                    State * stNext = new State(*it, nextColor);
                    space.insertNode(pair<int,int>(*it,nextColor),stNext);
                    
                    pair<int, int> transit(s->getCode(), *it);
                    space.insertEdge(transit, nextColor);
                    //pair<int, int> state(*it, nextColor); //需不需要用new？
                    //State* n = stNext;
                    s->putNext(stNext);
                    stNext->increNumOfParents();
                    q.push(stNext);
                }
            }
        }
        delete possibleSet; 
    }

    // for (pair<pair<int,int>, State* > node : *space.nodeList) {
    //     for (pair<pair<int,int>,int> edge : *space.edgeList) {
    //         if (edge.first.first == node.first.first) {
    //             for (pair<pair<int,int>,State* > node2 : *space.nodeList) {
    //                 if (node2.first.first == edge.first.second) {
    //                     node.second->putNext(node2.second);
    //                 }
    //             }
    //         }
    //     }
    // }

}

int stateSpace::bestMove(int code, int color) { //放入地方造成的棋盘
    int mycolor = 0; 
    if (color == 1) {
        mycolor = 2;
    } else {
        mycolor = 1;
    }

    if (!isMovePhase(code)) {
        //cout << "check phase " << code << " with " << color << endl;
        pair<int, int> possAddCritical = isAddCritical(code, color);
        //out << possAddCritical.first << " and " << possAddCritical.second << endl;
        if (possAddCritical.first != -1) {
            return addOneStepADD(code, possAddCritical.first, possAddCritical.second, mycolor);
        }
    }
    pair<int, int> bestmove = pair<int, int>(-1,-10000);
    std::set<int> * possibleSet = stateSpace::getNextSteps(code, mycolor);
    for (std::set<int>::iterator it=possibleSet->begin(); it!=possibleSet->end(); ++it) {
        int move = minimax(pair<int, int>(*it, mycolor), mycolor, 7, -10000, 10000);
        if (move > bestmove.second) {
            bestmove.first = *it;
            bestmove.second = move;
        }
    }
    return bestmove.first;
}

pair<int, int> stateSpace::isAddCritical(int code, int color) {
    int** _board = stateSpace::getBoard(code);

    int other = 0; 
    if (color == 1) {
        other = 2;
    } else {
        other = 1;
    }
    pair< pair<int, int>, int> numEmpty = pair< pair<int, int>, int>(pair<int, int>(-1,-1),0);
    //vertical
    for (int i = 0; i < 3; i++) {
        numEmpty = pair< pair<int, int>, int>(pair<int, int>(-1,-1),0);
        int num1 = 0;
        int num2 = 0;
        for (int j = 0; j < 3; j++) {
           if (_board[j][i] == 0) {
               numEmpty.first = pair<int, int>(j,i);
               numEmpty.second += 1;
           } else if (_board[j][i] == color) {
               num1++;
           } else {
               num2++;
           }
        }


        if (num1 == 2 && numEmpty.second == 1) {
            deleteBroad(_board);
            return numEmpty.first;
        }
    }

    //horizontal check
    for (int i = 0; i < 3; i++) {
        numEmpty = pair< pair<int, int>, int>(pair<int, int>(-1,-1),0);
        int num1 = 0;
        int num2 = 0;
        for (int j = 0; j < 3; j++) {
           if (_board[i][j] == 0) {
               numEmpty.first = pair<int, int>(i,j);
               numEmpty.second += 1;
           } else if (_board[i][j] == color) {
               num1++;
           } else {
               num2++;
           }
        }

        if (num1 == 2 && numEmpty.second == 1) {
            deleteBroad(_board);
            return numEmpty.first;
            
        }
    }

    //diag
    numEmpty = pair< pair<int, int>, int>(pair<int, int>(-1,-1),0);
    int num1 = 0;
    int num2 = 0;
    for (int i = 0; i < 3; i++) {
        if (_board[i][i] == 0) {
            numEmpty.first = pair<int, int>(i,i);
            numEmpty.second += 1;
        } else if (_board[i][i] == color) {
            num1++;
        } else {
            num2++;
        }

    }
    if (num1 == 2 && numEmpty.second == 1) {
        deleteBroad(_board);
        return numEmpty.first;
            
    }

    numEmpty = pair< pair<int, int>, int>(pair<int, int>(-1,-1),0);
    num1 = 0;
    num2 = 0;
    for (int i = 2; i >= 0; i--) {
        if (_board[i][2 - i] == 0) {
            numEmpty.first = pair<int, int>(i,2 - i);
            numEmpty.second += 1;
        } else if (_board[i][2 - i] == color) {
            num1++;
        } else {
            num2++;
        }

    }
    if (num1 == 2 && numEmpty.second == 1) {
        deleteBroad(_board);
        return numEmpty.first;
            
    }
    numEmpty = pair< pair<int, int>, int>(pair<int, int>(-1,-1),0);

    deleteBroad(_board);
    return numEmpty.first;
}

int stateSpace::minimax(pair<int, int> state, int mycolor, int depth,int alpha ,int beta) { //放入由对方造成的局面
    int othercolor = 0; 
    if (mycolor == 1) {
        othercolor = 2;
    } else {
        othercolor = 1;
    }

    if (checkEndGame(state.first) == othercolor) {
        return -1000; 
    } else if (checkEndGame(state.first) == mycolor) {
        return 1000;
    } else if (depth == 0) {
        return 0;
    } else {
        if (state.second == othercolor) { //现在是对方造成的局面，我来接着下棋，max
            int bestVal = -10000;
            std::set<int> * possibleSet = stateSpace::getNextSteps(state.first, state.second);
            for (std::set<int>::iterator it=possibleSet->begin(); it!=possibleSet->end(); ++it) {
                bestVal = std::max(bestVal, minimax(pair<int, int>(*it, mycolor), mycolor, depth-1, alpha, beta));
                alpha = std::max(alpha, bestVal);
                if (beta <= alpha) {
                    break;
                }
            }
            delete possibleSet;
            return bestVal;
        } else { //state.second == mycolor 我造成的局面， 对方会选择他的最优解，min
            int bestVal = 10000;
            std::set<int> * possibleSet = stateSpace::getNextSteps(state.first, othercolor);
            for (std::set<int>::iterator it=possibleSet->begin(); it!=possibleSet->end(); ++it) {
                bestVal = std::min(bestVal, minimax(pair<int, int>(*it, othercolor), mycolor, depth-1, alpha, beta));
                beta = std::min(beta, bestVal);
                if (beta <= alpha) {
                    break;
                }
            }
            delete possibleSet;
            return bestVal;
        }

    }
}

int stateSpace::getBoardScore(int code, int color) {
    int other = 0; 
    if (color == 1) {
        other = 2;
    } else {
        other = 1;
    }

    int score = 0;
    int otherscore = 0;

    if (criticalPoint(code,color) != 0) {
        score = criticalPoint(code, color);
    } else if (badPositionPoint(code, color) != 0) {
        score = badPositionPoint(code, color);
    } else {
        score = freedPoint(code, color);
    }
    cout <<score<< endl;

    if (criticalPoint(code,other) != 0) {
        otherscore = criticalPoint(code, other);
    } else if (badPositionPoint(code, other) != 0) {
        otherscore = badPositionPoint(code, other);
    } else {
        otherscore = freedPoint(code, other);
    }
    cout <<otherscore<< endl;

    return score - otherscore;

}

int stateSpace::freedPoint(int code, int color) {
    std::set<int> * possibleSet = stateSpace::getNextSteps(code, color);
    for (std::set<int>::iterator it=possibleSet->begin(); it!=possibleSet->end(); ++it) {
         cout << stateSpace::DecToTer(*it) <<endl;
    }
    int points = 3 * possibleSet->size();
    delete possibleSet;
    return points;
}

int stateSpace::criticalPoint(int code, int color) {
    int** _board = stateSpace::getBoard(code);
    drawBoard(code);

    int other = 0; 
    if (color == 1) {
        other = 2;
    } else {
        other = 1;
    }

    //vertical
    for (int i = 0; i < 3; i++) {
        int num1 = 0;
        int num2 = 0;
        pair< pair<int, int>, int> numEmpty = pair< pair<int, int>, int>(pair<int, int>(0,0),0);
        for (int j = 0; j < 3; j++) {
           if (_board[j][i] == 0) {
               numEmpty.first = pair<int, int>(j,i);
               numEmpty.second += 1;
           } else if (_board[j][i] == color) {
               num1++;
           } else {
               num2++;
           }
        }


        if (num1 == 2 && numEmpty.second == 1) {
            pair<int, int> neighber = sameColorneighber(code, numEmpty.first.first, numEmpty.first.second, color, true);
            std::set<pair<int, int> > * validNextPoint = stateSpace::validNextMove(code, neighber.first, neighber.second);//找出棋所有下一步可挪动坐标
            std::set<pair<int,int> >::iterator it = validNextPoint->find( numEmpty.first );
            if (it != (validNextPoint)->end()) {
                deleteBroad(_board);
                delete validNextPoint;
                return 30;
            }
            delete validNextPoint;
        }
    }
    //horizontal check
    for (int i = 0; i < 3; i++) {
        int num1 = 0;
        int num2 = 0;
        pair< pair<int, int>, int> numEmpty = pair< pair<int, int>, int>(pair<int, int>(0,0),0);
        for (int j = 0; j < 3; j++) {
           if (_board[i][j] == 0) {
               numEmpty.first = pair<int, int>(i,j);
               numEmpty.second += 1;
           } else if (_board[i][j] == color) {
               num1++;
           } else {
               num2++;
           }
        }

        if (num1 == 2 && numEmpty.second == 1) {

            pair<int, int> neighber = sameColorneighber(code, numEmpty.first.first, numEmpty.first.second, color, false);
            cout << neighber.first << " and " << neighber.second << endl;
            std::set<pair<int, int> > * validNextPoint = stateSpace::validNextMove(code, neighber.first, neighber.second);
            // for (std::set<pair<int, int> >::iterator it2=validNextPoint->begin(); it2!=validNextPoint->end(); ++it2) {
            //     cout << "Here are valid " << it2->first << " and " << it2->second << endl;
            // }
            std::set<pair<int,int> >::iterator it = validNextPoint->find( numEmpty.first );
            if (it != (validNextPoint)->end()) {
                deleteBroad(_board);
                delete validNextPoint;
                return 30;
            }
            delete validNextPoint;
        }
    }

    //diag
    if (_board[0][0] == _board[2][2] &&_board[0][0] == color && _board[1][1] == 0) {
        return 30;
    }
    if (_board[0][2] == _board[2][0] &&_board[0][2] == color && _board[1][1] == 0) {
        return 30;
    }

    deleteBroad(_board);
    return 0;
}

int stateSpace::badPositionPoint(int code, int color) {
    int** _board = stateSpace::getBoard(code);

    int other = 0; 
    if (color == 1) {
        other = 2;
    } else {
        other = 1;
    }
    for (int i = 0; i < 3; i++) {
       if (_board[0][i] == _board[2][i] && _board[0][i] == color && _board[1][i] == other) {
           return 5;
       }
       if (_board[i][0] == _board[i][2] && _board[i][0] == color && _board[i][1] == other) {
           return 5;
       }
    }
    if (_board[0][0] == color && _board[0][0] == _board[2][2] && _board[1][1] == other) {
        return 5;
    }
    if (_board[2][0] == color && _board[2][0] == _board[0][2] && _board[1][1] == other) {
        return 5;
    }
    deleteBroad(_board);
    return 0;
}
pair<int, int> stateSpace::sameColorneighber(int code, int x, int y, int color, bool isVertical) {
    int** _board = stateSpace::getBoard(code);
    pair<int, int> toreturn = pair<int, int>(-1,-1);
    if (isVertical) {
        int x_Coor = 0;
        for (int i = -1; i < 2; i++) {
            x_Coor = x+i;
            if (intheBound(x_Coor, y-1) && _board[x_Coor][y-1] == color) {
                return pair<int, int>(x_Coor, y-1);
            }
            if (intheBound(x_Coor, y+1) && _board[x_Coor][y+1] == color) {
                return pair<int, int>(x_Coor, y+1);
            }
        }
    } else {
        int y_Coor = 0;
        for (int i = -1; i < 2; i++) {
            y_Coor = y+i;
            if (intheBound(x-1, y_Coor) && _board[x-1][y_Coor] == color) {
                return pair<int, int>(x-1, y_Coor);
            }
            if (intheBound(x+1, y_Coor) && _board[x+1][y_Coor] == color) {
                return pair<int, int>(x+1, y_Coor);
            }
        }
    }
    deleteBroad(_board);
    return pair<int, int>(-1, -1);
}
//pageRank

void stateSpace::pageRank() {
    double pr[nodeList->size()];
    int i = 0;
    for (std::map<pair<int,int>,State*>::iterator it=nodeList->begin(); it!=nodeList->end(); ++it){
        pr[i] = 1.0/(double)nodeList->size();
        (it->second)->setRank(pr[i]);
    }

    for (int j = 0; j < 6; j++) {
        int i = 0;
        for (std::map<pair<int,int>,State*>::iterator it=nodeList->begin(); it!=nodeList->end(); ++it) {
            pr[i] = 0;
            for (State* s : *(it->second)->getNext()) {
                pr[i] += (s->getRank() / s->numOfParents());
            }
            //if (pr[i] == 0) pr[i] = 
            //converge = converge && (pr[i] == (it->second)->getRank());
            
            (it->second)->setRank(pr[i]);
            i++;
        }
    }
    
}



// void stateSpace::growFrom2(stateSpace& space, pair<int, int> start) {
//     /*
//     stateSpace空的nodelist
//         在nodelist里面放入-9841（1赢），-19682（2赢）这两种状态
//     stateSpace空的edgelist
//     给定空的queue
//     1. 给定一个状态放queue
//     2. while
//     取第一个
//     get所有nextstep
//     对于这些nextstep
//         如果1赢：生成新的edge，放入edgelist，（不放入新node，不加入queue）
//         如果2赢：生成新的edge，放入edgelist，

//         如果nodeset里面有这个step，
//             生成新的edge，放入edgelist，生成对应state（不放入新node，不加入queue）
//         否则如果没有这个nodestep
//             将本step加入nodeset，生成新的edge，放入edgelist，生成对应state，加入queue
    
//     结果：private variable被initialize. nodelist，edgelist
//     */
//     space.insertNode(pair<int,int>(-9841,0));
//     space.insertNode(pair<int,int>(-19682,0));
    
//     std::queue<pair<int, int> > q;

//     if (checkEndGame(start.first) == 0) {
//         State * st = new State(start.first, start.second);
//         space.putStart( st);
//         q.push(start);
//         space.insertNode(pair<int,int>(pair<int,int>(start.first,start.second)));
        
//     }
    
//     int i = 0; //change i in the while loop to change num of steps
//     while (! q.empty()) {//&& i<6
//         pair<int, int> s = q.front();
//         q.pop();

//         int nextColor = 0; 
//         if (s.second == 1) {
//             nextColor = 2;
//         } else {
//             nextColor = 1;
//         }
//         std::set<int> * possibleSet = stateSpace::getNextSteps(s.first, nextColor);
        
//         for (std::set<int>::iterator it=possibleSet->begin(); it!=possibleSet->end(); ++it) {
//             State * stNext = new State(*it, nextColor);
//             st->putNext(stNext);
//             if (checkEndGame(*it) == 1) {
//                 pair<int, int> transit(s.first, -9841);
//                 space.insertEdge(transit, nextColor);
//             } else if (checkEndGame(*it) == 2) {
//                 pair<int, int> transit(s.first, -19682);
//                 space.insertEdge(transit, nextColor);
//             } else {
//                 std::set<pair<int,int> >::iterator it2 = (space.getNodeList())->find( pair<int,int>(*it,nextColor) );
//                 if (it2 != (space.getNodeList())->end()) {
//                     pair<int, int> transit(s.first, *it);
//                     space.insertEdge(transit, nextColor);
//                 } else {
//                     space.insertNode(pair<int,int>(*it,nextColor));
//                     pair<int, int> transit(s.first, *it);
//                     space.insertEdge(transit, nextColor);
//                     pair<int, int> state(*it, nextColor); //需不需要用new？
//                     q.push(state);
//                 }
//             }
//         }
//         delete possibleSet; 
//         i++;
//         //std::cout <<"11111111111111111111"<< endl;

//     }
// }

///////////////////////THE ITERATOR//////////////////////

// class spaceTraversal {
//     public:
//         class Iterator : std::iterator<std::forward_iterator_tag, State> {
//         public:
//             Iterator(stateSpace graph_);
//             Iterator(spaceTraversal* traversal_, State state_);
//             Iterator & operator++();
//             State operator*();
//             bool operator!=(const Iterator &other);

//         private:
//             spaceTraversal* traversal;
//             State current;
//         };

//         virtual Iterator begin() = 0;
//         virtual Iterator end() = 0;
//         virtual void add(const State & t) = 0;
//         virtual State pop() = 0;
//         virtual State peek() const = 0;
//         virtual bool empty() const = 0;

// }; 
spaceTraversal::Iterator::Iterator() {
    current = NULL; 
}

spaceTraversal::Iterator::Iterator(stateSpace graph_) {
    current = graph_.getStart(); 
}

spaceTraversal::Iterator::Iterator(spaceTraversal* traversal_, State* state_) {
    traversal = traversal_;
    current = state_; 
}

spaceTraversal::Iterator& spaceTraversal::Iterator::operator++() {
    current = traversal->pop();  
    std::set<State* > * l = current->getNext();

    for (State* s : *l) {

        if (traversal->visitedStates.find(s->getCode()) != traversal->visitedStates.end()) {
            traversal->add(*s);
        }
        traversal->visitedEdges.insert(pair<int,int>(current->getCode(), s->getCode()));
    }

    traversal->visitedStates.insert(current->getCode());   
    current = traversal->peek();

    return *this;
}

State spaceTraversal::Iterator::operator*() {
  return *(this->current);
}

bool spaceTraversal::Iterator::operator!=(const spaceTraversal::Iterator &other) {
    return !(this->current == other.current);
}



// void stateSpace::growFrom(State& start) {
//     std::list<State> q;
//     q.push_back(start);

//     while (! q.empty()) {

//         State& s = q.front();
//         q.pop_front();

//         if (s.checkEndGame() == 1) {
//             pair<int, int> transit(s.getCode(), -9841);
//             edgeList.insert({transit, 1});
//             s.addNextStep(-9841, 1);
//         } else if (s.checkEngGame() == 2) {
//             pair<int, int> transit(s.getCode(), -19682);
//             edgeList.insert({transit, 2});
//             s.addNextStep(-19682, 1);
//         } else if  (! s.isMovePhase()) {
//             int color;
//             if (s.getChessNum() % 2 == 0) color = 1;
//             else color = 2;
            
//             for (int i = 0; i < 3; i++) {
//                 for (int j = 0; j < 3; j++) {
//                     if (s.getPosition(i,j) == 0) {
//                         int newCode = s.getCode() + color * int(pow(3,8-(3*i+j)));
//                         State::State next(newCode);
//                         if (! nodeList.contains({newCode, next})) {
//                             q.push_back(next);
//                             nodeList.insert({newCode, next});
//                         }
//                         pair<int, int> transit(s.getCode(), newCode);
//                         edgeList.insert({transit, color});

//                         s.addNextStep(nextCode, color);
//                     }
//                 }
//             }

//         } else {
            
//             for (int i = 0; i < 3; i++) {
//                 for (int j = 0; j < 3; j++) {
//                     int color = s.getPosition(i,j);
//                     if (color != 0) {

//                         for (int m = i - 1; m < i + 1; m++) {
//                             for (int n = j - 1; n < j + 1; n++) {
//                                 if ((m > -1 && m < 3 && m != i) && (n > -1 && n < 3 && n != j) && s.getPosition(m,n) == 0) {
//                                     int newCode = s.getCode() + color * (int(pow(3,8-(3*m+n)))-int(pow(3,8-(3*i+j))));
//                                     State::State next(newCode);
//                                     if (! nodeList.contains({newCode, next})) {
//                                         q.push_back(next);
//                                         nodeList.insert({newCode, next});
//                                     }
//                                     pair<int, int> transit(next, newCode);
//                                     edgeList.insert({transit, color});

//                                     s.addNextStep(nextCode, color);
//                                 }
//                             }
//                         }

//                     }
//                 }
//             }

//         }

//         q.pop_front();

//     }
// }

//测试用 网站直接粘贴https://onecompiler.com/cpp/3xhy87mvg
/*
#include <iostream>
#include <utility>
#include <vector>
#include <set>
#include <cmath>
#include <map>
#include <sstream>
#include <string>
#include<iomanip>
#include <unordered_set>
#include <queue>
#include <bits/stdc++.h>
using namespace std;

int toInt(string str) {
    int num; 
    stringstream ss;  
    ss << str;  
    ss >> num;  
    return num;
}

std::string toString(int value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

std::string toString9(int value) { //保证返回来的是9位数的string，是001002001，而不是1002001！
    std::ostringstream os;
    os << setw(9) << setfill('0') << value ;
    return os.str();
}

int DecToTer(int n) {
    std::string str_ret;
    if (n==0) return 0;
    if (n<0) n = 0 - n;
    while(n!=0) 
    {
       int digitofternary=n%3;
       n/=3;
       std::string str= toString(digitofternary);
       str_ret.append(str); 
       
    }
    reverse(str_ret.begin(), str_ret.end());
    //cout << str_ret << endl;
    return toInt(str_ret);
}

int TerToDec(int s) {
    int multiplier=1, result=0;
    if (s == 0) {
        return 0;
    }
    if (s<0) s = 0 - s;
    while(s>0)
    {
        result=result+s%10*multiplier;
        multiplier=multiplier*3;
        s=s/10;
    }
    return result;
}

int** getBoard(int code) { //十进制转三进制再转board//每一次getBoard请务必记得delete。
    int** a = new int*[3];
    for (int i = 0; i < 3; ++i) {
        a[i] = new int[3];
    }
    int one = DecToTer(code);
    string codeStr = toString9(one);
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            a[j][k] = toInt(codeStr.substr(0,1));
            codeStr = codeStr.substr(1);
        }
    }
    return a;
}

void deleteBroad(int** a) {
    for (int i = 0; i < 3; i++) {
        delete[] a[i];
    }
    delete[] a;
}


std::set<pair<int, int> > * allValidMoveNode(int code, int color) { //调用后一定要delete。
    set<pair<int, int> >* theSet = new set<pair<int, int> >; 
    int** a = getBoard(code);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (a[i][j] == color) {
                theSet->insert(make_pair(i, j));
            }
        }
    }
    deleteBroad(a);
    return theSet;
}

std::set<pair<int, int> >* allEmptyPosition(int code) {
    set<pair<int, int> > * emptyPos = new set<pair<int, int> >;
    int** a = getBoard(code);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (a[i][j] == 0) {
                emptyPos->insert(make_pair(i, j));
            }
        }
    }
    deleteBroad(a);
    return emptyPos;
}

bool isMovePhase(int code) {
    int count = 0;
    int terCode = DecToTer(code);
    string codeStr = toString9(terCode);
    for (std::string::size_type i = 0; i < codeStr.size(); ++i) {
        if (codeStr[i] == '0') {
            count++;
        }
    }
    if (count == 3) {
        return true;
    } else {
        return false;
    }
}

bool checkPositionValid(int code, int x_Coor, int y_Coor) {
    if (x_Coor < 0 || x_Coor > 2 ||y_Coor < 0 || y_Coor > 2) {
        return false;
    }
    int terCode = DecToTer(code);
    string codeStr = toString9(terCode);
    if (codeStr.at(x_Coor * 3 + y_Coor) != '0') {
        std::cout << codeStr.at(x_Coor * 3 + y_Coor) << endl;
        return false;
    }
    return true;
}

std::set<pair<int, int> > * validNextMove(int code, int x, int y) {
    set<pair<int, int> > * neighbers = new set<pair<int, int> >;
    if (checkPositionValid(code, x - 1, y - 1)) {
        neighbers->insert( pair<int,int>(x - 1, y - 1));
    }
    if (checkPositionValid(code, x - 1, y)) {
        neighbers->insert(pair<int,int>(x - 1, y));
    }
    if (checkPositionValid(code, x - 1, y + 1)) {
        neighbers->insert( pair<int,int>(x - 1, y + 1));
    }
    if (checkPositionValid(code, x, y - 1)) {
        neighbers->insert( pair<int,int>(x, y - 1));
    }
    if (checkPositionValid(code, x, y + 1)) {
        neighbers->insert( pair<int,int>(x, y + 1));
    }
    if (checkPositionValid(code, x + 1, y - 1)) {
        neighbers->insert( pair<int,int>(x + 1, y - 1));
    }
    if (checkPositionValid(code, x + 1, y)) {
        neighbers->insert( pair<int,int>(x + 1, y));
    }
    if (checkPositionValid(code, x + 1, y + 1)) {
        neighbers->insert( pair<int,int>(x + 1, y + 1));
    }
    return neighbers;
}

int checkEndGame(int code) {
    int** _board = getBoard(code);
    int _endGame = 0;
    for (int i = 0; i < 3; i++) {
        int y0 = _board[i][0];
        int y1 = _board[i][1];
        int y2 = _board[i][2];
        if (y0 == y1 && y1 == y2 && y0 != 0) {
            _endGame = y0;
            return y0;
        }

        int x0 = _board[0][i];
        int x1 = _board[1][i];
        int x2 = _board[2][i];

        if (x0 == x1 && x1 == x2 && x0 != 0) {
            _endGame = x0;
            return x0;
        }              
    }

    // check cross
    int c00 = _board[0][0];
    int c22 = _board[2][2];
    int c11 = _board[1][1];   

    int c20 = _board[2][0];
    int c02 = _board[0][2];
    if (c00 == c11 && c11 == c22 && c00 != 0) {
        _endGame = c00;
        return c00;
    }
    if (c20 == c11 && c11 == c02 && c20 != 0) {
        _endGame = c20;
        return c20;
    }
    //deleteBroad(_board);
    return 0;
}

int addOneStepADD(int code, int x_Coor, int y_Coor, int color) {
    if (x_Coor < 0 || x_Coor > 2 ||y_Coor < 0 || y_Coor > 2) {
        return code;
    }
    string newCodeStr;
    if (checkEndGame(code) == 0) {
        int tre = DecToTer(code);
        string codeStr = toString9(tre);
        int position = x_Coor *3 + y_Coor; 

        if (codeStr.at(position) == '0') {
            newCodeStr.append(codeStr.substr(0, position));
            newCodeStr.append(toString(color));
            newCodeStr.append(codeStr.substr(position+1));
        } else {
            return code;
        }

    } else {
        return code;
    }
    return TerToDec(toInt(newCodeStr));
}

int addOneStepMOVE(int code, pair<int, int> from, pair<int, int> to) {
    int tre = DecToTer(code);
    string codeStr = toString9(tre);
    int position = from.first *3 + from.second; 
    string thecolor;
    thecolor.push_back(codeStr.at(position));
    int color = toInt(thecolor);
    string newCodeStr;
    newCodeStr.append(codeStr.substr(0, position));
    newCodeStr.append("0");
    newCodeStr.append(codeStr.substr(position+1));
    int newcode = TerToDec(toInt(newCodeStr));
    return addOneStepADD(newcode, to.first, to.second, color);
    
}

std::set<int> * getNextSteps(int code, int color) { 
    set<int> * nextStep = new set<int>; //toreturn
    if (isMovePhase(code)){ //移棋状态
        set<pair<int, int> > * moveNode = allValidMoveNode(code, color); //找出所有可能挪动的棋子（全部黑棋，全部白棋）
        for (std::set<pair<int, int> >::iterator it=moveNode->begin(); it!=moveNode->end(); ++it) {//对于每一个可能挪动棋子
            pair<int, int> from = make_pair(it->first, it->second);
            std::set<pair<int, int> > * validNextPoint = validNextMove(code, it->first, it->second);//找出每个可能挪动棋子的下一步可能移动坐标
            //生成可能状态并储存
            for (std::set<pair<int, int> >::iterator it2=validNextPoint->begin(); it2!=validNextPoint->end(); ++it2) {
                nextStep->insert(addOneStepMOVE(code, from, make_pair(it2->first, it2->second)));
            }
            delete validNextPoint;
        }
        delete moveNode;
    } else { //下棋状态
        set<pair<int, int> > * addNode = allEmptyPosition(code); //找出所有可能下棋的位置（全部空白）
        //生成可能状态并储存
        for (std::set<pair<int, int> >::iterator it=addNode->begin(); it!=addNode->end(); ++it) { //有没有可能在这一步就避免对称呢？
            nextStep->insert(addOneStepADD(code, it->first, it->second, color));
        }
        //deleteSetPair(addNode);
    }
    return nextStep;
    
}

void growFrom2(pair<int, int> start, set<pair<int,int> >& nodeList, map<pair<int, int>, int>& edgeList) {
  
    nodeList.insert(pair<int,int>(-9841,0));
    nodeList.insert(pair<int,int>(-19682,0));

    std::queue<pair<int, int> > q;
    if (checkEndGame(start.first) == 0) {
        q.push(start);
        nodeList.insert(pair<int,int>(start.first,start.second));
    }
    
    //int i = 0;
    while (! q.empty()) {
        pair<int, int> s = q.front();
        q.pop();
        int nextColor = 0;
        if (s.second == 1) {
            nextColor = 2;
        } else {
            nextColor = 1;
        }
        std::set<int> * possibleSet = getNextSteps(s.first, nextColor);
        // for (std::set<int>::iterator it=possibleSet->begin(); it!=possibleSet->end(); ++it) {
        //   cout <<  DecToTer(*it) << "State "<<checkEndGame(*it) << endl;
        //   cout << "find  " << nodeList.count(*it) << endl;
        // }
        for (std::set<int>::iterator it=possibleSet->begin(); it!=possibleSet->end(); ++it) {
            
            if (checkEndGame(*it) == 1) {
              //cout << "1"<< endl;
                pair<int, int> transit(s.first, -9841);
                edgeList[transit] = nextColor;
            } else if (checkEndGame(*it) == 2) {
                //cout << "2"<< endl;
                pair<int, int> transit(s.first, -19682);
                edgeList[transit] = nextColor;
            } else {
                std::set<pair<int,int> >::iterator it2 = nodeList.find( pair<int,int>(*it,nextColor) );
                if (it2 != nodeList.end() ) {
                    //cout << "else continue 1"<< endl;
                    pair<int, int> transit(s.first, *it);
                    edgeList[transit] = nextColor;
                } else {
                    //cout << "else continue 2"<< endl;
                    nodeList.insert(pair<int,int>(*it,nextColor));
                    pair<int, int> transit(s.first, *it);
                    edgeList[transit] = nextColor;
                    pair<int, int> state(*it, nextColor); //需不需要用new？
                    q.push(state);
                }
            }
        }
        //i++;

    }
}

int main() 
{
    set<pair<int,int> >  nodeList;
    map<pair<int, int>, int> edgeList; 
    pair<int, int> startState(10719, 1);
    growFrom2(startState,nodeList, edgeList);
    
    // for (std::set<pair<int,int> > *::iterator it=nodeList.begin(); it!=nodeList.end(); ++it) {
    //   cout << "(" << DecToTer(it->first) << ") " << "(" << it->first << ")" << endl;
    // }
    
    
    for (std::map<pair<int, int>, int>::iterator it=edgeList.begin(); it!=edgeList.end(); ++it) {
      cout << "from (" << DecToTer((it->first).first) << ") to (" <<DecToTer((it->first).second) << ") : " << it->second << endl;
    }
    // std::set<int> * one = getNextSteps(10881, 1);
    // cout << checkEndGame(10881) << endl;
    // for (std::set<int>::iterator it=one->begin(); it!=one->end(); ++it) {
    //   cout << "(" << DecToTer(*it) << ")" << endl;
    // }
    // int is = addOneStepMOVE(11463, make_pair<int, int>(1,2), make_pair<int, int>(1,1));
    // cout << DecToTer(is) << endl;
    return 0;
}
*/