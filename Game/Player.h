#pragma once

class Player:public IGameObject
{
public:
	Player();
	~Player();
	//�X�V����
	void Update();
	//�`�揈��
	void Render(RenderContext& rc);
	//�ړ�����
	void Move();
	//��]����
	void Rotation();
	//�X�e�[�g�Ǘ�
	void ManageState();
	// �A�j���[�V�����̍Đ�
	void PlayAnimation();

	//�������烁���o�ϐ��B
	ModelRender m_modelRender; //���f�������_�[
	Vector3 m_position;        //���W�B
	enum EnAnimationClip {//�A�j���[�V����
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Run,
		enAnimationClip_Num,
	};
	AnimationClip m_animationClips[enAnimationClip_Num]; //�A�j���[�V�����N���b�v�B
	CharacterController m_characterController;           //�L�����N�^�[�R���g���[���[�B
	Vector3 m_moveSpeed;  //�ړ����x
	Quaternion m_rotation; //�N�H�[�^�j�I��
	int m_playerState = 0; //�v���C���[�X�e�[�g
	int playerState = 0;
	int m_itemCount = 0;//�W�߂��X�C�J�̐����J�E���g����B
	int JumpCount = 0;
};

