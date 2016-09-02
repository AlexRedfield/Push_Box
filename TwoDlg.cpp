// TwoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Push_Box.h"
#include "TwoDlg.h"
#include "afxdialogex.h"
#include <mmsystem.h>
#pragma comment( lib, "Winmm.lib" )  

// CTwoDlg 对话框

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


// CTwoDlg 消息处理程序


void CTwoDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	
	CRect ClientRect;
		CBitmap* OldBmp=NULL;        //保存原有Bitmap

		GetClientRect(&ClientRect);  //取窗体客户区大小

		m_memDC.CreateCompatibleDC(&dc);//根据原有DC创建内存兼容DC
		m_memBmp.CreateCompatibleBitmap(&dc,ClientRect.Width(),ClientRect.Height());//创建内存兼容位图

		m_memDC.SelectObject(&m_memBmp);//替换内存DC的位图

		OldBmp = m_memDC.SelectObject(&m_memBmp);
		//将图片绘制到内存DC上
		m_bkImg.BitBlt(m_memDC,0,0,ClientRect.Width(),ClientRect.Height(),0,0,SRCCOPY);

		//用内存DC上的内容覆盖窗体DC上的内容
		dc.BitBlt(0,0,ClientRect.Width(),ClientRect.Height(),&m_memDC,0,0,SRCCOPY);

		m_memDC.SelectObject(OldBmp);
		m_memDC.DeleteDC();     //删除创建的内存DC
		m_memBmp.DeleteObject();//删除创建的内存兼容位图
		CDialogEx::OnPaint();
}


BOOL CTwoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_bkImg.Load(TEXT(".\\res\\BG.jpg"));//载入图片
	// TODO:  在此添加额外的初始化
	PlaySound(_T(".\\res\\music.wav"), NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);   //播放音乐
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CTwoDlg::OnBnClickedInfo()
{//游戏 说明
	CString str;
	str.Format(_T("方向键控制，在5分钟内将箱子推到目标地点吧！\n(倒计时可在设置处关闭)"));
	AfxMessageBox(str);
	
}
