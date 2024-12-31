#pragma once
#include "CBattleScene.h"

CBattleScene::CBattleScene()
{
}

CBattleScene::~CBattleScene()
{
}

void CBattleScene::Create()
{
}

void CBattleScene::Releace()
{
}

void CBattleScene::LoadData()
{
}

void CBattleScene::Initialize()
{
}

void CBattleScene::Update()
{
	//フェードイン処理
	if (!FadeIn()) { return; }
}

void CBattleScene::Draw()
{
}

void CBattleScene::Debug()
{
}
