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
	XMFLOAT4X4 getPosition();
	void RotateY(float deg);
	void RotateX(float deg);
	void TranslateUP(float x, float y, float z);
	void TranslateSide(float x, float y, float z);
	void Movement();
	float translateX;
	float translateY;
	float translateZ;
	float rotX = 0;
	float rotY = 0;
	float rotZ = 0;
	
private:
	XMMATRIX View;

};

