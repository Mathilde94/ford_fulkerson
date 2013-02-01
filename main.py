class Edge():
    def __init__(self,source, sink, capacity,name, redge=None):
        self.source=source
        self.sink=sink
        self.capacity=capacity
        self.name=name
        self.redge=redge

class Graph():
    def __init__(self, adj={}, flows={}):
        self.adj=adj
        self.flows=flows

    def getEdges(self,edge):
        return self.adj[edge]

    def addVertex(self,u):
        self.adj[u]=[]
    
    def addEdges(self,u,v,c):
        a=Edge(u,v,c,str(u)+"--"+str(v),None)
        b=Edge(v,u,c,str(v)+"--"+str(u),None)
        a.redge=b
        b.redge=a
        self.adj[u].append(a)
        self.adj[v].append(b)
        self.flows[a]=0
        self.flows[b]=0


    def findPath(self,source,sink,path):
        if source==sink:
            return path
        for i in self.getEdges(source):
            residual=i.capacity-self.flows[i]  
            if residual>0 and not ((i, residual) in path or i.redge in [k[0] for k in path] ):
                result=self.findPath(i.sink,sink,path+[(i,residual)])
                if result!=None:
                    return result
                
    def max_flow(self, source, sink):
        path=self.findPath(source, sink, [])
        while path!=None:
            flow=min(res for edge,res in path)
            for i,resi in path:
                self.flows[i]+=flow
                self.flows[i.redge]-=flow
            path=self.findPath(source,sink,[])
        return sum(self.flows[i] for i in self.getEdges(source))

G=Graph()
map(G.addVertex,["s","o","p","q","r","t"]) 
G.addEdges("s","o",3)   
G.addEdges("s","p",4)
G.addEdges("o","p",4)
G.addEdges("o","q",5)
G.addEdges("p","r",3)
G.addEdges("r","t",3)
G.addEdges("q","r",4)
G.addEdges("q","t",3) 
print G.max_flow("s","t")

