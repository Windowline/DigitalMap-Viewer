
#pragma once
#include "StdAfx.h"
#include "GridController.h"
#include "SHPManager.h"
#include "Grid.h"
#include "MathUtil.h"
#include "shapefil.h"
#include "SHPEntry.h"

using namespace std;

GridController::GridController(void)
{
	m_divNum = 10;
	m_grid_list.assign(10+1, vector<Grid>(11));
	m_divPx.assign(10+1, 0);
	m_divPy.assign(10+1, 0);
}

GridController::GridController(int divNum)
{
	m_divNum = divNum;
	m_grid_list.assign(m_divNum+1, vector<Grid>(m_divNum+1));
	m_divPx.assign(m_divNum+1, 0);
	m_divPy.assign(m_divNum+1, 0);
}

GridController::~GridController(void)
{
}


void GridController:: setRange(shp_range range)
{
	this->m_range = range;
}


CPoint GridController::searchGrid(CPoint mouse, shp_range range) const
{
	return binarySearch_index(mouse, range);
}


void GridController::grouping(const vector<SHPEntry> &shp_e_list, shp_range range) //range: raw range
{
	//printf("--------------------------------그루핑----------------------------\n");

	// 가공전의 데이터에 대한 divPoint 세팅
	double dx = (range.end.x - range.start.x ) / m_divNum;
	double dy = (range.end.y - range.start.y) / m_divNum;

	for(int i=0; i<=m_divNum; i++)
	{
		m_divPx[i] = i*dx;
		m_divPy[i] = i*dy;
	}
	
	//printf("s [%d  %d ]\n", range.start.x, range.start.y );
	// 그루핑 점, 두 점 사이의 점이 그리드[x][y]에 속한다면 추가
	for(int i=0; i < shp_e_list.size(); i++)
	{
		const SHPObject * const pSh = shp_e_list[i].getShpOb();
		
		double cur_x,cur_y;
		double pre_x = pSh->padfX[0] - range.start.x;
		double pre_y = pSh->padfY[0] - range.start.y;
		//double pre_y = (range.end.y-range.start.y) - (pSh->padfY[0] - range.start.y);

		CPoint index = binarySearch_index(CPoint(pre_x, pre_y));
		//printf("0v : 그리드[%d][%d] \n", index.x, index.y);

		if( ! m_grid_list[index.x][index.y].isContain(i))
			m_grid_list[index.x][index.y].putIndex(i);
		
		for(int j=1; j < pSh->nVertices; j++)
		{
			cur_x = pSh->padfX[j] - range.start.x;
			cur_y = pSh->padfY[j] - range.start.y;
			//cur_y = (range.end.y - range.start.y) - (pSh->padfY[j] - range.start.y);

			CPoint mid = middlePoint(pre_x, pre_y, cur_x, cur_y);

			index = binarySearch_index(mid);
			//printf("중심(%d, %d)v : 그리드[%d][%d] \n", j-1, j, index.x, index.y);


			if(! m_grid_list[index.x][index.y].isContain(i))
				m_grid_list[index.x][index.y].putIndex(i);

			index = binarySearch_index(CPoint(cur_x, cur_y));
		//	printf("%d v : 그리드[%d][%d] \n", j, index.x, index.y);
			if(! m_grid_list[index.x][index.y].isContain(i))
				m_grid_list[index.x][index.y].putIndex(i);

			pre_x = cur_x;
			pre_y = cur_y;
		}
	}
}


void GridController:: drawGrid_gdi(Gdiplus::Bitmap * bmp, shp_range range) const
{
	CPoint start = range.start;
	CPoint end = range.end;
	double dx = (end.x - start.x) / m_divNum; 
	double dy = (end.y - start.y) / m_divNum;

	Gdiplus::Graphics mem(bmp);	
	Color c(200, 200, 200, 200);
	Pen p(c, 1);
	p.SetDashStyle((DashStyle)2);
	//p.SetDashStyle(PS_DOT);
	Gdiplus :: PointF p1, p2;
	for(int i=0; i<=m_divNum; i++)
	{
		p1.X = start.x + i*dx;
		p1.Y = start.y;
		p2.X = start.x + i*dx;
		p2.Y = end.y;
		mem.DrawLine(&p, p1, p2);
	}
	//행
	for(int i=0; i<=m_divNum; i++)
	{
		p1.X = start.x;
		p1.Y = start.y + i*dy;
		p2.X = end.x;
		p2.Y = start.y + i*dy;
		mem.DrawLine(&p, p1, p2);
	}

}


CPoint GridController::binarySearch_index(CPoint key) const //그루핑에 이용
{
	//printf("-key [%d , %d]\n", key.x, key.y);
	int ret_i=0;
	int ret_j=0;
	//x축
	int l = 1;
	int r = m_divNum;
	while(l<=r)
	{
		int mid = (l+r) / 2;
		if(m_divPx[mid-1] <= key.x  &&  m_divPx[mid] >= key.x)
		{
			ret_i = mid;
			//	printf("X: %d ~ %d 속함 div:[%d]\n", m_divPx[mid-1], m_divPx[mid], mid);
			break;
		}
		else if(m_divPx[mid] < key.x)
			l = mid+1;
		else if(m_divPx[mid-1] > key.x)
			r = mid-1;
	}	
	//y축
	l = 1;
	r = m_divNum;
	while(l<=r)
	{
		int mid = (l+r)/2;
		if(m_divPy[mid-1] <= key.y && m_divPy[mid]>=key.y)
		{
			ret_j = mid;
			//	printf("Y: %d ~ %d 속함 div:[%d]\n", m_divPy[mid-1], m_divPy[mid], mid);
			break;
		}
		else if(m_divPy[mid] < key.y)
			l = mid+1;
		else if(m_divPy[mid-1] > key.y)
			r = mid-1;
	}

	CPoint ret;
	ret.x = ret_i;
	ret.y = ret_j;

	return ret;
}



CPoint GridController ::  binarySearch_index(CPoint key, shp_range range)  const //클릭시 그리드 찾는 것에 이용
{
	
	double rate_x = (m_divPx[m_divNum] - m_divPx[0]) / (range.end.x - range.start.x);
	double rate_y = (m_divPy[m_divNum] - m_divPy[0]) / (range.end.y - range.start.y);		
	
//	if(rate!=0)
	double diff_x = (m_divPx[0]/rate_x) - range.start.x;
	double diff_y = (m_divPy[0]/rate_y) - range.start.y;
	
	//int diff_x =  range.start.x; // 0->이동거리
	//int diff_y =  range.start.y; // 0->이동거리

	int ret_i=0;
	int ret_j=0;
	//x축
	int l = 1;
	int r = m_divNum;
	while(l<=r)
	{
		int mid = (l+r) / 2;

		double comp1 = (m_divPx[mid-1] / rate_x) - diff_x;
		double comp2 = (m_divPx[mid] / rate_x) - diff_x;

		if( comp1 <= key.x  &&  comp2 >= key.x)
		{
			ret_i = mid;
			break;
		}
		else if( comp2 < key.x)
			l = mid+1;
		else if( comp1 > key.x)
			r = mid-1;
	}	
	//y축
	l = 1;
	r = m_divNum;
	while(l<=r)
	{
		int mid = (l+r)/2;

		double comp1 = (m_divPy[mid-1] / rate_y) - diff_y;
		double comp2 = (m_divPy[mid] / rate_y) - diff_y;

		if(comp1 <= key.y && comp2 >=key.y)
		{
			ret_j = mid;
			break;
		}
		else if(comp2 < key.y)
			l = mid+1;
		else if(comp1 > key.y)
			r = mid-1;
	}

	CPoint ret;
	ret.x = ret_i;
	ret.y = ret_j;

	return ret;
}

const vector<vector<Grid>> & GridController::getGridList() const
{
	const vector<vector<Grid>> & ref = m_grid_list;
	return ref;
}

Grid & GridController::getGrid(int x, int y)
{
	Grid & ref = m_grid_list[x][y];
	return ref;
}

int GridController::getDivNum() const
{
	return this->m_divNum;
}







/*gdi없이 그림*/
void GridController::drawGrid(CDC* pDC, shp_range range) const 
{
	CPen myPen;
	myPen.CreatePen(PS_DOT, 1, RGB(200, 200, 200));
	CPen *pOldPen;
	pOldPen = pDC->SelectObject(&myPen);

	CPoint start = range.start;
	CPoint end = range.end;
	double dx = (end.x - start.x) / m_divNum; 
	double dy = (end.y - start.y) / m_divNum;
	
	//열
	for(int i=0; i<=m_divNum; i++)
	{
		pDC->MoveTo(start.x + i*dx, start.y);
		pDC->LineTo(start.x + i*dx, end.y);
	}
	//행
	for(int i=0; i<=m_divNum; i++)
	{
		pDC->MoveTo(start.x, start.y + i*dy);
		pDC->LineTo(end.x, start.y + i*dy);
	}
}