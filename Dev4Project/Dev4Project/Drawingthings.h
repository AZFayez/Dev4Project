#include <d3d11.h>
#pragma comment( lib,"d3d11.lib")

class Drawingthings
{
public:
	Drawingthings();
	~Drawingthings();
	void Init(HWND &hwnd);
	void Render();

private:
	
	ID3D11Device				*myDevice = nullptr;
	IDXGISwapChain				*mySwapper = nullptr;
	ID3D11DeviceContext			*myContext = nullptr;
	ID3D11RenderTargetView		*myTargetv = nullptr;
	CD3D11_VIEWPORT				myPort;
	D3D_FEATURE_LEVEL			dx11;
	DXGI_SWAP_CHAIN_DESC		swap;

};