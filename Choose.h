#pragma once


// CChoose 对话框

class CChoose : public CDialogEx
{
	DECLARE_DYNAMIC(CChoose)

public:
	CChoose(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChoose();

// 对话框数据
	enum { IDD = IDD_CHOOSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedOk();

	long m_StageNum;//控件变量
};
