#pragma once


// CTwoDlg 对话框

class CTwoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTwoDlg)

public:
	CTwoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTwoDlg();

// 对话框数据
	enum { IDD = IDD_TWODLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CDC m_memDC;              //用于替换窗口DC
	CBitmap m_memBmp;     //内存兼容位图
	CImage  m_bkImg;           //背景图片
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedInfo();
};
