#include "CameraControl.h"

CameraControl::CameraControl()
{
	XMStoreFloat4x4(&View, XMMatrixIdentity());
}

CameraControl::~CameraControl()
{
}

XMFLOAT4X4 CameraControl::getView()
{
	XMMATRIX temp = XMMatrixTranslation(translateX, translateY, translateZ);
	temp = XMMatrixMultiply(temp, XMMatrixRotationX(rotX));
	temp = XMMatrixMultiply(temp, XMMatrixRotationY(rotY));
	temp = XMMatrixMultiply(temp, XMMatrixRotationZ(rotZ));
	temp = XMMatrixInverse(nullptr, temp);
	XMStoreFloat4x4(&View, temp);
	return View;
}

void CameraControl::Movement()
{
	if (GetAsyncKeyState(0x57))
		translateZ += 0.1;
	if (GetAsyncKeyState(0x53))
		translateZ -= 0.1;
	if (GetAsyncKeyState(0x44))
		translateX += 0.1;
	if (GetAsyncKeyState(0x41))
		translateX -= 0.1;
	if (GetAsyncKeyState(VK_SPACE))
		translateY += 0.1;
	if (GetAsyncKeyState(VK_SHIFT))
		translateY -= 0.1;
	if (GetAsyncKeyState(VK_UP))
		rotX -= 0.01;
	if (GetAsyncKeyState(VK_DOWN))
		rotX += 0.01;
	if (GetAsyncKeyState(VK_LEFT))
		rotY -= 0.01;
	if (GetAsyncKeyState(VK_RIGHT))
		rotY += 0.01;
	
}