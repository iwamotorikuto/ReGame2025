#include "stdafx.h"
#include "Item.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

//�A�C�e������
Item::Item()
{
	m_modelRender.Init("Assets/modelData/Item/ItemWood.tkm");

	//�v���C���[�̃I�u�W�F�N�g��T���Ď����Ă���B
	player = FindGO<Player>("player");

	//���ʉ��̓ǂݍ���
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/itemSE.wav");

}

Item::~Item() {

}

void Item::Update()
{
	//�ړ�����
	Move();
	//��]
	rot.AddRotationDegY(2.0f);
	//��]����
	m_modelRender.SetRotation(rot);

	//�v���C���[����Wood�Ɍ������x�N�g�����v�Z�B
	Vector3 diff = player->m_position - m_position;
	//�x�N�g���̒�����100.0f��菬����������B
	if (diff.Length() <= 90.0f)
	{
		//�J�E���g��+1����
		player->m_itemCount += 1;

		//���ʉ��̏���
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(1);
		se->SetVolume(3.5f);
		se->Play(false);

		//���g���폜����
		DeleteGO(this);
	}

	//�G�`������X�V�����B
	m_modelRender.Update();

}

void Item::Move()
{
	m_modelRender.SetPosition(m_position);
}

void Item::Render(RenderContext& rc)
{
	//Item��`�悷��B
	m_modelRender.Draw(rc);
}