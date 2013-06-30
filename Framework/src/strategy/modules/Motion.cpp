/*
 *   Motion.cpp
 *
 *   Author: Wu Chih-En
 *
 */

#include <stdio.h>
#include <math.h>
#include "Motion.h"
#include "Vector.h"

#define PI 3.1415926

using namespace Robot;

Motion* Motion::m_UniqueInstance = new Motion();

Motion::Motion()
{
}

Motion::~Motion()
{
}

void Motion::Initialize()
{
    motors.OpenDeviceAll();
    motors.SetEnableAll();
    motors.ActivateProfileVelocityModeAll();
}

void Motion::LoadINISettings(minIni* ini)
{
    LoadINISettings(ini, TASK_SECTION);
}

void Motion::LoadINISettings(minIni* ini, const std::string &section)
{
    //if((value = ini->getd(section, "pan_p_gain", INVALID_VALUE)) != INVALID_VALUE)  m_Pan_p_gain = value;
    //if((value = ini->getd(section, "pan_d_gain", INVALID_VALUE)) != INVALID_VALUE)  m_Pan_d_gain = value;
    //if((value = ini->getd(section, "tilt_p_gain", INVALID_VALUE)) != INVALID_VALUE) m_Tilt_p_gain = value;
    //if((value = ini->getd(section, "tilt_d_gain", INVALID_VALUE)) != INVALID_VALUE) m_Tilt_d_gain = value;
    //if((value = ini->getd(section, "left_limit", INVALID_VALUE)) != INVALID_VALUE)  m_LeftLimit = value;
    //if((value = ini->getd(section, "right_limit", INVALID_VALUE)) != INVALID_VALUE) m_RightLimit = value;
    //if((value = ini->getd(section, "top_limit", INVALID_VALUE)) != INVALID_VALUE)   m_TopLimit = value;
    //if((value = ini->getd(section, "bottom_limit", INVALID_VALUE)) != INVALID_VALUE)m_BottomLimit = value;
    //if((value = ini->getd(section, "pan_home", INVALID_VALUE)) != INVALID_VALUE)    m_Pan_Home = value;
    //if((value = ini->getd(section, "tilt_home", INVALID_VALUE)) != INVALID_VALUE)   m_Tilt_Home = value;
}

void Motion::SaveINISettings(minIni* ini)
{
    SaveINISettings(ini, TASK_SECTION);
}

void Motion::SaveINISettings(minIni* ini, const std::string &section)
{
    //ini->put(section,   "pan_p_gain",   m_Pan_p_gain);
    //ini->put(section,   "pan_d_gain",   m_Pan_d_gain);
    //ini->put(section,   "tilt_p_gain",  m_Tilt_p_gain);
    //ini->put(section,   "tilt_d_gain",  m_Tilt_d_gain);
    //ini->put(section,   "left_limit",   m_LeftLimit);
    //ini->put(section,   "right_limit",  m_RightLimit);
    //ini->put(section,   "top_limit",    m_TopLimit);
    //ini->put(section,   "bottom_limit", m_BottomLimit);
    //ini->put(section,   "pan_home",     m_Pan_Home);
    //ini->put(section,   "tilt_home",    m_Tilt_Home);
}
void Motion::Process()
{
	double FI = Status::FI;
	double w = Status::w;
	Vector3D vector = Status::vector;
	double cmd[3]={0};
	double robot_radius = 1;
	double angle1 = (PI/6)+FI;
	double angle2 = 5*(PI/6)+FI;
	double angle3 = 3*(PI/2)+FI;
	cmd[0]=-sin(angle1)*(vector.X)+cos(angle1)*(vector.Y)+robot_radius*w;
	cmd[1]=-sin(angle2)*(vector.X)+cos(angle2)*(vector.Y)+robot_radius*w;
	cmd[2]=-sin(angle3)*(vector.X)+cos(angle3)*(vector.Y)+robot_radius*w;
    //printf("%d %d %d\n", (long)cmd[0], (long)cmd[1], (long)cmd[2]);

    motors.SetVelocity(motors.motorHandle0, (long)-cmd[0]);
    motors.SetVelocity(motors.motorHandle1, (long)-cmd[1]);
    motors.SetVelocity(motors.motorHandle2, (long)-cmd[2]);
}