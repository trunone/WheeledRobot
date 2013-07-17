/*
 *   main.cpp
 *
 *   Author: Wu Chih-En
 */
#define ENABLE_STRATEGY

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <libgen.h>
#include <signal.h>
#include <iostream>
#include <tinyxml.h>

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "Motors.h"
#include "urg_cpp/Urg_driver.h"
#include "urg_cpp/math_utilities.h"

#include "LinuxWheeled.h"

using namespace Robot;
using namespace std;

Motors motors;
qrk::Urg_driver urg;
CvCapture *VisionCapture;

void change_current_dir()
{
    char exepath[1024] = {0};
    if(readlink("/proc/self/exe", exepath, sizeof(exepath)) != -1)
    {
        if(chdir(dirname(exepath)))
            fprintf(stderr, "chdir error!! \n");
    }
}

void sighandler(int sig)
{
    exit(0);
}

int main(void)
{
    signal(SIGABRT, &sighandler);
    signal(SIGTERM, &sighandler);
    signal(SIGQUIT, &sighandler);
    signal(SIGINT, &sighandler);

    change_current_dir();

    TiXmlDocument doc;

    motors.OpenDeviceAll();
    motors.SetEnableAll();
    motors.ActivateProfileVelocityModeAll();
    VisionCapture = cvCaptureFromCAM( -1 );

   ////////////////// Framework Initialize ////////////////////////////
#ifdef ENABLE_VISION
    if(VisionManager::GetInstance()->Initialize(VisionCapture) == false)
    {
        printf("Fail to initialize Vision Manager!\n");
        return 1;
    }

    //VisionManager::GetInstance()->AddModule((VisionModule*)VisionCapture::GetInstance());

    LinuxVisionTimer *vision_timer = new LinuxVisionTimer(VisionManager::GetInstance());
    vision_timer->Start();
#endif
    //-----------------------------------------------------------------------------------//
#ifdef ENABLE_LOCATION
    if(LocationManager::GetInstance()->Initialize(&urg) == false)
    {
        printf("Fail to initialize Location Manager!\n");
        return 1;
    }

    //LocationManager::GetInstance()->AddModule((LocationModule*)LaserCapture::GetInstance());

    LinuxLocationTimer *location_timer = new LinuxLocationTimer(LocationManager::GetInstance());
    location_timer->Start();
#endif
    //-----------------------------------------------------------------------------------//
#ifdef ENABLE_STRATEGY
    if(StrategyManager::GetInstance()->Initialize(&motors) == false)
    {
        printf("Fail to initialize Strategy Manager!\n");
        return 1;
    }

    StrategyManager::GetInstance()->AddModule((StrategyModule*)Motion::GetInstance());

    StrategyManager::GetInstance()->SetEnable(true);

    LinuxStrategyTimer *stragey_timer = new LinuxStrategyTimer(StrategyManager::GetInstance());
    stragey_timer->Start();
#endif
    ///////////////////////////////////////////////////////////////////

//    LinuxActionScript::PlayMP3("../../../Data/mp3/Demonstration ready mode.mp3");

    try
    {
        while(1) {

            string xml;
            LinuxServer new_sock;
            LinuxServer server(10373);
	
            cout << "[Waiting..]" << endl;
            server.accept ( new_sock );
            cout << "[Accepted..]" << endl;	

            try
            {
                while(true){	
                    TiXmlDocument doc;
                    new_sock >> xml;
                    cout << "[success recv]" << endl;
                    doc.Parse(xml.c_str());
                    TiXmlElement* root = doc.FirstChildElement("Command");
                    if(root != NULL) {
                        TiXmlElement* element;
                        element = root->FirstChildElement("ManualDirection");
                        if(element != NULL) {
                            TiXmlElement* child;
                            child = element->FirstChildElement("Rotate");
                            if(child != NULL){
                                child->Attribute("w", &StrategyStatus::w);
                            }
                            child = element->FirstChildElement("Vector");
                            if(child != NULL){
                                child->Attribute("x", &StrategyStatus::x);
                                child->Attribute("y", &StrategyStatus::y);
                            }
                        }
                    }
                    root = doc.FirstChildElement("Config");
                    if(root != NULL) {
                        TiXmlElement* element;
                        element = root->FirstChildElement("Vision");
                        if(element != NULL){
                            cout<<"I got vision"<<endl;
                        }
                    }
                    cout << StrategyStatus::x << StrategyStatus::y << StrategyStatus::w << endl;
                    cout << StrategyStatus::Motor1Speed << StrategyStatus::Motor2Speed << StrategyStatus::Motor3Speed << endl;
                }
            }
            catch ( LinuxSocketException& )
            {
                cout << "[Disconnected]" << endl;
            }
        }
    }
    catch ( LinuxSocketException& e )
    {
        cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
    return 0;
}
