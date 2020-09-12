/* pathfinder.cpp
 * ---------------
 * A starter file with some starting constants and handy utility routines.
 */
 
#include "genlib.h"
#include "simpio.h"
#include "extgraph.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include "vector.h"
#include "set.h"
#include "map.h"
#include "strutils.h"
#include "scanner.h"
#include "pqueue.h"

/* Constants
 * --------
 * A few program-wide constants concerning the graphical display.
 */
const double CircleRadius =.05;     	// the radius of a node
const int LabelFontSize = 9;          // for node name labels

struct nodeT;

/* Type: coordT
 * ------------
 * Just a simple struct to handle a pair of x,y coordinate values.
 */
struct coordT {
	double x, y;
};

/* Type: arcT
 * ------------
 * Just a simple struct to handle distance to the end city and pointer to that end city.
 */
struct arcT {
	nodeT *start, *end;
	double distance;
};

/* Type: nodeT
 * ------------
 * Just a simple struct to handle name and coordinates of a city and its arcs/connection of other cities.
 */
struct nodeT {
	string city;
	coordT pt;
	Vector<arcT> arcs;
};

struct spanElem {
	string name;
	Set<string> str;
};


/* Function: DrawFilledCircleWithLabel
 * Usage:  DrawFilledCircleWithLabel(center, "Green", "You are here");
 * -------------------------------------------------------------------
 * Uses facilities from extgraph to draw a circle filled with
 * color specified. The circle is centered at the given coord has the
 * specified radius.  A label is drawn to the right of the circle.
 * You can leave off the last argument if no label is desired.
 */
void DrawFilledCircleWithLabel(coordT center, string color, string label = "")
{
	MovePen(center.x + CircleRadius, center.y);
	SetPenColor(color);
	StartFilledRegion(1.0);
	DrawArc(CircleRadius, 0, 360);
	EndFilledRegion();
	if (!label.empty()) {
		MovePen(center.x + CircleRadius, center.y);
		SetFont("Helvetica");
		SetPointSize(LabelFontSize);
		DrawTextString(label);
	}
}

/* Function: DrawLineBetween
 * Usage:  DrawLineBetween(coord1, coord2, "Black");
 * -------------------------------------------------
 * Uses facilities from extgraph to draw a line of the
 * specified color between the two given coordinates.
 */
void DrawLineBetween(coordT start, coordT end, string color)
{
	SetPenColor(color);
	MovePen(start.x, start.y);
	DrawLine(end.x - start.x, end.y - start.y);
}


/* Function: GetMouseClick
 * Usage:  loc = GetMouseClick();
 * ------------------------------
 * Waits for the user to click somewhere on the graphics window
 * and returns the coordinate of where the click took place.
 */
coordT GetMouseClick()
{
	coordT where;
	WaitForMouseDown();
	WaitForMouseUp();
	where.x = GetMouseX();
	where.y = GetMouseY();
	return where;
}

/* Function: WithinDistance
 * Usage:  if (WithinDistance(click, pt))...
 * -----------------------------------------
 * Returns true if the Cartesian distance between the two coordinates
 * is <= the specified distance, false otherwise. If not specified,
 * the distance is assumed to be size of the node diameter on screen.
 */
bool WithinDistance(coordT pt1, coordT pt2, double maxDistance = CircleRadius*2)
{
	double dx = pt2.x - pt1.x;
	double dy = pt2.y - pt1.y;
	double distance = sqrt(dx*dx + dy*dy);
	return (distance <= maxDistance);
}

double DistanceCover(Vector<arcT> &a)
{
	double dist = 0;
	for(int i = 0; i < a.size(); i++) {
		dist += a[i].distance;
	}
	return dist;
}

/* Function: ArcCmp
 * Usage:  Sort(Vector, &ArcCmp)
 * -------------------------------------------------
 * Compares two arcT user defined datatypes a & b.
 * returns 1 if distance of a is greater than b.
 * returns -1 if distance of a is less than b.
 * returns 0 if distance of a is equals the b.
 */
int ArcCmp(arcT &a, arcT &b)
{
	if(a.distance == b.distance) return 0;
	else if(a.distance > b.distance) return 1;
	else return -1;
}

/* Function: NodeCmp
 * Usage:  Sort(Vector, &NodeCmp)
 * -------------------------------------------------
 * Compares two nodeT user defined datatypes a & b on the basis of their city name.
 * This function follows string comparison.
 * returns 1 if city of a is greater than b.
 * returns -1 if distance of a is less than b.
 * returns 0 if distance of a is equals the b.
 */
int NodeCmp(nodeT &a, nodeT &b) 
{
	if(a.city == b.city) return 0;
	else if(a.city > b.city) return 1;
	else return -1;
}

int ArcVectorCmp(Vector<arcT> &a, Vector<arcT> &b)
{
	if(DistanceCover(a) > DistanceCover(b)) return 1;
	else if(DistanceCover(a) < DistanceCover(b)) return -1;
	else return 0;
}

/* Function: OpenFile
 * Usage:  OpenFile(in)
 * -------------------------------------------------
 * Asks user for filename and open files.
 */
void OpenFile(ifstream &in)
{
	string fileName; 
	while(true) {
		cout << "\nEnter Filename: ";
		fileName =  GetLine();
		in.open(fileName.c_str());
		if(!in.fail()) break;
		in.clear();
		cout << "File do not exist!!! \nTry again." << endl;
	}
}

/* Function: Merge
 * Usage:  Merge(v, left, right, cmp)
 * -------------------------------------------------
 * Merges left and right vector into Vector v in sorted order.
 * It uses user defined compare function cmp for comparison.
 */
template <typename Type>
void Merge(Vector<Type> &v, Vector<Type> &left, Vector<Type> &right, int (* &cmp) (Type &, Type &))
{
    int nL = left.size();
    int nR = right.size();
    int i = 0, j = 0, k = 0;

    while (j < nL && k < nR) 
    {
		if (cmp(left[j], right[k]) <= 0) {
            v[i] = left[j];
            j++;
        } else {
            v[i] = right[k];
            k++;
        }
        i++;
    }
    while (j < nL) {
        v[i] = left[j];
        j++; 
		i++;
    }
    while (k < nR) {
        v[i] = right[k];
        k++; 
		i++;
    }
}

/* Function: Sort
 * Usage:  Sort(v, &cmp) : if cmp is fucntion reference. 
           Sort(v, cmp) : if cmp is a pointer.
 * -------------------------------------------------
 * Sorts a vector using user defined comparison function.
 */
template <typename Type>
void Sort(Vector<Type> &v, int (*cmp) (Type &, Type &))
{
	if (v.size() > 1) {
		int mid = v.size() / 2;
		Vector<Type> left;
		Vector<Type> right;

		for (int j = 0; j < mid;j++)
			left.add(v[j]);
		for (int j = 0; j < (v.size()) - mid; j++)
			right.add(v[mid + j]);

		Sort<Type>(left, cmp);
		Sort<Type>(right, cmp);
		Merge<Type>(v, left, right, cmp);
	}
}

/* Function: CheckIndex
 * Usage: int index = CheckIndex(nodes, 0,(nodes.size() - 1), cityName)
 * -------------------------------------------------
 * Search for cityName in Vector<nodeT> and returns its index if found or return -1 if not found.  
 */
int CheckIndex(Vector<nodeT> &nodes, int p, int r, string &name)
{
   if (p <= r) {
	  int mid = (p + r)/2;
	  if (nodes[mid].city == name) return mid ;
	  if (nodes[mid].city > name) return CheckIndex(nodes, p, mid-1, name);
	  if (nodes[mid].city < name) return CheckIndex(nodes, mid+1, r, name);
   }
   return -1;
}

/* Function: AddNode
 * Usage: AddNode(nodes, start, end, dist)
 * -------------------------------------------------
 * Adds an new arcT which nodeT *end is end and distance is dist in Vector<arcT> of nodeT  of Vector<nodeT> at index "start".
 */
void AddNode(Vector<nodeT> &nodes, int start, int end, double &dist)
{
	arcT newArc;
	newArc.start = &nodes[start];
	newArc.end = &nodes[end];
	newArc.distance = dist;
	nodes[start].arcs.add(newArc);
}

/* Function: SortArcs
 * Usage: SortArcs(nodes)
 * -------------------------------------------------
 * Sorts the Vector<arcT> on the basis of arcT distance of all nodeT in Vector<nodeT>.
 */
void SortArcs(Vector<nodeT> &nodes)
{
	for(int i = 0; i < nodes.size(); i++) {
		Sort<arcT>(nodes[i].arcs, &ArcCmp);
	}
}

/* Function: CreateArcs
 * Usage: CreateArcs(in, scanner, nodes)
 * -------------------------------------------------
 * Read file and adds Vector<arcT> for each nodeT in Vector<nodeT>.
 */
void CreateArcs(ifstream &in, Scanner &scanner, Vector<nodeT> &nodes)
{
	string line;
	while(true) {
		getline(in, line);
		if(line == "") break;	
		scanner.setInput(line);
		string city1 = scanner.nextToken();
		string city2 = scanner.nextToken();
		double dist = StringToReal(scanner.nextToken());
		int start, end;
		start = CheckIndex(nodes, 0, (nodes.size() - 1), city1);
		end = CheckIndex(nodes, 0, (nodes.size() - 1), city2);			
		AddNode(nodes, start, end, dist);
		AddNode(nodes, end, start, dist);
	}
	SortArcs(nodes);
}

/* Function: CreateNodes
 * Usage: CreateNodes(in, scanner, nodes)
 * -------------------------------------------------
 * Read file and adds nodeT to Vector<nodeT>.
 */
void CreateNodes(ifstream &in, Scanner &scanner, Vector<nodeT> &nodes)
{
	string line;
	scanner.setNumberOption(Scanner::ScanNumbersAsReals);
	while(true) {
		getline(in, line);
		if(line == "ARCS"){
			Sort<nodeT>(nodes, &NodeCmp);
			CreateArcs(in, scanner, nodes);
			break;
		}
		scanner.setInput(line);
		nodeT newNode;
		while(scanner.hasMoreTokens()) {
			newNode.city = scanner.nextToken();
			newNode.pt.x = StringToReal(scanner.nextToken());
			newNode.pt.y = StringToReal(scanner.nextToken());
		}
		nodes.add(newNode);
	}
}

/* Function: CreateDatabase
 * Usage: CreateDatabase(in, scanner, nodes, imageName)
 * -------------------------------------------------
 * Read file and distinguish the name of image and data to be stored in Vector<nodeT>.
 */
void CreateDatabase(ifstream &in, Scanner &scanner, Vector<nodeT> &nodes, string &imageName)
{
	string line;
	while(true) {
		getline(in, line);
		if(in.eof()) break;
		if(line == "NODES") {
			CreateNodes(in, scanner, nodes);
			break;
		}
		imageName = line;
		cout << "Image Name: " << imageName << endl;
	}
}

void PrintArcs(Vector<arcT> &arcs)
{
	for(int i = 0; i < arcs.size(); i++) {
		cout << "Linked : [" << arcs[i].start->city << "->"<< arcs[i].end->city << "] Distance: " << arcs[i].distance << endl; 
	}
}

void PrintDatabase(Vector<nodeT> &nodes) 
{
	for(int i = 0; i < nodes.size(); i++) {
		cout << endl << i+1 << ". City: " << nodes[i].city << " (" << nodes[i].pt.x << ", " << nodes[i].pt.y << ")" << endl;
		cout << "\nLinked to:" << endl;
		PrintArcs(nodes[i].arcs);
	}
}
int pairCount = 0;
void DrawPair(arcT &arc)
{
	DrawFilledCircleWithLabel(arc.start->pt, "Black", arc.start->city);
	DrawFilledCircleWithLabel(arc.end->pt, "Black", arc.end->city);
	DrawLineBetween(arc.start->pt, arc.end->pt, "Black");
	pairCount++;
}

bool CheckPairs(Vector<string> &pairs, arcT &arc)
{
	if(pairs.isEmpty()) return false;
	string str1 = arc.start->city + arc.end->city;
	string str2 = arc.end->city + arc.start->city;
	for(int i = 0; i < pairs.size(); i++) {
		if((pairs[i] == str1) || (pairs[i] == str2)) return true;
	}
	return false;
}

int CheckPoint(Vector<nodeT> &nodes, coordT &point)
{
	for(int i = 0; i < nodes.size(); i++) {
		if(((nodes[i].pt.x - 0.1) <= point.x && (nodes[i].pt.x + 0.1) >= point.x ) &&
			((nodes[i].pt.y - 0.1) <= point.y && (nodes[i].pt.y + 0.1) >= point.y )) {
				return i;
		}
	}
	return -1;
}

void DrawGraph(Vector<nodeT> &nodes)
{
	Vector<string> pairs;
	for(int i = 0; i < nodes.size() - 1; i++) {
		for(int j = 0; j < nodes[i].arcs.size(); j++) {
			if(!CheckPairs(pairs, nodes[i].arcs[j])) {
				DrawPair(nodes[i].arcs.getAt(j));
				string str = nodes[i].arcs[j].start->city + nodes[i].arcs[j].end->city;
				pairs.add(str);
			}
		}
	}
	cout << "Total drawn pairs: " << pairCount << endl;
}

void NewFile(Vector<nodeT> &nodes, string &imageName)
{
	ifstream in;
	Scanner scanner;
	scanner.setSpaceOption(Scanner::IgnoreSpaces);
	OpenFile(in);
	CreateDatabase(in, scanner, nodes, imageName);
	in.close();
	MovePen(0.0, 0.0);
	SaveGraphicsState();
	DrawNamedPicture(imageName);
	DrawGraph(nodes);
}

int GetLocation(Vector<nodeT> &nodes)
{
	coordT pt;
	int nodeIndex;
	while(true) {
		pt = GetMouseClick();
		nodeIndex = CheckPoint(nodes, pt);
		if(nodeIndex > -1) {
			cout << "\nLocation Selected: " << nodes[nodeIndex].city << endl;
			break;
		} else {
			cout << "\nInvalid selected location" << endl;
		}
	}
	return nodeIndex;
}

bool CheckArcs(Vector<arcT> &a, arcT &arc)
{
	for(int i = 0; i < a.size(); i++) {
		if(a[i].end->city == arc.end->city || a[i].start->city == arc.end->city) {
			return true;
		}
	}
	return false;
}

void DrawPath(Vector<arcT> &a, double &dist, string &imageName)
{
	RestoreGraphicsState();
	SaveGraphicsState();
	DrawNamedPicture(imageName);
	for(int i = 0; i < a.size(); i++) {
		dist += a[i].distance;
		DrawFilledCircleWithLabel(a[i].start->pt, "Red", a[i].start->city);
		DrawLineBetween(a[i].start->pt, a[i].end->pt, "Red");
		DrawFilledCircleWithLabel(a[i].end->pt, "Red", a[i].end->city);
	}
}

void FindPath(nodeT &startLoc, nodeT &endLoc, Vector<nodeT> &nodes,	PQueue<Vector<arcT> > &PQ, int &count, double &dist, string &imageName)
{
	Vector<arcT> a, b, c;

	if(PQ.isEmpty()) {
		for(int i = 0; i < startLoc.arcs.size(); i++) {
			count++;
			a.clear();
			a.add(startLoc.arcs.getAt(i));
			if(a[a.size() - 1].end->city == endLoc.city){
				DrawPath(a, dist, imageName);
				return;
			} else {
				PQ.enqueue(a);
			}
		}	
	} 
	while(!PQ.isEmpty()) {
		a.clear();
		a = PQ.dequeueMin();
		c = a[a.size() - 1].end->arcs;
		for(int i = 0; i < c.size(); i++) {
			count++;
			b.clear();
			b = a;
			if(!CheckArcs(a,c[i])) {
				b.add(c[i]);
				if(b[b.size() - 1].end->city == endLoc.city) {
					DrawPath(b, dist, imageName);
					return;
				}
				PQ.enqueue(b);
			}
		}
	}
	
}

void ShortestPath(Vector<nodeT> &nodes, string &imageName)
{
	PQueue<Vector<arcT> > PQ(&ArcVectorCmp);
	nodeT startLoc, endLoc;
	int count = 0;
	double dist = 0;
	cout << "\nClick on start location: " << endl;
	startLoc = nodes[GetLocation(nodes)];
	DrawFilledCircleWithLabel(startLoc.pt, "Red", startLoc.city);
	cout << "\nClick on end location: " << endl;
	endLoc = nodes[GetLocation(nodes)];
	
	FindPath(startLoc, endLoc, nodes, PQ, count, dist, imageName);
	DrawFilledCircleWithLabel(endLoc.pt, "Red", endLoc.city);
	cout << "\nShortest from " << startLoc.city << " to " << endLoc.city << " is of " << dist << " miles.";
	cout << "\nShortest path found after anlyzing " << count << " paths" << endl;
}

void EnqueueArc(Vector<nodeT> &nodes, PQueue<arcT> &PQ) 
{
	Vector<string> pairs;
	for(int i = 0; i < nodes.size(); i++) {
		for(int j = 0; j < nodes[i].arcs.size(); j++) {
			if(!CheckPairs(pairs, nodes[i].arcs[j])) {
				PQ.enqueue(nodes[i].arcs.getAt(j));
				string str = nodes[i].arcs[j].start->city + nodes[i].arcs[j].end->city;
				pairs.add(str);
			}
		} 
	}
}

int CheckVisited(Vector<spanElem> &spans, string name)
{
	for(int i = 0; i < spans.size(); i++) {
		if(spans[i].str.contains(name)) return i;
	}
	return -1;
}

void CreateMinSpan(Vector<nodeT> &nodes, Vector<arcT> &visited, PQueue<arcT> &PQ)
{
	Vector<spanElem> spans;

	for(int i = 0; i < nodes.size(); i++) {
		spanElem a;
		a.name = nodes[i].city;
		a.str.add(nodes[i].city);
		spans.add(a);
	}
	while(!PQ.isEmpty()) {
		if(visited.size() == nodes.size()) break;
		arcT a = PQ.dequeueMin();
		int start = CheckVisited(spans, a.start->city);
		int end = CheckVisited(spans, a.end->city);
		if(start != end) {
			visited.add(a);
			spans[end].str.unionWith(spans[start].str);
			spans.removeAt(start);
		}
	}
}

void MinimunSpanTree(Vector<nodeT> &nodes, string &imageName)
{
	RestoreGraphicsState();
	SaveGraphicsState();
	DrawNamedPicture(imageName);
	PQueue<arcT> PQ(&ArcCmp);
	Vector<arcT> visited;

	for(int i = 0; i < nodes.size(); i++) {
		DrawFilledCircleWithLabel(nodes[i].pt, "Black", nodes[i].city);
	}

	EnqueueArc(nodes, PQ);
	cout << endl;
	CreateMinSpan(nodes, visited, PQ);
	for(int i = 0; i < visited.size(); i++) {
		Pause(0.05);
		DrawLineBetween(visited[i].start->pt, visited[i].end->pt, "Red");
	}
	cout << "\nMinimumSpan Tree is of " << DistanceCover(visited) << " miles";
}

int Menu()
{
	int choice;
	cout <<"1. Open new file" << endl
		 <<"2. Find shortest path" << endl
		 <<"3. Draw minimum spanning tree" << endl
		 <<"4. Exit" << endl
		 << "\nEnter: ";
	choice = GetInteger();
	return choice;
}

int main()
{
	InitGraphics();
	string imageName;
	Vector<nodeT> nodes;

	

	SetWindowTitle("CS106 Pathfinder");
    cout << "This masterful piece of work is a graph extravaganza!" << endl
        << "The main attractions include a lovely visual presentation of the graph" << endl
        << "along with an implementation of Dijkstra's shortest path algorithm and" << endl
        << "the computation of a minimal spanning tree.  Enjoy!" << endl;
	
	NewFile(nodes, imageName);

	while(true) {
		int choice = Menu();
		if(choice == 1){
			nodes.clear();
			imageName = "";
			NewFile(nodes, imageName);
		} else if(choice == 2) { 
			ShortestPath(nodes, imageName);
			cout << "\nPress enter to return:" ;
			GetLine();
		} else if(choice == 3) {
			MinimunSpanTree(nodes, imageName);
			cout << "\nPress enter to return:" ;
			GetLine();
		} else if(choice == 4) {
			break;
		} else {
			cout << "\nInvalid Choice." << endl;
		}
		
		RestoreGraphicsState();
		SaveGraphicsState();
		DrawNamedPicture(imageName);
		DrawGraph(nodes);
	}
	ExitGraphics();
    return 0;
}