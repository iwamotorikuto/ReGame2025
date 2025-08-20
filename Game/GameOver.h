#pragma once

class GameOver;
class explain;
class GameOver:public IGameObject
{
public:
	GameOver();
	~GameOver();

	void Update();
	void Render(RenderContext& rc);

	SpriteRender spriteRender;

};

