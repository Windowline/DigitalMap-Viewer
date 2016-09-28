
#pragma once
#include "stdafx.h"
#include <vector>
#include "shapefil.h"
#include "SHPEntry.h"
#include "DataStructs.h"

using namespace std;

class SHPManager
{

	private:
		vector< SHPHandle > hSHP_list;
		vector< SHPEntry > eSHP_list;		
		shp_range m_raw_range; 	//파일 추가때마다 변화
		int m_selected; // 현재선택된 엔트리인덱스


	public:
		//수정된 shape range 반환, 드로우
		shp_range drawAllSHP_e_gdi2(Gdiplus::Bitmap * bmp, double width, double height, double zoom, double dx, double dy) const;
		shp_range add_SHP_File(const SHPHandle hSHP, const DBFHandle hDBF, int c); // 파일 추가(엔트리추가), c: 색상요소
		int selectEntry(CPoint mousePos, double width, double height, double zoom, double dx, double dy);// shape검색
		shp_range getSHPrange() const; // raw 범위 반환
		shp_range getSHPrange(double zoom, double dx, double dy) const; // 외부변수에 의해 변형된 범위 반환
		vector<SHPEntry> & getShpList();

		
		//shp_range getSHPrange(dou);
		shp_range drawAllSHP_e( CDC* const pDC, double width, double height, double zoom, double dx, double dy) const;
		SHPManager(void);
		~SHPManager(void);		
		
		shp_range getSCRange(double width, double height) const;
};
