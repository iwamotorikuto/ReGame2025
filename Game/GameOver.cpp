#include "stdafx.h"
#include "GameOver.h"
#include "Game.h"
#include "Title.h"


GameOver::GameOver()
{
	//‰æ‘œˆ—
	spriteRender.Init("Assets/GameOver/GameOver.DDS",1920.0f,1080.0f);

}

GameOver::~GameOver()
{

}

void GameOver::Update()
{
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		NewGO<Title>(0);
		DeleteGO(this);
	}

	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0);
		DeleteGO(this);
	}
}

void GameOver::Render(RenderContext& rc)
{
	//•`‰æˆ—
	spriteRender.Draw(rc);
}