#include <iostream>
#include <chrono>
#include <random>
#include <vector>

#include <cmath>
#include <set>

using namespace std;

vector<vector<vector<double> > > tex_synth_cpp(const vector<vector<vector<double> > > & texture,const vector<vector<vector<double> > > & input,int T,int K)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::uniform_int_distribution<int> dist;
	std::default_random_engine gen(seed);

	int tN = texture.size();
	int tM = texture[0].size();
	
	int C  = texture[0][0].size();
	
	int iN = input.size();
	int iM = input[0].size();
	
	vector<vector<vector<double> > > output(iN,vector<vector<double> >(iM,vector<double>(C+2,0.0)));
	
	for(int x=0;x<iN;x++)
	for(int y=0;y<iM;y++)
	for(int c=0;c<C;c++)
		output[x][y][c] = input[x][y][c];
	
	vector<vector<int> > U(iN,vector<int>(iM,-1));
	vector<vector<int> > V(iN,vector<int>(iM,-1));
	
	for(int x=0;x<iN;x++)
	for(int y=0;y<iM;y++)
	{
		U[x][y] = dist(gen)%tN;
		V[x][y] = dist(gen)%tM;
	}
	
	for(int it=0;it<T;it++)
	{
		
		for(int x1=0;x1<iN;x1++)
		for(int y1=0;y1<iM;y1++)
		{
			if(x1 % 16 == 0 && y1 == 0)
				cout << it << " " << x1 << endl;

			int    best_u = -1;
			int    best_v = -1;
			double best_E = 1e14;
			
			set<pair<int,int> > cand;
			
			for(int k1=-K;k1<=K;k1++)
			for(int l1=-K;l1<=K;l1++)
			{
				if(k1 == 0 && l1 == 0)
				{
					 if(it == 0) break;
					 else continue;
				}
				
				int x2 = (iN+x1+k1)%iN;
				int y2 = (iM+y1+l1)%iM;
				int u2 = (tN+U[x2][y2]-k1)%tN;
				int v2 = (tM+V[x2][y2]-l1)%tM;
				cand.insert(pair<int,int>(u2,v2));
			}
			for(set<pair<int,int> >::iterator ct = cand.begin();ct != cand.end();ct++)
			{
				int u1 = ct->first;
				int v1 = ct->second;
				
				double E = 0.0;
				for(int k1=-K;k1<=K;k1++)
				for(int l1=-K;l1<=K;l1++)
				{
					if(k1 == 0 && l1 == 0)
					{
						if(it == 0) break;
						else continue;
					}
					
					int u2 = (tN+u1+k1)%tN;
					int v2 = (tM+v1+l1)%tM;
					
					int x2 = (iN+x1+k1)%iN;
					int y2 = (iM+y1+l1)%iM;
					
					if((k1 == 0 && l1 >= 0)||(k1 > 0))
						for(int c=0;c<C;c++)
							E += (input[x2][y2][c]-texture[u2][v2][c])*(input[x2][y2][c]-texture[u2][v2][c]);
					else
						for(int c=0;c<C;c++)
							E += (output[x2][y2][c]-texture[u2][v2][c])*(output[x2][y2][c]-texture[u2][v2][c]);
				}
				if(E < best_E)
				{
					best_u = u1;
					best_v = v1;
					best_E = E;
				}
			}
			
			U[x1][y1] = best_u;
			V[x1][y1] = best_v;

			for(int c=0;c<C;c++)
				output[x1][y1][c] = texture[best_u][best_v][c];
			output[x1][y1][C  ] = best_u*1.0/tN;
			output[x1][y1][C+1] = best_v*1.0/tM;
		}
	}
	return output;
}
