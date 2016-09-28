// MyDlg.cpp : ���� �����Դϴ�.
//
#pragma once
#include "stdafx.h"
#include "MiniNavi_t2.h"
#include "MyDlg.h"
#include <string.h>
#include <string>
#include <stdlib.h>
// CMyDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMyDlg, CDialog)

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
	, m_test(0)
{

}

CMyDlg::~CMyDlg()
{
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CTL2, m_ListC);
	DDX_Control(pDX, IDC_BUTTON1, m_testBut);
	DDX_Control(pDX, RECORD_LIST, m_recordList);
}


BOOL CMyDlg::Create(CWnd* pParentWnd)
{
	return CDialog::Create(IDD, pParentWnd);
}


BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyDlg::OnBnClickedButton1)

	ON_MESSAGE(WM_MYMSG, OnMyMsg)

	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CTL, &CMyDlg::OnLvnItemchangedListCtl)
END_MESSAGE_MAP()

// CMyDlg �޽��� ó�����Դϴ�.

LRESULT CMyDlg::OnMyMsg(WPARAM wParam, LPARAM lParam) // Shape�˻���, ������ ��� wParam: fpath, lParam: ���ϳ� �ε���
{
	CString * tmp = (CString*)wParam;
	int index = lParam;

	char dbf[4] ="dbf";
	char shp[4] = "shp";
	char fpath_dbf[100] ={0, };
	char fpath_shp[100] ={0, };
	strncpy(fpath_dbf, (LPSTR)(LPCSTR)(*tmp), strlen((*tmp))-3);
	strncpy(fpath_shp, (LPSTR)(LPCSTR)(*tmp), strlen((*tmp))-3);
	strcat(fpath_dbf, dbf);
	strcat(fpath_shp, shp);

	DBFHandle hDBF = DBFOpen(fpath_dbf, "rb");

	//if(hDBF==NULL)
	//{
	//	printf("�ȿ���\n");
	//	return TRUE;
	//}

	//printf("������������������������������������������������ SHP INFO START������������������������������������������������\n");	
	int		nWidth, nDecimals;
	char	szTitle[12];
	int fieldCnt = DBFGetFieldCount(hDBF);


	UpdateData(TRUE);
	m_ListC.DeleteAllItems(); // �ʵ��� �Ӽ�
	m_recordList.DeleteAllItems(); // �ʵ尪

	/*�ش� DBF������ �Ӽ��� ���� ���� */
	for(int i = 0; i < fieldCnt; i++ )
	{	
		DBFFieldType	eType;
		const char	 	*pszTypeName;			
		eType = DBFGetFieldInfo(hDBF, i, szTitle, &nWidth, &nDecimals );			
		if( eType == FTString )
			pszTypeName = "String";
		else if( eType == FTInteger )
			pszTypeName = "Integer";
		else if( eType == FTDouble )
			pszTypeName = "Double";
		else if( eType == FTInvalid )
			pszTypeName = "Invalid";

		//printf( "Field %d: Type=%s, Title=`%s', Width=%d, Decimals=%d\n", i, pszTypeName, szTitle, nWidth, nDecimals );

		char tmp_cnum[30];

		LVITEM Item;
		Item.mask = LVIF_TEXT;
		Item.iItem = i;
		
		for(int k=0; k<5; k++)
		{
			Item.iSubItem = k;
			
			if(k==0)
			{
				itoa(i, tmp_cnum, 10);
				Item.pszText = (LPSTR)tmp_cnum;
			}
			else if(k==1)
			{
				Item.pszText = ( (pszTypeName!=NULL) ? (LPSTR)pszTypeName : (LPSTR)"NULL" );
	
			}
			else if(k==2)
			{
				Item.pszText = ( (szTitle!=NULL) ? (LPSTR)szTitle : (LPSTR)"NULL");
			}
			else if(k==3)
			{
				itoa(nWidth, tmp_cnum, 10);
				Item.pszText = (LPSTR)tmp_cnum;
			}
			else if(k==4)
			{
				itoa(nDecimals, tmp_cnum, 10);
				Item.pszText = (LPSTR)tmp_cnum;
			}
			m_ListC.InsertItem(&Item);
			m_ListC.SetItem(&Item);
		}	
	}


	/*���ڵ�(hDBF, index)�� ���� ���� ���( �Ӽ�, ��) */
	for(int i = 0; i < fieldCnt; i++ )
	{
		DBFFieldType	eType;
		eType = DBFGetFieldInfo( hDBF, i, szTitle, &nWidth, &nDecimals );


		LVITEM Item;
		Item.mask = LVIF_TEXT;
		Item.iItem = i;
		
		/*�Ӽ������Է�*/
		Item.iSubItem = 0;
		Item.pszText = (LPSTR)szTitle;
		m_recordList.InsertItem(&Item);
		m_recordList.SetItem(&Item);


		/*�Ӽ��Է°�*/
		char tmp_cnum[30];
		Item.iSubItem = 1;
		if(DBFIsAttributeNULL(hDBF, index,  i)) // i�Ӽ��� NULL
		{
			Item.pszText = (LPSTR)"NULL";
		}
		else
		{
			switch(eType)
			{
				case FTString:
					Item.pszText = (LPSTR)DBFReadStringAttribute(hDBF, index, i);
					break;
				
				case FTInteger:
					itoa(DBFReadIntegerAttribute(hDBF, index, i), tmp_cnum, 10);
					Item.pszText = (LPSTR)tmp_cnum;
					break;

				case FTDouble:
					itoa(DBFReadDoubleAttribute(hDBF, index, i), tmp_cnum, 10);
					Item.pszText = (LPSTR)tmp_cnum;	
					break;
				
				default:
					break;

			}
			m_recordList.InsertItem(&Item);
			m_recordList.SetItem(&Item);

		} //else

	}//for - i

	const char 	*pszPlus;
	int iPart = 0;
	SHPHandle hSHP = SHPOpen(fpath_shp,"rb");
	SHPObject * psShape = SHPReadObject(hSHP, index);

	for(int j=0, iPart = 1; j < psShape->nVertices; j++)
	{
		const char	*pszPartType = "";

		if( j == 0 && psShape->nParts > 0 )
			pszPartType = SHPPartTypeName( psShape->panPartType[0] );

		if( iPart < psShape->nParts && psShape->panPartStart[iPart] == j )
		{
			pszPartType = SHPPartTypeName( psShape->panPartType[iPart] );
			iPart++;
			pszPlus = "+";
		}
		else
			pszPlus = " ";
/*
		printf("   %s (%12.3f,%12.3f, %g, %g) %s \n",
			pszPlus,
			psShape->padfX[j],
			psShape->padfY[j],
			psShape->padfZ[j],
			psShape->padfM[j],
			pszPartType );*/
		
	}
	 SHPClose( hSHP );
	
	 UpdateData(FALSE);


	return TRUE;
}




BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	pDlg = this;

//�ʵ� ����
	char *szText[5]={"Field","Type", "Title", "Width", "Decimals"};
	int nWid[5]={70, 70, 100, 70, 63};

	LV_COLUMN lCol;
	lCol.mask=LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH;  //����ü�� ����� Ȯ���� �÷��׸� ����
	lCol.fmt=LVCFMT_LEFT;  //Į���� ������ �������ķ� ����(_CENTER, _LEFT, _RIGHT�� ����)

	for(int i=0; i<5; i++)
	{
		lCol.pszText=szText[i];  //Į���� ������ ����
		lCol.iSubItem=i;  //����������� �ε����� ����
		lCol.cx=nWid[i];  //Į���� ���̸� ����
		m_ListC.InsertColumn(i,&lCol);  //LVCOLUMN����ü�� ������� ���� ���� ����Ʈ ��Ʈ�ѿ� Į���� ����
	}


//���ڵ� ���� (�Ӽ� / ��)
	
	LV_COLUMN lCol2;
	lCol2.mask=LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH;  //����ü�� ����� Ȯ���� �÷��׸� ����
	lCol2.fmt=LVCFMT_LEFT;

	lCol2.pszText = "Attribute";
	lCol2.iSubItem = 0;
	lCol2.cx = 100;
	m_recordList.InsertColumn(0, &lCol2);


	lCol2.pszText = "Value";
	lCol2.iSubItem = 1;
	lCol2.cx = 100;
	m_recordList.InsertColumn(1, &lCol2);

	//this->SetWindowPos(NULL, 0, 0, 300, 500, SWP_NOREPOSITION); 



//���ڵ�����


	
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}















void CMyDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

}

void CMyDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	CDialog::OnGetMinMaxInfo(lpMMI);
}


/*�������������*/
void CMyDlg::OnBnClickedButton1() 
{

	//UpdateData(FALSE);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMyDlg::OnLvnItemchangedListCtl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}
