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
	std::vector<float> xParams;
	xParams.push_back(10);
	xParams.push_back(yStart);
	x.SetParameters(xParams);

	RungeKutta y(dydt, yStart, tStart, tStep);
	std::vector<float> yParams;
	yParams.push_back(28.0f);
	yParams.push_back(xStart);
	yParams.push_back(zStart);
	y.SetParameters(yParams);

	RungeKutta z(dzdt, zStart, tStart, tStep);
	std::vector<float> zParams;
	zParams.push_back(xStart);
	zParams.push_back(yStart);
	zParams.push_back(8.0f/3.0f);
	z.SetParameters(zParams);

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
