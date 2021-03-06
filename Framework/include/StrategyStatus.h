/*
 *   StrategyStatus.h
 *
 *   Author: Wu Chih-En
 *
 */

#ifndef _STRATEGY_STATUS_H_
#define _STRATEGY_STATUS_H_

#include "TCoordinate.h"
#include "Vector.h"
#include <vector>
#include "Stra_Task_stage1.h"
#include "Stra_Task_Stage2.h"
#include <tinyxml.h>

namespace Robot
{
class StrategyStatus
{
private:

public:
    //motion data
    static double x;
    static double y;
    static double w;
    static double FI;
    static double CameraAngle;
    static bool SimulatorFlag;
    static TCoordinate StartPosition;
    static TCoordinate EscapePosition;
    static TCoordinate EndPosition;
    static TCoordinate RobotPos;
    static TCoordinate RootHandle;
    static TCoordinate LivRMDoor;
    static TCoordinate LivRMCen;
    static TCoordinate DinRMDoor;
    static TCoordinate DinRMCen;
    static TCoordinate LibDoor;
    static TCoordinate LibCen;
    static TCoordinate BedRMDoor;
    static TCoordinate BedRMCen;
    static TCoordinate ChrgDoor;
    static TCoordinate ChrgCen;

    static int GotoRoomStep;
    //--------------------------------------------------
    // task information
    typedef enum { etFree = 0, etOpen, etClosed, etObstacle, etFocus } teNodeStatus;

    typedef enum { etMotion =0, etAchieve } teAstarStatus;

    typedef struct {
        int Status;
        TCoordinate StartPos;
        TCoordinate GoalPos;
        int PCnt;
    } tsAStarPath;

    typedef struct {
        TCoordinate Origin;
        float Scale;
        int Width,Height;
    } tsMapInfo;

    typedef struct {
        TCoordinate Position;
        float Angle;
        int Distance;
        short UPDown;       //Down : 1 , Up : -1 , Mid : 0 , No ball :-999
        short LeftRight;    //Left : 1 , URightp : -1 , Mid : 0 , No ball :-999
        unsigned char FindBallCnt;
    } tsStraBallInfo;
    static long MotorSpeed[3];

    static int CurrentBallState;

    static int RoomOrder;

    static int FamilyMember;

    static bool FlagMember;

    static bool FlagGrandPa;

    static bool FlagGrandMa;

    static bool FlagFather;

    static bool FlagMother;

    static bool FlagSon;

    static bool Flagdaughter;

    static bool FlagRoomRenew;

    static int ThiefRoom;
    static int RoomSort;
    static int FindBallEn;
    static int LivRM, DinRM, Lib, BedRM;
    static tsAStarPath AStarPath;

    //----------------------------------------------------------------------
    //---------- Strategy --------------------------------------------------
    static TCoordinate Goal1;                   // Target1 vector
    static TCoordinate Goal2;                   // Target2 vector
    static double Direction;                    // Target direction
    static bool FlagDetour;
    static bool FlagForward;

    //----------------------------------------------------------------------
    //----------- Path Plan ------------------------------------------------
    static TCoordinate GoalVector;

    //----------------------------------------------------------------------
    //----------- Avoidance ------------------------------------------------
    static bool FlagAvoidEnable;
    static TCoordinate CorrectionVector;

    //----------------------------------------------------------------------
    //----------- Velocity Control -----------------------------------------
    static float FixSpeed;                                 // Speed Power 1~100 %
    static double MotionDistance;
    static double MotionAngle;
    static TCoordinate PathMotion;
    static float PathRotation;

    //----------------------------------------------------------------------
    static bool PathR_Priority;

    //----------------------------------------------------------------------
    //----------- Ball Data ------------------------------------------------
    static tsStraBallInfo RadBallInfo;
    //tsObjectiveInfo RedBall;
    static unsigned char FindBallCnt;
    static bool FlagRecognize;
    static int CatchBallMode;

    //----------------------------------------------------------------------
    //---------- Laser Average Data ----------------------------------------
    static int LaserAverageData[3];

    //----------------------------------------------------------------------
    //----------------------------------------------------------------------
    static int FindBallState;

    //----------------------------------------------------------------------
    //----------------------------------------------------------------------
    static bool FindLocResample;
    static TCoordinate RseLocPos;

    static bool AStarEnable;
};
}
#endif
