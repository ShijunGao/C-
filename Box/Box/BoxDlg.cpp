
// BoxDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Box.h"
#include "BoxDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBoxDlg �Ի���


CBoxDlg::CBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBoxDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBoxDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_HALT, &CBoxDlg::OnBnClickedButtonHalt)
	ON_BN_CLICKED(IDC_BUTTON_START, &CBoxDlg::OnBnClickedButtonStart)
	ON_WM_TIMER() // ӳ�������Ϣ
END_MESSAGE_MAP()


// CBoxDlg ��Ϣ�������

BOOL CBoxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	game = new Game(game->NET_HEIGHT,game->NET_WIDTH);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CBoxDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBoxDlg::OnPaint()
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
		CDialogEx::OnPaint();
		DrawNet();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBoxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//-----------------�Զ����¼�-----------------------


// ��������ͣ��ť���
void CBoxDlg::OnBnClickedButtonHalt()
{
	game->HaltOrContinue();

	if(game->GetState()==HALT)
		KillTimer(1);

	if(game->GetState()==GO)
		SetTimer(1,game->TIME_STEP,NULL);
}

// ��������ͣ��ť���
void CBoxDlg::OnBnClickedButtonStart()
{
	game->Start();
	SetTimer(1,game->TIME_STEP,NULL);
}

BOOL CBoxDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message==WM_KEYDOWN)
		OnKeyDown((UINT)pMsg->wParam);
	return false;
}


// ʵ���������  ��ʱ��
void CBoxDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(!game->Go())
	{
		KillTimer(1);
		TCHAR *msg = _T("Game Over!");
		MessageBox(msg);
	}
	Invalidate(true);// �ػ滭��
}


void CBoxDlg::DrawNet()
{
	DrawSmallNet();
	DrawBigNet();
}

void CBoxDlg::DrawBigNet()
{
	CRect rect;
	CWnd *wnd = GetDlgItem(IDC_PIC_MAIN);
	CPaintDC dc(wnd);

	wnd->GetClientRect(&rect);

	if(game->GetBigNet())
	{
		for(int i=0;i<game->NET_HEIGHT;i++)
			for(int j=0;j<game->NET_WIDTH;j++)
				if(game->GetBigNet()[i*(game->NET_WIDTH)+j]==1)
				{
					dc.Rectangle(
						j*rect.Width()/game->NET_WIDTH,
						i*rect.Height()/game->NET_HEIGHT,
						(j+1)*rect.Width()/game->NET_WIDTH,
						(i+1)*rect.Height()/game->NET_HEIGHT);
				}
	}

	wnd->RedrawWindow();
}

void CBoxDlg::DrawSmallNet()
{
	CRect rect;
	CWnd *wnd = GetDlgItem(IDC_PIC_SMALL);
	CPaintDC dc(wnd);

	wnd->GetClientRect(&rect);

	if(game->GetSmallNet())
	{
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				if(game->GetSmallNet()[i*4+j]==1)
				{
					dc.Rectangle(
						j*rect.Width()/4,
						i*rect.Height()/4,
						(j+1)*rect.Width()/4,
						(i+1)*rect.Height()/4);
				}
	}

	wnd->RedrawWindow();
}


void CBoxDlg::OnKeyDown(UINT nChar)
{
	game->Input(nChar);
	Invalidate(true);// �ػ滭��
}

