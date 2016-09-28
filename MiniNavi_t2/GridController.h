#pragma once
#include "stdafx.h"
#include "shapefil.h"
#include <vector>
#include "SHPManager.h"
#include "Grid.h"
#include "DataStructs.h"

using namespace std;

class GridController
{
	private:
		shp_range m_range;
		int m_divNum;
		vector<vector<Grid>> m_grid_list;
		vector<double> m_divPx;
		vector<double> m_divPy;


	public:
		GridController(void);
		GridController(int divNum);
		~GridController(void);
		void setRange(shp_range range);
		void drawGrid(CDC* pDC, shp_range range) const;
		void drawGrid_gdi(Gdiplus::Bitmap * bmp, shp_range range) const;
		void grouping(const vector<SHPEntry> &shp_e_list, shp_range range);
		CPoint searchGrid(CPoint mouse, shp_range range) const;
		const vector<vector<Grid>> & getGridList() const;
		Grid & getGrid(int x, int y);
		int getDivNum() const;

	private:
		CPoint binarySearch_index(CPoint key) const;
		CPoint binarySearch_index(CPoint key, shp_range range) const;
		
};
