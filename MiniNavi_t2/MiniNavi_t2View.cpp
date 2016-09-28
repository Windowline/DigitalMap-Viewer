// MiniNavi_t2View.cpp : CMiniNavi_t2View Ŭ������ ����
//

#include "stdafx.h"
#include "MiniNavi_t2.h"

#include "MiniNavi_t2Doc.h"
#include "MiniNavi_t2View.h"

#include "shapefil.h"
#include "MainFrm.h"

#include <vector>
#include <algorithm>
#include <math.h>

#include "string"
#include "SHPManager.h"
#include "GridController.h"

#ifdef _DEBUG

#define new DEBUG_NEW
#define OriginX 0
#define OriginY 0
#define MAX_PATH_LEN 100

#define SELECT_RANGE 30

#endif


#include <iostream>

using namespace std;

// CMiniNavi_t2View

IMPLEMENT_DYNCREATE(CMiniNavi_t2View, CView)

BEGIN_MESSAGE_MAP(CMiniNavi_t2View, CView)

// ǥ�� �μ� ����Դϴ�.
ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_WM_CREATE()
//	ON_WM_KEYDOWN()
//ON_WM_MOUSEMOVE()
//ON_WM_PAINT()
ON_WM_MOUSEWHEEL()
ON_WM_HSCROLL()
ON_WM_VSCROLL()
//ON_WM_KEYDOWN()
//ON_WM_KEYDOWN()
ON_WM_KEYDOWN()
ON_WM_DROPFILES()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_RBUTTONDOWN()
ON_WM_MOUSEMOVE()

END_MESSAGE_MAP()

// CMiniNavi_t2View ����/�Ҹ�


CMiniNavi_t2View::CMiniNavi_t2View()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_Zoom = 1.f;
	m_is_mouse_down = false;
	m_dx = 0;
	m_dy = 0;
	m_cur_x=0;
	m_cur_y=0;
	m_f_cnt = 0;
	m_selected = -1;

	m_zdx = 0;
	m_zdy = 0;
}

CMiniNavi_t2View::~CMiniNavi_t2View()
{
}

BOOL CMiniNavi_t2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMiniNavi_t2View �׸���

void CMiniNavi_t2View::OnDraw(CDC* pDC)
{
	CMiniNavi_t2Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CClientDC dc(this);
	CRect rect;
	dc.GetClipBox(&rect);

	m_width = rect.Width();
	m_height = rect.Height();

	
	//GDI ���
	Gdiplus:: Bitmap bitmap(m_width, m_height);
	Gdiplus:: Graphics grph((*pDC));
	
	if(m_is_mouse_down) // �巡�� o	
		m_range = manager.drawAllSHP_e_gdi2(&bitmap, m_width, m_height, m_Zoom, m_cur_x + m_dx, m_cur_y+m_dy);

	else if(!m_is_mouse_down) //�巡�� x
		m_range = manager.drawAllSHP_e_gdi2(&bitmap, m_width, m_height, m_Zoom, m_cur_x, m_cur_y);	

	g_controller.drawGrid_gdi(&bitmap, m_range);

	grph.DrawImage(&bitmap, 0, 0);

}


// CMiniNavi_t2View �μ�

BOOL CMiniNavi_t2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMiniNavi_t2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMiniNavi_t2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}




// CMiniNavi_t2View ����

#ifdef _DEBUG
void CMiniNavi_t2View::AssertValid() const
{
	CView::AssertValid();
}

void CMiniNavi_t2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMiniNavi_t2Doc* CMiniNavi_t2View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMiniNavi_t2Doc)));
	return (CMiniNavi_t2Doc*)m_pDocument;
}

#endif //_DEBUG



BOOL CMiniNavi_t2View::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	CClientDC dc(this);
	CRect rect;
	dc.GetClipBox(&rect);
	
	shp_range scRange = manager.getSCRange(m_width, m_height); // ��,���콺���� ȭ��� ��������(ȭ������� ����: �׻󰰾ƾ�)

	//ȭ��� ����
	double cx = m_width/2;
	double cy = m_height/2;
	
	//ȭ��� ����
	double ox = 0.0;
	double oy = 0.0;

	//���� shape���� ����
	double shape_ox = scRange.start.x * m_Zoom + m_cur_x;
	double shape_oy = scRange.start.y * m_Zoom + m_cur_y;

	//���� sh���� - ȭ��� ������ �Ÿ�
	double shox_to_cx = cx + (ox - shape_ox);
	double shoy_to_cy = cy + (oy - shape_oy);

	//���� ����
	double len_cur_x = m_Zoom * (scRange.end.x - scRange.start.x);
	double len_cur_y = m_Zoom * (scRange.end.y - scRange.start.y);

	if(zDelta<0)
	{
		if(m_Zoom==0.1)
			return FALSE;

		m_Zoom -= 0.1f;
	}
	if(zDelta >0 )
	{
		m_Zoom += 0.1f;
	}
	//���� ����
	double len_zoom_x = m_Zoom * (scRange.end.x - scRange.start.x);
	double len_zoom_y = m_Zoom * (scRange.end.y - scRange.start.y);
	
	//������ �߾��̾��� ���� ������ ��ġ
	double shox_to_cx_zoom = (shox_to_cx * len_zoom_x) / len_cur_x;	
	double shoy_to_cy_zoom = (shoy_to_cy * len_zoom_y) / len_cur_y;
	
	//���� ���� ����
	double diff_cx = shox_to_cx_zoom - shox_to_cx;
	double diff_cy = shoy_to_cy_zoom - shoy_to_cy;

	m_cur_x -= diff_cx;
	m_cur_y -= diff_cy;


	Invalidate(FALSE);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}





void CMiniNavi_t2View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}


void CMiniNavi_t2View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	DragAcceptFiles(TRUE);
	m_PageSize = CSize(1000, 1000);
	SetScrollSizes(MM_TEXT, m_PageSize);
}


void CMiniNavi_t2View::OnDropFiles(HDROP hDropInfo)
{

	UINT uiRet = DragQueryFile(hDropInfo, -1, NULL, NULL);
	
	if(uiRet==1)
	{	
		shp_range range;


		char dbf[4] = "dbf";
		char shp[4] = "shp";
		CString fpath; //150 max path

		DragQueryFile(hDropInfo, 0, fpath.GetBuffer(MAX_PATH_LEN), MAX_PATH_LEN);
		
		//�����ߺ�üũ
		for(int i=0; i<m_fpath.size(); i++)
		{
			if(strlen(m_fpath[i])!=strlen(fpath)) //���̴ٸ�
				break;
			
			if(strncmp(m_fpath[i], fpath, strlen(fpath)-3)==0)
			{
				AfxMessageBox("�̹� ���� �����Դϴ�.");
				return;
			}
		}

		/* CString -> char*   path.shp <--> path.dbf  CString�� �ٷ�� ����� �� �𸣰��� */

		char input1[MAX_PATH_LEN] = {0,};
		char input2[MAX_PATH_LEN] = {0,};
		int len = min(MAX_PATH_LEN, strlen(fpath));
		strncpy(input1, (LPSTR)(LPCSTR)fpath, len);
		strncpy(input2, input1, len-3);


		DBFHandle hDBF;
		if(input1[len-3]=='s' && input1[len-2]=='h' &&  input1[len-1]=='p') //shp
		{
			strcat(input2, dbf);			
			hDBF = DBFOpen(input2, "rb");
			range = manager.add_SHP_File(SHPOpen(input1, "rb"), hDBF, m_f_cnt);
			m_f_cnt++;
		}
		else if(input1[len-3]=='d' && input1[len-2]=='b' && input1[len-1] =='f') //dbf
		{
			strcat(input2, shp);	
			hDBF = DBFOpen(input1, "rb");
			range = manager.add_SHP_File(SHPOpen(input2, "rb"), hDBF, m_f_cnt);
			m_f_cnt++;
		}
		else
		{
			AfxMessageBox("shp Ȥ�� dbf�� ��������\n");
			printf("shp Ȥ�� dbf�� ��������\n");
			return;
		}

		m_fpath.push_back(fpath); // �ߺ� üũ �� shp�˻��� �޼����� �Բ������� ���ϰ��

		g_controller.grouping(manager.getShpList(), range); //range : raw min max

		Invalidate();
	}
	else
		AfxMessageBox("1����..\n");
	

	CScrollView::OnDropFiles(hDropInfo);
}

void CMiniNavi_t2View::OnLButtonDown(UINT nFlags, CPoint point)
{

	if(!m_is_mouse_down)
	{
		m_is_mouse_down = true;
		m_mouse_down_pos= point;
		m_dx = 0;
		m_dy = 0;		
	}

	CScrollView::OnLButtonDown(nFlags, point);
}

void CMiniNavi_t2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(m_is_mouse_down)
	{
		m_dx = point.x - m_mouse_down_pos.x;
		m_dy = point.y - m_mouse_down_pos.y;

		Invalidate(FALSE);
	}
	CScrollView::OnMouseMove(nFlags, point);
}

void CMiniNavi_t2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(m_is_mouse_down)
	{
		m_dx = point.x - m_mouse_down_pos.x;
		m_dy = point.y - m_mouse_down_pos.y;
		m_cur_x += m_dx;
		m_cur_y += m_dy;
		m_is_mouse_down = false;
		Invalidate(FALSE);
	}

	CScrollView::OnLButtonUp(nFlags, point);
}




void CMiniNavi_t2View::OnRButtonDown(UINT nFlags, CPoint point) //������Ž��
{
	
	/******************************��� ��Ʈ���� �� �˻�***********************/
	//printf("\n==============================search normal====================\n");
	//int choice = manager.selectEntry(point, m_width, m_height, m_Zoom, m_cur_x, m_cur_y);	
	//printf("NORMAL SELECT : %d\n", choice);	
	//if(choice!=-1)
	//{
	//	int f_index = ref[choice].get_h_index();
	//	CString fp = m_fpath[f_index];
	//	int index = ref[choice].get_index();

	//	::SendMessage(pDlg->GetSafeHwnd(), WM_MYMSG, (WPARAM)&fp, index);	
	//	Invalidate(FALSE); //ã���� ���� �ٽ� �׷���� 
	//}
	


	// �˻��� �׸��� �ֺ� �׸���� �Բ� Ž��
	//printf("\n==============================search grid====================\n"); 
	CPoint grid_idx = g_controller.searchGrid(point, m_range); //���콺�� �ִ� �׸���
	//printf("Grid: [ %d, %d ] \n", grid_idx.x, grid_idx.y);

	vector<SHPEntry> &ref = manager.getShpList();
	shp_range raw_range = manager.getSHPrange();
	//shp_range  raw_range = m_range;
	int divNum = g_controller.getDivNum();
	searchInfo answer;
	answer.min_index = -1;
	answer.min_dist = (1<<30);

	for(int X = grid_idx.x - 1; X <= grid_idx.x + 1; X++) 
	{
		if(X <= 0) continue;
		if(X > divNum) break;
		for(int Y = grid_idx.y -1; Y <=grid_idx.y + 1; Y++ )
		{
			if(Y <= 0) continue;
			if(Y > divNum) break;
			
			searchInfo tmp = g_controller.getGrid(X, Y).searchShp(point, ref, raw_range, m_width, m_height, m_Zoom, m_cur_x, m_cur_y);

			if(tmp.min_dist < answer.min_dist)
			{
				answer.min_index = tmp.min_index;
				answer.min_dist = tmp.min_dist;
			}
		}
	}

	int g_choice = answer.min_index;
	
	printf("GRID SELECT : %d\n", g_choice);		

	if(g_choice!=-1)
	{
		if(m_selected!=-1) 
			ref[m_selected].setDrawTypeDefault();//�� �� ���� ����
		
		ref[g_choice].setDrawType(0, 0, 0, 8);
		m_selected = g_choice;

		int f_index = ref[g_choice].get_h_index();
		CString fp = m_fpath[f_index];
		int index = ref[g_choice].get_index();
		::SendMessage(pDlg->GetSafeHwnd(), WM_MYMSG, (WPARAM)&fp, index);	
		Invalidate(FALSE); //ã���� ���� �ٽ� �׷���� 

	}
	CScrollView::OnRButtonDown(nFlags, point);
}





void CMiniNavi_t2View::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMiniNavi_t2View::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CMiniNavi_t2View::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point)
{
	printf("OnDrop\n");

	return CScrollView::OnDrop(pDataObject, dropEffect, point);
}

DROPEFFECT CMiniNavi_t2View::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
	return CScrollView::OnDragEnter(pDataObject, dwKeyState, point);
}

void CMiniNavi_t2View::OnDragLeave()
{
	CScrollView::OnDragLeave();
}

DROPEFFECT CMiniNavi_t2View::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
	return CScrollView::OnDragOver(pDataObject, dwKeyState, point);
}




