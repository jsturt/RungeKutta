#include <iostream>
#include <vector>
#include <cstdarg>
#include <string>
#include <fstream>

class RungeKutta
{
public:
	RungeKutta(float (&f)(float, float, std::vector<float>), const float &y_0, const float &t_0, const float &tStep);
	~RungeKutta();
	const void Step();
	const void SaveValues(std::string filename);
	const void SaveTSteps(std::string filename);
	const void SetParameters(const int num, ...);
	const void UpdateParameter(const unsigned int index, const float value);
	const float GetLast(); 
private:
	const float m_Dt;
	std::vector<float> m_Steps;
	std::vector<float> m_TSteps;
	float (&m_F)(float, float, std::vector<float>);
	const float m_Y0;
	const float m_T0;
	std::vector<float> m_Param;

	const float m_K1();
	const float m_K2(const float &k_1);
	const float m_K3(const float &k_2);
	const float m_K4(const float &k_3);

};
