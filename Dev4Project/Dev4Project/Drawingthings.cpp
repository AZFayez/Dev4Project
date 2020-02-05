#include "Drawingthings.h"

Drawingthings::Drawingthings()
{
}

Drawingthings::~Drawingthings()
{
	myDevice->Release();
	mySwapper->Release();
	myContext->Release();
	myTargetv->Release();
}

void Drawingthings::Init(HWND &hwnd)
{
	RECT myWinR;
	GetClientRect(hwnd, &myWinR);

	dx11 = D3D_FEATURE_LEVEL_11_0;
	ZeroMemory(&swap, sizeof(DXGI_SWAP_CHAIN_DESC));
	swap.BufferCount = 1;
	swap.OutputWindow = hwnd;
	swap.Windowed = true;
	swap.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swap.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap.BufferDesc.Width = myWinR.right - myWinR.left;
	swap.BufferDesc.Height = myWinR.bottom - myWinR.top;
	swap.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap.SampleDesc.Count = 1;

	HRESULT hr;

	// change d3d11 device debug to null on release
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG, &dx11,
									1, D3D11_SDK_VERSION, &swap, &mySwapper, &myDevice, 0, &myContext);
	
	ID3D11Resource* backbuffer = nullptr;
	hr = mySwapper->GetBuffer(0, __uuidof(backbuffer), (void**)&backbuffer);
	hr = myDevice->CreateRenderTargetView(backbuffer, NULL, &myTargetv);

	backbuffer->Release();

	myPort.Width = swap.BufferDesc.Width;
	myPort.Height = swap.BufferDesc.Height;
	myPort.TopLeftX = myPort.TopLeftY = 0;
	myPort.MinDepth = 0;
	myPort.MaxDepth = 1;
}

void Drawingthings::Render()
{
	ID3D11RenderTargetView* tempRTv[] = {myTargetv};
	myContext->OMSetRenderTargets(1, tempRTv, nullptr);

	float color[] = { 0, 1, 1, 1 };
	myContext->ClearRenderTargetView(myTargetv, color);

	mySwapper->Present(1, 0);
}