// Fill out your copyright notice in the Description page of Project Settings.

#include "TestP4P.h"
#include "P4PActor.h"




// Sets default values
AP4PActor::AP4PActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AP4PActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AP4PActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AP4PActor::P4pTest_OnStep(FVector oa, FVector ob, FVector oc, FVector od, FVector4 A1, FVector4& outA1, FVector4 &outF)
{
	GLog->Log(TEXT("Log input A1:"));
	for (int i = 0; i < 4; i++) {
		GLog->Log(FString::SanitizeFloat(A1[i]));
	}
	
	FVector e1 = oa.GetSafeNormal();
	FVector e2 = ob.GetSafeNormal();
	FVector e3 = oc.GetSafeNormal();
	FVector e4 = od.GetSafeNormal();
	
	
	float d12 = (oa - ob).Size();
	float d23 = (ob - oc).Size();
	float d34 = (oc - od).Size();
	float d41 = (od - oa).Size();

	float t12 = FVector::DotProduct(e1, e2);
	float t23 = FVector::DotProduct(e2, e3);
	float t34 = FVector::DotProduct(e3, e4);
	float t41 = FVector::DotProduct(e4, e1);

	
	float ts[4] = { t12, t23, t34, t41};
	float ds[4] = { d12 , d23 , d34, d41};
	FVector4 deltaA = jfFunc(A1, ts, ds);
	outA1 = A1 - deltaA;
}

float AP4PActor::distFunc(float a1, float a2, float d12, float t12)
{
	long double aa1 = a1, aa2 = a2, dd12 = d12, tt12 = t12;
	return aa1 * aa1 - 2 * aa1 * aa2 * tt12 + aa2 * aa2 - dd12 * dd12;
}

FVector4 AP4PActor::jfFunc(FVector4 A, float ts[4], float ds[4])
{

	GLog->Log(TEXT("Log input ts:"));
	for (int i = 0; i < 4; i++) {
		GLog->Log(FString::SanitizeFloat(ts[i]));
	}

	GLog->Log(TEXT("Log input ds:"));
	for (int i = 0; i < 4; i++) {
		GLog->Log(FString::SanitizeFloat(ds[i]));
	}
	FMatrix J, Jinv;
	J.M[0][0] = jfHelpFunc(A[0], ts[0], A[1]); J.M[0][1] = jfHelpFunc(A[1], ts[0], A[0]); J.M[0][2] = 0; J.M[0][3] = 0;
	
	J.M[1][0] = 0; J.M[1][1] = jfHelpFunc(A[1], ts[1], A[2]); J.M[1][2] = jfHelpFunc(A[2], ts[1], A[1]); J.M[1][3] = 0;
	
	J.M[2][0] = 0; J.M[2][1] = 0; J.M[2][2] = jfHelpFunc(A[2], ts[2], A[3]); J.M[2][3] = jfHelpFunc(A[3], ts[2], A[2]);

	J.M[3][0] = jfHelpFunc(A[0], ts[3], A[3]); J.M[3][1] = 0; J.M[3][2] = 0; J.M[3][3] = jfHelpFunc(A[3], ts[3], A[0]);

	GLog->Log(TEXT("Log input J:"));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			GLog->Log(FString::SanitizeFloat(J.M[i][j]));
		}
		GLog->Log(TEXT("---------------------"));
	}

	FVector4 fv, fres;
	fv[0] = distFunc(A[0], A[1], ds[0], ts[0]);
	fv[1] = distFunc(A[1], A[2], ds[1], ts[1]);
	fv[2] = distFunc(A[2], A[3], ds[2], ts[2]);
	fv[3] = distFunc(A[0], A[3], ds[3], ts[3]);

	Jinv = J.Inverse();
	GLog->Log(TEXT("Log input Jinv:"));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			GLog->Log(FString::SanitizeFloat(Jinv.M[i][j]));
		}
		GLog->Log(TEXT("---------------------"));
	}
	for (int i = 0; i < 4; i++) {
		fres[i] = 0;
		long double temp = 0;
		for (int j = 0; j < 4; j++) {
			temp += Jinv.M[i][j] * fv[j];
		}
		fres[i] =  temp;
		GLog->Log(FString::SanitizeFloat(fres[i]));
	}


	return fres;
}

float AP4PActor::jfHelpFunc(float a1, float t12, float a2)
{
	long double aa1 = a1, tt12 = t12, aa2 = a2;
	return 2 * aa1 - 2 * tt12 * aa2;
}

void getInversMatrix(FMatrix src, FMatrix &res) {

	//get getDeterminant
//	double ret = 0;
//	for (int i = 0; i < Order; i++)
//	{
//		FMatrix temp = src.getResidualMatrix(0, i);
//		SquareMatrix sm = new SquareMatrix(temp.Rows);
//		for (int k = 0; k < sm.Order; k++)
//		{
//			for (int j = 0; j < sm.Order; j++)
//			{
//				sm.Element[k, j] = temp.Element[k, j];
//			}
//		}
//		if (i % 2 == 0)
//		{
//			ret += this.Element[0, i] * sm.getDeterminant();
//		}
//		else
//		{
//			ret -= this.Element[0, i] * sm.getDeterminant();
//		}
//	}
//	=
//}
}

