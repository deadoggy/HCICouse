#pragma once
#ifndef  _DETECT_H_
#define _DETECT_H_

#include<string>
#include<vector>
#include<math.h>
#include"Leap.h"
using namespace Leap;

struct GestureModel
{
	std::string GestureName;
	float GestureData[5][4][3][3];
};


class Detect {
public:
	Detect();
	bool compareGesture(GestureModel* gm_1, GestureModel* gm_2);
	bool getGesture(std::string& ret);
	float getAngle(float*  a, float* b);
private:
	Controller* LeapController;
	std::vector<GestureModel*> GestureList;
};
#endif