
// Push_BoxDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Push_Box.h"
#include "Push_BoxDlg.h"
#include "afxdialogex.h"
#include "TwoDlg.h"
#include "Choose.h"
#include <mmsystem.h>
#pragma comment( lib, "Winmm.lib" )  
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAP_BACK      0
#define MAP_WALL      1
#define MAP_ROAD      2
#define MAP_DEST     3
#define MAP_CRATE       4
#define MAP_REDBOX    5
#define MAP_MAN       6
#define MAP_BALLMAN      7

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




BEGIN_MESSAGE_MAP(CPush_BoxDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_COMMAND(ID_CHOOSE_STAGE, &CPush_BoxDlg::OnChooseStage)
	ON_COMMAND(ID_BGM, &CPush_BoxDlg::OnBgm)
	ON_COMMAND(ID_TON, &CPush_BoxDlg::OnTon)
	ON_COMMAND(ID_TOFF, &CPush_BoxDlg::OnToff)


//	ON_WM_KEYDOWN()
//ON_WM_KEYDOWN()
ON_COMMAND(ID_RESTART, &CPush_BoxDlg::OnRestart)
END_MESSAGE_MAP()


// CPush_BoxDlg 消息处理程序
CPush_BoxDlg::CPush_BoxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPush_BoxDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_step  =0;
	m_level =1;
}

void CPush_BoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BOOL CPush_BoxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	CTwoDlg m_DlgTwo;
	m_DlgTwo.DoModal();  //主界面生成前打开子界面

	m_ImgBack.Load(L"res\\0.png");//加载背景图片
	m_ImgWall.Load(L"res\\1.png");//加载墙图片
	m_ImgRoad.Load(L"res\\2.png");//加载通道图片
	m_ImgDest.Load(L"res\\3.png");//加载目的地图片
	m_ImgCrate.Load(L"res\\4.png");//加载箱子图片
	m_ImgRedBox.Load(L"res\\5.png");//加载箱子图片
	m_ImgMan.Load(L"res\\6.png");//加载人图片
	m_ImgBallMan.Load(L"res\\7.png");//加载墙图片

	loadMap(m_level);//加载关卡数据到数组中

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。



void CPush_BoxDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		drawMap(&dc);
		CFont font;                                       //定义一个字体对象
		CFont* OldFont =NULL;                  //保存系统原有字体

		font.CreatePointFont(150,TEXT("微软雅黑"));//创建字体
		OldFont=dc.SelectObject(&font);  //替换系统原有字体
dc.SetBkMode(TRANSPARENT);   //设置文本的输出模式为透明
		CString DrawString;
	
			DrawString.Format(TEXT("第%01d关 "),m_level);
		dc.TextOutW(410,20,DrawString);//设置字体位置
		DrawString.Format(TEXT("已走步数:%01d "),m_step);
		dc.TextOutW(410,60,DrawString);//设置字体位置
		dc.SelectObject(OldFont);            //恢复系统原有字体

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPush_BoxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPush_BoxDlg::loadMap( int iMissionNum)       
{
	CString str;
	str.Format( TEXT( "[%d]" ), iMissionNum );

	FILE *pFile = _wfopen( L"map.txt", L"r" );
	if ( pFile == NULL )
		return;

	TCHAR cTmp[20] = L"\0";
	fgetws( cTmp, 20, pFile );
	while ( wcsncmp( cTmp, str, 3 ) != 0 )
	{
		fgetws( cTmp, 20, pFile );
	}

	for (int i = 0; i < 14; i++)
		fgetws( m_cMap[i], 20, pFile );

	fclose(pFile);
}
void CPush_BoxDlg::OnChooseStage()
{
	// 打开选择关卡界面
   CChoose m_choose;
   m_choose.DoModal(); 
  
   if(m_choose.m_StageNum>42||m_choose.m_StageNum<1)
	   AfxMessageBox(_T("请输入42以内的数字"));
   else
   {  m_level=m_choose.m_StageNum;
   OnRestart();}
}

void CPush_BoxDlg::drawMap(CDC *pDC)           //画地图
{
	int i, j, x, y;
	for (i = 0; i < 14; i++)//数组行
	{
		for (j = 0; j < 16; j++)//数组的列
		{
			x = j * 25;//35 表示每个小图片的大小
			y = i * 25;

		int iValue = m_cMap[i][j] - 48;//把字符转换为int
			switch (iValue)
			{
			case MAP_BACK://0    背景	
				DrawBack(x, y, pDC);
				break;
			case MAP_WALL://1   墙
				DrawWall(x, y, pDC);
				break;
			case MAP_ROAD://2   路	
				DrawRoad(x, y, pDC);
				break;
			case MAP_DEST://3  地点
				DrawDest(x, y, pDC);
				break;
			case MAP_CRATE://4    箱子
				DrawCrate(x, y, pDC);
				break;
			case MAP_REDBOX://5   目的地的箱子
				DrawRedBox(x, y, pDC);
				break;
			case MAP_MAN://6    人物
				DrawMan(x, y, pDC);
				break;
			case MAP_BALLMAN://7   目的地的 人物
				DrawBallMan(x, y, pDC);
				break;
				}
		}
	}
}
void CPush_BoxDlg::DrawBack(int x,int y,CDC *pDC)
{

	CRect rect;
	GetClientRect(&rect);

	m_ImgBack.Draw(*pDC,x,y,25,25);

}
void CPush_BoxDlg::DrawWall(int x,int y,CDC *pDC)
{

	CRect rect;
	GetClientRect(&rect);

	m_ImgWall.Draw(*pDC,x,y,25,25);

}

void CPush_BoxDlg::DrawRoad(int x,int y,CDC *pDC)
{

	CRect rect;
	GetClientRect(&rect);

	m_ImgRoad.Draw(*pDC,x,y,25,25);

}

void CPush_BoxDlg::DrawDest(int x,int y,CDC *pDC)
{

	CRect rect;
	GetClientRect(&rect);

	m_ImgDest.Draw(*pDC,x,y,25,25);

}

void CPush_BoxDlg::DrawCrate(int x,int y,CDC *pDC)
{

	CRect rect;
	GetClientRect(&rect);

	m_ImgCrate.Draw(*pDC,x,y,25,25);

}


void CPush_BoxDlg::DrawRedBox(int x,int y,CDC *pDC)
{

	CRect rect;
	GetClientRect(&rect);

	m_ImgRedBox.Draw(*pDC,x,y,25,25);

}

void CPush_BoxDlg::DrawMan(int x,int y,CDC *pDC)
{

	CRect rect;
	GetClientRect(&rect);

	m_ImgMan.Draw(*pDC,x,y,25,25);

}

void CPush_BoxDlg::DrawBallMan(int x,int y,CDC *pDC)
{

	CRect rect;
	GetClientRect(&rect);

	m_ImgBallMan.Draw(*pDC,x,y,25,25);

}
BOOL CPush_BoxDlg::IsFinish()
{
	for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (int(m_cMap[i][j]-48) == MAP_DEST|| int(m_cMap[i][j] -48)== MAP_BALLMAN)
			{
                return FALSE;
			}
        }
    }
    return TRUE;

}
BOOL CPush_BoxDlg::PreTranslateMessage(MSG* pMsg)
{
			    if(pMsg->message == WM_KEYDOWN)
	{
		updateMap(pMsg->wParam);
		Invalidate(true);
			if(IsFinish())
		{
			AfxMessageBox(_T("Well Done，您将进入下一关!"));
			m_level = m_level + 1;
           loadMap(m_level);
			m_ptManPosition =getManPosition();
			OnRestart();
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);

}
CPoint CPush_BoxDlg::getManPosition()
{
		CPoint manPosition;
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (int (m_cMap[i][j]-48) == MAP_MAN  ||int(m_cMap[i][j]-48) == MAP_BALLMAN)//逐点判断是不是人
            {
                manPosition.x = j;
                manPosition.y = i;
            }
        }
    }
    return manPosition;
}
void CPush_BoxDlg::updateMap(UINT nChar)
{
	int x1,y1,x2,y2,x3,y3;
	
	//获得人的位置
	x1 = getManPosition().x;
	y1 = getManPosition().y;

	switch(nChar)
	{
		case VK_UP:
			x2 = x1;
			y2 = y1 - 1;
			x3 = x1;
			y3 = y1 - 2;
			ReDrawMap(y1,x1,y2,x2,y3,x3);
			break;
		case VK_DOWN:
			x2 = x1;
			y2 = y1 + 1;
			x3 = x1;
			y3 = y1 + 2;
			ReDrawMap(y1,x1,y2,x2,y3,x3);
			break;
		case VK_LEFT:
			x2 = x1 - 1;
			y2 = y1;
			x3 = x1 - 2;
			y3 = y1;
			ReDrawMap(y1,x1,y2,x2,y3,x3);
			break;
		case VK_RIGHT:
			x2 = x1 + 1;
			y2 = y1;
			x3 = x1 + 2;
			y3 = y1;
			ReDrawMap(y1,x1,y2,x2,y3,x3);
			break;
		default:
			break;
	}
}

void CPush_BoxDlg::ReDrawMap(int x1, int y1, int x2, int y2, int x3, int y3)  //核心语句，根据键盘按键更新地图
{
	int iValue1=m_cMap[x1][y1]-48;
	int iValue2=m_cMap[x2][y2]-48;
	int iValue3=m_cMap[x3][y3]-48;
	switch (iValue2)
    {
    case MAP_WALL:          
        break;
    case MAP_ROAD:           
      m_cMap[x2][y2] = '6';
        if (iValue1 == MAP_MAN)
		m_cMap[x1][y1] = '2';
     else if (iValue1 == MAP_BALLMAN)   //
	 m_cMap[x1][y1] = '3';
        m_ptManPosition.x = x2;
        m_ptManPosition.y = y2;
		m_step++;
        break;
    case MAP_DEST:            
           m_cMap[x2][y2] = '7';   
        if (iValue1 == MAP_MAN)
		m_cMap[x1][y1] = '2';
        else if (iValue1  == MAP_BALLMAN)//
		m_cMap[x1][y1] = '3';     
       m_ptManPosition.x = x2;
       m_ptManPosition.y = y2;
		m_step++;
        break;
    case MAP_CRATE:         
        if (iValue3 == MAP_DEST) 
        {
			m_cMap[x3][y3] ='5';
               m_cMap[x2][y2]= '6';m_step++;
            if (iValue1 == MAP_MAN)
			m_cMap[x1][y1]= '2';
            else if (iValue1 == MAP_BALLMAN)//
               m_cMap[x1][y1] = '3';
          m_ptManPosition.x = x2;
          m_ptManPosition.y = y2;
		m_step++;
        }
        else if (iValue3 == MAP_ROAD) 
        {
            m_cMap[x3][y3] = '4';
            m_cMap[x2][y2]= '6';
            if (iValue1  == MAP_MAN)
                m_cMap[x1][y1]='2';
            else if (iValue1  == MAP_BALLMAN)//
                m_cMap[x1][y1]  ='3';
          m_ptManPosition.x = x2;
          m_ptManPosition.y = y2;
		m_step++;
        }
        break;
    case MAP_REDBOX:             
        if (iValue3 == MAP_DEST)
        {
            m_cMap[x3][y3]= '5';
            m_cMap[x2][y2] = '7';
            if (iValue1 == MAP_MAN)
               m_cMap[x1][y1]='2';
            else if (iValue1  == MAP_BALLMAN)//
               m_cMap[x1][y1]='3';
           m_ptManPosition.x = x2;
           m_ptManPosition.y = y2;
			m_step++;
        }
        else if (iValue3 == MAP_ROAD)
        {
            m_cMap[x3][y3]='4';
            m_cMap[x2][y2] ='7';//
            if (iValue1 == MAP_BALLMAN)
                 m_cMap[x1][y1]  ='2';
            else if (iValue1  == MAP_BALLMAN)//
                 m_cMap[x1][y1] ='3';
        m_ptManPosition.x = x2;
        m_ptManPosition.y = y2;
		m_step++;
        }        
        break;

        case MAP_MAN:            //地图有问题
        AfxMessageBox(_T("地图有问题"));
        break;

    }
	InvalidateRect(NULL);
}

void CPush_BoxDlg::OnBgm()
{
	
	PlaySound(_T(".\\res\\music.wav"), NULL, SND_FILENAME | SND_ASYNC); 
	
	PlaySound(NULL,NULL,SND_PURGE);
	// 
}


void CPush_BoxDlg::OnTon()
{
	PlaySound(_T(".\\res\\music.wav"), NULL, SND_FILENAME|SND_ASYNC|SND_LOOP); 
	// 播放音乐
}


void CPush_BoxDlg::OnToff()
{
	// 关闭音乐
	PlaySound(NULL,NULL,SND_PURGE);
}


void CPush_BoxDlg::OnRestart()//重置游戏
{
	m_step=0;
	loadMap(m_level);
	Invalidate();
}