#pragma once


// CTwoDlg �Ի���

class CTwoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTwoDlg)

public:
	CTwoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTwoDlg();

// �Ի�������
	enum { IDD = IDD_TWODLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CDC m_memDC;              //�����滻����DC
	CBitmap m_memBmp;     //�ڴ����λͼ
	CImage  m_bkImg;           //����ͼƬ
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedInfo();
};
