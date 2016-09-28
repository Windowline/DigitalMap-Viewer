
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
		shp_range m_raw_range; 	//���� �߰������� ��ȭ
		int m_selected; // ���缱�õ� ��Ʈ���ε���


	public:
		//������ shape range ��ȯ, ��ο�
		shp_range drawAllSHP_e_gdi2(Gdiplus::Bitmap * bmp, double width, double height, double zoom, double dx, double dy) const;
		shp_range add_SHP_File(const SHPHandle hSHP, const DBFHandle hDBF, int c); // ���� �߰�(��Ʈ���߰�), c: ������
		int selectEntry(CPoint mousePos, double width, double height, double zoom, double dx, double dy);// shape�˻�
		shp_range getSHPrange() const; // raw ���� ��ȯ
		shp_range getSHPrange(double zoom, double dx, double dy) const; // �ܺκ����� ���� ������ ���� ��ȯ
		vector<SHPEntry> & getShpList();

		
		//shp_range getSHPrange(dou);
		shp_range drawAllSHP_e( CDC* const pDC, double width, double height, double zoom, double dx, double dy) const;
		SHPManager(void);
		~SHPManager(void);		
		
		shp_range getSCRange(double width, double height) const;
};
