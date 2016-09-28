// MiniNavi_t2Doc.cpp : CMiniNavi_t2Doc 클래스의 구현
//

#include "stdafx.h"
#include "MiniNavi_t2.h"
#include "MiniNavi_t2Doc.h"

#include "shapefil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMiniNavi_t2Doc

IMPLEMENT_DYNCREATE(CMiniNavi_t2Doc, CDocument)

BEGIN_MESSAGE_MAP(CMiniNavi_t2Doc, CDocument)
END_MESSAGE_MAP()


// CMiniNavi_t2Doc 생성/소멸

CMiniNavi_t2Doc::CMiniNavi_t2Doc()
{	//일회성 코드
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("파일입력 드래그 앤 드롭\n");
	printf("줌 인/아웃 : 마우스 휠\n");
	printf("이동: 마우스왼쪽 클릭 후 드래그\n");
	printf("shp상세정보: 마우스우 클릭 \n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

}

CMiniNavi_t2Doc::~CMiniNavi_t2Doc()
{
}

BOOL CMiniNavi_t2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMiniNavi_t2Doc serialization

void CMiniNavi_t2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}


// CMiniNavi_t2Doc 진단

#ifdef _DEBUG
void CMiniNavi_t2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMiniNavi_t2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMiniNavi_t2Doc 명령
