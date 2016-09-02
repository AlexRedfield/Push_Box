// TwoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Push_Box.h"
#include "TwoDlg.h"
#include "afxdialogex.h"
#include <mmsystem.h>
#pragma comment( lib, "Winmm.lib" )  

// CTwoDlg �Ի���

IMPLEMENT_DYNAMIC(CTwoDlg, CDialogEx)

CTwoDlg::CTwoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTwoDlg::IDD, pParent)
{

}

CTwoDlg::~CTwoDlg()
{
}

void CTwoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTwoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_INFO, &CTwoDlg::OnBnClickedInfo)
END_MESSAGE_MAP()


// CTwoDlg ��Ϣ�������


void CTwoDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	
	CRect ClientRect;
		CBitmap* OldBmp=NULL;        //����ԭ��Bitmap

		GetClientRect(&ClientRect);  //ȡ����ͻ�����С

		m_memDC.CreateCompatibleDC(&dc);//����ԭ��DC�����ڴ����DC
		m_memBmp.CreateCompatibleBitmap(&dc,ClientRect.Width(),ClientRect.Height());//�����ڴ����λͼ

		m_memDC.SelectObject(&m_memBmp);//�滻�ڴ�DC��λͼ

		OldBmp = m_memDC.SelectObject(&m_memBmp);
		//��ͼƬ���Ƶ��ڴ�DC��
		m_bkImg.BitBlt(m_memDC,0,0,ClientRect.Width(),ClientRect.Height(),0,0,SRCCOPY);

		//���ڴ�DC�ϵ����ݸ��Ǵ���DC�ϵ�����
		dc.BitBlt(0,0,ClientRect.Width(),ClientRect.Height(),&m_memDC,0,0,SRCCOPY);

		m_memDC.SelectObject(OldBmp);
		m_memDC.DeleteDC();     //ɾ���������ڴ�DC
		m_memBmp.DeleteObject();//ɾ���������ڴ����λͼ
		CDialogEx::OnPaint();
}


BOOL CTwoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_bkImg.Load(TEXT(".\\res\\BG.jpg"));//����ͼƬ
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	PlaySound(_T(".\\res\\music.wav"), NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);   //��������
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CTwoDlg::OnBnClickedInfo()
{//��Ϸ ˵��
	CString str;
	str.Format(_T("��������ƣ���5�����ڽ������Ƶ�Ŀ��ص�ɣ�\n(����ʱ�������ô��ر�)"));
	AfxMessageBox(str);
	
}
