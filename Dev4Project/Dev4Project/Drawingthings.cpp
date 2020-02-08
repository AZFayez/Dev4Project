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
	myLayout->Release();
	vBuff->Release();
	cBuff->Release();
	vShader->Release();
	pShader->Release();
	vBuffMesh->Release();
	iBuffMesh->Release();
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

	aspectRatio = swap.BufferDesc.Width / static_cast<float>(swap.BufferDesc.Height);

	HRESULT hr;

	// change d3d11 device debug to null on release
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG, &dx11,
									1, D3D11_SDK_VERSION, &swap, &mySwapper, &myDevice, 0, &myContext);
	
	ID3D11Resource* backbuffer = nullptr;
	hr = mySwapper->GetBuffer(0, __uuidof(backbuffer), (void**)&backbuffer);
	hr = myDevice->CreateRenderTargetView(backbuffer, NULL, &myTargetv);

	backbuffer->Release();

	myPort.Width = static_cast<float>(swap.BufferDesc.Width);
	myPort.Height = static_cast<float>(swap.BufferDesc.Height);
	myPort.TopLeftX = myPort.TopLeftY = 0;
	myPort.MinDepth = 0;
	myPort.MaxDepth = 1;

	MyVertex tri[] =
	{
		//front
		{ {0, 1, 0, 1}, {1, 1, 0, 1} },
		{ {0.25f, -0.25f, -0.25f, 1}, {1, 0, 1, 1} },
		{ {-0.25f, -0.25f, -0.25f, 1}, {0, 1, 1, 1} },
		//right
		{ {0, 1, 0, 1}, {1, 1, 0, 1} },
		{ {0.25f, -0.25f, 0.25f, 1}, {0, 1, 1, 1} },
		{ {0.25f, -0.25f, -0.25f, 1}, {1, 0, 1, 1} },
		//back
		{ {0, 1, 0, 1}, {1, 1, 0, 1} },
		{ {-0.25f, -0.25f, 0.25f, 1},{1, 0, 1, 1}  },
		{ {0.25f, -0.25f, 0.25f, 1},  {0, 1, 1, 1}},
		//left
		{ {0, 1, 0, 1}, {1, 1, 0, 1} },
		{ {-0.25f, -0.25f, -0.25f, 1}, {0, 1, 1, 1} },
		{ {-0.25f, -0.25f, 0.25f, 1}, {1, 0, 1, 1} },
	};

	numverts = ARRAYSIZE(tri);

	//load vertexes to card
	D3D11_BUFFER_DESC bDesc;
	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&bDesc, sizeof(bDesc));
	ZeroMemory(&subData, sizeof(subData));

	bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bDesc.ByteWidth = sizeof(MyVertex) * numverts;
	bDesc.CPUAccessFlags = 0;
	bDesc.MiscFlags = 0;
	bDesc.StructureByteStride = 0;
	bDesc.Usage = D3D11_USAGE_IMMUTABLE;

	subData.pSysMem = tri;

	hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuff);

	//write compile load shaders

	hr = myDevice->CreateVertexShader(MyVertx, sizeof(MyVertx), nullptr, &vShader);
	hr = myDevice->CreatePixelShader(MypShader, sizeof(MypShader), nullptr, &pShader);

	//describe vertex	to d3d11
	D3D11_INPUT_ELEMENT_DESC iDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	hr = myDevice->CreateInputLayout(iDesc, 2, MyVertx, sizeof(MyVertx), &myLayout);
	
	//create constant buffer
	ZeroMemory(&bDesc, sizeof(bDesc));
	ZeroMemory(&subData, sizeof(subData));

	bDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bDesc.ByteWidth = sizeof(WVP);
	bDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bDesc.MiscFlags = 0;
	bDesc.StructureByteStride = 0;
	bDesc.Usage = D3D11_USAGE_DYNAMIC;

	hr = myDevice->CreateBuffer(&bDesc, nullptr, &cBuff);

	ZeroMemory(&bDesc, sizeof(bDesc));
	ZeroMemory(&subData, sizeof(subData));

	bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bDesc.ByteWidth = sizeof(StoneHenge_data);
	bDesc.CPUAccessFlags = 0;
	bDesc.MiscFlags = 0;
	bDesc.StructureByteStride = 0;
	bDesc.Usage = D3D11_USAGE_IMMUTABLE;

	subData.pSysMem = StoneHenge_data;

	hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuffMesh); // vertex buffer

	//index buffer
	ZeroMemory(&subData, sizeof(subData));

	bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bDesc.ByteWidth = sizeof(StoneHenge_indicies);
	subData.pSysMem = StoneHenge_indicies;

	hr = myDevice->CreateBuffer(&bDesc, &subData, &iBuffMesh);

	//load new mesh shader
	
	//hr = myDevice->CreateVertexShader(MyVMeshShader, sizeof(MyVMeshShader), nullptr, &vShader);

}

void Drawingthings::Render()
{
	float color[] = { 0, 0 , 0, 1 };
	myContext->ClearRenderTargetView(myTargetv, color);

	// setup the pipeline

	// output merger
	ID3D11RenderTargetView* tempRTv[] = { myTargetv };
	myContext->OMSetRenderTargets(1, tempRTv, nullptr);

	// rasterizer
	myContext->RSSetViewports(1, &myPort);

	// Input Assembler
	myContext->IASetInputLayout(myLayout);
	UINT strides[] = { sizeof(MyVertex) };
	UINT offsets[] = { 0 };
	ID3D11Buffer* tempVB[] = { vBuff };
	myContext->IASetVertexBuffers(0, 1, tempVB, strides, offsets);
	myContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// vertex shader
	myContext->VSSetShader(vShader, 0, 0);
	// pixel shader
	myContext->PSSetShader(pShader, 0, 0);

	//world m
	XMMATRIX temp = XMMatrixTranslation(0, 0, 2);
	XMStoreFloat4x4(&MyMatracies.wMatrix, XMMatrixMultiply(XMMatrixRotationY(rot), temp));
	//view m
	XMStoreFloat4x4(&MyMatracies.vMatrix, XMMatrixLookAtLH({ 2,2,-3 }, { 0,0,1 }, { 0,1,0 }));
	//projection m
	XMStoreFloat4x4(&MyMatracies.pMatrix, XMMatrixPerspectiveFovLH(3.14f / 2.0f, aspectRatio, 0.1f, 1000));

	//upload matracies to video card
	D3D11_MAPPED_SUBRESOURCE gpuBuff;
	HRESULT hr =  myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuff);
	memcpy(gpuBuff.pData, &MyMatracies, sizeof(WVP));
	myContext->Unmap(cBuff, 0);

	//connect constant buff to pipeline
	ID3D11Buffer* constants[] = { cBuff };
	myContext->VSSetConstantBuffers(0, 1, constants);

	// draw
	myContext->Draw(numverts, 0);

	mySwapper->Present(1, 0);
}