#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "SHPEntry.h"
#include "shapefil.h"
#include "SHPManager.h"

#define WM_MYMSG WM_USER+1

// CMyDlg 대화 상자입니다.

class CMyDlg : public CDialog
{
	DECLARE_DYNAMIC(CMyDlg)

public:
	BOOL CMyDlg::Create(CWnd* pParentWnd);
	CMyDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMyDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	
	afx_msg LRESULT OnMyMsg(WPARAM wParam, LPARAM lParam); // 사용자 정의 메세지

	DECLARE_MESSAGE_MAP()
public:
	int m_test;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);



public: //멤버변수
	CListBox m_attrList;


	CListCtrl m_ListC;
	afx_msg void OnBnClickedButton1();
	CButton m_testBut;
	afx_msg void OnLvnItemchangedListCtl(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_recordList;
};
