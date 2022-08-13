#pragma once

#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <map>

#include "Graph.h"
#include "Nodes.h"                                                                                                                                                                                                                                                                                         

class BFS : public spaceTraversal {
    public:
        BFS(State* start);
        BFS(stateSpace* graph);
        //BFS(const stateSpace & graph, const & State start);

        spaceTraversal::Iterator begin();
        spaceTraversal::Iterator end(); 

        void add(State * state);
        State* pop();
        State* peek() const;
        bool empty() const;

    private: 

};

class DFS : public spaceTraversal {
    public:
        DFS(State* start);
        DFS(stateSpace* graph);
        //DFS(const stateSpace & graph, const & State start);

        spaceTraversal::Iterator begin();
        spaceTraversal::Iterator end();

        void add(State * state);
        State* pop();
        State* peek() const;
        bool empty() const;
    private:
};