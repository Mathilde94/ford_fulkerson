#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include<algorithm>

using namespace std;
#define FOR(i,a,b) for(int i=a;i<b;i++)

class Edge{
public:
  string source;
  string sink;
  int capacity;
  string name;
  Edge * reverse;
  Edge(string src, string snk,int cap,Edge * rev){
    source=src;
    sink=snk;
    capacity=cap;
    reverse=rev;
    name=src+snk;
  }
  bool operator==(Edge a) const {
    return sink==a.sink && source==a.source;
  }
  bool operator<(Edge a) const{
    return name<a.name;
  }
};

bool edgeIsInVector(Edge * edge, vector<Edge *> v){
  return find(v.begin(),v.end(),edge)!=v.end();
}


class pathElements{
public:
  vector<Edge *> edges;
  int residual;
  pathElements(vector<Edge *> path,int res){
    edges=path;
    residual=res;
  }
};


class Network{
public:
  map<string, vector<Edge *> > adjacent;
  set<string> setVertex;
  map<Edge *, int> flow;

  Network(){}

  void addEdges(string src,string snk, int cap){
    Edge * edge = new Edge(src,snk,cap,NULL);
    flow[edge]=0;
    Edge * reverseEdge =new Edge(snk,src,cap,edge); 
    flow[reverseEdge]=0;
    edge->reverse=reverseEdge;

    adjacent[src].push_back(edge);
    adjacent[snk].push_back(reverseEdge);
    setVertex.insert(src);
    setVertex.insert(snk);
  }
  
  void display(){
    for(set<string>::iterator it=setVertex.begin();it!=setVertex.end();it++){
      cout << *it <<" Adjacents: ";
      for (vector<Edge *>::iterator it_edges=adjacent[*it].begin();it_edges!=adjacent[*it].end();it_edges++){
        cout << (*it_edges)->sink <<' ';
      }
      cout << endl;
    }
  }

  pathElements findPath(string src, string snk, vector<Edge *> path,int minResidual){
    if (src==snk) {
      pathElements pathFinal = pathElements(path,minResidual);
      return pathFinal;
    }
    for (vector<Edge *>::iterator it=adjacent[src].begin();it!=adjacent[src].end();it++){
      int residual = (*it)->capacity - flow[(*it)];
      Edge * reverse =(*it)->reverse;
      if (residual>0 && !( edgeIsInVector( (*it), path) || edgeIsInVector(reverse,path)) ){
        vector<Edge *> path2 = path;
        path2.push_back((*it));
        pathElements result = findPath((*it)->sink,snk,path2,min(minResidual,residual));
        if (!result.edges.empty()){
          return result;
        }
      }
    }
    vector<Edge *> result;
    pathElements pathFinal = pathElements(result,minResidual);
    return pathFinal;
  }


  int max_flow(string source,string sink){
    vector<Edge *> res;
    pathElements p = findPath(source,sink,res,90000); 
    while (!p.edges.empty()){
      for (vector<Edge *>::iterator it=p.edges.begin();it!=p.edges.end();it++){
        flow[(*it)]+=p.residual;         
        flow[(*it)->reverse]-=p.residual;
      }
      vector<Edge *> res;
      p= findPath(source,sink,res,90000);
    }                                                                                                                                                                        
    int flowRes(0);
    for (vector<Edge *>::iterator it=adjacent[source].begin();it!=adjacent[source].end();it++){                                                                                
      flowRes+=flow[(*it)];          
    }                                                                                                                                                                         
    return flowRes;
  }      
      

};


int main(){
  
  Network N= Network();
  N.addEdges("s","o",3);
  N.addEdges("s","p",4);
  N.addEdges("o","p",4);
  N.addEdges("o","q",5);
  N.addEdges("p","r",3);
  N.addEdges("r","t",3);
  N.addEdges("q","r",4);
  N.addEdges("q","t",3);

  //N.display();
  cout <<N.max_flow("s","t")<<endl;
  return 0;
}
