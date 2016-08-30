
// Push_BoxDlg.h : 头文件
//

#pragma once


// CPush_BoxDlg 对话框
class CPush_BoxDlg : public CDialogEx
{

public:
	CPush_BoxDlg(CWnd* pParent = NULL);	// 标准构造函数
	
// 对话框数据
	enum { IDD = IDD_PUSH_BOX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;     

	
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	UINT m_level;//当前关卡
	UINT m_maxlevel;
	TCHAR m_cMap[20][20];//地图数据
	CImage m_ImgBack;    //背景图片
	CImage m_ImgWall;    //墙图片
	CImage m_ImgRoad;   //路图片
	CImage m_ImgDest;     //目的地图片
	CImage m_ImgCrate;   //箱子图片
	CImage m_ImgMan;    //人图片
	CImage m_ImgRedBox;
	CImage m_ImgBallMan;

	void DrawMap(CDC *pDC);      //画地图
	void DrawBack(int x,int y,CDC *pDC);//画背景
	void DrawWall(int x,int y,CDC *pDC);//画墙
	void DrawRoad(int x,int y,CDC *pDC);//画路
	void DrawDest(int x,int y,CDC *pDC);//画地点
	void DrawCrate(int x,int y,CDC *pDC);//画箱子
    void DrawRedBox(int x,int y,CDC *pDC);//画成功箱子
	void DrawMan(int x,int y,CDC *pDC);//画人
	void DrawBallMan(int x,int y,CDC *pDC);//画人和地点

	POINT m_ptManPosition;        //人的位置
	UINT m_step;                          //步数
	void updateMap(UINT nChar);
	CPoint getManPosition();        //获得人的位置
	void loadMap(int iMissionNum);//加载地图
	void drawMap(CDC *pDC);      //画地图
	void ReDrawMap(int x1, int y1, int x2, int y2, int x3, int y3);//更新地图
	void StartGame();                   //开始游戏
	BOOL IsFinish();                      //判断箱子是否到目的地

	afx_msg void OnChooseStage();
	afx_msg void OnBgm();
	afx_msg void OnTon();
	afx_msg void OnToff();

//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRestart();         //重置游戏
};
