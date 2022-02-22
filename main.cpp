#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <stdlib.h>

using namespace std;

int grid[9][9], counter;
clock_t start,stop;
bool ask=true;
char c;


void write_to_file(string name_of_file)
{
	fstream file;
	file.open(name_of_file, (ios::app));
	if(file.good())
	{
		file<<"\n[+] Sudoku number "<<counter+1<<" solved in "<<fixed<<(double)(stop-start)/CLOCKS_PER_SEC<<" seconds."<<endl;
		for(int j=0; j<9; j++)
		{
			for(int i=0; i<9; i++)
			{
				file<<grid[j][i]<<" ";	
			}
			file<<endl;
		}
	}
	file.close();
}


void make_grid(string name_of_file)
{
	int y=0;
	int x=0;
	fstream file;
	file.open(name_of_file, (ios::in));
	if(file.good())
	{
		string number;
		while(getline(file, number, ','))
		{
			if(x == 9){x=0,y++;}
		  grid[y][x] = stoi(number);
			x++;
		}
	}
	file.close();
}


bool can_be(int y, int x, int n)
{
	bool canbe;
	for(int i=0; i<9; i++)
	{
		if(grid[y][i] == n) // horizontal axis
		{
			return false;
		}
		if(grid[i][x] == n) // vertical axis
		{
			return false;
		}
	}

	int x0 = floor(x/3)*3; // coordinates for left corner square (3x3) where is number
	int y0 = floor(y/3)*3;

	for(int k=0; k<3; k++)
	{
		for(int j=0; j<3; j++)
		{
			if(grid[y0+k][x0+j] == n) return false; // checking square 3x3
		}
	}

	return true;
}


void solve()
{
	for(int y=0; y<9; y++)
	{
		for(int x=0; x<9; x++)
		{
			if(grid[y][x] == 0)
			{
				for(int n=1; n<10; n++)
				{
					if(can_be(y,x,n))
					{
						grid[y][x] = n;
						solve();
						grid[y][x] = 0;
					}
				}
				return;
			}
		}
	}
	stop = clock();
	write_to_file("solved-sudoku.txt");
	counter++;
	if(ask){
		cout<<"[+] Solved "<<counter<<" time."<<endl;
		cout<<"Next solution (type \"a\" for all and \"e\" for exit):";
		c = cin.get();
	}
	if(c == 'a') ask = false;
	else if(c == 'e')
	{
		cout<<"\nYou're sudoku has been solved "<<counter<<" times."<<endl;
		exit(0);
	}
	start = clock();
}


void begin(string name_of_file)
{
	make_grid(name_of_file);
	start = clock();
	solve();
	cout<<"\nYou're sudoku has been solved "<<counter<<" times."<<endl;
}


int main()
{
	string file_name = "grid.txt";
	begin(file_name);
	return 0;
}