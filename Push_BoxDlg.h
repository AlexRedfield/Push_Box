
// Push_BoxDlg.h : ͷ�ļ�
//

#pragma once


// CPush_BoxDlg �Ի���
class CPush_BoxDlg : public CDialogEx
{

public:
	CPush_BoxDlg(CWnd* pParent = NULL);	// ��׼���캯��
	
// �Ի�������
	enum { IDD = IDD_PUSH_BOX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;     

	
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int m_time;//ʱ��
	int m_vtime;//ʱ����
	int m_score[42];//����
	int m_Score;//��ǰ�ܷ���
	int m_record;//��߼�¼
	UINT m_step; //����
	UINT m_level;//��ǰ�ؿ�
	TCHAR m_cMap[20][20];//��ͼ����
	CImage m_ImgBack;    //����ͼƬ
	CImage m_ImgWall;    //ǽͼƬ
	CImage m_ImgRoad;   //·ͼƬ
	CImage m_ImgDest;     //Ŀ�ĵ�ͼƬ
	CImage m_ImgCrate;   //����ͼƬ
	CImage m_ImgMan;    //��ͼƬ
	CImage m_ImgRedBox; //Ŀ�ĵص�����ͼƬ
	CImage m_ImgBallMan; //Ŀ�ĵص���ͼƬ

	void DrawMap(CDC *pDC);      //����ͼ
	void DrawBack(int x,int y,CDC *pDC);//������
	void DrawWall(int x,int y,CDC *pDC);//��ǽ
	void DrawRoad(int x,int y,CDC *pDC);//��·
	void DrawDest(int x,int y,CDC *pDC);//���ص�
	void DrawCrate(int x,int y,CDC *pDC);//������
    void DrawRedBox(int x,int y,CDC *pDC);//���ɹ�����
	void DrawMan(int x,int y,CDC *pDC);//����
	void DrawBallMan(int x,int y,CDC *pDC);//���˺͵ص�

	POINT m_ptManPosition;        //�˵�λ��
	void updateMap(UINT nChar);
	CPoint getManPosition();        //����˵�λ��
	void loadMap(int iMissionNum);//���ص�ͼ
	void drawMap(CDC *pDC);      //����ͼ
	void ReDrawMap(int x1, int y1, int x2, int y2, int x3, int y3);//���µ�ͼ
	void StartGame();                   //��ʼ��Ϸ
	BOOL IsFinish();                      //�ж������Ƿ�Ŀ�ĵ�

	afx_msg void OnChooseStage();
	afx_msg void OnTon();
	afx_msg void OnToff();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnRestart();         //������Ϸ
	afx_msg void OnTimer(UINT_PTR nIDEvent);//ʵ�ֶ�ʱ����
	afx_msg void OnRecord();//��ʾ��¼
	afx_msg void OnSave();//������Ϸ
	afx_msg void OnLoad();//������Ϸ
	afx_msg void OnVclose();//�ر�ʱ����
};
