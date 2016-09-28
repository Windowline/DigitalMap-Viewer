
#pragma once
#include "stdafx.h"
#include <hash_map>
#include <vector>
#include "shapefil.h"
#include "SHPEntry.h"
#include "DataStructs.h"

using namespace stdext;

class Grid
{
	private:
		hash_map<int, int> shp_index_map;
		//int g_index; 
		//int x; 
		//int y;

	public:
		Grid(void);
		~Grid(void);
		bool isContain(int index);
		void putIndex(int index);
		searchInfo searchShp(CPoint mouse,  const std::vector<SHPEntry> & shp_e_list, shp_range raw_range, double width, double height, double zoom, double dx, double dy); // ���� �׸��峻���� ���콺�� ���� ����� shp Ž��
};
