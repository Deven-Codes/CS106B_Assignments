/*
 * Project: Ruler
 * Created by CS106 C++ Assignment Wizard 0.1
 *
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * [TODO: Describe assignment]
 */

#include <iostream>
#include "graphics.h"
#include "extgraph.h"

void DrawRuler(double x, double y, double w, double h);

int main ()
{
	InitGraphics();
	SetWindowSize(8,4);

	double w = GetWindowWidth();
	double h = GetWindowHeight();
	double x = w/2;
	double y = h/2;

	MovePen(0,0.1);
	DrawLine(w,0);
	DrawRuler(x, y, w, h);

	return 0;
}

void DrawRuler(double x, double y, double w, double h)
{
	if(x < 0.0625 || y < 0.03125) {
		// base case does nothing
	} else {
		MovePen(x,0.1);
		DrawLine(0,y);
		Pause(0.05);
        DrawRuler(x - (w/4), y/2, w/2, h);
		DrawRuler(x + (w/4), y/2, w/2, h);
	}
}
