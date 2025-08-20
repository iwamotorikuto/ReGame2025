#pragma once

class Player;
class Item;
extern Item* item;
class Item:public IGameObject
{
public:
	Item();
	~Item();
	//XVˆ—
	void Update();
	//•`‰æˆ—
	void Render(RenderContext& rc);
	//ˆÚ“®ˆ—
	void Move();
	
	ModelRender m_modelRender;
	Vector3 m_position;
	Vector3 firstPosition;
	Quaternion rot;
	Player* player;

};

