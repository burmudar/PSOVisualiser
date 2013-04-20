#ifndef CHART2DPLOTTER_H_
#define CHART2DPLOTTER_H_
#include <iostream>
#include "SDL_opengl.h"
#include <list>
#include <cmath>
//(0,768) 		(1024,768)
//
//
//
//(0,0) 		(1024,0)
enum AXIS { X,Y};
class Chart2DPlotter
{
public:
	Chart2DPlotter(float startx,float starty,float endx,float endy,float borderwidth);
	~Chart2DPlotter();
	void Plot(float x,float y);
	void DrawChart();
	void DrawGrid(bool val);
	void Clear();
	void Test();
	bool MustDrawGrid();
private:
	void Loose_label();
	void DrawAxis();
	void DrawTicks();
	void CalculateZeroYAxisPosition();
	float PixelGraphShift(float pixel_position,const AXIS& axis);
	float CalculatePixelPosition(float& value_on_axis,const AXIS& axis);
	float BestTick(float largest, float mostticks);
	float NiceNumber(float value,bool round);
	float chart_pixel_start_x;
	float chart_pixel_start_y;
	float chart_pixel_end_x;
	float chart_pixel_end_y;
	float max_x_axis_value;
	float max_y_axis_value;
	float min_x_axis_value;
	float min_y_axis_value;
	float change_in_graph_pixel_x;
	float change_in_graph_pixel_y;
	float zero_y_axis_value_pixel_position; // The position of where 0 is on the y axis in pixels
	std::list<float> x_values;
	std::list<float> y_values;
	bool grid;
};
#endif
