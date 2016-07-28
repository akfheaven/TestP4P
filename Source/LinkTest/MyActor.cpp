// Fill out your copyright notice in the Description page of Project Settings.

#include "LinkTest.h"
#include "MyActor.h"
#include "opencv2/calib3d/calib3d.hpp"
#include <iostream>
using namespace cv;
using namespace std;

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

FTransform AMyActor::MySolvePnP(const TArray<FVector>& aop, const TArray<FVector2D>&  aip){
	int32 arraySize = aop.Num();
	FVector bb = aop[0];
	Mat op = (Mat_<Point3d>(1, 4) <<
		Point3d(aop[0].X, aop[0].Y, aop[0].Z),
		Point3d(aop[1].X, aop[1].Y, aop[1].Z),
		Point3d(aop[2].X, aop[2].Y, aop[2].Z),
		Point3d(aop[3].Y, aop[3].Y, aop[3].Z)
		);


	//Mat ip = (Mat_<Point2d>(1, 4) <<
	//	Point2d(-0.2, 0),
	//	Point2d((sqrt(2.0) / 2 - 1) / (5 - sqrt(2.0) / 2), 0),
	//	Point2d(-0.2, 0.4),
	//	Point2d((3 * sqrt(2.0) / 2 - 1) / (5 + 3 * sqrt(2.0) / 2), 0)
	//	);

	Mat ip = (Mat_<Point2d>(1, 4) <<
		Point2d(aip[0].X, aip[0].Y),
		Point2d(aip[1].X, aip[1].Y),
		Point2d(aip[2].X, aip[2].Y),
		Point2d(aip[3].X, aip[3].Y)
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
//	GLog->Log(FString::Printf(""));
	FTransform aa = FTransform::Identity;
	aa.SetLocation(FVector(tv[0], tv[1], tv[2]));
	FMatrix mat = FMatrix::Identity;
	mat.M[0][0] = _r[0]; mat.M[0][1] = _r[1]; mat.M[0][2] = _r[2];
	mat.M[1][0] = _r[3]; mat.M[1][1] = _r[4]; mat.M[1][2] = _r[5];
	mat.M[2][0] = _r[6]; mat.M[2][1] = _r[7]; mat.M[2][2] = _r[8];
	aa.SetRotation(mat.ToQuat().Inverse());
	return aa;
}

