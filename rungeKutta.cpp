#include "rungeKutta.hpp"

RungeKutta::RungeKutta(float (&f)(float, float, std::vector<float>), const float &y_0, const float &t_0, const float &tStep) : m_F(f), m_Y0(y_0), m_T0(t_0), m_Dt(tStep)
{
	m_Steps.push_back(m_Y0);
	m_TSteps.push_back(m_T0);
}

RungeKutta::~RungeKutta()
{

}

const void RungeKutta::Step()
{
	float k1 = m_K1();
	float k2 = m_K2(k1);
	float k3 = m_K3(k2);
	float k4 = m_K4(k3);

	m_Steps.push_back( m_Steps.back() + ( m_Dt * (1.0f/6.0f) * ( k1 + (2.0f * k2) + (2.0f * k3) + k4 ) ) );
	m_TSteps.push_back(m_Dt + m_TSteps.back());
}

const float RungeKutta::m_K1()
{
	return m_F(m_TSteps.back(), m_Steps.back(), m_Param);
}

const float RungeKutta::m_K2(const float &k_1)
{
	return m_F(m_TSteps.back() + (m_Dt/2.0f), m_Steps.back() + ((m_Dt * k_1)/2.0f), m_Param);
}

const float RungeKutta::m_K3(const float &k_2)
{
	return m_F(m_TSteps.back() + (m_Dt/2.0f), m_Steps.back() + ((m_Dt * k_2)/2.0f), m_Param);
}

const float RungeKutta::m_K4(const float &k_3)
{
	return m_F(m_TSteps.back() + m_Dt, m_Steps.back() + (m_Dt * k_3), m_Param);
}

const void RungeKutta::SaveValues(std::string filename)
{
	std::ifstream is;
	is.open(filename);
	if(is)
	{
		std::cout<<"file \"" << filename << "\" already exists" << std::endl;
		return;
	}
	is.close();

	std::ofstream fs;
	fs.open(filename);
	for(auto &elem : m_Steps)
	{
		fs << elem << "\t";
	}
	fs.close();

}

const void RungeKutta::SaveTSteps(std::string filename)
{
	std::ifstream is;
	is.open(filename);
	if(is)
	{
		std::cout<<"file \"" << filename << "\" already exists" << std::endl;
		return;
	}
	is.close();

	std::ofstream fs;
	fs.open(filename);
	for(auto &elem : m_TSteps)
	{
		fs << elem << "\t";
	}
	fs.close();

}

const void RungeKutta::SetParameters(const int num, ...)
{
	va_list args;
	va_start(args, num);
	for(int i=0; i<num; i++)
	{
		m_Param.push_back(va_arg(args,double));
	}
	va_end(args);
}

const void RungeKutta::UpdateParameter(const unsigned int index, const float value)
{
	m_Param[index] = value;
}

const float RungeKutta::GetLast()
{
	return m_Steps.back();
}
