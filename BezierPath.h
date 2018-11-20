#ifndef _BEZIERPATH_H
#define _BEZIERPATH_H

#include "MathHelper.h"
#include <vector>

using namespace std;

class BezierPath
{
private:
	vector<BezierCurve> mCurves;
	vector<int> mSamples;

public:
	BezierPath();
	~BezierPath();

	void AddCurve(BezierCurve curve, int samples);
	void Sample(vector<Vector2>* sampledPath);
};

#endif