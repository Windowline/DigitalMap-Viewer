// MiniNavi_t2Doc.h : CMiniNavi_t2Doc Ŭ������ �������̽�
//
#include "shapefil.h"


#pragma once

using namespace std;


class CMiniNavi_t2Doc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CMiniNavi_t2Doc();
	DECLARE_DYNCREATE(CMiniNavi_t2Doc)

// Ư���Դϴ�.
public:


// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CMiniNavi_t2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


