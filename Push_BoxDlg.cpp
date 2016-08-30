
// Push_BoxDlg.cpp : ʵ���ļ�
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


// CPush_BoxDlg ��Ϣ�������
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	CTwoDlg m_DlgTwo;
	m_DlgTwo.DoModal();  //����������ǰ���ӽ���

	m_ImgBack.Load(L"res\\0.png");//���ر���ͼƬ
	m_ImgWall.Load(L"res\\1.png");//����ǽͼƬ
	m_ImgRoad.Load(L"res\\2.png");//����ͨ��ͼƬ
	m_ImgDest.Load(L"res\\3.png");//����Ŀ�ĵ�ͼƬ
	m_ImgCrate.Load(L"res\\4.png");//��������ͼƬ
	m_ImgRedBox.Load(L"res\\5.png");//��������ͼƬ
	m_ImgMan.Load(L"res\\6.png");//������ͼƬ
	m_ImgBallMan.Load(L"res\\7.png");//����ǽͼƬ

	loadMap(m_level);//���عؿ����ݵ�������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�



void CPush_BoxDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		drawMap(&dc);
		CFont font;                                       //����һ���������
		CFont* OldFont =NULL;                  //����ϵͳԭ������

		font.CreatePointFont(150,TEXT("΢���ź�"));//��������
		OldFont=dc.SelectObject(&font);  //�滻ϵͳԭ������
dc.SetBkMode(TRANSPARENT);   //�����ı������ģʽΪ͸��
		CString DrawString;
	
			DrawString.Format(TEXT("��%01d�� "),m_level);
		dc.TextOutW(410,20,DrawString);//��������λ��
		DrawString.Format(TEXT("���߲���:%01d "),m_step);
		dc.TextOutW(410,60,DrawString);//��������λ��
		dc.SelectObject(OldFont);            //�ָ�ϵͳԭ������

		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	// ��ѡ��ؿ�����
   CChoose m_choose;
   m_choose.DoModal(); 
  
   if(m_choose.m_StageNum>42||m_choose.m_StageNum<1)
	   AfxMessageBox(_T("������42���ڵ�����"));
   else
   {  m_level=m_choose.m_StageNum;
   OnRestart();}
}

void CPush_BoxDlg::drawMap(CDC *pDC)           //����ͼ
{
	int i, j, x, y;
	for (i = 0; i < 14; i++)//������
	{
		for (j = 0; j < 16; j++)//�������
		{
			x = j * 25;//35 ��ʾÿ��СͼƬ�Ĵ�С
			y = i * 25;

		int iValue = m_cMap[i][j] - 48;//���ַ�ת��Ϊint
			switch (iValue)
			{
			case MAP_BACK://0    ����	
				DrawBack(x, y, pDC);
				break;
			case MAP_WALL://1   ǽ
				DrawWall(x, y, pDC);
				break;
			case MAP_ROAD://2   ·	
				DrawRoad(x, y, pDC);
				break;
			case MAP_DEST://3  �ص�
				DrawDest(x, y, pDC);
				break;
			case MAP_CRATE://4    ����
				DrawCrate(x, y, pDC);
				break;
			case MAP_REDBOX://5   Ŀ�ĵص�����
				DrawRedBox(x, y, pDC);
				break;
			case MAP_MAN://6    ����
				DrawMan(x, y, pDC);
				break;
			case MAP_BALLMAN://7   Ŀ�ĵص� ����
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
			AfxMessageBox(_T("Well Done������������һ��!"));
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
            if (int (m_cMap[i][j]-48) == MAP_MAN  ||int(m_cMap[i][j]-48) == MAP_BALLMAN)//����ж��ǲ�����
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
	
	//����˵�λ��
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

void CPush_BoxDlg::ReDrawMap(int x1, int y1, int x2, int y2, int x3, int y3)  //������䣬���ݼ��̰������µ�ͼ
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

        case MAP_MAN:            //��ͼ������
        AfxMessageBox(_T("��ͼ������"));
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
	// ��������
}


void CPush_BoxDlg::OnToff()
{
	// �ر�����
	PlaySound(NULL,NULL,SND_PURGE);
}


void CPush_BoxDlg::OnRestart()//������Ϸ
{
	m_step=0;
	loadMap(m_level);
	Invalidate();
}