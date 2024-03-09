// Author: Nikola Tunguz
// Date: May 10, 2023
// Purpose: Graph data structure declarations.

#ifndef GRAPH_H
#define GRAPH_H


#include <stack>
#include <queue>

#include "GraphInterface.h"
#define MAX_VERTICES 999
    
template <class LabelType>
class Graph : public GraphInterface<LabelType>{
    LabelType* vertexArray; 
    int **adjacencyMatrix;
    int numVertices = 0;
    int numEdges = 0;

    void removeVertex(int vertexIndex);

    public:
        Graph();   
        ~Graph();  

        int getNumVertices() const;  
        int getNumEdges() const;     
        bool add(LabelType start, LabelType end, int edgeWeight); 
        bool remove(LabelType start, LabelType end); 
        int getEdgeWeight(LabelType start, LabelType end) const; 
        void depthFirstTraversal(LabelType start, void visit(LabelType&) );
        void breadthFirstTraversal(LabelType start, void visit(LabelType&) );
     
};

#include "Graph.cpp"
#endif