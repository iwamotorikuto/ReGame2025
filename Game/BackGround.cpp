#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	m_modelRender.Init("Assets/modelData/stage/stage.tkm");
	//m_modelRender.Update();
	physicsStaticObject.CreateFromModel(m_modelRender.GetModel(),
	m_modelRender.GetModel().GetWorldMatrix());

}

BackGround::~BackGround()
{

}

void BackGround::Render(RenderContext& rc)
{
	//���f����`�悷��B
	m_modelRender.Draw(rc);
}