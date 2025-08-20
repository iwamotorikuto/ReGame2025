#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "sound/SoundSource.h"
#include "sound/SoundEngine.h"



Player::Player()
{
	//�A�j���[�V�����N���b�v�����[�h����B
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	
	//���f��������������
	m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num,enModelUpAxisY);

	//�L�����R��������������B
	m_characterController.Init(25.0f, 75.0f, m_position);

	g_soundEngine->ResistWaveFileBank(2, "Assets/Sound/Jamp.wav");
}

Player::~Player()
{

}

void Player::Update()
{
	//�ړ�����
	Move();

	//��]����
	Rotation();

	//�X�e�[�g�Ǘ�
	ManageState();

	//�A�j���[�V�����̍Đ�
	PlayAnimation();

	//���f�����X�V����B
	m_modelRender.Update();
}

void Player::Move()
{
	//xz�̈ړ����x��0.0f�ɂ���B
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	

	//���X�e�B�b�N�̓��͗ʂ��擾�B
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	if (g_pad[0]->IsPress(enButtonB))
	{
		m_moveSpeed.z += 200.0f;
	}

	//�J�����̑O�����ƉE�����̃x�N�g���������Ă���B
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y�����ɂ͈ړ������Ȃ��B
	forward. y = 0.0f;
	right.y = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ�200.0f����Z�B
	right *= stickL.x * 200.0f;
	forward *= stickL.y * 200.0f;

	//�ړ����x�ɃX�e�B�b�N�̓��͗ʂ����Z����B
	m_moveSpeed += right + forward;

	//�n�ʂɕt���Ă�����B
	if (m_characterController.IsOnGround())
	{
		JumpCount = 0;

		//A�{�^���������ꂽ��B
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			m_moveSpeed.y = 620.0f;
			JumpCount++;

			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(2);
			se->SetVolume(2.0f);
			se->Play(false);
		}
	}
	//�n�ʂɕt���Ă��Ȃ�������B
	else
	{
		if (g_pad[0]->IsTrigger(enButtonA) && JumpCount < 2)
		{
			m_moveSpeed.y = 800.0f;
			JumpCount++;

			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(2);
			se->SetVolume(2.0f);
			se->Play(false);
		}
		
	}

	if (m_characterController.IsOnGround());
	{
		//�d�͂𔭐�������B
		m_moveSpeed.y -= 20.0f;
	}

	//�L�����N�^�[�R���g���[���[���g���č��W���ړ�������B
	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

	//�G�`������ɍ��W��������B
	m_modelRender.SetPosition(m_position);
}

void Player::Rotation()
{
	//x��z�̈ړ����x����������i�X�e�B�b�N�̓��͂���������).
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f);
	{
		//�L�����N�^�[�̕�����ς���B
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
        //�G�`������ɉ�]��������B
		m_modelRender.SetRotation(m_rotation);
	}
}

//�X�e�[�g�Ǘ�
void Player::ManageState()
{
	//�n�ʂɕt���Ă��Ȃ�������B

	if (m_characterController.IsOnGround() == false)
	{
		//�X�e�[�g��1(�W�����v��)�ɂ���B
		m_playerState = 1;
		//������ManageState�̏������I��点��B
		return;

	}

	//�n�ʂɕt���Ă�����B
	//x��z�̈ړ����x����������i�X�e�B�b�N�̓��͂���������)�B
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//�X�e�[�g��2(����)�ɂ���B
		m_playerState = 2;

	}
	//x��z�̈ړ����x������������i�X�e�B�b�N�̓��͂�����������)�B
	else
	{
		//�X�e�[�g��0(�ҋ@)�ɂ���
		m_playerState = 0;
	}

	if (g_pad[0]->IsPress(enButtonB))
	{
		//�X�e�[�g��3(�_�b�V��)�ɂ���
		m_playerState = 3;
	}

}

//�A�j���[�V�����̍Đ��B
void Player::PlayAnimation()
{
	//switch���B
	switch (m_playerState) {
		//�v���C���[�X�e�[�g��0(�ҋ@)��������B
	case 0:
		//�ҋ@�A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
		//�v���C���[�X�e�[�g��1(�W�����v��)��������B
	case 1:
		//�W�����v�A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
		//�v���C���[�X�e�[�g��2(����)��������B
	case 2:
		//�����A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
		//�v���C���[�X�e�[�g��3(����)��������B
	case 3:
		//�_�b�V���A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;
	}

}

void Player::Render(RenderContext& rc)
{
	//���f����\������B
	m_modelRender.Draw(rc);
}