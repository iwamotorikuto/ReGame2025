#include "stdafx.h"
#include "Item.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

//アイテム処理
Item::Item()
{
	m_modelRender.Init("Assets/modelData/Item/ItemWood.tkm");

	//プレイヤーのオブジェクトを探して持ってくる。
	player = FindGO<Player>("player");

	//効果音の読み込み
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/itemSE.wav");

}

Item::~Item() {

}

void Item::Update()
{
	//移動処理
	Move();
	//回転
	rot.AddRotationDegY(2.0f);
	//回転処理
	m_modelRender.SetRotation(rot);

	//プレイヤーからWoodに向かうベクトルを計算。
	Vector3 diff = player->m_position - m_position;
	//ベクトルの長さが100.0fより小さかったら。
	if (diff.Length() <= 90.0f)
	{
		//カウントを+1する
		player->m_itemCount += 1;

		//効果音の処理
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(1);
		se->SetVolume(3.5f);
		se->Play(false);

		//自身を削除する
		DeleteGO(this);
	}

	//絵描きさん更新処理。
	m_modelRender.Update();

}

void Item::Move()
{
	m_modelRender.SetPosition(m_position);
}

void Item::Render(RenderContext& rc)
{
	//Itemを描画する。
	m_modelRender.Draw(rc);
}