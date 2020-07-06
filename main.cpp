#include "dinic.cpp"
#include "fordful.cpp"
#include <iostream>
#include <chrono>

using namespace std;

int main()
{
    setbuf(stdout,NULL);
	int t;
	scanf("%d",&t);
	for(int l=0;l<t;l++)
	{
		int n,e;
		scanf("%d %d",&n,&e);
		vector<vector<int>> capacity(n,vector<int>(n,0));
		int a,b,c;
		for(int i=0;i<e;i++)
		{
		    scanf("%d %d %d",&a,&b,&c);
		    capacity[a][b] = c;
		}
		//printf("Input taken\n");
		int s,d;
		scanf("%d %d",&s,&d);

		ford_fulkerson_implementation *fobj = new ford_fulkerson_implementation(n,capacity);
		dinic_implementation *dobj = new dinic_implementation(n,capacity);
		//call the function max_flow here for both algorithms
		//printf("Initialization done\n");
		// Checking execution time for Ford-Fulkerson
		auto start = chrono::high_resolution_clock::now();
		int max_flow1 = fobj->max_flow(s,d);
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		printf("The max flow by Ford-Fulkerson %d\n",max_flow1);
		cout<<"Time Taken: "<<duration.count()<<" microseconds"<<endl;

		start = chrono::high_resolution_clock::now();
		int max_flow2 = dobj->max_flow(s,d);
		stop = chrono::high_resolution_clock::now();
		duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		printf("The max flow by Dinic %d\n",max_flow2);
		cout<<"Time Taken: "<<duration.count()<<" microseconds"<<endl;
	}
    

    return 0;
}
