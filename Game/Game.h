#pragma once

//#include "Level3DRender/LevelRender.h"

class Player;
class GameCamera;
class BackGround;
class Item;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	void InitSky();
	void Update();
	void Render(RenderContext& rc);
	

	Player* m_player;
	BackGround* m_backGround;
	ModelRender m_modelRender;
	GameCamera* m_gameCamera;
	Item* m_item;
	Vector3* m_position;
	SkyCube* m_skyCube;
	int m_skyCubeType = enSkyCubeType_Day;
};

