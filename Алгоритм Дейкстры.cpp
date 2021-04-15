#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <string>   
#include <sstream>
#include <set>
#include <iterator>

using namespace std;

class Deicstra
{
public:
	Deicstra();
	Deicstra(int a, int b);
	int to_vertex;
	int mass;
};

Deicstra::Deicstra()
{
	to_vertex = -1;
	mass = 0;
}

Deicstra::Deicstra(int a, int b)
{
	to_vertex = a;
	mass = b;
}

int main()
{
	int n, m, u, v, w;
	ifstream input;
	input.open("input.txt");
	string line;
	getline(input, line);
	istringstream istring(line);
	vector<string> string_1
	{
		istream_iterator<string>(istring), {}
	};
	n = stoi(string_1[0]);
	m = stoi(string_1[1]);
	bool find;
	vector <vector<Deicstra>> Vertex(n);
	vector <bool> is_used_vertex(n, false);
	vector <long long int> mass_vertex(n, 4000000000);
	for (int i = 0; i < m; i++)
	{
		getline(input, line);
		istringstream istring(line);
		vector<string> next_string
		{
			istream_iterator<string>(istring), {}
		};
		u = stoi(next_string[0]);
		v = stoi(next_string[1]);
		w = stoi(next_string[2]);
		u--;
		v--;
		if (u != v)
		{
			/*find = false;
			for (int i = 0; i < Vertex[u].size(); i++)
			{
				if (Vertex[u][i].to_vertex == v)
				{
					find = true;
					if (Vertex[u][i].mass > w)
					{
						Vertex[u][i].mass = w;
					}
					break;
				}
			}
			if (!find)
			{*/
				Vertex[u].push_back(Deicstra(v, w));
			/*}
			find = false;
			for (int i = 0; i < Vertex[v].size(); i++)
			{
				if (Vertex[v][i].to_vertex == u)
				{
					find = true;
					if (Vertex[v][i].mass > w)
					{
						Vertex[v][i].mass = w;
					}
					break;
				}
			}
			if (!find)
			{*/
				Vertex[v].push_back(Deicstra(u, w));
			/*}*/
		}
	}
	input.close();
	int find_num = n;
	find_num--;
	mass_vertex[0] = 0;
	int num;
	set<pair<int, int>> next_steps;
	next_steps.insert({ 0, 0 });
	int j = 0;
	while (true)
	{
		auto step = next_steps.begin();
		num = (*step).second;
		next_steps.erase(step);
		if (find_num == num)
		{
			ofstream ouput;
			ouput.open("output.txt");
			ouput << mass_vertex[num];
			ouput.close();
			break;
		}
		is_used_vertex[num] = true;
		for (int i = 0; i < Vertex[num].size(); i++)
		{
			j = Vertex[num][i].to_vertex;
			if (!is_used_vertex[j])
			{
				long long int new_mass = mass_vertex[num] + Vertex[num][i].mass;
				if (new_mass < mass_vertex[j])
				{
					mass_vertex[j] = new_mass;
					next_steps.insert({ new_mass, j });
				}
			}
		}
	}
}