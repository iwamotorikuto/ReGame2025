#include "stdafx.h"
#include "GameClear.h"
#include "Player.h"
#include "Game.h"
#include "Item.h"



GameClear::GameClear()
{
	spriteRender.Init("Assets/GameClear/GameClear.DDS",1920.0f,1080.0f);

}

GameClear::~GameClear()
{

}

void GameClear::Update()
{
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		NewGO<Game>(0);
		DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}
