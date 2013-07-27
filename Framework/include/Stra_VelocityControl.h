//=============================================
//File name: Stra_VelocityControl
//
//Author   :Hsieh Ming-Hua
//          Transplant form 2012 SKS project
//Phone    :0921307020
//E-mail   :ta180109@hotmail.com
//Update   :2013/07/05
//
//Function :Use S-Function to decide the robot velocity
//          x-axis parameter:dismax, dismin
//          y-axis parameter:speedmax, speedmin
//===============================================

#ifndef Stra_VelocityControlH
#define Stra_VelocityControlH
#include "StrategyModule.h"
#include <stdio.h>
#include <tinyxml.h>
namespace Robot{
	class Stra_VelocityControl : public StrategyModule
	{

	public:
    		~Stra_VelocityControl();   //žÑºcšçŠ¡

		static Stra_VelocityControl*  GetInstance() {return m_UniqueInstance;}
		//static string  ParameterReset(void);           //°ÑŒÆ­«žm

    		void Initialize(void);                  //ªì©l€Æ

    		void Process(void);                     //°õŠæšçŒÆ

	private:

		int loadxml(TiXmlElement* element);  //loadxml

		static Stra_VelocityControl* m_UniqueInstance; 

		Stra_VelocityControl();      //«ØºcšçŠ¡

		void VelocityTransform( double, double, double );   //¶]³æÂI­y¹D³W¹º

   		double S_Function( const double& , const double& , const double& , const double&, double );

   		double Raise_Function( double V, double Cmd );

   		double GoalDistance;

   		double GoalAngle;

   		double HandleAngle;

		double DistanceMax;

   		double DistanceMin;

   		double SpeedMax;

    		double SpeedMin;

		double ThetaMax;

   		double ThetaMin;

    		double OmegaMax;

    		double OmegaMin;

	    	double SpeedCmd;

   	 	double SpeedTmp;

	};
}
#endif
