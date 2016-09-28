// MyDlg.cpp : 구현 파일입니다.
//
#pragma once
#include "stdafx.h"
#include "MiniNavi_t2.h"
#include "MyDlg.h"
#include <string.h>
#include <string>
#include <stdlib.h>
// CMyDlg 대화 상자입니다.

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

// CMyDlg 메시지 처리기입니다.

LRESULT CMyDlg::OnMyMsg(WPARAM wParam, LPARAM lParam) // Shape검색후, 상세정보 출력 wParam: fpath, lParam: 파일내 인덱스
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
	//	printf("안열림\n");
	//	return TRUE;
	//}

	//printf("━━━━━━━━━━━━━━━━━━━━━━━━ SHP INFO START━━━━━━━━━━━━━━━━━━━━━━━━\n");	
	int		nWidth, nDecimals;
	char	szTitle[12];
	int fieldCnt = DBFGetFieldCount(hDBF);


	UpdateData(TRUE);
	m_ListC.DeleteAllItems(); // 필드의 속성
	m_recordList.DeleteAllItems(); // 필드값

	/*해당 DBF파일의 속성에 대한 정보 */
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


	/*레코드(hDBF, index)에 대한 정보 출력( 속성, 값) */
	for(int i = 0; i < fieldCnt; i++ )
	{
		DBFFieldType	eType;
		eType = DBFGetFieldInfo( hDBF, i, szTitle, &nWidth, &nDecimals );


		LVITEM Item;
		Item.mask = LVIF_TEXT;
		Item.iItem = i;
		
		/*속성제목입력*/
		Item.iSubItem = 0;
		Item.pszText = (LPSTR)szTitle;
		m_recordList.InsertItem(&Item);
		m_recordList.SetItem(&Item);


		/*속성입력값*/
		char tmp_cnum[30];
		Item.iSubItem = 1;
		if(DBFIsAttributeNULL(hDBF, index,  i)) // i속성이 NULL
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
	

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	pDlg = this;

//필드 정보
	char *szText[5]={"Field","Type", "Title", "Width", "Decimals"};
	int nWid[5]={70, 70, 100, 70, 63};

	LV_COLUMN lCol;
	lCol.mask=LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH;  //구조체의 기능을 확장할 플래그를 지정
	lCol.fmt=LVCFMT_LEFT;  //칼럼의 정렬을 왼쪽정렬로 지정(_CENTER, _LEFT, _RIGHT중 선택)

	for(int i=0; i<5; i++)
	{
		lCol.pszText=szText[i];  //칼럼의 제목을 지정
		lCol.iSubItem=i;  //서브아이템의 인덱스를 지정
		lCol.cx=nWid[i];  //칼럼의 넓이를 지정
		m_ListC.InsertColumn(i,&lCol);  //LVCOLUMN구조체로 만들어진 값을 토대로 리스트 컨트롤에 칼럼을 삽입
	}


//레코드 정보 (속성 / 값)
	
	LV_COLUMN lCol2;
	lCol2.mask=LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH;  //구조체의 기능을 확장할 플래그를 지정
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



//레코드정보


	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}















void CMyDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

}

void CMyDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	CDialog::OnGetMinMaxInfo(lpMMI);
}


/*사용하하지않음*/
void CMyDlg::OnBnClickedButton1() 
{

	//UpdateData(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMyDlg::OnLvnItemchangedListCtl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}
