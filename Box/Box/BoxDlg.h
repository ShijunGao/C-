
// BoxDlg.h : ͷ�ļ�
//

#pragma once

#include "Game.h"


// CBoxDlg �Ի���
class CBoxDlg : public CDialogEx
{
private:
	// ��Ϸ����̨����
	Game *game;

// ����
public:
	CBoxDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BOX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

//--------------�¼� -------------------------
public:
	afx_msg void OnBnClickedButtonHalt();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);// ���� ���෽��
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
//----------���ܺ�����------------------------
private:
	void DrawNet();
	void DrawBigNet();
	void DrawSmallNet();
	void OnKeyDown(UINT nChar);
};
