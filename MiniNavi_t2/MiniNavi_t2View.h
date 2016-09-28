// MiniNavi_t2View.h : CMiniNavi_t2View Ŭ������ �������̽�
//

#pragma once

#include <vector>
#include "shapefil.h"
#include "SHPManager.h"
#include "GridController.h"
#include "DataStructs.h"


class CMiniNavi_t2View : public CScrollView
{
protected: // serialization������ ��������ϴ�.
	CMiniNavi_t2View();
	DECLARE_DYNCREATE(CMiniNavi_t2View)

// Ư���Դϴ�.
public:
	CMiniNavi_t2Doc* GetDocument() const;
	CWnd m_wndChild;
	CPoint   m_ptMouse; //--------------------------��ü ����
	CSize m_PageSize;

	//�巡�� ����
	bool m_is_mouse_down;
	CPoint m_mouse_down_pos;
	CPoint m_pre_mouse_pos;

	double m_dx, m_dy, m_cur_x, m_cur_y, m_width, m_height, m_Zoom;;
	shp_range m_range; // shape�� �׷��� ����

	//�����Է°���
	int m_f_cnt;
	vector<CString> m_fpath;


	//�ܿ� ���� diff
	double m_zdx;
	double m_zdy;

	
	SHPManager manager;
	GridController g_controller;	
	int m_selected;


// �۾��Դϴ�.
public:
	

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);


// �����Դϴ�.
public:
	virtual ~CMiniNavi_t2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual void OnInitialUpdate();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual void OnDragLeave();
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	CPoint toScreen(double x, double y, double x_len, double y_len);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

};

#ifndef _DEBUG  // MiniNavi_t2View.cpp�� ����� ����
inline CMiniNavi_t2Doc* CMiniNavi_t2View::GetDocument() const
   { return reinterpret_cast<CMiniNavi_t2Doc*>(m_pDocument); }
#endif

