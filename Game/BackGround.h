#pragma once

class BackGround:public IGameObject
{
public:
	BackGround();
	~BackGround();

	//�`��֐�
	void Render(RenderContext& rc);

	//���f�������_�[�B
	ModelRender m_modelRender;

	PhysicsStaticObject physicsStaticObject;
};

