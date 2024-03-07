#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <algorithm>


typedef struct node{

    int dest;
    int distance;

}Node;

std::map<int , std::list<Node>> graph; // Source Node -> Destination Node , Distance
std::vector<bool> visitedGraph ;
std::vector<int> connections ;
int  maxPtpLinks;

int networkCost(int len){


    //confirm if all nodes are visited
    if(std::all_of(visitedGraph.begin(), visitedGraph.end(),[](bool val) { return val; }))
        return len;

    std::list<Node> temp;
    int l = 100000;
    std::pair<int, std::list<Node>> gF;
    int dest;
    for (const auto& g : graph) {

        if(visitedGraph[g.first - 1]){

            for (const auto& neighbor : graph) {
                gF = neighbor;
                if (!visitedGraph[gF.first - 1] && connections[g.first - 1] < maxPtpLinks){
                    visitedGraph[gF.first - 1] = true;
                    //std::cout << "NODE VISITED \n";
                    connections[g.first - 1]++;
                    connections[gF.first - 1]++;
                    temp = graph.at(g.first);

                    dest = gF.first;
                    //std::cout << "LOOKING FOR DISTANCE BEETWEN NODES \n";
                    auto it = std::find_if(temp.begin(), temp.end(), [dest](const Node& element) {
                        return element.dest == dest;
                    });
                    std::cout << "DISTANCE ACHIEVED: " << (*it).distance << "\n";
                    l = std::min(l, networkCost(len + (*it).distance));
                    connections[g.first - 1]--;
                    connections[gF.first - 1]--;
                    visitedGraph[gF.first - 1] = false;
                }
            }
        }

        
        //std::cout << "UNMARKING NODE \n";

    }


    return l;
}

int main() {

    int nNodes, ptpLinks;
    int sourceNode, newSourceNode;


    //while(){

        visitedGraph.push_back(true); // first node is visited
        connections.push_back(0);
        for (int i = 1; i < nNodes; ++i){

            visitedGraph.push_back(false);
            connections.push_back(0);
        }


        std::cin >> nNodes >> ptpLinks >> maxPtpLinks;
        for (int i = 0; i < ptpLinks; ++i) {

            Node tempNode;
            std::cin >> sourceNode >> tempNode.dest >> tempNode.distance;
            graph[sourceNode].push_back(tempNode);
            newSourceNode = tempNode.dest;
            tempNode.dest = sourceNode;
            graph[newSourceNode].push_back(tempNode);
        }

        //graph.clear();
        //visitedGraph.clear();

       std::cout << networkCost(0) << "\n";
    //}

    // Print the graph for verification
    /*for (const auto& g : graph) {
        std::cout << "Source Node " << g.first << " has destinations: ";
        for (const auto &node : g.second) {
            std::cout << "Destination: " <<node.dest << " Distance: " << node.distance << " ";
        }
        std::cout << "\n";
    }*/



    return 0;
}
