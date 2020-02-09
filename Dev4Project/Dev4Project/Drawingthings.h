#include <d3d11.h>
#pragma comment( lib,"d3d11.lib")

//#include <DirectXMath.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "MyVertx.h"
#include "MypShader.h"
#include "MyVMeshShader.h"
#include "MyPMeshShader.h"
#include "ComplexVertexShader.h"
#include "ComplexPShader.h"
#include "Assets/StoneHenge.h"
#include "DDSTextureLoader.h"
#include "CameraControl.h"

using namespace DirectX;
using namespace std;

class Drawingthings
{
public:
	Drawingthings();
	~Drawingthings();
	void Init(HWND &hwnd);
	void Render();
	void CameraMove();
	float						rot = 0;

private:
	struct WVP
	{
		XMFLOAT4X4 wMatrix;
		XMFLOAT4X4 vMatrix;
		XMFLOAT4X4 pMatrix;
	}MyMatracies;
	struct SimpleVertex
	{
		XMFLOAT3 Pos;
		XMFLOAT3 Normal;
		XMFLOAT2 Tex;
	};

	struct SimpleMesh
	{
		vector<SimpleVertex> vertexList;
		vector<int> indicesList;
	}simpleMesh;

	void LoadMesh(const char* meshFileName, SimpleMesh& mesh);
	// Math
	unsigned int				numverts = 0;
	float						aspectRatio = 1;
	CameraControl				camera;
	
	ID3D11Device				*myDevice = nullptr;
	IDXGISwapChain				*mySwapper = nullptr;
	ID3D11DeviceContext			*myContext = nullptr;
	ID3D11RenderTargetView		*myTargetv = nullptr;
	ID3D11InputLayout			*myLayout = nullptr;
	ID3D11InputLayout			*myMeshLayout = nullptr;
	ID3D11InputLayout			*myComplexMeshLayout = nullptr;
	ID3D11Buffer				*vBuff = nullptr;
	ID3D11Buffer				*cBuff = nullptr;
	ID3D11Buffer				*vBuffMesh = nullptr;
	ID3D11Buffer				*iBuffMesh = nullptr;
	ID3D11Buffer				*vBuffCMesh = nullptr;
	ID3D11Buffer				*iBuffCMesh = nullptr;
	ID3D11VertexShader			*vShader = nullptr;
	ID3D11PixelShader			*pShader = nullptr;
	ID3D11VertexShader			*vMeshShader = nullptr;
	ID3D11PixelShader			*pMeshShader = nullptr;
	ID3D11VertexShader			*ComplexvMeshShader = nullptr;
	ID3D11PixelShader			*ComplexpMeshShader = nullptr;
	ID3D11Texture2D				*zBuffer = nullptr;
	ID3D11DepthStencilView		*zBufferView = nullptr;
	ID3D11ShaderResourceView	*meshTexture = nullptr;
	ID3D11ShaderResourceView	*CmeshTexture = nullptr;
	CD3D11_VIEWPORT				myPort;
	D3D_FEATURE_LEVEL			dx11;
	DXGI_SWAP_CHAIN_DESC		swap;

};

struct MyVertex
{
	float pos[4];
	float clr[4];
};