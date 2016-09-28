#include "shapefil.h"

#pragma once

class SHPEntry
{

	private:
		int h_index; // �ڵ鷯 �ε���
		int index; // �ڵ鷯 �������� �ε���
		const SHPObject  *  pSHP;
		int cent_x; 
		int cent_y;
		int c_index;

	public: // �׸��� �Ӽ�
		int d_rgb[3];
		int d_width;

	public:
		SHPEntry(int _h_index, int _index,  const SHPObject *  _pSHP, int c);
		void setDrawType(int r, int g, int b, int width);
		void setDrawTypeDefault();
		const SHPObject * const getShpOb() const;
		SHPEntry(void);
		int get_h_index() const;
		int get_index() const;
		~SHPEntry(void);

};
