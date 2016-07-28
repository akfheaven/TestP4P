// Fill out your copyright notice in the Description page of Project Settings.

#include "LinkTest.h"
#include "MyClass.h"
#include "opencv2/calib3d/calib3d.hpp"
#include <iostream>
using namespace std;
using namespace cv;

MyClass::MyClass()
{
	Mat op = (Mat_<Point3d>(1, 4) <<
		Point3d(0, 0, 0),
		Point3d(1, 0, 0),
		Point3d(0, 2, 0),
		Point3d(0, 0, 3)
	);


	Mat ip = (Mat_<Point2d>(1, 4) <<
		Point2d(-0.2, 0),
		Point2d((sqrt(2.0) / 2 - 1) / (5 - sqrt(2.0) / 2), 0),
		Point2d(-0.2, 0.4),
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
}

MyClass::~MyClass()
{
}
