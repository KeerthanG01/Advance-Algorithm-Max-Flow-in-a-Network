#include<vector>
#include<queue>
#include<limits>
using namespace std;

class dinic_implementation
{
private:
    int n;
    int e;
    queue<int> q;
    vector<vector<int>> capacity;
    vector<vector<int>> flow;
    vector<int> level;
    vector<int> rev;

public:
    dinic_implementation(int,vector<vector<int>>);
    int bfs(int start,int target);
    int send_flow(int,int,int);
    int max_flow(int source,int sink);

};

dinic_implementation::dinic_implementation(int n,vector<vector<int>> capacity)
{
    this->n = n;
    this->capacity = capacity;
    flow.resize(n,vector<int>(n,0));
}

int dinic_implementation::bfs(int start,int target)
{
    if(level.size() > 0)
    {
        level.clear();
    }
    for(int i=0;i<n;i++)
    {
        level.push_back(-1);
    }
    level[start] = 0;
    q.push(start);
    int u,v;
    while (!q.empty())
    {
        u = q.front();
        q.pop();
        for(int v=0;v<n;v++)
        {
            if(level[v] < 0 && capacity[u][v] > flow[u][v])
            {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return level[target]>=0;
}

int dinic_implementation::send_flow(int start,int path_flow,int target)
{
    if(start == target)
    {
        return path_flow;
    }
    
    int current_flow;
    int future_flow;

    for(int v=0;v<n;v++)
    {
        if(level[v] == level[start]+1 && capacity[start][v] > flow[start][v])
        {
            current_flow = min(path_flow,capacity[start][v]-flow[start][v]);
            future_flow = send_flow(v,current_flow,target);
            if(future_flow > 0)
            {
                flow[start][v] += future_flow;
                //omitted rev
                return future_flow;
            }
        }
    }
    return 0;
}

int dinic_implementation::max_flow(int source,int sink)
{
    if(source == sink)
    {
        return -1;
    }
    int max_flow = 0;

    while(bfs(source,sink) == true)
    {
        while(int i = send_flow(source,numeric_limits<int>::max(),sink))
        {
            max_flow += i;
        }
    }

    return max_flow;
}