#pragma once

#include "StdAfx.h"
#include "SHPManager.h"
#include "SHPEntry.h"
#include <algorithm>
#include <math.h>
#include "DataStructs.h"
#include "MathUtil.h"
#define ADMISSBLE_RANGE 35

using namespace std;

SHPManager::SHPManager(void)
{
	m_selected = -1;
}

SHPManager::~SHPManager(void)
{
	for(int i=0; i < hSHP_list.size(); i++)
		 SHPClose(hSHP_list[i]);
}



shp_range SHPManager::add_SHP_File(const SHPHandle hSHP, const DBFHandle hDBF, int c)
{
	int	nShapeType, nEntities, bValidate = 0,nInvalidCount=0;
	double 	adfMinBound[4], adfMaxBound[4];

	hSHP_list.push_back(hSHP);

	SHPGetInfo(hSHP, &nEntities, &nShapeType, adfMinBound, adfMaxBound);
	
	const int h_index = hSHP_list.size()-1;
	for(int i=0; i<nEntities; i++)
	{
		const SHPObject * const psShape = SHPReadObject(hSHP, i );
		//eSHP_list.push_back(SHPEntry(hSHP, hDBF, i, psShape, c));
		eSHP_list.push_back(SHPEntry(h_index, i, psShape, c));
	}	
	m_raw_range = getSHPrange();

	//printf("add file   dif x :%d   dif y %d \n", m_raw_range.start.x, m_raw_range.start.y);
	
	return m_raw_range;
	
}	

//전체 엔트리 검색
//int SHPManager::selectEntry(CPoint mousePos, double width, double height, double zoom, double dx, double dy)
//{
//	double min = (1<<30);
//	int min_i = -1;
//
//	double diff_x = m_raw_range.start.x;
//	double diff_y = m_raw_range.start.y;
//	double len_x = m_raw_range.end.x - m_raw_range.start.x;
//	double len_y = m_raw_range.end.y - m_raw_range.start.y;
//
//	for(int i=0; i<eSHP_list.size(); i++)
//	{
//		const SHPObject * const psShape = eSHP_list[i].getShpOb();
//		
//		double pre_sx = (((psShape->padfX[0] - diff_x)*width / len_x) * zoom) + dx;
//		double pre_sy = height - (((psShape->padfY[0] - diff_y)*height / len_y)) * zoom + dy;
//		
//		for(int j=1; j< psShape->nVertices; j++)
//		{
//			/* 선[j-1 , j]와 점과의 거리  */
//			double cur_sx =  (((psShape->padfX[j] - diff_x)*width / len_x) * zoom) + dx;
//			double cur_sy =  height - (((psShape->padfY[j] - diff_y)*height / len_y)) * zoom + dy;
//
//			double dist = distBtwPoint_And_Line(mousePos.x, mousePos.y, pre_sx, pre_sy, cur_sx, cur_sy);
//
//			if(dist < ADMISSBLE_RANGE && min > dist)
//			{
//				min = dist;
//				min_i = i; // i번쨰 shp객체
//			}		
//			pre_sx = cur_sx;
//			pre_sy = cur_sy;
//		}
//	}
//		
//	if(m_selected!=-1)	
//		eSHP_list[m_selected].setDrawTypeDefault();
//	
//	if(min_i != -1)
//	{
//		m_selected = min_i;
//		eSHP_list[min_i].setDrawType(0, 0, 0, 8);
//	}
//
//	printf("Select Entry dist %f\n", min);
//
//	return min_i;	
//}



shp_range SHPManager :: getSHPrange() const
{
	CPoint min, max;
	min.x = min.y = (1<<30);
	max.x = max.y = -1*(1<<30);

	for(int i=0; i<hSHP_list.size(); i++)
	{
		int		nShapeType, nEntities, bValidate = 0,nInvalidCount=0;
		double 	adfMinBound[4], adfMaxBound[4];

		SHPGetInfo(hSHP_list[i], &nEntities, &nShapeType, adfMinBound, adfMaxBound);

		min.x = min(min.x, adfMinBound[0]);
		min.y = min(min.y, adfMinBound[1]);

		max.x = max(max.x, adfMaxBound[0]);
		max.y = max(max.y, adfMaxBound[1]);
	}
	
	shp_range range;
	range.start = min;
	range.end = max;

	return range;
}

vector<SHPEntry> & SHPManager:: getShpList()
{
	vector<SHPEntry> & ref = eSHP_list;
	return ref;
}

shp_range SHPManager:: drawAllSHP_e_gdi2(Gdiplus::Bitmap * bmp, double width, double height, double zoom, double dx, double dy) const
{
	Gdiplus::Graphics mem(bmp);	
	Gdiplus:: SolidBrush whiteBrush(Gdiplus::Color(255, 255, 255, 255));
	mem.FillRectangle(&whiteBrush, 0, 0, width, height);

	double min_x, min_y, max_x, max_y;

	min_x = min_y = (1<<30);
	max_x = max_y = -1*(1<<30);

	double diff_x = m_raw_range.start.x;
	double diff_y = m_raw_range.start.y;
	double len_x = m_raw_range.end.x - m_raw_range.start.x;
	double len_y = m_raw_range.end.y - m_raw_range.start.y;

	for(int e = 0; e < eSHP_list.size(); e++)
	{
		Color c(eSHP_list[e].d_rgb[0], eSHP_list[e].d_rgb[1], eSHP_list[e].d_rgb[2]);
		Pen p(c, eSHP_list[e].d_width);
		Gdiplus :: PointF p1, p2;

		const SHPObject * const psShape = eSHP_list[e].getShpOb();
		
		int iPart;

		for(int j=0, iPart =1; j<psShape->nVertices-1; j++)
		{
			double x1 = (((psShape->padfX[j] - diff_x)*width / len_x) * zoom) + dx;
			//double y1 = height - (((psShape->padfY[j] - diff_y)*height / len_y)) * zoom + dy;
			double y1 = (((psShape->padfY[j] - diff_y)*height / len_y)) * zoom + dy;

			double x2 = (((psShape->padfX[j+1] - diff_x)*width / len_x) * zoom) + dx;
			double y2 = (((psShape->padfY[j+1] - diff_y)*height / len_y)) * zoom + dy;
			p1.X = x1;
			p1.Y = y1;
			p2.X = x2;
			p2.Y = y2;


			min_x = min(min_x, x1);
			min_y = min(min_y, y1);
			max_x = max(max_x, x1);
			max_y = max(max_y, y1);

			min_x = min(min_x, x2);
			min_y = min(min_y, y2);
			max_x = max(max_x, x2);
			max_y = max(max_y, y2);

			if(iPart< psShape->nParts && (psShape->panPartStart[iPart] ==j ||psShape->panPartStart[iPart] ==j+1)) //링제거
			{
				iPart++;
				continue;
			}
			mem.DrawLine(&p, p1, p2);
		}
	}

	CPoint s(min_x, min_y);
	CPoint e(max_x, max_y);
	shp_range ret;
	ret.start=s;
	ret.end=e;

	return ret;
}


/* ***********************************************gdi 없이 그림*/
//shp_range SHPManager:: drawAllSHP_e(CDC* const pDC, double width, double height, double zoom, double dx, double dy) const //현재 전체 SHP 구조물들의 범위 반환
//{
//	double min_x, min_y, max_x, max_y;
//
//	min_x = min_y = (1<<30);
//	max_x = max_y = -1*(1<<30);
//
//	//printf("mdx %d mdy %d \n", m_raw_range.start.x, m_raw_range.start.y);
//	double diff_x = m_raw_range.start.x;
//	double diff_y = m_raw_range.start.y;
//	double len_x = m_raw_range.end.x - m_raw_range.start.x;
//	double len_y = m_raw_range.end.y - m_raw_range.start.y;
//
//	for(int e = 0; e < eSHP_list.size(); e++)
//	{
//		CPen myPen;
//		myPen.CreatePen(PS_SOLID, eSHP_list[e].d_width , RGB(eSHP_list[e].d_rgb[0], eSHP_list[e].d_rgb[1], eSHP_list[e].d_rgb[2]));
//		CPen *pOldPen;
//		pOldPen = pDC->SelectObject(&myPen);
//
//		const SHPObject * const psShape = eSHP_list[e].getShpOb();
//		double x = (((psShape->padfX[0] - diff_x)*width / len_x) * zoom) + dx;
//		double y = height - (((psShape->padfY[0] - diff_y)*height / len_y)) * zoom + dy;
//
//		min_x = min(min_x, x);
//		min_y = min(min_y, y);
//		max_x = max(max_x, x);
//		max_y = max(max_y, y);
//		pDC->MoveTo(x, y);
//
//		for(int j=1; j<psShape->nVertices; j++)
//		{
//			double x = (((psShape->padfX[j] - diff_x)*width / len_x) * zoom) + dx;
//			double y = height - (((psShape->padfY[j] - diff_y)*height / len_y)) * zoom + dy;
//			pDC->LineTo(x, y);
//			min_x = min(min_x, x);
//			min_y = min(min_y, y);
//			max_x = max(max_x, x);
//			max_y = max(max_y, y);
//		}
//	}
//
//	CPoint s(min_x, min_y);
//	CPoint e(max_x, max_y);
//	shp_range ret;
//	ret.start=s;
//	ret.end=e;
//
//	return ret;
//}
//
//




shp_range SHPManager:: getSCRange(double width, double height) const
{
	double diff_x = m_raw_range.start.x;
	double diff_y = m_raw_range.start.y;
	double len_x = m_raw_range.end.x - m_raw_range.start.x;
	double len_y = m_raw_range.end.y - m_raw_range.start.y;

	CPoint min, max;
	min.x = (m_raw_range.start.x - diff_x)*width / len_x;
	min.y = (m_raw_range.start.y - diff_y)*height / len_y;
	max.x = (m_raw_range.end.x - diff_x)*width / len_x;
	max.y = (m_raw_range.end.y - diff_y)*height / len_y;

	shp_range ret;
	ret.start = min;
	ret.end = max;
	return ret;
}