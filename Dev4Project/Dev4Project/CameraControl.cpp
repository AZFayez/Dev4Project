#include "CameraControl.h"

CameraControl::CameraControl()
{
	displacement =XMVectorZero();
	translateX = 0;
	translateY = 4;
	translateZ = -10;
	View = XMMatrixTranslation(0, 4, -10);
}

CameraControl::~CameraControl()
{
}

XMFLOAT4X4 CameraControl::getView()
{
	XMFLOAT4X4 temp;
	XMStoreFloat4x4(&temp, XMMatrixInverse(nullptr, View));
	return temp;
}

void CameraControl::RotateY(float deg)
{
	XMVECTOR pos = View.r[3];
	View = View * XMMatrixRotationY(deg);
	View.r[3] = pos;
}

void CameraControl::RotateX(float deg)
{
	View = XMMatrixRotationX(deg)* View;
}

void CameraControl::TranslateUP(float x, float y, float z)
{
	View = XMMatrixTranslation(x, y, z) * View;
}

void CameraControl::TranslateSide(float x, float y, float z)
{
	View = XMMatrixTranslation(x, y, z) * View;
}

void CameraControl::Movement()
{
	if (GetAsyncKeyState(0x57) && 0x8000)
		TranslateSide(0, 0, 0.1f);
	if (GetAsyncKeyState(0x53) && 0x8000)
		TranslateSide(0, 0, -0.1f);
	if (GetAsyncKeyState(0x44) && 0x8000)
		TranslateSide(0.1f, 0, 0);
	if (GetAsyncKeyState(0x41) && 0x8000)
		TranslateSide(-0.1f, 0, 0);
	if (GetAsyncKeyState(VK_SPACE) && 0x8000)
		TranslateUP(0, 0.1f, 0);
	if (GetAsyncKeyState(VK_SHIFT) && 0x8000)
		TranslateUP(0, -0.1f, 0);
	if (GetAsyncKeyState(VK_UP) && 0x8000)
		RotateX(-0.01f);
	if (GetAsyncKeyState(VK_DOWN) && 0x8000)
		RotateX(0.01f);
	if (GetAsyncKeyState(VK_LEFT) && 0x8000)
		RotateY(-0.01f);
	if (GetAsyncKeyState(VK_RIGHT) && 0x8000)
		RotateY(0.01);
}