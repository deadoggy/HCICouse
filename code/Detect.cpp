#include"Detect.h"
#include<fstream>
#include<math.h>
Detect::Detect()
{
	LeapController = new Controller();
	std::ifstream ReadFile ("gesdata.dat");
	std::string  TempName;
	while (ReadFile >> TempName)
	{
		GestureModel* gm = new GestureModel;
		gm->GestureName = TempName;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					ReadFile >> gm->GestureData[i][j][k][0];
					ReadFile >> gm->GestureData[i][j][k][1];
					ReadFile >> gm->GestureData[i][j][k][2];
				}
			}
		}
		GestureList.push_back(gm);
	}
}

bool Detect::compareGesture(GestureModel* gm_1, GestureModel* gm_2)
{
	float angle[19] = {0.0};
	float avg_angle = 0.0;
	float variance = 0.0;
	int index = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (0 == i && 0 == j)
			{
				continue;
			}
			angle[index] = getAngle(gm_1->GestureData[i][j][2], gm_2->GestureData[i][j][2]);
			avg_angle += angle[index];
			index++;
		}
	}
	for (int i = 0; i < 19; i++)
	{
		variance += (angle[i] - avg_angle) * (angle[i] - avg_angle);
	}
	variance = variance/19;
	if (variance <= 14)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

bool Detect::getGesture(std::string& ret)
{
	if(false == LeapController->isConnected())
	{
		return false;
	}
	HandList HL = LeapController->frame().hands();
	Hand     hand = HL[0];
	FingerList fingers = hand.fingers();
	GestureModel * gm = new GestureModel;
	Leap::Matrix handTransform = hand.basis();
	handTransform.origin = hand.palmPosition();
	handTransform = handTransform.rigidInverse();
	//get gesture data
	int i = 0;
	for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
		const Finger finger = *fl;
		// Get finger bones
		for (int b = 0; b < 4; ++b) {
			Bone::Type boneType = static_cast<Bone::Type>(b);
			Bone bone = finger.bone(boneType);
			Leap::Vector ori = bone.prevJoint();
			Leap::Vector tP = handTransform.transformPoint(ori);
			gm->GestureData[i][b][0][0] = tP[0];
			gm->GestureData[i][b][0][1] = tP[1];
			gm->GestureData[i][b][0][2] = tP[2];
			tP = handTransform.transformPoint(bone.nextJoint());
			gm->GestureData[i][b][1][0] = tP[0];
			gm->GestureData[i][b][1][1] = tP[1];
			gm->GestureData[i][b][1][2] = tP[2];
			tP = handTransform.transformPoint(bone.direction());
			gm->GestureData[i][b][2][0] = gm->GestureData[i][b][1][0] - gm->GestureData[i][b][0][0];
			gm->GestureData[i][b][2][1] = gm->GestureData[i][b][1][1] - gm->GestureData[i][b][0][1];
			gm->GestureData[i][b][2][2] = gm->GestureData[i][b][1][2] - gm->GestureData[i][b][0][2];
		}
		i++;
	}

	//compare
	for (int index = 0; index < GestureList.size(); index++)
	{
		if (true == compareGesture(GestureList[index], gm))
		{
			ret = GestureList[index]->GestureName;
			return true;
		}
	}
	ret = " ";
	return false;
}

float Detect::getAngle( float*  a, float* b)
{
	float up         = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	float m = a[0] * a[0] + a[1] * a[1] +a[2] * a[2];
	float n = b[0] * b[0] + b[1] * b[1] + b[2] * b[2];
	float down    = sqrt(n) * sqrt(m);
	if (up > down)
		return 0.0;

	return acos(up/down);
}