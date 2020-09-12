/*
 * Project: Maze
 * Created by CS106 C++ Assignment Wizard 0.1
 *
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * [TODO: Describe assignment]
 */

#include <iostream>
#include "maze.h"
#include "graphics.h"
#include "simpio.h"
#include "Vector.h"
#include "random.h"
#include "stack.h"
#include "queue.h"


using namespace std;

struct point {
	int status;
	pointT pt;
};

Vector<point> Points;
Queue<pointT> PtList;
Vector<pointT> in_Point;
Vector<Stack<pointT> > PtStack;

pointT endPt;
int rows, cols;

void AddData();
void CreateMaze(Maze & m);
int Index(pointT p);
bool CheckStatus();
pointT NextPoint(pointT curPt, Maze & m);
Stack<pointT> solveMaze(Maze &m);
void drawSolution(Stack<pointT> path, Maze &m);
Vector<pointT> findNeighbors(Maze m, pointT position);
bool pointsEqual(pointT p1, pointT p2);


int main ()
{	
	Randomize();
	string s;
	while(true) {
		
		cout << "Enter number of rows: ";
		rows = GetInteger();
		cout << "Enter number of columns: ";
		cols = GetInteger();
		AddData();
		//InitGraphics();
		Maze m(rows, cols, true);
		m.draw();
		CreateMaze(m);
		cout << "Press Enter to solve.";
		GetLine();
		Stack<pointT> solution = solveMaze(m);
        drawSolution(solution,m);
        cout << "Whew, that was a fun one!  Want me to solve another maze, Y/N? ";
        string choice = GetLine();
        if(choice == "N" || choice == "n") {
                cout << "Okay, bye!" << endl;
                break;
        }
		Points.clear();
	}

	return 0;
}

void AddData() 
{
	point data;
	data.status = 0;
	for(int i = 0; i < rows; i++) {
		data.pt.row = i;
		for(int j = 0; j < cols; j++) {
			data.pt.col = j;
			Points.add(data);
		}
	}
}

void CreateMaze(Maze & m) {
	pointT curPt;
	curPt.row = RandomInteger(0, (rows -1));
	curPt.col = RandomInteger(0, (cols -1));
	Points[Index(curPt)].status = 1;

	while(true) {
		if(CheckStatus()) break;
		pointT nextPt = NextPoint(curPt, m);
		if(Points[Index(nextPt)].status == 0) {
			m.setWall(curPt, nextPt, false);
			Points[Index(nextPt)].status = 1;
		}
		curPt = nextPt;
	}

}

int Index(pointT p) {
	return (p.row * cols) + p.col;
}

bool CheckStatus() {
	for(int i = 0; i < Points.size(); i++) {
		if(Points[i].status == 0) return false;
	}
	return true;
}

pointT NextPoint(pointT curPt, Maze & m)
{
	pointT nextPt;
	while(true) {
		if(RandomChance(0.5)) {
			if(RandomChance(0.5)) {
				nextPt.row = curPt.row - 1;
			} else {
				nextPt.row = curPt.row + 1;
			}
			nextPt.col = curPt.col;
		} else {
			if(RandomChance(0.5)) {
				nextPt.col = curPt.col - 1;
			} else {
				nextPt.col = curPt.col + 1;
			}
			nextPt.row = curPt.row;
		}
		if(m.pointInBounds(nextPt)) break;
	}
	return nextPt;
}

Stack<pointT> solveMaze(Maze &m){
 Queue<Stack<pointT> > possible_paths;                      //This queue holds many possible paths, each of which is a stack of pointTs.
 
 pointT goal = {rows-1, cols-1};          //defining the "goal" cell as the top-right corner

 pointT origin = {0,0};                                     //defining the "origin" cell as the bottom-left corner

 Stack<pointT> path_0;                                      //Generates the first path, which starts at the origin.
 path_0.push(origin);                                       //Pushes two copies of the origin cell onto the stack to guard against an error 
 path_0.push(origin);                                       //in the anti-backtracking line during the very first iteration of the loop when the Stack size is 1.
                                                            
 possible_paths.enqueue(path_0);                            //Pushes our first stack into the queue!
 
 Stack<pointT> current_path;
 while(true) {
    current_path = possible_paths.dequeue();                // get the next stack from our queue
    if(pointsEqual(current_path.peek(), goal)) { break;}    // if the topmost cell in the stack is the goal cell, this path is complete! maze solved.
    pointT current_pos = current_path.pop();                // get the topmost point from our stack of points - this is the current endpoint of the path in progress.
    
    Vector<pointT> neighbors = findNeighbors(m, current_pos);   // get possible neighbor cells for the current position.

        for(int i = 0; i < neighbors.size(); i++){          // this loop generates an "offshoot" path for each valid possible next step, 
                                                            // and then adds these offshoot paths back to the queue.

            if(!m.isWall(current_pos, neighbors[i]) &&      // checks 2 conditions for a valid move.  must be no wall present, and 
            !pointsEqual(neighbors[i],current_path.peek())) // the next step must not be the same as the previous step (to prevent backtracking).
            {
                Stack<pointT> next_path = current_path;     // makes a copy of the current path
                next_path.push(current_pos);                // puts the current position back onto the "next path" stack
                next_path.push(neighbors[i]);               // puts the newly identified valid next move onto the "next path" stack
                possible_paths.enqueue(next_path);          // puts the "next path" into the main queue.
            }
        }
 }
 return current_path;                                       // returns the current_path after the while loop breaks - this is the solution to the maze.
}

/*
 * FUNCTION: drawSolution
 * -------------------------
 * This function takes the solution path (a Stack of pointTs), inverts it,
 * and then asks the Maze object to display the solution cell-by-cell, with a brief pause
 * between each mark so that the user can see the "progress" from start cell to finish cell.
 */ 


void drawSolution(Stack<pointT> path, Maze &m){
    
    Stack<pointT> inverted_path;                    // inverting the stack so that the maze path will print out from start to finish.
    while(!path.isEmpty()) {
        inverted_path.push(path.pop());
    }
    
    while(!inverted_path.isEmpty()){
        m.drawMark(inverted_path.pop(), "red");     // draw a mark at each of the cells along the solution path.
      //  Pause(.01);                                 // slight Pause included so that user can see "motion" or "progress"
    }
}

bool pointsEqual(pointT p1, pointT p2){
    if (p1.row == p2.row && p1.col == p2.col) { 
        return true;
    } else { 
        return false;
    }
}

Vector<pointT> findNeighbors(Maze m, pointT position) {
    Vector<pointT> neighbors;
    for(int i = 0; i < 4; i++){
        
    // populates "neighbors" with 4 copies of the current position.  
    // it will then edit each position to generate the possible neighbor coordinates.
        neighbors.add(position);    
    }
    neighbors[0].row += 1;          // this defines the "north neighbor"
    neighbors[1].col += 1;          // east neighbor
    neighbors[2].row -= 1;          // south neighbor
    neighbors[3].col -= 1;          // west neighbor
    
    // collects only the neighbors that are within the legal bounds of the maze
    Vector<pointT> in_bounds_neighbors;     
    for(int i = 0; i < 4; i++){
        if(m.pointInBounds(neighbors[i])) {
            in_bounds_neighbors.add(neighbors[i]);
        }
    }
return in_bounds_neighbors;
}