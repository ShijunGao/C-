#pragma once
#include "Tool.h"



enum GAME_STATE
{
	HALT,//��ͣ
	GO,  //����
	STOP //ֹͣ
};


class Game
{
private:
	int *BigNet;
	int *SmallNet;
	GAME_STATE state;

	Tool *tool;
	Tool *nextTool;

	// ��ľλ�ã���4x4��������ϽǶ���λ��
	int Loc_X;
	int Loc_Y;

public:
	static const int TIME_STEP = 500;
	static const int NET_WIDTH = 9;
	static const int NET_HEIGHT = 20;

private:
    void AddTool(int *net); // ��������ӵ�����
	void NextTool();// ������һ����ľ

	bool IsDead();

	bool CanMoveDown();
	bool CanMoveLeft();
	bool CanMoveRight();
	bool CanRoll();
	void Roll();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void RemoveLines();
	void RemoveLine(int index);
	bool CanRemoveLine(int index);

public:
	int  Height;
    int  Width; 

public:
	Game(int height,int width);
	~Game(void);

	int* GetBigNet(); 
	int* GetSmallNet() ;
    GAME_STATE GetState();

	void Start();    // ��ʼ
	bool Go();       // ����һ��,��Ϸ����ʱ����false
    void HaltOrContinue();  // ��ͣ�����
	void Input(UINT nChar);
};
