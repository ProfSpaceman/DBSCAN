#include "dbscan.h"
#include <iostream>
#include <string>
#include <vector>
// #include <fstream>
#include <math.h>

using namespace std;

dbscan::dbscan(){
	
}

vector<dbscan::node > dbscan::insert_data(double x, double y){
	node mynode = {x,y,false,false,false};
	data.push_back(mynode);
	return data;
}

vector<dbscan::cluster > dbscan::DBSCAN(vector <node > D, double eps, int MinPts)
{
	vector <node> NeighborPts;
	vector <cluster > C;
	for(size_t i = 0; i < D.size(); i++)
	{
		if((D[i].visited==true))
		{
			i++;
		}else{
			D[i].visited = true;
			NeighborPts = regionQuery(D, i,eps);
			if(NeighborPts.size() < MinPts){
				D[i].noise = true;
			}
			else
			{	
				expandCluster(D, i,NeighborPts, C, eps, MinPts);
			}
		}
	}
	return C;
}

void dbscan::expandCluster(vector <node >& P, int pos, vector <node >& NeighborPts, vector <cluster >& C, double eps, int MinPts)
{
	vector<node > NeighborPts2;
	vector<node > datRet;
	cluster myCluster;
	
	P[pos].clustered = true;
	datRet.push_back(P[pos]);
	
	for(size_t i = 0; i < NeighborPts.size(); i++)
	{	
		if(NeighborPts[i].visited != true)
		{
			NeighborPts[i].visited = true;
			NeighborPts2 = regionQuery(NeighborPts, i, eps);
			if(NeighborPts2.size() >= MinPts)
			{
				for(size_t j = 0; j < NeighborPts2.size(); j++)
				{
					NeighborPts.push_back(NeighborPts2[j]);
				}
			}
		}
		if(NeighborPts[i].clustered != true)
		{	
			NeighborPts[i].clustered = true;
			//cout<< NeighborPts[i].x << endl;
			datRet.push_back(NeighborPts[i]);
		}
	}

	myCluster.Nodes = datRet;
	C.push_back(myCluster);
}

vector<dbscan::node > dbscan::regionQuery(vector <node >& P, int pos,double eps)
{
	vector<node > Reg;
	vector<node > NeighborPts;
	Reg = P;

	for(size_t i = 0; i < Reg.size();i++)
	{
		distance = sqrt(( pow( ((P[pos].x) - (Reg[i].x)),2) ) + ( pow( ( (P[pos].y) - (Reg[i].y) ),2 )) );
		if(distance <= eps)
		{
			if(P[i].visited != true)
			{
				P[i].visited = true;
			}
			NeighborPts.push_back(P[i]);
		}	
	}
	return NeighborPts;
}

dbscan::~dbscan(){
// 	data.clear();
// 	clusters.clear();
}