/*
 * Project: chaosGame
 * Created by CS106 C++ Assignment Wizard 0.1
 *
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * [TODO: Describe assignment]
 */

#include <iostream>
#include "genlib.h"
#include "simpio.h"
#include "graphics.h"
#include "extgraph.h"
#include "random.h"

using namespace std;

void GetPoints();
void DrawTriangle();
void DrawPoints();
void ChaosGame();
double GetDiffPoint(double d1, double d2);
void PenColor();

/* x and y coordinate of points */
double x[3];
double y[3];

int main ()
{
	double width = 10.0;
	double height = 7.0;
	string title = "Chaos Game";
	SetWindowSize(width, height);
	SetWindowTitle(title);
	InitGraphics();
	Randomize();
	GetPoints();
	//DrawTriangle();
	ChaosGame();
	WaitForMouseUp();
	WaitForMouseDown();
	ExitGraphics();

	return 0;	
}

void GetPoints()
{
	double r = 0.0125;
	for(int i = 0; i < 3; i++) {
		WaitForMouseDown();
		x[i] = GetMouseX();
		y[i] = GetMouseY();
		cout << "Point " << (i + 1) << " : (" << x[i] << ", " << y[i] << ")" << endl;
		MovePen((x[i] + r), (y[i] + r));
		DrawPoints();
		WaitForMouseUp();
	}
}

void DrawTriangle()
{

	double prevX;
	double prevY;
	double curX;
	double curY;

	for(int i = 0; i < 2; i++) {
		prevX = x[i];
		prevY = y[i];
		curX = x[i+1];
		curY = y[i+1];
		MovePen(curX, curY);
		DrawLine((prevX - curX), (prevY - curY));
		if(i == 1) {
			prevX = x[i+1];
			prevY = y[i+1];
			curX = x[i-1];
			curY = y[i-1];
			MovePen(curX, curY);
			DrawLine((prevX - curX), (prevY - curY));
		}
	} 
}

void DrawPoints()
{	
	double r = 0.0125;
	StartFilledRegion(1.0);
	DrawArc(r, 0, 360);
	EndFilledRegion();
}

void ChaosGame()
{
	
	int i = RandomInteger(0, 2);
	double curX = x[i];
	double curY = y[i];
	double prevX = 0;
	double prevY = 0;
	
	MovePen(curX, curY);

	
	while(true)
	{
		if(MouseButtonIsDown()) break;
		prevX = curX;
		prevY = curY;
		i = RandomInteger(0, 2);
		curX = x[i];
		curY = y[i];
		double pointX = GetDiffPoint(prevX, curX);
		double pointY = GetDiffPoint(prevY, curY);
		MovePen(pointX, pointY);
		PenColor();
		DrawPoints();
		curX = pointX;
		curY = pointY;
		UpdateDisplay();
	}
}

double GetDiffPoint(double d1, double d2)
{
	double result;
	if(d1 > d2) {
		result = d2 + ((d1 - d2) / 2);
	} else {
		result = d1 + ((d2 - d1) / 2);
	}
	return result;
}

void PenColor()
{
	double i = RandomReal(0, 1);
	double j = RandomReal(0, 1);
	double k = RandomReal(0, 1);
	SetPenColorRGB(i, j, k);
}

