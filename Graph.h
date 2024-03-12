/*
Author: Nikola Tunguz
Purpose: Templated graph data structure declarations using an adjacency matrix.
*/
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
        //constructor and destructor
        Graph();   
        ~Graph();  

        //basic getters
        int getNumVertices() const;  
        int getNumEdges() const;     
        //adding and removing edges
        bool add(LabelType start, LabelType end, int edgeWeight); 
        bool remove(LabelType start, LabelType end); 
        //retrieving information
        int getEdgeWeight(LabelType start, LabelType end) const; 
        void depthFirstTraversal(LabelType start, void visit(LabelType&) );
        void breadthFirstTraversal(LabelType start, void visit(LabelType&) );
     
};

#include "Graph.cpp"
#endif