#pragma once

class Title:public IGameObject
{
public:
	Title();
	~Title();
	//�X�V����
	void Update();
	//�`��֐�
	void Render(RenderContext& rc);
	//�X�v���C�g�����_�[
	SpriteRender m_spriteRender;
	
};

