#pragma once
#include "StdAfx.h"
#include "MathUtil.h"
#include "DataStructs.h"
#include <math.h>


//double distBtwPoints(double x1, double y1, double x2, double y2)
//{
//	return sqrt((double)(abs(x1-x2)*abs(x1-x2) + abs(y1-y2)*abs(y1-y2)));
//}
//
//double distBtwPoint_And_Line(double px, double py, double A_x, double A_y, double B_x, double B_y)
//{
//	double line_len = distBtwPoints(A_x, A_y, B_x, B_y);
//
//	if(line_len==0)
//		return distBtwPoints(px, py, A_x, A_y);
//
//	double prj_pA_AB = ((px - A_x)*(B_x - A_x) + (py - A_y)*(B_y - A_y)); //내적
//
//	if(prj_pA_AB < 0) // A에 더 가까움
//		return distBtwPoints(px, py, A_x, A_y);
//
//	else if(prj_pA_AB> line_len )//B에 더 가까움
//		return distBtwPoints(px, py, B_x, B_y);
//
//	else 
//		return fabs(  ( (double)(-1) * (px - A_x) * (B_y - A_y) + (py - A_y)*(B_x - A_x) ) );  // 법선벡터 길이
//}
//
//
//CPoint middlePoint(double x1, double y1, double x2, double y2)
//{
//	CPoint ret;
//	ret.x = (x1+x2)/2;
//	ret.y = (y1+y2)/2;
//	return ret;
//}


double distBtwPoints(int x1, int y1, int x2, int y2)
{
	return sqrt((double)(abs(x1-x2)*abs(x1-x2) + abs(y1-y2)*abs(y1-y2)));
}

double distBtwPoint_And_Line(int px, int py, int A_x, int A_y, int B_x, int B_y)
{
	double line_len = distBtwPoints(A_x, A_y, B_x, B_y);

	if(line_len==0)
		return distBtwPoints(px, py, A_x, A_y);

	double prj_pA_AB = ((px - A_x)*(B_x - A_x) + (py - A_y)*(B_y - A_y)); //내적

	if(prj_pA_AB < 0) // A에 더 가까움
		return distBtwPoints(px, py, A_x, A_y);

	else if(prj_pA_AB> line_len )//B에 더 가까움
		return distBtwPoints(px, py, B_x, B_y);

	else 
		return fabs(  ( (double)(-1) * (px - A_x) * (B_y - A_y) + (py - A_y)*(B_x - A_x) ) );  // 법선벡터 길이
}


CPoint middlePoint(int x1, int y1, int x2, int y2)
{
		CPoint ret;
		ret.x = (x1+x2)/2;
		ret.y = (y1+y2)/2;
		return ret;
}
