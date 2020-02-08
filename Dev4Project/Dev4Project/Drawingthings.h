#include <d3d11.h>
#pragma comment( lib,"d3d11.lib")

#include <DirectXMath.h>
#include "MyVertx.h"
#include "MypShader.h"
#include "MyVMeshShader.h"
#include "MyPMeshShader.h"
#include "Assets/StoneHenge.h"
#include "DDSTextureLoader.h"

using namespace DirectX;

class Drawingthings
{
public:
	Drawingthings();
	~Drawingthings();
	void Init(HWND &hwnd);
	void Render();
	float						rot = 0;

private:
	// Math
	unsigned int				numverts = 0;
	float						aspectRatio = 1;
	struct WVP
	{
		XMFLOAT4X4 wMatrix;
		XMFLOAT4X4 vMatrix;
		XMFLOAT4X4 pMatrix;
	}MyMatracies;
	
	ID3D11Device				*myDevice = nullptr;
	IDXGISwapChain				*mySwapper = nullptr;
	ID3D11DeviceContext			*myContext = nullptr;
	ID3D11RenderTargetView		*myTargetv = nullptr;
	ID3D11InputLayout			*myLayout = nullptr;
	ID3D11InputLayout			*myMeshLayout = nullptr;
	ID3D11Buffer				*vBuff = nullptr;
	ID3D11Buffer				*cBuff = nullptr;
	ID3D11Buffer				*vBuffMesh = nullptr;
	ID3D11Buffer				*iBuffMesh = nullptr;
	ID3D11VertexShader			*vShader = nullptr;
	ID3D11PixelShader			*pShader = nullptr;
	ID3D11VertexShader			*vMeshShader = nullptr;
	ID3D11PixelShader			*pMeshShader = nullptr;
	ID3D11Texture2D				*zBuffer = nullptr;
	ID3D11DepthStencilView		*zBufferView = nullptr;
	ID3D11ShaderResourceView	*meshTexture = nullptr;
	CD3D11_VIEWPORT				myPort;
	D3D_FEATURE_LEVEL			dx11;
	DXGI_SWAP_CHAIN_DESC		swap;

};

struct MyVertex
{
	float pos[4];
	float clr[4];
};