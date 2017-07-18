#ifndef DBSCAN_H
#define DBSCAN_H
#include <vector>

using namespace std;

class dbscan{
	private:
		
		
	public:
		struct node{
			double x;
			double y;
			bool visited;
			bool clustered;
			bool noise;
		};

		struct cluster{
			vector <node > Nodes;
		};
		double distance;
		vector <node > data;
		vector <cluster > clusters;
		
		
		dbscan();
		vector <node > insert_data(double x, double y);
		vector <cluster > DBSCAN(vector <node > D, double eps, int MinPts);
		void expandCluster(vector <node >& P, int pos, vector <node >& NeighborPts, vector <cluster >& C, double eps, int MinPts);
		vector<node > regionQuery(vector <node >& P, int pos,double eps);
		~dbscan();
	protected:

};

#endif