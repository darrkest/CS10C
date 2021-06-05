#include "Graph.h"

using namespace std;

Graph::Graph() {}

Graph::Graph(ifstream &inFS) {
    if (!inFS.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    int numNodes;
    inFS >> numNodes;                                               
    int numEdges;
    inFS >> numEdges;                                               

    map<string, int> graph;                                         
    string currInput;
    Vertex currVert;
    for (int i = 0; i < numNodes; ++i) {                            
        inFS >> currInput;
        currVert.label = currInput;                                 
        vertices.push_back(currVert);                               
        graph[currInput] = i;                                       
    }

    string sourceVert;
    string sinkVert;
    int cost;
    int index;
    for (int i = 0; i < numEdges; ++i) {                            
        inFS >> sourceVert >> sinkVert >> cost;                     
        index = graph[sourceVert];                                  
        pair<int, int> newNode(graph[sinkVert], cost);              
        vertices.at(index).neighbors.push_back(newNode);            
    }

}

Graph::~Graph() {
    while (vertices.size() != 0) {
        vertices.pop_back();
    }
}

void Graph::output_graph(const string &outputFilename){
 ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,0);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());   
}

void Graph::visualizeTree(ofstream & outFS, int n){
    
    if(vertices[n].color == "BLACK")
        return;
    vertices[n].color = "BLACK";
    outFS << vertices[n].label << "[label=\"" << vertices[n].label << ", " << vertices[n].distance << "\"];" << endl; 
    for(list<pair<int,int>>::const_iterator it = vertices[n].neighbors.begin(); it != vertices[n].neighbors.end(); it++)
    {
        outFS<< vertices[n].label <<" -> " << vertices[(*it).first].label <<";"<<endl;
        visualizeTree(outFS,(*it).first);
    }
}


void Graph::bfs() {
    for (unsigned int i = 0; i < vertices.size(); ++i) {
        vertices.at(i).color = "WHITE";
        vertices.at(i).distance = INT_MAX;
        vertices.at(i).prev = nullptr;
    }

    vertices.at(0).color = "GRAY";
    vertices.at(0).distance = 0;
    vertices.at(0).prev = nullptr;

    queue<Vertex> vertQueue;
    vertQueue.push(vertices.at(0));
    while (!vertQueue.empty()) {
        Vertex curr = vertQueue.front();
        vertQueue.pop();
        list<pair<int, int>>::iterator i = curr.neighbors.begin();
        for (i = curr.neighbors.begin(); i != curr.neighbors.end(); ++i) {
            if (vertices.at(i->first).color == "WHITE") {
                vertices.at(i->first).color = "GRAY";
                vertices.at(i->first).distance = curr.distance + i->second;
                vertices.at(i->first).prev = &curr;
                vertQueue.push(vertices.at(i->first));
            }
        }
        curr.color = "BLACK";
    }
}