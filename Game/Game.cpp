#include "stdafx.h"
#include "Game.h"
#include "nature/SkyCube.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Item.h"
#include "GameClear.h"
#include "GameOver.h"
#include "Title.h"
#include "graphics/RenderingEngine.h"

Game::Game()
{
	InitSky();

	m_player = NewGO<Player>(0, "player");

	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	m_backGround = NewGO<BackGround>(0);

	Item* item1 = NewGO<Item>(0, "item");
	item1->m_position = { 0.0f,25.0f,1100.0f };
	item1->firstPosition = item1->m_position;

	Item* item2 = NewGO<Item>(0, "item");
	item2->m_position = { 0.0f,450.0f,2460.0f };
	item2->firstPosition = item2->m_position;

	Item* item3 = NewGO<Item>(0, "item");
	item3->m_position = { 0.0f,750.0f,3950.0f };
	item3->firstPosition = item3->m_position;

	Item* item4 = NewGO<Item>(0, "item");
	item4->m_position = { 0.0f,-900.0f,4100.0f };
	item4->firstPosition = item4->m_position;

	Item* item5 = NewGO<Item>(0, "item");
	item5->m_position = { 0.0f,-400.0f,6500.0f };
	item5->firstPosition = item5->m_position;

	
}

Game::~Game()
{
	DeleteGO(m_player);

	DeleteGO(m_gameCamera);

	DeleteGO(m_backGround);

	DeleteGO(m_skyCube);
}

void Game::InitSky()
{
	//現在の空の破棄
	DeleteGO(m_skyCube);
	m_skyCube = NewGO<SkyCube>(0, "skycube");

	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetType((EnSkyCubeType)m_skyCubeType);

	//環境光の計算のためのILBテクスチャをセットする。
	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 1.0f);
	//環境日光の影響が分かりやすいように、ディレクションライトはオフに。
	g_renderingEngine->SetDirectionLight(0, g_vec3Zero, g_vec3Zero);
}

void Game::Update()
{
	// g_renderingEngine->DisableRaytracing();
	//m_modelRender.Update();

	if (m_player->m_position.y <= -1000.0f)
	{
		NewGO<GameOver>(0, "gameover");
		DeleteGO(this);
	}
}

void Game::Render(RenderContext& rc)
{
	if (m_player->m_itemCount >= 5)
	{
		NewGO<GameClear>(0, "gameclear");
		DeleteGO(this);
	}

}



