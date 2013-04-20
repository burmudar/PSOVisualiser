#include "Chart2DPlotter.h"

using namespace std;

Chart2DPlotter::Chart2DPlotter(float startx,float starty,float endx,float endy,float borderwidth)
{
	chart_pixel_start_x = startx + borderwidth;
	chart_pixel_start_y = starty + borderwidth;
	chart_pixel_end_x = endx - borderwidth;
	chart_pixel_end_y = endy - borderwidth;
	change_in_graph_pixel_x = chart_pixel_end_x - chart_pixel_start_x;
	change_in_graph_pixel_y = chart_pixel_end_y - chart_pixel_start_y;
	max_x_axis_value = 0;
	max_y_axis_value = 0;
	min_x_axis_value = 0;
	min_y_axis_value = 0;
	zero_y_axis_value_pixel_position = chart_pixel_start_x;
	grid = false;
}

Chart2DPlotter::~Chart2DPlotter()
{
}

void Chart2DPlotter::DrawGrid(bool val)
{
	grid = val;
}

bool Chart2DPlotter::MustDrawGrid()
{
	return grid;
}

void Chart2DPlotter::DrawAxis()
{
	glColor3f(1,0,0);
	glBegin(GL_LINES);
	glVertex2f(chart_pixel_start_x,chart_pixel_start_y);//Start of y axis
	glVertex2f(chart_pixel_start_x,chart_pixel_end_y);
	if (zero_y_axis_value_pixel_position != chart_pixel_start_y)
	{
		glVertex2f(chart_pixel_start_x,zero_y_axis_value_pixel_position);
		glVertex2f(chart_pixel_end_x,zero_y_axis_value_pixel_position);
	}
	glVertex2f(chart_pixel_start_x,chart_pixel_start_y);//Start of x axis
	glVertex2f(chart_pixel_end_x,chart_pixel_start_y);
	glEnd();
}

void Chart2DPlotter::DrawTicks()
{
	float x = 0;
	float y = 0;
	float xtick = BestTick(max_x_axis_value,10);
	float ytick = BestTick(max_y_axis_value,10);
	glBegin(GL_LINES);
	glColor3f(1.0,0.0,0.0);
	switch(grid)
	{
		case false:
			{
			for(float i = min_x_axis_value;i <= max_x_axis_value;i += xtick)
				{
					x = PixelGraphShift(CalculatePixelPosition(i,X),X);
					glVertex2f(x,zero_y_axis_value_pixel_position );
					glVertex2f(x,zero_y_axis_value_pixel_position + 5);
				}
			for(float i = min_y_axis_value;i <= max_y_axis_value;i += ytick)
				{
					y = PixelGraphShift(CalculatePixelPosition(i,Y),Y);
					glVertex2f(chart_pixel_start_x,y);
					glVertex2f(chart_pixel_start_x+5,y);
				}
			}
		break;
		case true:
			{
				for(float i = min_x_axis_value;i <= max_x_axis_value;i += xtick)
				{
					x = PixelGraphShift(CalculatePixelPosition(i,X),X);
					glVertex2f(x,chart_pixel_start_y);
					glVertex2f(x,chart_pixel_end_y);
				}
				for(float i = min_y_axis_value;i <= max_y_axis_value;i += ytick)
				{
					y = PixelGraphShift(CalculatePixelPosition(i,Y),Y);
					glVertex2f(chart_pixel_start_x,y);
					glVertex2f(chart_pixel_end_x,y);
				}
			}
		break;
	}
	glEnd();
}

/*
	Method keeps track of where Zero lies on the Y Axis
*/
void Chart2DPlotter::CalculateZeroYAxisPosition()
{
	float y_axis_value_range = abs(max_y_axis_value) + abs(min_y_axis_value);
	float zero_y_axis_value = y_axis_value_range - abs(max_y_axis_value);//Calculation of where the y = 0 lies between the max and min y axis values
	zero_y_axis_value_pixel_position = CalculatePixelPosition(zero_y_axis_value,Y) + chart_pixel_start_y ;
}

/*
	Given the value and the axis to which the value corresponds, the method calculates where the correct pixel position is to represent the 
	value correctly on the given axis. The calculation is intended to perform the following:
	Max = 10
	Min = -10
	Range = |10| + |-10| = 20
	Value = -5
	Change in graph pixel x = 200
	To get the position we normalize the value to get a number between 0 and 1
	-5/20 = -0.25
	-0.25 * 200 = -50
	This is why we keep track of the zero axis pixel position since we can't draw past 0.
	ZeroAxis = (Range - Max) / Range * 200
	PixelPosition = -50 + ZeroAxis
	TODO: Must we still keep track of the Axis if we just return an absolute value of the calculated pixel ?
*/
float Chart2DPlotter::CalculatePixelPosition(float& value_on_axis,const AXIS& axis)
{
	switch(axis)
	{
		case X:
		{
			float x_axis_value_range = abs(max_x_axis_value) + abs(min_x_axis_value);
			return (value_on_axis / x_axis_value_range) * change_in_graph_pixel_x;
		}
		break;
		case Y:
		{
			float y_axis_value_range = abs(max_y_axis_value) + abs(min_y_axis_value);
			return (value_on_axis / y_axis_value_range) * change_in_graph_pixel_y;
		}
		break;
	}
	return chart_pixel_start_x;
}
// Shifts the pixel to the correct chart display position
float Chart2DPlotter::PixelGraphShift(float pixel_position,const AXIS& axis)
{
	switch(axis)
	{
		case X:return pixel_position + chart_pixel_start_x; 
		break;
		case Y:return pixel_position + zero_y_axis_value_pixel_position;
		break;
	}
	return pixel_position;
}

float Chart2DPlotter::BestTick(float largest,float mostticks)
{
	float minimum = largest / mostticks;
	float magnitude = pow(10,floor(log10(minimum) / log10(10)));
	float residual = minimum / magnitude;
	float tick = 1;
	if (residual >= 5)
	{
		tick = 10 * magnitude;
	}
	else if (residual >= 2)
	{
		tick = 5 * magnitude;
	}
	else if (residual >= 1)
	{
		tick = 2 * magnitude;
	}
	return tick;
}

void Chart2DPlotter::Loose_label()
{
	int nfrac;
	float d;
	float graphmin;
	float graphmax;
	float range;
	float x,y;
	range = NiceNumber(max_x_axis_value - min_x_axis_value,false);
	d = NiceNumber(range / 10 -1,true);
	graphmin = floor(min_x_axis_value / d)*d;
	graphmax = ceil(max_x_axis_value / d)*d;
	float val = -1* floor(log10(d));
	if (val > 0)
		nfrac = val;
	else nfrac = 0;
	glBegin(GL_LINES);
	for(float i =graphmin; i <= graphmax + 0.5*d; i+=d)
	{
		x = PixelGraphShift(CalculatePixelPosition(i,X),X);
		glVertex2f(x,zero_y_axis_value_pixel_position );
		glVertex2f(x,zero_y_axis_value_pixel_position + 5);
	}
	range = NiceNumber(max_y_axis_value - min_y_axis_value,false);
	d = NiceNumber(range / 10 -1,true);
	graphmin = floor(min_y_axis_value /d)*d;
	graphmax = ceil(max_y_axis_value /d)*d;
	val = -1* floor(log10(d));
	if (val > 0)
		nfrac = val;
	else nfrac = 0;
	for(float i =graphmin; i <= graphmax + 0.5*d; i+=d)
	{
		y = PixelGraphShift(CalculatePixelPosition(i,Y),Y);
		glVertex2f(chart_pixel_start_x,y);
		glVertex2f(chart_pixel_start_x+5,y);
	}
	glEnd();
}

float Chart2DPlotter::NiceNumber(float value, bool round)
{
	int exp = 0; //exponent of x
	float f  = 0;//fractional part of x
	float nf = 0;//nice, rounded fraction
	exp = floor(log10(value));
	f = value / pow(10.0,(double)exp);
	if (round)
	{
		if (f < 1.5)
			nf = 1;
		else if(f < 3)
			nf = 2;
		else if(f < 7)
			nf = 5;
		else
			nf =10;
	}
	else
	{
		if (f <= 1)
			nf = 1;
		else if(f <= 2)
			nf = 2;
		else if(f <= 5)
			nf = 5;
		else nf = 10;
	}
	return nf*pow(10.0,(double)exp);
}

void Chart2DPlotter::Clear()
{
	x_values.clear();
	y_values.clear();
	max_x_axis_value = 0;
	max_y_axis_value = 0;
	min_x_axis_value = 0;
	min_y_axis_value = 0;
	zero_y_axis_value_pixel_position = chart_pixel_start_y;
}

void Chart2DPlotter::Plot(float x,float y)
{
	x_values.push_back(x);
	y_values.push_back(y);
	if (x > max_x_axis_value)
	{
		max_x_axis_value = x + (x * 0.05);
	}
	if (x < min_x_axis_value)
	{
		min_x_axis_value = x;
	}
	if(y > max_y_axis_value)
	{
		max_y_axis_value = y + (y * 0.05);
		max_y_axis_value = ceil(max_y_axis_value);
		CalculateZeroYAxisPosition();
	}
	if (y < min_y_axis_value)
	{
		min_y_axis_value = floor(y);
		if (min_y_axis_value < 0.0000000001)
		{
			min_y_axis_value += min_y_axis_value * 0.05;
		}
		CalculateZeroYAxisPosition();
	}
}

void Chart2DPlotter::DrawChart()
{
	float x,y;

	DrawAxis();
	//DrawTicks();
	Loose_label();
	glColor3f(0,0,0);
	glBegin(GL_LINE_STRIP);
	list<float>::iterator xpos;
	list<float>::iterator ypos;
	xpos = x_values.begin();
	ypos = y_values.begin();
	while(xpos!=x_values.end() && ypos!=y_values.end())
	{
		//x = ((pixels_per_spacing_x*x_values[i])+chart_pixel_start_x) ;
		x = PixelGraphShift(CalculatePixelPosition(*xpos,X),X) ;
		y = PixelGraphShift(CalculatePixelPosition(*ypos,Y),Y);
		if (y < 20)
		{
			int i;
			cin >> i;
		}
		xpos++;
		ypos++;
		glVertex2f(x,y);
	}
	glEnd();
}

void Chart2DPlotter::Test()
{
	BestTick(-0.788,10);
	Clear();
}
