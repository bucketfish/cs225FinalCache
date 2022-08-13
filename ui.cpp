#include "ui.h"
#include "Nodes.h"
#include "Graph.h"

using namespace std;

game::game() {
    //default, empty board, player is 1(X) and moves first
    //_now = new State(0,2);
    State startState(0,2);
    _graph = new stateSpace(startState);
    stateSpace::growFrom2(*_graph,startState.getcc());
    _graph->pageRank();  
    _now = _graph->getStart();

    _player = 1;
    _cpu = 2;
    _curr = 1;
    _endGame = false;
    _winner = 0;

}

game::game(int code, int player, int curr) {
//     int color;
//     if (curr == 1) color = 2;
//     else color = 1;
//     State startState(code,color);
//     _graph = new stateSpace();
//     stateSpace::growFrom2(*_graph,startState.getcc());
//     _graph->pageRank();
//     _now = _graph->getStart();

//     _player = player;
//     if (_player == 1) _cpu = 2;
//     else _cpu = 1;

//     _curr = curr;
//     _endGame = false;
//     _winner = 0;
 }

game::game(State * start) {
	//_graph = &graph;
	_now = start;;
    if (start->getColor() == 1) _player = 2;
    else _player = 1;
	_curr = _player;
	_endGame = false;
	_winner = 0;	
}


game::~game() {
    delete _graph;
    delete _now;
}

//SUPER CHORUS TIME

void game::echoPlayerMove() {
    if (_now->important()) {
        cout<<"critical move! think twice\n";
    }

    //displayBoard();

    if (stateSpace::isMovePhase(_now->getCode())) {
        cout<<"YOUR MOVE\n input: pick a piece on position(#,#) and move it to (#,#) \n\n";
    } else {
        cout<<"YOUR MOVE\n input: put a piece on pisition(#,#) \n\n";
    }
}

void game::playerMove() {
    _curr = _player;
    if (stateSpace::isMovePhase(_now->getCode())) {
        
        while (true) {
            std::string piece;
            cin>>piece;
            //cout<<"\n";

            std::string position;
            cin>>position;
            cout<<"\n";

            //char * from = (char *) piece.c_str();
            //char * to = (char *) position.c_str();
            int valid = 0;
            if (!piece.empty() && !position.empty()) {
                int newCode = stateSpace::addOneStepMOVE(_now->getCode(), 
			                                pair<int,int>(stateSpace::toInt(piece.substr(0,1)), stateSpace::toInt(piece.substr(2,3))), 
			                                pair<int,int>(stateSpace::toInt(position.substr(0,1)), stateSpace::toInt(position.substr(2,3))));
                for (State * next : *_now->getNext()) {
                    //cout<<next->getCode()<<"\n"; 
                    if (next->getCode() == newCode) {
                        _now = next;
                        valid = 1;
                        break;
                    }
                    //break;
                }
                if (valid == 1) break;
                cout<<"impossible move: enter again\n";
            } else {
                cout<<"invalid input: enter again\n";
            }
        }

    } else {

        while (true) {
            std::string position;
            cin >> position;
            cout<<"\n";
            //cout<<position<<"\n";

            //char* pos = (char*) position.c_str();
            int valid = 0;
	        if (!position.empty()) {
                int newCode = stateSpace::addOneStepADD(_now->getCode(), stateSpace::toInt(position.substr(0,1)), stateSpace::toInt(position.substr(2,3)), _player);
		        //cout<<pos[0]<<" "<<pos[1]<<"\n";
                for (State * next : *_now->getNext()) {
                   // cout<<next->getCode()<<"\n";
			        if (next->getCode() == newCode) {
                        _now = next;
                        valid = 1;
                        break;
                    }
                    
                }
                //_curr = _now->getColor();
                if (valid == 1) break;
                cout<<"impossible move: enter again\n";
            } else {
                cout<<"invalid input: enter again\n";
            }
        
	}
	}	

	displayBoard();
}

void game::cpuMove() {
    _curr = _cpu;
    //cout<<"CPU M"
    int newCode = stateSpace::bestMove(_now->getCode(), _player);
    //cout<<newCode<<"\n";
    for (State * next : *_now->getNext()) {
        if (next->getCode() == newCode) _now = next;
    }

}


void game::echoCPUMove() {
    cout<<"CPU MOVE\n\n";
    displayBoard();
}

void game::displayBoard() {
    // int ** board = _now->deRenderCode(_now->getCode());

    // for (int i = 0; i < 2; i++) {
    //     for (int j = 0; j < 2; j++) {
    //         cout<<board[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    
    // delete board;

    stateSpace::drawBoard(_now->getCode());
    cout<<"\n";
}

bool game::endGame() {
    _winner = stateSpace::checkEndGame(_now->getCode());
    return (_winner != 0);
}

void game::echoEndGame() {
    cout<<"ENDGAME\n ";
    if (_winner == _player) cout<<"YOU WIN";
    else cout<<"YOU LOSE";

    cout<<"\n";
}


void game::process() {
    //cout<<"/////////////////////////////////"
    cout<<"\n////////THREE-MEN MORRIS////////\n";
    cout<<"RULES:\n";
    cout<<"1) put your pieces on any empty position on the board, one at a time;\n";
    cout<<"2) after 3 pieces are put, move them, one piece and one step at a time, \n";
    cout<<"   VERTICALLY, HORIZONTALY or along the DIAGONAL LINE of the board. \n";
    cout<<"try to align all your piece in a line to win.\n";
    cout<<"HAVE FUN!\n";
    cout<<"///////////////////////////////\n";


    displayBoard();
    while (!_endGame) {

        if (_curr == _player) {
            echoPlayerMove();
            playerMove();
            //update(); 
            //displayBoard();
            _curr = _cpu;
        } else {
            cpuMove(); 
            echoCPUMove();
            //update();
            //displayBoard();
            _curr = _player;
        }
        if (endGame()) break;
    }

    echoEndGame();
}
