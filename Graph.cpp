/*
Author: Nikola Tunguz
Purpose: Templated graph data structure function implementations.
*/

//default constructor
template <class LabelType>
Graph<LabelType>::Graph(){
    numVertices = 0;
    numEdges = 0;
    vertexArray = new LabelType[MAX_VERTICES];

    adjacencyMatrix = new int*[MAX_VERTICES];
    for( int i = 0; i < MAX_VERTICES; i++){
        adjacencyMatrix[i] = new int[MAX_VERTICES];
    }
}    
//destructor
template <class LabelType>
Graph<LabelType>::~Graph(){
    for(int i = 0; i < MAX_VERTICES; i++){
        delete[] adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;
}

//gets number of vertices in graph
template <class LabelType>
int Graph<LabelType>::getNumVertices() const{
    return numVertices;
}
//gets number of edges
template <class LabelType>
int Graph<LabelType>::getNumEdges() const{
    return numEdges;
}
//adding edge to the graph
template <class LabelType>
bool Graph<LabelType>::add(LabelType start, LabelType end, int edgeWeight) {
     
    bool startExist = false;
    bool endExist = false;
    int startIndex = -1;
    int endIndex = -1;

    for(int i = 0; i < numVertices; i ++){
        if( vertexArray[i] == start){
            startExist = true;
            startIndex = i;
        }
        if(vertexArray[i] == end){
            endExist = true;
            endIndex = i;
        }
    }
    //if doesnt exist, create new vertices & add to array
    if(startExist == false){
        vertexArray[numVertices] = start;
        startIndex = numVertices;
        numVertices++;
    }
    if(endExist == false){
        vertexArray[numVertices] = end;
        endIndex = numVertices;
        numVertices++;
    }
   
    //connect vertices in matrix
    adjacencyMatrix[startIndex][endIndex] = edgeWeight;
    adjacencyMatrix[endIndex][startIndex] = edgeWeight;
    numEdges++;
     
    return true;
}
//removing edges
template <class LabelType>
bool Graph<LabelType>::remove(LabelType start, LabelType end){
    // find indices
    int startIndex = -1;
    int endIndex = -1;
    for(int i = 0; i < numVertices; i++){
        if( vertexArray[i] == start){
            startIndex = i;
        }
        if(vertexArray[i] == end){
            endIndex = i;
        }
    }

    //if both vertices exist, remove, cant only have one vertex exist, connection would not exist
    if(startIndex != -1 && endIndex != -1) {
        //if connection exists set them to 0
        if(adjacencyMatrix[startIndex][endIndex] != 0){
            numEdges--;
            adjacencyMatrix[startIndex][endIndex] = 0;
            adjacencyMatrix[endIndex][startIndex] = 0;
        }

        //checking to remove start vertex
        bool removeStartVertex = true;
        for( int i = 0; i < numVertices - 1; i++){
            //if vertex has any remaining connection, do not remove
            if(adjacencyMatrix[startIndex][i] != 0){
                removeStartVertex = false;
            }   
        }
        //checking to remove end vertex
        bool removeEndVertex = true;
        for( int i = 0; i < numVertices - 1; i++){
            //if vertex has any remaining connection, do not remove
            if(adjacencyMatrix[i][endIndex] != 0){
                removeEndVertex = false;
            }
            
        }
        //remove from vertex array, and adjust adjacency matrix similarly
        if(removeStartVertex){
            removeVertex(startIndex);
        }
        if(removeEndVertex){
            removeVertex(endIndex);
        }

        return true;
    }
    //if doesnt exist, return false
    return false;
}
//retrieving edge weight information from two verticies
template <class LabelType>
int Graph<LabelType>::getEdgeWeight(LabelType start, LabelType end) const{
    int edgeWeight = 0;
    int startIndex = -1;
    int endIndex = -1;

    //find indices of vertices
    for(int i = 0; i < numVertices; i++){
        if(vertexArray[i] == start){
            startIndex = i;
        }
        if(vertexArray[i] == end){
            endIndex = i;
        }
    }

    //if vertex exist, find their connection weight
    if(startIndex != -1 && endIndex != -1){
        edgeWeight = adjacencyMatrix[startIndex][endIndex];
        //if no connection, max out the weight
        if(edgeWeight == 0){
            throw std::invalid_argument("Connection does not exist.");
        }

    }
    else{
        //throw exception if doesnt exist
        throw std::invalid_argument("Either start or end vertex does not exist.");
    }
   
    return edgeWeight;
    
}
//traversing the graph depth first
template <class LabelType>
void Graph<LabelType>::depthFirstTraversal(LabelType start, void visit(LabelType&) ){
    int currentIndex = -1;
    LabelType currentVertex;
    std::stack<LabelType> stack;
    bool seenArray[numVertices];

    for(int i = 0; i < numVertices; i++){
        if(start == vertexArray[i]){
            currentIndex = i;
        }
    }

    stack.push(start);
    visit(start);
    seenArray[currentIndex] = true;

    while( !stack.empty() ){
        bool flag = false;
        currentVertex = stack.top();
        for(int i = 0; i < numVertices; i++){
            if(currentVertex == vertexArray[i]){
                currentIndex = i;
            }
        }

        for( int i = 0; i < numVertices; i++){
            if(adjacencyMatrix[currentIndex][i] != 0 && seenArray[i] == false && flag == false){
                flag = true;
                currentVertex = vertexArray[i];
                seenArray[i] = true;
            }
        }
        if(flag){
            stack.push(currentVertex);
            visit(currentVertex);
            for(int i = 0; i < numVertices; i++){
                if(currentVertex == vertexArray[i]){
                    currentIndex = i;
                }
            }
        }
        else{
            stack.pop();
        }
    }
}

//traversing the graph breadth first
template <class LabelType>
void Graph<LabelType>::breadthFirstTraversal(LabelType start, void visit(LabelType&) ){
    int currentIndex = -1;
    LabelType currentVertex;
    std::queue<LabelType> queue;
    bool seenArray[numVertices];

    for(int i = 0; i < numVertices; i++){
        if(start == vertexArray[i]){
            currentIndex = i;
        }
    }

    queue.push(start);
    seenArray[currentIndex] = true;
    
    while( !queue.empty() ){
        currentVertex = queue.front();
        visit(currentVertex);
        queue.pop();

        for(int i = 0; i < numVertices; i++){
            if(currentVertex == vertexArray[i]){
                currentIndex = i;
            }
        }

        for(int i = 0; i < numVertices; i++){
            if( adjacencyMatrix[currentIndex][i] != 0 && seenArray[i] == false){
                queue.push(vertexArray[i]);
                seenArray[i] = true;
            }
        }
    }

    
}

//removing a vertex from the matrix (helper for remove)
template <class LabelType>
void Graph<LabelType>::removeVertex(int vertexIndex){
    //adjust matrix by shifting rows and columns
    //shift rows up
    for(int row = vertexIndex; row < numVertices; row++){
        for( int col = 0; col < numVertices; col++){
            adjacencyMatrix[row][col] = adjacencyMatrix[row + 1][col];
        }
    }
    
    //shift columns left
    for(int row = 0; row < numVertices; row++){
        for( int col = vertexIndex; col < numVertices; col++){
            adjacencyMatrix[row][col] = adjacencyMatrix[row][col + 1];
        }
    }

    //adjust vertexArray
    for(int i = vertexIndex; i < numVertices - 1; i++){
        vertexArray[i] = vertexArray[i + 1];
    }
    numVertices--;
}
