#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>
#include "Graph.h"
#include "Traversals.h"

BFS::BFS(State* start){ 
    start_ = start;
    visitedStates.clear();
    visitedEdges.clear();
    states.clear();
}

BFS::BFS(stateSpace* graph) {
    start_ = graph->getStart();
    visitedStates.clear();
    visitedEdges.clear();
    states.clear();
}

spaceTraversal::Iterator BFS::begin() {
    spaceTraversal * bfs = new BFS(start_); 
    spaceTraversal::Iterator it(bfs, start_);
    return it; 
}


spaceTraversal::Iterator BFS::end() {
    return spaceTraversal::Iterator();
}

void BFS::add(State* state) { 
    states.push_back(state); 
    return;
}

State* BFS::pop() {
    if (states.empty()) return NULL;
    State* tmp = states.front();
    states.pop_front();
    return tmp;
}

State* BFS::peek() const {
    if (states.empty()) return NULL;
    return states.front();
}

bool BFS::empty() const {
    return states.empty();
}

////////

DFS::DFS(State* start){ 
    start_ = start;
    visitedStates.clear();
    visitedEdges.clear();
    states.clear();
}

DFS::DFS(stateSpace* graph) {
    start_ = graph->getStart();
    visitedStates.clear();
    visitedEdges.clear();
    states.clear();
}

spaceTraversal::Iterator DFS::begin() {
    spaceTraversal * dfs = new DFS(start_); 
    spaceTraversal::Iterator it(dfs, start_);
    return it; 
}


spaceTraversal::Iterator DFS::end() {
    return spaceTraversal::Iterator();
}

void DFS::add(State* state) { 
    states.push_front(state); 
    return;
}

State* DFS::pop() {
    if (states.empty()) return NULL;
    State* tmp = states.front();
    states.pop_front();
    return tmp;
}

State* DFS::peek() const {
    if (states.empty()) return NULL;
    return states.front();
}

bool DFS::empty() const {
    return states.empty();
}
