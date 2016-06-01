// OpenCVPnPTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;
int _tmain(int argc, _TCHAR* argv[])
{
	puts("hehehe");

	Mat op = (Mat_<Point3d>(1, 4) << 
			Point3d(0, 0, 0),
			Point3d(1, 0, 0),
			Point3d(0, 2, 0),
			Point3d(0, 0, 3)
		);
	Mat ip = (Mat_<Point2d>(1, 4) <<
			Point2d(-0.2, 0),
			Point2d((sqrt(2.0) / 2 - 1) / (5 - sqrt(2.0) / 2), 0),
			Point2d (- 0.2, 0.4),
			Point2d((3 * sqrt(2.0) / 2 - 1) / (5 + 3 * sqrt(2.0) / 2), 0)
		);
	
	Matx33d camMatrix(
			1, 0, 0,
			0, 1, 0,
			0, 0, 1.0
		);

	vector<double> tv(3), rv(3);
	Mat rvec(rv), tvec(tv);


	solvePnP(op, ip, camMatrix, noArray(), rvec, tvec, false, CV_EPNP);

	double rot[9] = { 0 };
	Mat rotM(3, 3, CV_64FC1, rot);
	Rodrigues(rvec, rotM);
	double* _r = rotM.ptr<double>();
	printf("rotation mat: \n %.3f %.3f %.3f\n%.3f %.3f %.3f\n%.3f %.3f %.3f\n",
		_r[0], _r[1], _r[2], _r[3], _r[4], _r[5], _r[6], _r[7], _r[8]);

	printf("trans vec: \n %.3f %.3f %.3f\n", tv[0], tv[1], tv[2]);


	getchar();
	return 0;
}



