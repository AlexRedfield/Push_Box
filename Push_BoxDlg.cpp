
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
	ON_COMMAND(ID_TON, &CPush_BoxDlg::OnTon)
	ON_COMMAND(ID_TOFF, &CPush_BoxDlg::OnToff)
ON_COMMAND(ID_RESTART, &CPush_BoxDlg::OnRestart)
ON_WM_TIMER()
ON_COMMAND(ID_RECORD, &CPush_BoxDlg::OnRecord)
ON_COMMAND(ID_SAVE, &CPush_BoxDlg::OnSave)
ON_COMMAND(ID_LOAD, &CPush_BoxDlg::OnLoad)
ON_COMMAND(ID_VCLOSE, &CPush_BoxDlg::OnVclose)
END_MESSAGE_MAP()


// CPush_BoxDlg 消息处理程序
CPush_BoxDlg::CPush_BoxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPush_BoxDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_step  =0;
	m_level =1;
	m_time=0;
	m_vtime=0;
	for(int i=0;i<42;++i)
	m_score[i]=0;
	m_Score=0;
	
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
	SetTimer(1, 1000, NULL);//设置计时器

	freopen("res\\record.txt","r",stdin);//读取最高记录
	 scanf("%d",&m_record);
	 fclose(stdin);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

/*********************************************************
	函数名称：OnPaint
	功能描述：绘图
	作者：	  微软
	创建时间：2016-08-26
	参数说明：无
	返 回 值：无
*********************************************************/


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

		CBrush brush(RGB(255,0,0));
		CBrush* OldBrush=NULL;

		font.CreatePointFont(110,TEXT("微软雅黑"));//创建字体

		OldFont=dc.SelectObject(&font);  //替换系统原有字体
		OldBrush=dc.SelectObject(&brush);

        dc.SetBkMode(TRANSPARENT);   //设置文本的输出模式为透明

		CString DrawString;
	    SetTextColor(dc,RGB(0,0,0));//字体颜色
		DrawString.Format(TEXT("第%01d关 "),m_level);
		dc.TextOutW(400,10,DrawString);//设置字体位置
		
		DrawString.Format(TEXT("已走步数:%01d "),m_step);
		dc.TextOutW(400,40,DrawString);

		DrawString.Format(TEXT("时间:%02d "),m_time);
		dc.TextOutW(400,70,DrawString);

		DrawString.Format(TEXT("积分:%01d "),m_Score);
		dc.TextOutW(400,100,DrawString);

		
		dc.TextOutW(400,100,DrawString);
		if(m_vtime<301)
		dc.Rectangle(100,420,420-1.06*m_vtime,430);

		dc.SelectObject(OldFont);            //恢复系统原有字体
		dc.SelectObject(OldBrush);
	
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPush_BoxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*********************************************************
	函数名称：loadMap
	功能描述：从文件中载入地图
	作者：	  沈钰博
	创建时间：2016-08-27
	参数说明：关卡
	返 回 值：无
*********************************************************/
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
  
   if(m_choose.m_StageNum>42||m_choose.m_StageNum<1)//输入数必须在1到42之间
	   AfxMessageBox(_T("请输入42以内的数字"));
   else
   {  
	   m_level=m_choose.m_StageNum;
       OnRestart();}
   }
/*********************************************************
	函数名称：drawMap
	功能描述：绘制地图
	作者：	  沈钰博
	创建时间：2016-08-27
	参数说明：界面指针
	返 回 值：无
*********************************************************/
void CPush_BoxDlg::drawMap(CDC *pDC)           //画地图
{
	int i, j, x, y;
	for (i = 0; i < 14; i++)//数组行
	{
		for (j = 0; j < 16; j++)//数组的列
		{
			x = j * 32;//30 表示每个小图片的大小
			y = i *32;

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

	m_ImgBack.Draw(*pDC,x,y,32,32);

}
void CPush_BoxDlg::DrawWall(int x,int y,CDC *pDC)
{

	CRect rect;
	GetClientRect(&rect);

	m_ImgWall.Draw(*pDC,x,y,32,32);

}

void CPush_BoxDlg::DrawRoad(int x,int y,CDC *pDC)
{

	CRect rect;
	GetClientRect(&rect);

	m_ImgRoad.Draw(*pDC,x,y,32,32);

}

void CPush_BoxDlg::DrawDest(int x,int y,CDC *pDC)
{

	CRect rect;
	GetClientRect(&rect);

	m_ImgDest.Draw(*pDC,x,y,32,32);

}

void CPush_BoxDlg::DrawCrate(int x,int y,CDC *pDC)
{

	CRect rect;
	GetClientRect(&rect);

	m_ImgCrate.Draw(*pDC,x,y,32,32);

}


void CPush_BoxDlg::DrawRedBox(int x,int y,CDC *pDC)
{

	CRect rect;
	GetClientRect(&rect);

	m_ImgRedBox.Draw(*pDC,x,y,32,32);

}

void CPush_BoxDlg::DrawMan(int x,int y,CDC *pDC)
{

	CRect rect;
	GetClientRect(&rect);

	m_ImgMan.Draw(*pDC,x,y,32,32);

}

void CPush_BoxDlg::DrawBallMan(int x,int y,CDC *pDC)
{

	CRect rect;
	GetClientRect(&rect);

	m_ImgBallMan.Draw(*pDC,x,y,32,32);

}
/*********************************************************
	函数名称：IsFinish
	功能描述：判定是否过关
	作者：	  沈钰博
	创建时间：2016-08-29
	参数说明：无
	返 回 值：真假
*********************************************************/
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
/*********************************************************
	函数名称：PreTranslateMessage
	功能描述：接受键盘消息并执行进入下一关的操作
	作者：	  微软
	创建时间：2016-08-29
	参数说明：消息指针
	返 回 值：真假
*********************************************************/
BOOL CPush_BoxDlg::PreTranslateMessage(MSG* pMsg)
{
	    if(pMsg->message == WM_KEYDOWN)
	{
		updateMap(pMsg->wParam);
		Invalidate(true);
		
			if(IsFinish())
		{
			AfxMessageBox(_T("Well Done！您将进入下一关"));
			if (m_score[m_level]==0)//计算积分
				{
				m_score[m_level]=1000+int(2000/ (m_step+m_time))*m_level;
                m_Score+=m_score[m_level];
			    }
			if (m_Score>m_record)            //若总分大于记录则将当前总分写入文件
			{
				freopen("res\\record.txt","w",stdout);
				printf("%d",m_Score);
				fclose(stdout);
			}
			m_level = m_level + 1;            //进入下一关
            loadMap(m_level);
			m_ptManPosition =getManPosition();
			OnRestart();
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);

}
/*********************************************************
	函数名称：getManPosition
	功能描述：获得人的位置
	作者：	  沈钰博
	创建时间：2016-08-28
	参数说明：无
	返 回 值：CPoint
*********************************************************/
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
/*********************************************************
	函数名称：updateMap
	功能描述：根据键盘消息更新地图
	作者：	  沈钰博
	创建时间：2016-08-28
	参数说明：无
	返 回 值：无
*********************************************************/
void CPush_BoxDlg::updateMap(UINT nChar)
{
	int x1,y1,x2,y2,x3,y3;
	
	//获得人的位置
	x1 = getManPosition().x;
	y1 = getManPosition().y;
	//根据键盘消息更新地图
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
/*********************************************************
	函数名称：ReDrawMap
	功能描述：碰撞检测算法(逐个检测人将要移动的位置，然后改变3种坐标的图片)
	作者：	  沈钰博
	创建时间：2016-08-28
	参数说明：分别为人现在，想要人移动到，想要物品移动到的坐标位置
	返 回 值：无
*********************************************************/
void CPush_BoxDlg::ReDrawMap(int x1, int y1, int x2, int y2, int x3, int y3)  
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
     else if (iValue1 == MAP_BALLMAN)   
	 m_cMap[x1][y1] = '3';
        m_ptManPosition.x = x2;
        m_ptManPosition.y = y2;
		m_step++;
        break;
    case MAP_DEST:            
           m_cMap[x2][y2] = '7';   
        if (iValue1 == MAP_MAN)
		m_cMap[x1][y1] = '2';
        else if (iValue1  == MAP_BALLMAN)
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
            else if (iValue1 == MAP_BALLMAN)
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
            else if (iValue1  == MAP_BALLMAN)
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
            else if (iValue1  == MAP_BALLMAN)
               m_cMap[x1][y1]='3';
           m_ptManPosition.x = x2;
           m_ptManPosition.y = y2;
			m_step++;
        }
        else if (iValue3 == MAP_ROAD)
        {
            m_cMap[x3][y3]='4';
            m_cMap[x2][y2] ='7';//
            if (iValue1 == MAP_MAN)
                 m_cMap[x1][y1]  ='2';
            else if (iValue1  == MAP_BALLMAN)
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
	SetTimer(1, 1000, NULL);

	m_step=0;
	m_vtime=m_time=0;
	loadMap(m_level);
	Invalidate();
}
/*********************************************************
	函数名称：OnTimer
	功能描述：实现定时控制
	作者：	  沈钰博
	创建时间：2016-08-29
	参数说明：计时器ID
	返 回 值：无
*********************************************************/
void CPush_BoxDlg::OnTimer(UINT_PTR nIDEvent)
{
	
	switch (nIDEvent) 
		{      
    case 1: 
		
		m_time++;
		m_vtime++;
		if(m_vtime==301)//若时间条结束则停止游戏
			{AfxMessageBox(_T("没时间啦，游戏结束"));
		exit(0);}
		
		Invalidate();
        break;      
 
    default:      
        break;      
    }   
	
	CDialogEx::OnTimer(nIDEvent);
}

//显示最高记录
void CPush_BoxDlg::OnRecord()
{
	CString str;
	str.Format(_T("%d"),m_record);
	AfxMessageBox(str);
}

//保存游戏
void CPush_BoxDlg::OnSave()
{
    freopen("res\\save.txt","w",stdout);
	for (int i = 0; i < 14; i++)
        for (int j = 0; j < 16; j++)
			printf("%c",m_cMap[i][j]);
	printf("\n");
	printf("%d\n%d\n%d\n%d\n%d",m_time,m_Score,m_step,m_level,m_vtime);

	fclose(stdout);
}

//读取游戏
void CPush_BoxDlg::OnLoad()
{
	 freopen("res\\save.txt","r",stdin);
		  for (int i = 0; i < 14; i++)
          for (int j = 0; j < 16; j++)
			scanf("%c",&m_cMap[i][j]); 
		  scanf("%d%d%d%d%d",&m_time,&m_Score,&m_step,&m_level,&m_vtime);
		  fclose(stdin);
         Invalidate();
}


//关闭时间条
void CPush_BoxDlg::OnVclose()
{
	m_vtime=302;
	Invalidate();
}
