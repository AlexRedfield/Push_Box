#pragma once


// CChoose �Ի���

class CChoose : public CDialogEx
{
	DECLARE_DYNAMIC(CChoose)

public:
	CChoose(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChoose();

// �Ի�������
	enum { IDD = IDD_CHOOSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	int m_StageNum;
	afx_msg void OnBnClickedOk();
//	int m_StageNum;
	long m_StageNum;
};
