#pragma once
#include "winClass.h"
#include "timerClass.h"

class core :
	public winClass
{
	timerClass m_Timer;

public:
	bool    GameInit()    override;  // 게임 초기화
	bool    GameRun()     override;  // 게임 실행
	bool    GameRelease() override;  // 게임 종료
public:
	core();
	virtual ~core();
};

