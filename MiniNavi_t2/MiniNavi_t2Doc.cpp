// MiniNavi_t2Doc.cpp : CMiniNavi_t2Doc Ŭ������ ����
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


// CMiniNavi_t2Doc ����/�Ҹ�

CMiniNavi_t2Doc::CMiniNavi_t2Doc()
{	//��ȸ�� �ڵ�
	printf("����������������������������������������������������������������������������������������������\n");
	printf("�����Է� �巡�� �� ���\n");
	printf("�� ��/�ƿ� : ���콺 ��\n");
	printf("�̵�: ���콺���� Ŭ�� �� �巡��\n");
	printf("shp������: ���콺�� Ŭ�� \n");
	printf("����������������������������������������������������������������������������������������������\n");

}

CMiniNavi_t2Doc::~CMiniNavi_t2Doc()
{
}

BOOL CMiniNavi_t2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CMiniNavi_t2Doc serialization

void CMiniNavi_t2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}


// CMiniNavi_t2Doc ����

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


// CMiniNavi_t2Doc ���
