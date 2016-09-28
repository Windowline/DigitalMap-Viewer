#pragma once
#include "StdAfx.h"
#include "Grid.h"
#include <iterator>
#include <iostream>
#include "DataStructs.h"
#include "MathUtil.h"
#define ADMISSBLE_RANGE 35
using namespace stdext;

Grid::Grid(void)
{
}
Grid::~Grid(void)
{
}

bool Grid::isContain(int index)
{
	if(shp_index_map[index]==0)
		return false;
	else
		return true;
}
void Grid::putIndex(int index)
{
	shp_index_map[index] = 1;
}


//ret min_index,   ret.y: min_dist
searchInfo Grid::searchShp(CPoint mouse, const std::vector<SHPEntry> & shp_e_list, shp_range raw_range, double width, double height, double zoom, double dx, double dy) 
{
	//printf("=======================searh in grid================\n");
	double min = (1<<30);
	int min_i = -1;
	
	double diff_x = raw_range.start.x;
	double diff_y = raw_range.start.y;
	double len_x = raw_range.end.x - raw_range.start.x;
	double len_y = raw_range.end.y - raw_range.start.y;

	hash_map<int, int >::iterator itr;
	for(itr = shp_index_map.begin(); itr!=shp_index_map.end(); itr++)
	{
		const SHPObject * const pSh = shp_e_list[itr->first].getShpOb();
		double pre_sx = (((pSh->padfX[0] - diff_x)*width / len_x) * zoom) + dx;
		double pre_sy = (((pSh->padfY[0] - diff_y)*height / len_y)) * zoom + dy;
		double cur_sx, cur_sy;
		//printf("comp shp id : %d \n", itr->first);

		for(int j=1; j < pSh->nVertices; j++)
		{
			cur_sx =  (((pSh->padfX[j] - diff_x)*width / len_x) * zoom) + dx;
			cur_sy =  (((pSh->padfY[j] - diff_y)*height / len_y)) * zoom + dy;
			double dist = distBtwPoint_And_Line(mouse.x, mouse.y, pre_sx, pre_sy, cur_sx, cur_sy);

			if(dist < ADMISSBLE_RANGE && min > dist)
			{
				min = dist;
				min_i = itr->first; 
			}		
			pre_sx = cur_sx;
			pre_sy = cur_sy;
		}
	}	
	
	searchInfo ret;
	ret.min_index = min_i;
	ret.min_dist = min;
	//printf("Grid Search dist %f \n", min);
	return ret;
}
