#include "StdAfx.h"
#include "SHPEntry.h"
#include "shapefil.h"


//SHPEntry::SHPEntry()
//{
//
//}


SHPEntry::SHPEntry(int _h_index, int _index,  const SHPObject*  _pSHP, int c) :h_index(_h_index), index(_index), pSHP(_pSHP)
{	
	int x=0;
	int y=0;

	for(int i=0; i<pSHP->nVertices; i++)
	{
		x += pSHP->padfX[i];
		y += pSHP->padfY[i];
	}

	this->cent_x = x / pSHP->nVertices;
	this->cent_y = y / pSHP->nVertices;

	this->d_rgb[0] = (10+(50*c))% 255;
	this->d_rgb[1] = abs(70-(50*c)) % 255;
	if(c%2==0)
		this->d_rgb[2] = (150+(50*c)) % 255;
	else
		this->d_rgb[2] = abs(120-(50*c)) % 255;

	this->d_width = 3;
	this->c_index = c;
}


void SHPEntry::setDrawTypeDefault()
{
	this->d_rgb[0] = (10+(50*c_index))% 255;
	this->d_rgb[1] = abs(70-(50*c_index)) % 255;
	if(c_index%2==0)
		this->d_rgb[2] = (150+(50*c_index)) % 255;
	else
		this->d_rgb[2] = abs(120-(50*c_index)) % 255;

	this->d_width = 3;
}

void SHPEntry::setDrawType(int r, int g, int b, int width)
{
	this->d_rgb[0] = r;
	this->d_rgb[1] = g;
	this->d_rgb[2] = b;
	this->d_width = width;
}


const SHPObject * const SHPEntry::getShpOb() const
{
	return pSHP;
}


int SHPEntry::get_h_index() const
{
	return h_index;
}
int SHPEntry::get_index() const
{
	return index;
}


SHPEntry::~SHPEntry(void)
{
}
