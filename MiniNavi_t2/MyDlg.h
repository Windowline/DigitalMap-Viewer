#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "SHPEntry.h"
#include "shapefil.h"
#include "SHPManager.h"

#define WM_MYMSG WM_USER+1

// CMyDlg ��ȭ �����Դϴ�.

class CMyDlg : public CDialog
{
	DECLARE_DYNAMIC(CMyDlg)

public:
	BOOL CMyDlg::Create(CWnd* pParentWnd);
	CMyDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMyDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	
	afx_msg LRESULT OnMyMsg(WPARAM wParam, LPARAM lParam); // ����� ���� �޼���

	DECLARE_MESSAGE_MAP()
public:
	int m_test;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);



public: //�������
	CListBox m_attrList;


	CListCtrl m_ListC;
	afx_msg void OnBnClickedButton1();
	CButton m_testBut;
	afx_msg void OnLvnItemchangedListCtl(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_recordList;
};
