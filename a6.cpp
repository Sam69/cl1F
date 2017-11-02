#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int main()
	{
		//take input
		int n;
		cout<<"Enter number of elements"<<endl;
		cin>>n;		
		double x[n],y[n];

		cout<<"Enter elements"<<endl;
		for(int i=0;i<n;i++)
			cin>>x[i]>>y[i];

		cout<<"Entered elements are"<<endl;
		for(int i=0;i<n;i++)
			cout<<x[i]<<","<<y[i]<<endl;		

		int clusters;
		cout<<"Enter number of clusters"<<endl;
		cin>>clusters;

		vector<double> *means;
		means = new vector<double>[2];

		cout<<"enter cluster means"<<endl;
		for(int i=0;i<clusters;i++)
		{
			int meanx,meany;			
			cin>>meanx>>meany;
			means[0].push_back(meanx);
			means[1].push_back(meany);			
		}

		vector<double> *prev_means;
		prev_means = new vector<double>[2]; //this for checking end condition

		vector<int> *clusteritems;
		clusteritems = new vector<int>[n]; 

		int redo = 1;
		while(redo)
		{
			//doing knn here
			cout<<"iteration "<<redo<<endl;
			
			prev_means[0] = means[0];
			prev_means[1] = means[1];

			for(int i=0;i<clusters;i++)			
				clusteritems[i].erase(clusteritems[i].begin(),clusteritems[i].end()); //this will delete all items in clusters for next iteration
			
			for(int i=0;i<n;i++)		//checking for every element which is closest cluster for it
			{
				double temp,min = 999999;
				int pos = 0;

				for(int j=0;j<clusters;j++)
				{
					temp = sqrt(pow((x[i]-means[0][j]),2)+pow((y[i]-means[1][j]),2));
					if(min>temp){
						min = temp;
						pos = j;
					}					
				}
				clusteritems[pos].push_back(i); //assignment to apt cluster
			}

			for(int i = 0;i<clusters;i++)
				{
					double sumx=0,sumy=0;
					for(int j = 0;j<clusteritems[i].size();j++)
						{
							sumx += x[clusteritems[i][j]];
							sumy += y[clusteritems[i][j]];
						}
					means[0][i] = sumx/clusteritems[i].size();
					means[1][i] = sumy/clusteritems[i].size();

				}				

			if(prev_means[0] == means[0] && prev_means[1] == means[1])
				redo = 0;
			else
				redo++;
		}

		for(int i=0;i<clusters;i++)
		{
			cout<<"Cluster "<<i+1<<endl;
			cout<<"Cluster mean: "<<means[0][i]<<","<<means[1][i]<<endl;
			cout<<"Cluster items:"<<endl;
			for(int j=0;j<clusteritems[i].size();j++)
				cout<<x[clusteritems[i][j]]<<","<<y[clusteritems[i][j]]<<endl;			

		}	
		return 0;
	}