// Choose.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Push_Box.h"
#include "Choose.h"
#include "afxdialogex.h"


// CChoose �Ի���

IMPLEMENT_DYNAMIC(CChoose, CDialogEx)

CChoose::CChoose(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChoose::IDD, pParent)
{

	//  m_StageNum = 0;
	//  m_StageNum = 0;
	m_StageNum = 0;
}

CChoose::~CChoose()
{
}

void CChoose::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT_NUM, m_StageNum);
	//  DDV_MinMaxInt(pDX, m_StageNum, 1, 100);
	//  DDX_Text(pDX, IDC_EDIT_NUM, m_StageNum);
	//  DDV_MinMaxInt(pDX, m_StageNum, 1, 42);
	DDX_Text(pDX, IDC_EDIT_NUM, m_StageNum);
	DDV_MinMaxLong(pDX, m_StageNum, -100, 100);
}


BEGIN_MESSAGE_MAP(CChoose, CDialogEx)
	ON_BN_CLICKED(IDOK, &CChoose::OnBnClickedOk)
END_MESSAGE_MAP()


// CChoose ��Ϣ�������


void CChoose::OnBnClickedOk()
{
	UpdateData(TRUE);//���ؼ�������ݴ����ؼ��󶨱�����
	CDialogEx::OnOK();
}
