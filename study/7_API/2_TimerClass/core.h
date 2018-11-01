#pragma once
#include "winClass.h"
#include "timerClass.h"

class core :
	public winClass
{
	timerClass m_Timer;

public:
	bool    GameInit()    override;  // ���� �ʱ�ȭ
	bool    GameRun()     override;  // ���� ����
	bool    GameRelease() override;  // ���� ����
public:
	core();
	virtual ~core();
};

