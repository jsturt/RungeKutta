#include <iostream>
#include <cmath>
#include <vector>
#include "rungeKutta.hpp"

float dxdt(float t, float x, std::vector<float> p)
{
	return p[0]*(p[1] - x);
}

float dydt(float t, float y, std::vector<float> p)
{
	return (p[0] * p[1]) - y - (p[1] * p[2]);
}

float dzdt(float t, float z, std::vector<float> p)
{
	return (p[0] * p[1]) - (p[2] * z);
}

int main()
{
	float tStart = 0.0f;
	float tStep = 0.01f;
	float xStart = 1.0f;
	float yStart = 1.0f;
	float zStart = 20.01f;
	unsigned int numSteps = 10000;

	RungeKutta x(dxdt, xStart, tStart, tStep);
	x.SetParameters(2, 10.0f, yStart);

	RungeKutta y(dydt, yStart, tStart, tStep);
	y.SetParameters(3, 28.0f, xStart, yStart);

	RungeKutta z(dzdt, zStart, tStart, tStep);
	z.SetParameters(3, xStart, yStart, 8.0f/3.0f);
	
	for(unsigned int i=0; i<numSteps; i++)
	{
		x.UpdateParameter(1, y.GetLast());
		x.Step();
		y.UpdateParameter(1, x.GetLast());
		y.UpdateParameter(2, z.GetLast());
		y.Step();
		z.UpdateParameter(0, x.GetLast());
		z.UpdateParameter(1, y.GetLast());
		z.Step();
	}

	x.SaveTSteps("tsteps.txt");

	x.SaveValues("xvalues.txt");
	y.SaveValues("yvalues.txt");
	z.SaveValues("zvalues.txt");

	return 0;
}
