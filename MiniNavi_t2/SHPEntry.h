#include "shapefil.h"

#pragma once

class SHPEntry
{

	private:
		int h_index; // 핸들러 인덱스
		int index; // 핸들러 내에서의 인덱스
		const SHPObject  *  pSHP;
		int cent_x; 
		int cent_y;
		int c_index;

	public: // 그리기 속성
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
