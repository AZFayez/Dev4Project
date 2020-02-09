#pragma once
#include <DirectXMath.h>
#include <Windows.h>

using namespace DirectX;

class CameraControl
{
public:
	CameraControl();
	~CameraControl();
	XMFLOAT4X4 getView();
	void Movement();
	float translateX = 0;
	float translateY = 0;
	float translateZ = 0;
	float rotX = 0;
	float rotY = 0;
	float rotZ = 0;
	
private:
	XMFLOAT4X4 View;

};

