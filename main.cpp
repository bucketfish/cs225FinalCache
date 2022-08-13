// #include <set>
// #include <iostream>
// #include <fstream>
// #include <string>
// #include <map>
#include "ui.h"
#include "Nodes.h"
#include "Graph.h"

// /*
// 运行注意合集：
// 1. 使用clang++ main.cpp Graph.cpp Nodes.cpp ui.cpp -o main 然后输入./main就可以运行。
// 2. 在输入初始状态时请不要直接输入startState（0，1），你可以从100000000状态开始，即 startState（6561，1）。
// 3. 如果你想运行固定步长的值，请在Graph.cpp中growFrom调整i值，如果想整个遍历请把i删掉。
//     请注意：i仅代表queue中元素的数量（while运行次数）,并不带表真正步长值。
// */




fstream ofs;

int main() 
{
    State startState(0,2);
    stateSpace spaceFromEmpty(startState);
    stateSpace::growFrom2(spaceFromEmpty,startState.getcc());
    spaceFromEmpty.pageRank();
    game * theGame = new game(spaceFromEmpty.getStart());
    theGame->process();
    
    // ofs.open("out_nodelist.txt", ios::out | ios::trunc);
    // double a = 5.0/10.0;
    // ofs<<setprecision(2)<<a<<"\n";
    // for (std::map<pair<int,int>, State* >::iterator it= spaceFromEmpty.getNodeList()->begin(); it!=spaceFromEmpty.getNodeList()->end(); ++it) {
    //     ofs<<"(" << stateSpace::DecToTer((it->first).first) << ") " << "(" << (it->first).first << ") ";
    //     if ((it->second)->important()) {
    //       ofs<<" critical!";
    //     }
    //     //ofs<<"rank :" <<setprecision(5)<<(it->second)->getRank();
    //     ofs<<"\n"; 
    // } 
    // ofs.close(); 
    
    // ofs.open("out_edgelist.txt", ios::out | ios::trunc);
    // for (std::map<pair<int, int>, int>::iterator it=spaceFromEmpty.geteEdgeList()->begin(); it!=spaceFromEmpty.geteEdgeList()->end(); ++it) {
    //   ofs << "from (" << stateSpace::DecToTer((it->first).first) /*<< "/"  << (it->first).first*/ <<") to (" <<stateSpace::DecToTer((it->first).second) << ") : " << it->second << "\n";
    // }
    // ofs.close();

    //cout << stateSpace::DecToTer(stateSpace::bestMove(stateSpace::TerToDec(10102221), 2 ) )<<endl;

    // std::set<State *> * next = spaceFromEmpty.getStart()->getNext();
    // for (std::set<State *>::iterator it=next->begin(); it!=next->end(); ++it) {
    //   cout << stateSpace::DecToTer((*it)->getCode() ) <<endl;
    // }

    
    return 0;
}
