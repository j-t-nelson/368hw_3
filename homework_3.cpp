/* ******************************************************
 * Name: Jasper Nelson
 * Wisc ID: 9073545106
 * OS: MAC
 * IDE (or text editor): Eclipse
 * Compiler: Eclipse
 * How long did the assignment take you to complete in minutes: 200
 * What other resources did you consult (copy and paste links below):
 * cplusplus.com
 * stackoverflow.com
*/ //******************************************************
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <time.h>      // time

using namespace std;

// feel free to use this function if you wish
// purpose: generate random coordinates
// input: none
// output: a vector with 2 coordinates between 1,1 and 4,4
vector<int> Get_A_Random_Square()
{
	return vector<int>{rand()%4+1, rand()%4+1};
}

// feel free to use this function if you wish
// purpose: verifies if the coordinates of a square fall within the cave
// input: coordinates of a square
// output: true if the square is in the cave otherwise false
bool Is_Square_Valid(const vector<int> &square)
{
	for (auto e : square)
		if (e < 1 || e > 4)
			return false;
	return true;
}

// don't change this function
// purpose: prints a map of the cave to the console
// input: the printable map a vector of strings
// output: none - console output of the cave diagram
void Print_Cave_Diagram(const vector<string> &cave_diagram)
{
	for (auto s : cave_diagram)
		cout<<s<<endl;
}

// Implement these functions below
// Do not change the function prototpyes
void Initialize_Cave(map<vector<int>, set<string> > &cave);
void Print_Square(map<vector<int>, set<string> > &cave, const vector<int> &rc);
void Get_Cave_Diagram(map<vector<int>, set<string> > &cave, vector<string> &cave_diagram);


// sample main function
int main()
{
	srand(time(NULL)); // seed the random generator

	// Declare the cave data structure to 'map' coordinates to a 'set' of strings describing the cell contents
	map<vector<int>, set<string> > cave;

	// Check this out! The cave data structure has a lot going on
	// Uncomment the block below to see a demo of how to use the cave map
	// use the [] to access the set contained in the map
	// insert puts the word "ladder" into the set
	// cave[rc] is the set of words at coordinates rc
	// cave[rc].begin() returns an iterator to the first element of the set
	// note your program will likely crash if the set is empty
	// I recommend checking for this.
	// use the * to dereference the pointer to get the first word stored in the set


	/*
	vector<int> rc{1, 1}; // row column
	cave[rc].insert("ladder");
	if (cave[rc].empty() == false)
		cout<<"cave square (1,1) contains a "<<*cave[rc].begin()<<endl;
	// */

	Initialize_Cave(cave);

	for (int r=1; r<=4; r++) {
		for (int c=1; c<=4; c++)
		{
			vector<int> rc{r, c};
			Print_Square(cave, rc);
		}
	}

	vector<string> cave_diagram;
	Get_Cave_Diagram(cave, cave_diagram);
	Print_Cave_Diagram(cave_diagram);

	return 0;
}

// add the player, ladder, wumpus, pits, gold, stench, breeze to the map
// input: the Map of the cave
// output: N/A
void Initialize_Cave(map<vector<int>, set<string> > &cave)
{
	// place the "ladder" in row 1 column 1
	// place the "player" at the same location as the ladder
	vector<int> lsquare{1,1};
	cave[lsquare].insert("ladder");
	cave[lsquare].insert("player");

	// place the "wumpus" - can't be in the same square as the ladder
	vector<int> wsquare{1,1};
	while(wsquare.at(0)==1 && wsquare.at(1)==1)
	{
		wsquare = Get_A_Random_Square();
	}
	cave[wsquare].insert("wumpus");

	// place the 3 "pits" - can't be in the same square as the ladder, wumpus, or another pit
	int i = 0;
	vector<int> pit;
	vector<int> pitlist; //used to keep track of the positions of all 3 pits
	while(i < 3)
	{
		pit = Get_A_Random_Square();
		if(cave[pit].empty() == false) continue;//if pit is invalid, repeat until valid
		else
		{
			cave[pit].insert("pit");
			pitlist.push_back(pit.at(0));
			pitlist.push_back(pit.at(1));//add pit to the list of pits
			i++;
		}
	}

	// place the "gold" - can't be in the same square as a pit or the ladder
	vector<int> pit1, pit2, pit3;
	pit1.push_back(pitlist.at(0));
	pit1.push_back(pitlist.at(1));
	pit2.push_back(pitlist.at(2));
	pit2.push_back(pitlist.at(3));
	pit3.push_back(pitlist.at(4));
	pit3.push_back(pitlist.at(5));

	vector<int> gold = Get_A_Random_Square();
	//ensure the pit is valid
	while(gold == lsquare || gold == pit1 || gold == pit2 || gold == pit3)
	{
		gold = Get_A_Random_Square();
	}
	cave[gold].insert("gold");

	// place the "stench" squares to the left, right, up, and down from the wumpus
	int y1 = wsquare.at(0);
	int x1 = wsquare.at(1);
	vector<int> stench1{y1+1, wsquare.at(1)};
	cave[stench1].insert("stench");
	vector<int> stench2{y1-1, wsquare.at(1)};
	cave[stench2].insert("stench");
	vector<int> stench3{wsquare.at(0), x1+1};
	cave[stench3].insert("stench");
	vector<int> stench4{wsquare.at(0), x1-1};
	cave[stench4].insert("stench");

	// place the "breeze" squares to the left, right, up, and down from the three pits
	int x2, x3, y2, y3;
	x1 = pit1.at(1);
	y1 = pit1.at(0);
	vector<int> breeze1{y1+1, pit1.at(1)};
	cave[breeze1].insert("breeze");
	vector<int> breeze2{y1-1, pit1.at(1)};
	cave[breeze2].insert("breeze");
	vector<int> breeze3{pit1.at(0), x1+1};
	cave[breeze3].insert("breeze");
	vector<int> breeze4{pit1.at(0), x1-1};
	cave[breeze4].insert("breeze");

	x2 = pit2.at(1);
	y2 = pit2.at(0);
	breeze1 = {y2+1, pit2.at(1)};
	cave[breeze1].insert("breeze");
	breeze2 = {y2-1, pit2.at(1)};
	cave[breeze2].insert("breeze");
	breeze3 = {pit2.at(0), x2+1};
	cave[breeze3].insert("breeze");
	breeze4 = {pit2.at(0), x2-1};
	cave[breeze4].insert("breeze");

	x3 = pit3.at(1);
	y3 = pit3.at(0);
	breeze1 = {y3+1, pit3.at(1)};
	cave[breeze1].insert("breeze");
	breeze2 = {y3-1, pit3.at(1)};
	cave[breeze2].insert("breeze");
	breeze3 = {pit3.at(0), x3+1};
	cave[breeze3].insert("breeze");
	breeze4 = {pit3.at(0), x3-1};
	cave[breeze4].insert("breeze");
}


// print the contents of the square
// input:The map of the cave, and a vector containing the coordinates of the square
//		 to be printed
// output: N/A
void Print_Square(map<vector<int>, set<string> > &cave, const vector<int> &rc)
{
	cout<< "This part of the cave contains" <<endl;
	if(cave[rc].empty() == true)
	{
		cout << "    nothing\n" << endl;
		return;
	}
	for(auto it = cave[rc].begin(); it != cave[rc].end(); ++it)
	{
		cout << "    " << *it << endl;
	}
	cout<<endl;
}

// build a vector of strings where each string in the vector represents one row of the cave output
// input:The map of the cave, a vector of strings holding each row of the diagram to be printed
// output: N/A
void Get_Cave_Diagram(map<vector<int>, set<string> > &cave, vector<string> &cave_diagram)
{
	int cell_rows = 5;
	int cell_columns = 11;
	int total_rows = cell_rows*4 + 1;
	int total_columns = cell_columns*4 + 1;

	// fill in with vertical cell divisions
	for (int r=0; r<total_rows; r++)
	{
		string row(total_columns, ' ');
		for (int c=0; c<total_columns; c+=cell_columns)
		{
			row[c] = '|';
		}
		cave_diagram.push_back(row);
	}

	// udpate horizontal rows with '-'
	for (int i=0; i<total_rows; i+=cell_rows) {
		cave_diagram[i] = string(total_columns, '-');
	}

	// update cell corners with '+'
	for (int r=0; r<total_rows; r+=cell_rows)
	{
		for (int c=0; c<total_columns; c+=cell_columns)
		{
			cave_diagram[r][c]='+';
		}
	}

	// replace the part of the string with the cell contents

	for(int a = 0; a < 4; a++)
	{
		for(int b = 0; b < 4; b++)
		{
			vector<int> tmp{a+1,b+1};
			int row = (a * cell_rows) + 1;
			int col = (b * cell_columns) + 3;
			for(auto it = cave[tmp].begin(); it != cave[tmp].end(); ++it)
			{
				string hld = *it;
				int l = hld.length();
				cave_diagram[row].replace(col, l, hld);
				row++;

			}
		}
	}
}


