# ifndef GRAPH_HPP
# define GRAPH_HPP

# include <utility>
# include <vector>
# include <queue>
# include <map>
#include <unordered_map>

#include <functional>
#include <cstddef>

# include <iostream>
# include <math.h>

using namespace std;

# define MAX_INT = 2147483647

/* 
    NodeT: the type of datas stored at the node
    EdgeT(TBD): the type of length of edges between nodes
    Compare: the class indicating how we compare two edges
*/

template<class NodeT, class Compare = std::less<double>>
class UndirGraph
{
private:

    /*
     node 1:
     [
        key_1 = 1
        [... data... ]
        adjList_1 := [
                      ...
                      (i, (i, val_i)),
                      ...
                      (j, (j, val_j)),
                      ...
                     ]
     ]

      |
     \ /

     node i
     [
        key_i = i
        ...
     ]

      |
     \ /

     ...

      |
     \ /

     node n:
     [
        key_n = n
        ...
     ]

    */

    struct node
    {
        NodeT* data;

        /* 
            int: the sequence number of the adjacent node
            double: the length of this edge
            Compare: how we compare between edges when implementing polymorphism
        */
        map<int, double> adjList;
        ~ node(){ delete data; }
    };
    
    map<int, node> nodes;

public:
    UndirGraph(/* args */){ }
    ~UndirGraph(){}

    /*
        add a node (update if exists)
        seqNum: the sequence number of this node
        data: the data stored in this new node
        
    */
    bool addNode(int seqNum, NodeT data)
    {
        typename map<int, node>::const_iterator itr;
        node tmp;
        tmp.data = new NodeT(data);

        /* true if add a new node; false if the node already exists */
        return nodes.insert(pair<int, node>(seqNum, tmp)).second;
    }
    
    /*
        we might also want to pass an pointer to it
    */
    bool addNode(int seqNum, NodeT* data)
    {
        node tmp;
        tmp.data = data;

        /* true if add a new node; false if the node already exists */
        return nodes.insert(pair<int, node>(seqNum, tmp)).second;
    }


    /* node, node, weight */
    bool addEdge(int seqNum1, int seqNum2, double val)
    {
        typename map<int, node>::iterator itr1, itr2;
        /* check whether we have this node, insert it with empty data if no such one */
        itr1 = nodes.find(seqNum1);
        if(itr1 == nodes.end())
        {
            node tmp;
            tmp.data = nullptr;
            itr1 = nodes.insert(pair<int, node>(seqNum1, tmp)).first;
        }

        itr2 = nodes.find(seqNum2);
        if(itr2 == nodes.end())
        {
            node tmp;
            tmp.data = nullptr;
            itr2 = nodes.insert(pair<int, node>(seqNum2, tmp)).first;
        }

        return
                (itr1->
                   second.adjList.insert
                   (make_pair(seqNum2, val))).second
                &&
                (itr2->
                        second.adjList.insert
                        (make_pair(seqNum1, val))).second;

    }

    int getSize()
    {
        return nodes.size();
    }

    void printGraph()
    {
        cout << "Nodes' Number\tAdjacent Edges";
        typename map<int, node> :: iterator itr;
        for(itr = nodes.begin(); itr != nodes.end(); ++itr)
        {
            cout << itr -> first << "\t\t";

            typename map<int, double> :: iterator subItr;
            for (subItr = itr -> second.adjList.begin();
                    subItr != itr -> second.adjList.end(); ++subItr)
            {
                cout << '(' << subItr -> first << ", " << subItr ->second << ")  ";
            }
            cout << '\n';
        }
        cout << '\n';
    }


private:
    struct tmpNode
    {
        double val;
        int num;
        tmpNode(double v, int s)
        {
            val = v;
            num = s;
        }
        friend bool operator < (const tmpNode &a, const tmpNode &b) {
            return a.val > b.val;
        }
    };

public:
    /*
     return value:
         first: seqNum of a node;
         second: current value of a node;
    */
    vector<pair<int, double>> runDijkstra(int seqNum)
    {
        typename map<int, node>::iterator itr;
        itr = nodes.find(seqNum);
        if(itr == nodes.end())
            cout << "Wrong nodes";


        vector<pair<int, double>> nodeSet;
        vector<bool> pathFound;
        typename map<int, node> :: iterator itr1;

        int src = 0, i=0;
        unordered_map<int, int> hashtable;

        /* initialization */
        for(itr1 = nodes.begin(); itr1!=nodes.end(); itr1++, i++)
        {
            nodeSet.push_back(pair<int, double>(itr1 -> first, INFINITY));
            pathFound.push_back(false);
            if(itr == itr1)
                src = i;
            hashtable[itr1 -> first] = i;
        }

        priority_queue<tmpNode> q;
        q.push(tmpNode(0, src));
        while(!q.empty())
        {
            tmpNode tn = q.top();
            q.pop();
            if (pathFound[tn.num])
                continue;

            nodeSet[tn.num].second = tn.val;
            pathFound[tn.num] = true;

            // cout << tn.num << ' ' << tn.val;
            //int seqN = tn.seqNum;
            typename map<int, double> :: iterator subItr;
            itr1 = nodes.find(nodeSet[tn.num].first);

            /* for every node adjacent to it */
            for(subItr = itr1 -> second.adjList.begin();
                subItr != itr1 -> second.adjList.end(); ++ subItr)
            {
                int i = hashtable[subItr -> first];
                if(pathFound[i])
                    continue;

                /* update nodeSet */
                if( nodeSet[tn.num].second + subItr -> second < nodeSet[i].second )
                {
                    nodeSet[i].second = nodeSet[tn.num].second + subItr -> second;
                    q.push(tmpNode(nodeSet[i].second, i));
                }

            }

        }

        return  nodeSet;
    }

};




# endif