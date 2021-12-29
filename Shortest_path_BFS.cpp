#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <ctime>

using namespace std;

// class to represent a graph.
class graph
{

private:
    int v;
    // array of vectors is used to store the graph in the form of an adjacency list
    vector<int> *adj;

public:
    // constructor.
    graph(int v)
    {
        this->v = v;
        adj = new vector<int> [v];
    }

    // set all the edges.
    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void print_path(int, int);
    bool BFS(int, int, int*);
};

// function to print the shortest path.
void graph::print_path(int source, int dest)
{

    // it stores parent for each vertex to trace the path.
    int *parent = new int[v];

    // BFS returns false means destination is not reachable.
    if(BFS(source, dest, parent) == false)
    {
        cout << "Destination is not reachable from this source.\n";
        return;
    }

    // stack to store the shortest path.
    stack<int> st;

    // tracing the path.
    while(parent[dest] != -1)
    {
        st.push(dest);
        dest = parent[dest];
    }

    // printing the path via stack and clearing the stack at the same time.
    cout << source;
    while(!st.empty())
    {
        cout << " " << st.top();
        st.pop();
    }

    return;
}

// this function returns if destination is reachable or not
// additionally it sets the parent array to say the path (if exist).
bool graph::BFS(int source, int dest, int parent[])
{

    queue<int> q;
    int *visited = new int[v];

    // setting all the vertices as non-visited
    // and parents of all vertices as -1.
    for(int i=0; i<v; i++)
    {
        visited[i] = 0;
        parent[i] = -1;
    }

    // pushing the source into the queue and mark it as visited.
    q.push(source);
    visited[source] = 1;

    // loop executes until all vertices are traversed.
    while(!q.empty())
    {

        // popping one element from queue.
        int temp = q.front();
        q.pop();

        // check for all adjacents.
        for(int k: adj[temp])
        {
            if(visited[k] == false)
            {

                // pushing into queue and mark it visited as well as
                // set the parent of the adjacent in parent array.
                q.push(k);
                visited[k] = true;
                parent[k] = temp;

                // if destination is reached, returns true
                // to state that there exist a path.
                if(k == dest)
                    return true;
            }
        }
    }

    // if destination is not reachable.
    return false;
}

// driver function.
int main()
{

    // sample graph.
    graph g(49);

    g.add_edge(0, 1);
    g.add_edge(0, 3);
    g.add_edge(3, 4);
    g.add_edge(3, 7);
    g.add_edge(4, 7);
    g.add_edge(4, 6);
    g.add_edge(4, 5);
    g.add_edge(1, 2);
    g.add_edge(7, 6);
    g.add_edge(6, 5);
    g.add_edge(1, 8);
    g.add_edge(8, 9);


    g.print_path(6, 9);

    return 0;
}
