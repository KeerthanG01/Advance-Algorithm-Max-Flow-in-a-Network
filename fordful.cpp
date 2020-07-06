#include <vector>
#include <queue>
#include <limits>
#include <iostream>
#define WHITE 0
#define GRAY 1
#define BLACK 2

using namespace std;

class ford_fulkerson_implementation
{
private:
    int n;
    int e;
    queue<int> q;
    vector<vector<int>> capacity;
    vector<vector<int>> flow;
    vector<int> color;
    vector<int> augpath;

public:
    ford_fulkerson_implementation(int,vector<vector<int>>);
    int bfs(int, int);
    int max_flow(int,int);
};

ford_fulkerson_implementation::ford_fulkerson_implementation(int n,vector<vector<int>> capacity)
{
    this->n = n;
    this->capacity = capacity;
    flow.resize(n,vector<int>(n,0));
    augpath.resize(n,0);
}

int ford_fulkerson_implementation::bfs(int start, int target)
{
    //printf("Inside bfs\n");
    if(color.size() > 0)
    {
        color.clear();
    }
    
    for (int i = 0; i < n; i++)
    {
        color.push_back(WHITE);
    }
    augpath[start] = -1;
    int u, v;
    q.push(start);
    color[start] = GRAY;
    //printf("Entering while\n");
    while (!q.empty())
    {
        u = q.front();
        q.pop(); 
        color[u] = BLACK;
        //printf("u=%d queue size=%d\n",u,q.size());
        //printf("Entering for loop\n");
        for (v = 0; v < n; v++)
        {
            if (color[v] == WHITE && capacity[u][v] - flow[u][v] > 0)
            {
                q.push(v);
                color[v] = GRAY;
                augpath[v] = u;
            }
        }
        //printf("Exiting for loop\n");
    }

    return color[target]==BLACK;
}

int ford_fulkerson_implementation::max_flow(int source,int sink)
{
    int max_flow = 0;
    //printf("Calling bfs\n");

    while (bfs(source,sink))
    {
        //printf("Inside while of ford\n");
        int increment = numeric_limits<int>::max();
        for(int u=n-1;augpath[u]>=0;u=augpath[u])
        {
            increment = min(increment,capacity[augpath[u]][u]-flow[augpath[u]][u]);
        }

        for(int u=n-1;augpath[u]>=0;u=augpath[u])
        {
            flow[augpath[u]][u] += increment;
            flow[u][augpath[u]] += increment;
        }
        max_flow += increment;
        
    }

    return max_flow;
}


