#include "GameDebugDraw.h"

GameDebugDraw::GameDebugDraw()
{
	mSpriteHandler = Game::GetInstance()->GetSpriteHandler();
	//mddv = Game::GetInstance()->GetDirect3DDevice();
	//mSpriteHandler->GetDevice(&mddv);
	D3DXCreateLine(Game::GetInstance()->GetDirect3DDevice(), &LineDraw);

	//set size cho line
	LineDraw->SetWidth(1);

	//set mau cho line
	mColor = D3DCOLOR_XRGB(255, 0, 0);

}

GameDebugDraw::~GameDebugDraw()
{

}

void GameDebugDraw::Draw()
{

}

void GameDebugDraw::setLineSize(float width)
{
	LineDraw->SetWidth(width);
}

void GameDebugDraw::DrawLine(D3DXVECTOR2 lines[], int count)
{
	LineDraw->Draw(lines, count, mColor);
}

void GameDebugDraw::DrawRect(RECT rect, Camera *camera)
{

	D3DXVECTOR3 trans = D3DXVECTOR3(0, 0, 0);
	if (camera)
	{
		trans = - D3DXVECTOR3(camera->getPosition().x, camera->getPosition().y,0.0f);
	}
	D3DXVECTOR2 lines[] = { D3DXVECTOR2(rect.left + trans.x, rect.top + trans.y),
							D3DXVECTOR2(rect.right + trans.x, rect.top + trans.y),
							D3DXVECTOR2(rect.right + trans.x, rect.bottom + trans.y),
							D3DXVECTOR2(rect.left + trans.x, rect.bottom + trans.y),
							D3DXVECTOR2(rect.left + trans.x, rect.top + trans.y) };

	DrawLine(lines, 5);
}

void GameDebugDraw::setColor(D3DCOLOR color)
{
	mColor = color;
}