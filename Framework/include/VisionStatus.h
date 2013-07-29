/*
 *   VisionStatus.h
 *
 *   Author: Wu Chih-En
 *
 */
#ifndef _VISION_STATUS_H_
#define _VISION_STATUS_H_
#include <vector>
#include <string>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#define M_PI       3.14159265358979323846

using namespace std;
using namespace cv;
//---------------------------------------------------------------------------

#define cBLACK      colorBGR(0,0,0)
#define cWHITE      colorBGR(255,255,255)
#define cRED        colorBGR(0,0,255)
#define cGREEN      colorBGR(0,255,0)
#define cBLUE       colorBGR(255,0,0)
#define cYELLOW     colorBGR(0,255,255)
#define cMAGENTA    colorBGR(255,0,255)
#define cCYAN       colorBGR(255,0,255)
#define GrayPixel(Scale)    colorBGR(Scale,Scale,Scale)
#define BinaryPixel(White)  (White)?cWHITE:cBLACK
#define EdgeColor 1
#define NaN 0
#define Def_ImgWidth    640
#define Def_ImgHeight   480
#define Def_ImgByte     3
#define Def_ImgSize     307200  //640*480
#define Def_ImgSizeM3   921600  //640*480*3

using namespace cv;

namespace Robot
{
	
	class VisionStatus
	{

	private:

	public:
		struct ColorRange
		{
			double HueMax;
			double HueMin;
			double SaturationMax;
			double SaturationMin;
			double BrightnessMax;
			double BrightnessMin;
		};

        unsigned char *yiqColorModel; 

		//---seg
		
		/*static int Xmax, Xmin, Ymax, Ymin;
		static int PointCnt;
		static void SegmentationInit(int Xvalue, int Yvalue);
		static void SegmentationInsert(int Xvalue, int Yvalue);
		static vector <SegmentLocation> LocationList;*/
	
		//--- Global
		static const int ImageWidth = 640, ImageHeight = 480;

		static Mat frame;
		static Mat send_frame;
		
		static unsigned char Blue_Ball[VisionStatus::ImageWidth * VisionStatus::ImageHeight],
				     Green_Ball[VisionStatus::ImageWidth * VisionStatus::ImageHeight],
				     Red_Ball[VisionStatus::ImageWidth * VisionStatus::ImageHeight];
		static int Red_X,Red_Y,Green_X,Green_Y,Blue_X,Blue_Y;

		//--- ModelUnit
		static ColorRange hsvGreenRange, hsvBlueRange, hsvRedRange;

		static int ColorDeep;

		static int xImageCenter, yImageCenter;
		static int GlobalScanMagnEnd;

		static float AngularToRadian,RadianToAngular;


		static float ComputeCenterAngle(float AngleStartPoint, float AngleEndPoint);

		static Mat VideoFrame;
	
		typedef enum{ etDinRM=0, etBedRM, etLib }teRoomOrder;

		typedef enum{ etGrandPa=0, etGrandMa, etFather, etMother, etSon, etdaughter }teMember;

		typedef enum{ BLUE=0 , GREEN=1 , RED=2 , B=0 , G=1 , R=2 }BGRcolor;

		typedef enum{ Y=0 , U=1 , V=2}YUVcolor;
	
		typedef struct{
            unsigned char ColorEle[3];
		}tsColor;

		typedef struct{
            int CenterX;
		  	int CenterY;
            int InternalRadius;
            int ExternalRadius;
            void LoadSetting();
            void WriteSetting();
            unsigned char BinaryThreshold;
		}tsImgProSet;

		typedef struct{
	    	unsigned char* ImgData;
	    	int Width;
	    	int Height;
	    	int Dimension;
	    	tsColor GetColor(int x,int y);
	    	unsigned char*  GetPixelPtr(int x,int y);
	    	void SetColor(int x,int y ,tsColor cBGR);
	    	void SetColor(int x,int y ,unsigned char* Color);
		}tsBmpPtr;

		typedef struct{
	    	bool enable;

		    typedef struct{
                float Distance;
                float Pixel;
            }tsDisPixel;

            tsDisPixel *DisPixel_Model ;
	    	
            int ModelNum;

	    	float Pixel2Distance(int pixel);

	    	void  LoadModel();

	    	void  WriteModel();

		}tsImgDisModel;

		tsColor colorBGR (unsigned char B ,unsigned char G , unsigned char R);

		//---------------------------------------------------------------------------
        typedef struct{
			int X;
			int Y;
        }tsCoordinate;

        typedef struct{
			short int Cx;
			short int Cy;
			short int Cr;
			short int PixelDistance;
			double Angle;
        }tsObjectiveInfo;
	//----------------------------------------

    	typedef struct{

        	tsCoordinate LeftUp;

        	tsCoordinate RightDown;

        	unsigned int countcolor;

    	}tsRecord_Blockinfo;

	//---------------------------------------------------------------------------



        enum{OrangeLabel = 0x01, YellowLabel = 0x02, BlueLabel = 0x04
            , GreenLabel = 0x08, BlackLabel = 0x10, RedLabel = 0x20
            , OthersLabel = 0x80};

        struct CIRCLE
        {
            short int CCX;
            short int CCY;
            short int Rr;
        };

        typedef struct{
            unsigned char Y;
            unsigned char U;
            unsigned char V;
        }tsYUVData;

	//--------------------------------------------------------------------------
		//TImg(void);
		//~TImg(void);
		//static unsigned char ColorSegmentation(unsigned char yValue, unsigned char uValue, unsigned char vValue);
		//static double ComputeCenterAngle(double AngleStartPoint, double AngleEndPoint);
		//static void LoadModelFromFile(AnsiString FileString);
		//static void SaveColorRangeFormFile(AnsiString FileString);
		//static void LoadColorRangeFormFile(AnsiString FileString);

		//static int ImageWidth, ImageHeight, ImageByte;		//影像的寬、高、大小
		//static int ImageLevel;
		//static double AngularToRadian, RadianToAngular;
		//static ColorRange *hsvBlueRange, *hsvBlackRange, *hsvGreenRange, *hsvOrangeRange, *hsvYellowRange, *hsvRedRange;
		//static unsigned char *pImage;
		//static unsigned char *pWebCamImage;
		//static unsigned char *pFindEdgeImage;

		static tsObjectiveInfo BallInfo;
		static tsBmpPtr Image;
		static tsImgProSet ProcessSetting;
		static tsImgDisModel DisModel;
		static tsYUVData *RGBtoYUV_Table;

        static unsigned char PixelGrayScale(tsColor Pixel);
        static bool PixelBinarization(tsColor Pixel, unsigned char Threshold );
        static void ImgGrayScale   (tsBmpPtr Image);
        static void ImgBinarization(tsBmpPtr Image, unsigned char Threshold);


	//------ FaceData ----------------------------------------------------------
		static unsigned char Favg[40*40*3];
		static float FeatureFaceW[40*40*3];
		static float cvGet2D_1;
		static float cvGet2D_2;
		static float cvGet2D_3;
		static float cvGet2D_4;
		static float cvGet2D_5;
		static float cvGet2D_6;
		static float cvGet2D_7;
		static float cvGet2D_8;
		static float cvGet2D_9;
		static float cvGet2D_10;
		static float cvGet2D_11;
		static float cvGet2D_12;

	};
}

#endif
