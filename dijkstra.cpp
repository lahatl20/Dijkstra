#include "queue.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "graph.h"
#include <cstdlib>
#include <vector>
#include <climits>
#include <iomanip>
#include <stack>
#include <set>

using namespace std;

#include "HashTable.h"


struct VertexType
{
	string name;
	bool marked;
	int distance;
	string previous;	
};

void insertionSort(string cities[], int numVertices);
void checkInFile(int argc);
void buildDGraph(Graph<string> &dGraph, string filename, string cities[], int &numVertices, int &numEdges, VertexType myVertices[]);
void printCities(int numVertices, string cities[]);
string setStart(string start, int numVertices, VertexType myVertices[]);
void printRow(int location, VertexType myVertices[]);
int findMin(VertexType myVertices[], int numVertices);
void dijkstra(Graph<string> &dGraph, int numVertices, VertexType myVertices[]);
bool allMarked(int numVertices, VertexType myVertices[]);
void assignWeights(Graph<string> &dGraph, int numVertices, VertexType myVertices[], int startingLocation, Queue<string>& getTo);

int main(int argc, char* argv[])
{
	checkInFile(argc);	// Checks to see if Filename is given

	// Creation of Input File:
	string filename = argv[1];

	Graph<string> dGraph; 
	int numVertices;
	int numEdges;
	VertexType myVertices [50];
	string cities [50];
	buildDGraph(dGraph, filename, cities, numVertices, numEdges, myVertices);	// Builds the Graph using the data from the external file.
	printCities(numVertices, cities);	// Prints Cities found in file
	dijkstra(dGraph, numVertices, myVertices);	// Computes Dijkstra's Algorithm:
}

// Checks to see if Filename is given:
void checkInFile(int argc)
{
  if(argc < 2)
  {
    cout << "Error. Filename was not given";
    exit(0);
  }
}

// Computes Dijkstra's Algorithm:
void dijkstra(Graph<string> &dGraph, int numVertices, VertexType myVertices[])
{
  Queue<string> getTo;
  int location = 0;  
  string start = setStart(start, numVertices, myVertices);
  
  cout<<""<<endl;
  cout<<"--------------------------------------------------------"<<endl;
  cout<<" "<<endl;
  
  for(int i = 0; i <= numVertices; i++)
  {
   if(myVertices[i].name.compare(start) == 0)
   {
     location = i;
     myVertices[i].marked = true;
     myVertices[i].distance = 0;
     myVertices[i].previous = "N/A";
     printRow(location, myVertices);
     break;
   }
  }
  
  dGraph.GetToVertices(myVertices[location].name, getTo);
  assignWeights(dGraph, numVertices, myVertices, location, getTo);
  
  while(!allMarked(numVertices, myVertices))
  {
    location = findMin(myVertices, numVertices);
    printRow(location, myVertices);
    myVertices[location].marked = true;
    dGraph.GetToVertices(myVertices[location].name, getTo);
    assignWeights(dGraph, numVertices, myVertices, location, getTo);
  }
}

// Assign weights based on the starting location
void assignWeights(Graph<string> &dGraph, int numVertices, VertexType myVertices[], int startingLocation, Queue<string>& getTo)
{ 
  int weight = 0;  int sum = 0;  int position = 0;

  while(!getTo.isEmpty())
  {
    string comparison = getTo.dequeue();
  
    for(int j = 0; j < numVertices; j++)
    {
      
      if(myVertices[j].name.compare(comparison) == 0)
      {
        position = j;
        break;
      }
    }

    weight = dGraph.WeightIs(myVertices[startingLocation].name, comparison);
    sum = weight + myVertices[startingLocation].distance;
      
    if(myVertices[position].distance > sum)
    {
      myVertices[position].distance = sum;
      myVertices[position].previous = myVertices[startingLocation].name;
    }
  }
}

// Checks to see if all Vertices have been marked:
bool allMarked(int numVertices, VertexType myVertices[])
{
  for(int i = 0; i < numVertices; i++)
  {
    if(!myVertices[i].marked)
      return false;
  }
  
  return true;
}

// Builds the Graph using the data from the External File:
void buildDGraph(Graph<string> &dGraph, string filename, string cities[], int &numVertices, int &numEdges, VertexType myVertices[])
{
  ifstream myFile;
  myFile.open(filename.c_str());  
  string prev;  string curr;  int weight;
  HashTable<string> cityList("ZZZ" ,50);
  
    while(myFile)
    {
      getline(myFile, prev, ';');
      getline(myFile, curr, ';');
      myFile >> weight;
      myFile.ignore();
      
      if((cityList.find(prev) != prev))
      {
        dGraph.AddVertex(prev);
        cityList.insert(prev);
        cities[numVertices] = prev;
        myVertices[numVertices].name = prev;
        myVertices[numVertices].marked = false;
        myVertices[numVertices].distance = INT_MAX;
        numVertices++;
      }
      
      if((cityList.find(curr) != curr))
      {
        dGraph.AddVertex(curr);
        cityList.insert(curr);
        cities[numVertices] = curr;
        myVertices[numVertices].name = curr;
        myVertices[numVertices].marked = false;
        myVertices[numVertices].distance = INT_MAX;
        numVertices++;
      }
      
      dGraph.AddEdge(prev, curr, weight);
      numEdges++;
    }
    
    myFile.close();
}

// Prints Cities found in External File:
void printCities(int numVertices, string cities[])
{
  cout<<"----------------- DIJKSTRA'S ALGORITHM -----------------\n\n";
  cout<<" A Weighted Graph Has Been Built For These " << numVertices << " Cities : \n\n";
  
  insertionSort(cities, numVertices);
  int count = 0;
  
  for(int i = 0; i < numVertices; i++)
  {
    cout << "\t" << cities[i] << "\t";
    count++;
    
    if(count % 3 == 0)
    {
      cout << "\n";
      count = 0;
    }
  }
  
  cout << "\n";
}

// Sorts the Cities Alphabetically:
void insertionSort(string cities[], int numVertices)
{
  for(int i = 1; i < numVertices; i++)
  {
    string key = cities[i];  int j;
    for(j = i; j > 0 && key < cities[j-1]; j--)
    {
      cities[j] = cities[j-1];
    }
    
    cities[j] = key;
  }
}

//Sets the Starting Value in Dijsktra's Algorithm:
string setStart(string start, int numVertices, VertexType myVertices[])
{
	cout << " Please input your starting vertex: ";
	string response;
	getline(cin,response);
	bool isThere = false;
	for (int i = 0;	i < numVertices; i++)
	{
		if (myVertices[i].name.compare(response) == 0)
		{
			start = response;
			return start;
		}
	}
	while (!isThere)
	{
		cout << " Starting location does not exist..." << endl;
		cout << " Please input your new vertex: ";
        	string response;
        	cin >> response;
		for (int i = 0; i < numVertices; i++)
        	{
                	if (myVertices[i].name.compare(response) == 0)
			{
                        	start = response;
                        	return start;
                	}
        	}
	}
}

// Finds the minimum non-marked values in VertexType Array:
int findMin(VertexType myVertices[], int numVertices)
{
 		int minWeight = INT_MAX - 1;
                int minThing = -1;
		for (int i = 0; i < numVertices; i++)
                {
                        if (myVertices[i].distance < minWeight && !myVertices[i].marked)
                        {
                                minWeight = myVertices[i].distance;
                                minThing = i;
                        }
			else if (myVertices[i].distance == minWeight && !myVertices[i].marked)
        		{
                                minWeight = myVertices[i].distance;
                                minThing = i;
                        }

		}        
		return minThing;
}

// Prints a given row in a Summary Table:
void printRow(int location, VertexType myVertices[])
{
	if (myVertices[location].distance != -1)
	cout << setw(14) << myVertices[location].name << setw(18) << myVertices[location].distance << setw(16) << myVertices[location].previous << endl;
	else
	 cout << setw(14) << myVertices[location].name << setw(18) << "Not On Path" << setw(16) << myVertices[location].previous << endl;
}

