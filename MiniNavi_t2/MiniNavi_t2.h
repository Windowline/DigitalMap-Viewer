// MiniNavi_t2.h : MiniNavi_t2 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMiniNavi_t2App:
// �� Ŭ������ ������ ���ؼ��� MiniNavi_t2.cpp�� �����Ͻʽÿ�.
//

class CMiniNavi_t2App : public CWinApp
{
public:
	CMiniNavi_t2App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CMiniNavi_t2App theApp;