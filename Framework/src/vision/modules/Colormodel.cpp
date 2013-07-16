#include "Colormodel.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace Robot;
using namespace std;


bool Colormodel::HSV_hsvCheckRange_Blue(float hValue, float sValue, float vValue){  
	if(VisionStatus::hsvBlueRange.HueMax >= VisionStatus::hsvBlueRange.HueMin){   
		if(VisionStatus::hsvBlueRange.HueMax >= hValue && VisionStatus::hsvBlueRange.HueMin <= hValue
	   	&& VisionStatus::hsvBlueRange.SaturationMax >= sValue && VisionStatus::hsvBlueRange.SaturationMin <= sValue
	   	&& VisionStatus::hsvBlueRange.BrigshtnessMax >= vValue && VisionStatus::hsvBlueRange.BrightnessMin <= vValue)
		return true;
	}else{
		if( (VisionStatus::hsvBlueRange.HueMax >= hValue || VisionStatus::hsvBlueRange.HueMin <= hValue)
		&& VisionStatus::hsvBlueRange.SaturationMax >= sValue && VisionStatus::hsvBlueRange.SaturationMin <= sValue
		&& VisionStatus::hsvBlueRange.BrightnessMax >= vValue && VisionStatus::hsvBlueRange.BrightnessMin <= vValue)
		return true;
	}
	        return false;
}
bool Colormodel::HSV_hsvCheckRange_Red(float hValue, float sValue, float vValue){  
	if(VisionStatus::hsvRedRange.HueMax >= VisionStatus::hsvRedRange.HueMin){   
		if(VisionStatus::hsvRedRange.HueMax >= hValue && VisionStatus::hsvRedRange.HueMin <= hValue
	   	&& VisionStatus::hsvRedRange.SaturationMax >= sValue && VisionStatus::hsvRedRange.SaturationMin <= sValue
	   	&& VisionStatus::hsvRedRange.BrightnessMax >= vValue && VisionStatus::hsvRedRange.BrightnessMin <= vValue)
			return true;
	}else{
		if( (VisionStatus::hsvRedRange.HueMax >= hValue || VisionStatus::hsvRedRange.HueMin <= hValue)
		&& VisionStatus::hsvRedRange.SaturationMax >= sValue && VisionStatus::hsvRedRange.SaturationMin <= sValue
		&& VisionStatus::hsvRedRange.BrightnessMax >= vValue && VisionStatus::hsvRedRange.BrightnessMin <= vValue)
			return true;
	}
	        return false;
}
bool Colormodel::HSV_hsvCheckRange_Green(float hValue, float sValue, float vValue){  
	if(VisionStatus::hsvGreenRange.HueMax >= VisionStatus::hsvGreenRange.HueMin){   
		if(VisionStatus::hsvGreenRange.HueMax >= hValue && VisionStatus::hsvGreenRange.HueMin <= hValue
	   	&& VisionStatus::hsvGreenRange.SaturationMax >= sValue && VisionStatus::hsvGreenRange.SaturationMin <= sValue
	   	&& VisionStatus::hsvGreenRange.BrightnessMax >= vValue && VisionStatus::hsvGreenRange.BrightnessMin <= vValue)
			return true;
	}else{
		if( (VisionStatus::hsvGreenRange.HueMax >= hValue || VisionStatus::hsvGreenRange.HueMin <= hValue)
		&& VisionStatus::hsvGreenRange.SaturationMax >= sValue && VisionStatus::hsvGreenRange.SaturationMin <= sValue
		&& VisionStatus::hsvGreenRange.BrightnessMax >= vValue && VisionStatus::hsvGreenRange.BrightnessMin <= vValue)
			return true;
	}
	        return false;
}
void Colormodel::Erosion(unsigned char *source, unsigned char *target){
	for(int j=1;j<479;j++){
		for(int i=1;i<639;i++){
				 target[j*640+i]=source[(j-1)*640+(i-1)]&source[(j-1)*640+(i)]&source[(j-1)*640+(i+1)]&
						 source[(j)*640+(i-1)]&source[(j-1)*640+(i+1)]&source[(j+1)*640+(i-1)]&
						 source[(j+1)*640+(i)]&source[(j+1)*640+(i+1)];
	}
		}
}
void Colormodel::Dilation(unsigned char *source, unsigned char *target){
	for(int j=1;j<479;j++){
		for(int i=1;i<639;i++){
			target[j*640+i]=source[(j-1)*640+(i-1)]|source[(j-1)*640+(i)]|source[(j-1)*640+(i+1)]|
					source[(j)*640+(i-1)]|source[(j-1)*640+(i+1)]|source[(j+1)*640+(i-1)]|
					source[(j+1)*640+(i)]|source[(j+1)*640+(i+1)];
		}
	}
}
void Colormodel::Process(){ 
	unsigned char temp [VisionStatus::ImageWidth * VisionStatus::ImageHeight];
	
	cv::Mat hsv;
	cv::cvtColor(VisionStatus::frame, hsv, CV_BGR2HSV);
	for(int WidthCnt = 0; WidthCnt < VisionStatus::ImageWidth; WidthCnt++){
		for(int HeightCnt = 0; HeightCnt < VisionStatus::ImageHeight; HeightCnt++){
						
			float hValue = hsv.data[3*(HeightCnt * VisionStatus::ImageWidth + WidthCnt)+0];
			float sValue = hsv.data[3*(HeightCnt * VisionStatus::ImageWidth + WidthCnt)+1];
			float vValue = hsv.data[3*(HeightCnt * VisionStatus::ImageWidth + WidthCnt)+2];
			//------catch Blue
			if(Colormodel::HSV_hsvCheckRange_Blue(hValue, sValue, vValue)){					 
				VisionStatus::Blue_Ball[(HeightCnt * VisionStatus::ImageWidth + WidthCnt)] = 1;
			}else{
				VisionStatus::Blue_Ball[(HeightCnt * VisionStatus::ImageWidth + WidthCnt)] = 0;			
			}
		}
	}
	Erosion(VisionStatus::Blue_Ball,temp);
	Dilation(temp,VisionStatus::Blue_Ball);
	//SegmentationFunction::SegmentationFunction(TMPWebcamBoolBuffer,VisionStatus::frame.data);
	
	for(int WidthCnt = 0; WidthCnt < VisionStatus::ImageWidth; WidthCnt++){
		for(int HeightCnt = 0; HeightCnt < VisionStatus::ImageHeight; HeightCnt++){
						
			float hValue = hsv.data[3*(HeightCnt * VisionStatus::ImageWidth + WidthCnt)+0];
			float sValue = hsv.data[3*(HeightCnt * VisionStatus::ImageWidth + WidthCnt)+1];
			float vValue = hsv.data[3*(HeightCnt * VisionStatus::ImageWidth + WidthCnt)+2];
			//------catch red
			if(Colormodel::HSV_hsvCheckRange_Red(hValue, sValue, vValue)){
				VisionStatus::Green_BallRed_Ball[(HeightCnt * VisionStatus::ImageWidth + WidthCnt)] = 1;
			}else{
				VisionStatus::Green_BallRed_Ball[(HeightCnt * VisionStatus::ImageWidth + WidthCnt)] = 0;
			}
		}
	}
	Erosion(VisionStatus::Green_BallRed_Ball,temp);
	Dilation(temp,VisionStatus::Green_BallRed_Ball);
	//SegmentationFunction::SegmentationFunction(TMPWebcamBoolBuffer,VisionStatus::frame.data);

	for(int WidthCnt = 0; WidthCnt < VisionStatus::ImageWidth; WidthCnt++){
		for(int HeightCnt = 0; HeightCnt < VisionStatus::ImageHeight; HeightCnt++){
						
			float hValue = hsv.data[3*(HeightCnt * VisionStatus::ImageWidth + WidthCnt)+0];
			float sValue = hsv.data[3*(HeightCnt * VisionStatus::ImageWidth + WidthCnt)+1];
			float vValue = hsv.data[3*(HeightCnt * VisionStatus::ImageWidth + WidthCnt)+2];
			//------catch Green
			if(Colormodel::HSV_hsvCheckRange_Green(hValue, sValue, vValue)){
				VisionStatus::Green_BallGreen_Ball[(HeightCnt * VisionStatus::ImageWidth + WidthCnt)] = 1;
			}else{
				VisionStatus::Green_BallGreen_Ball[(HeightCnt * VisionStatus::ImageWidth + WidthCnt)] = 0;
			}
		}
	}
	Erosion(VisionStatus::Green_BallGreen_Ball,temp);
	Dilation(temp,VisionStatus::Green_BallGreen_Ball);
	//SegmentationFunction::SegmentationFunction(TMPWebcamBoolBuffer,VisionStatus::frame.data);
	
	
}

