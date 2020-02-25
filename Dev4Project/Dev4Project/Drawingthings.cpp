#include "Drawingthings.h"

Drawingthings::Drawingthings()
{
	CurrScene = STUPID;
	//directional
	MyMatracies.lights[0].lightDirection = { 1, -1, 0, 0 };
	MyMatracies.lights[0].lightColor = { 0.5f, 0.5f, 0.5f, 1 };

	//Point
	MyMatracies.lights[1].position = { -10, 3, 0, 1 };
	MyMatracies.lights[1].lightColor = { 0, 0, 1, 1 };
	MyMatracies.lights[1].lightRadius = 20;

	//spot
	MyMatracies.lights[2].position = { 0, 5, 0, 1 };
	MyMatracies.lights[2].lightColor = { 1, 0, 0, 1 };
	MyMatracies.lights[2].lightDirection = { 0, -1, 0.5f, 0 };
	MyMatracies.lights[2].cosineInnerCone = .8f;
	MyMatracies.lights[2].cosineOuterCone = .4f;

	for (int i = 0; i < 10; i++)
	{
		XMStoreFloat4x4(&instancDate.position[i], XMMatrixMultiply(XMMatrixRotationZ(36 * (i + 1)), XMMatrixTranslation(i - 5, 5, 0)));
	}
}

MyVertex tri[] =
{
	//front
	{ {0, 1, 0, 1}, {1, 0, 0, 0.5f} },
	{ {0.25f, -0.25f, -0.25f, 1}, {1, 0, 0, 0.5f} },
	{ {-0.25f, -0.25f, -0.25f, 1}, {1, 0, 0, 0.5f} },
	//right
	{ {0, 1, 0, 1}, {1, 0, 0, 0.5f} },
	{ {0.25f, -0.25f, 0.25f, 1}, {1, 0, 0, 0.5f} },
	{ {0.25f, -0.25f, -0.25f, 1}, {1, 0, 0, 0.5f} },
	//back
	{ {0, 1, 0, 1}, {1, 0, 0, 0.5f} },
	{ {-0.25f, -0.25f, 0.25f, 1},{1, 0, 0, 0.5f}  },
	{ {0.25f, -0.25f, 0.25f, 1},  {1, 0, 0, 0.5f}},
	//left
	{ {0, 1, 0, 1}, {1, 0, 0, 0.5f} },
	{ {-0.25f, -0.25f, -0.25f, 1}, {1, 0, 0, 0.5f} },
	{ {-0.25f, -0.25f, 0.25f, 1}, {1, 0, 0, 0.5f} },
};
MyVertex tri2[] =
{
	//front
	{ {0, 1, 0, 1}, {0, 1, 0, 0.5f} },
	{ {0.25f, -0.25f, -0.25f, 1}, {0, 1, 0, 0.5f} },
	{ {-0.25f, -0.25f, -0.25f, 1}, {0, 1, 0, 0.5f} },
	//right
	{ {0, 1, 0, 1}, {0, 1, 0, 0.5f} },
	{ {0.25f, -0.25f, 0.25f, 1}, {0, 1, 0, 0.5f} },
	{ {0.25f, -0.25f, -0.25f, 1}, {0, 1, 0, 0.5f} },
	//back
	{ {0, 1, 0, 1}, {0, 1, 0, 0.5f} },
	{ {-0.25f, -0.25f, 0.25f, 1},{0, 1, 0, 0.5f}  },
	{ {0.25f, -0.25f, 0.25f, 1},  {0, 1, 0, 0.5f}},
	//left
	{ {0, 1, 0, 1}, {0, 1, 0, 0.5f} },
	{ {-0.25f, -0.25f, -0.25f, 1}, {0, 1, 0, 0.5f} },
	{ {-0.25f, -0.25f, 0.25f, 1}, {0, 1, 0, 0.5f} },
};
MyVertex tri3[] =
{
	//front
	{ {0, 1, 0, 1}, {0, 0, 1, 0.5f} },
	{ {0.25f, -0.25f, -0.25f, 1}, {0, 0, 1, 0.5f} },
	{ {-0.25f, -0.25f, -0.25f, 1}, {0, 0, 1, 0.5f} },
	//right
	{ {0, 1, 0, 1}, {0, 0, 1, 0.5f} },
	{ {0.25f, -0.25f, 0.25f, 1}, {0, 0, 1, 0.5f} },
	{ {0.25f, -0.25f, -0.25f, 1}, {0, 0, 1, 0.5f} },
	//back
	{ {0, 1, 0, 1}, {0, 0, 1, 0.5f} },
	{ {-0.25f, -0.25f, 0.25f, 1},{0, 0, 1, 0.5f}  },
	{ {0.25f, -0.25f, 0.25f, 1},  {0, 0, 1, 0.5f}},
	//left
	{ {0, 1, 0, 1}, {0, 0, 1, 0.5f} },
	{ {-0.25f, -0.25f, -0.25f, 1}, {0, 0, 1, 0.5f} },
	{ {-0.25f, -0.25f, 0.25f, 1}, {0, 0, 1, 0.5f} },
};

Drawingthings::~Drawingthings()
{
	if (myDevice) myDevice->Release();
	if (mySwapper) mySwapper->Release();
	if (myContext) myContext->Release();
	if (myTargetv) myTargetv->Release();
	if (myLayout) myLayout->Release();
	if (myMeshLayout) myMeshLayout->Release();
	if (vBuff) vBuff->Release();
	if (vBuff1) vBuff1->Release();
	if (vBuff2) vBuff2->Release();
	if (cBuff) cBuff->Release();
	if (vShader) vShader->Release();
	if (vMeshShader) vMeshShader->Release();
	if (pShader) pShader->Release();
	if (vBuffMesh) vBuffMesh->Release();
	if (iBuffMesh) iBuffMesh->Release();
	if (vBuffCMesh) vBuffCMesh->Release();
	if (iBuffCMesh) iBuffCMesh->Release();
	if (zBuffer) zBuffer->Release();
	if (zBufferView) zBufferView->Release();
	if (meshTexture) meshTexture->Release();
	if (pMeshShader) pMeshShader->Release();
	if (ComplexvMeshShader) ComplexvMeshShader->Release();
	if (ComplexpMeshShader) ComplexpMeshShader->Release();
	if (myComplexMeshLayout) myComplexMeshLayout->Release();
	if (CmeshTexture) CmeshTexture->Release();
	if (SkyboxTextureDefault) SkyboxTextureDefault->Release();
	if (Skybox) Skybox->Release();
	if (vBuffCube) vBuffCube->Release();
	if (iBuffCube) iBuffCube->Release();
	if (myRasterizer) myRasterizer->Release();
	if (SkyPShader) SkyPShader->Release();
	if (zBuffState) zBuffState->Release();
	if (cubeSamplerState) cubeSamplerState->Release();
	if (instanceBuff) instanceBuff->Release();
	if (SkyVShader) SkyVShader->Release();
	if (SkyLayout) SkyLayout->Release();
	if (mySampler) mySampler->Release();
	if (SkyboxTextureIsland) SkyboxTextureIsland->Release();
	if (SkyboxTextureSpace) SkyboxTextureSpace->Release();
	if (vPlanetMesh) vPlanetMesh->Release();
	if (iPlanetMesh) iPlanetMesh->Release();
	if (PlanetTexture) PlanetTexture->Release();
	if (PlanetHeight) PlanetHeight->Release();
	if (PlanetVShader) PlanetVShader->Release();
	if (PlanetPShader) PlanetPShader->Release();
	if (NoHeight) NoHeight->Release();
	if (MoonTexture) MoonTexture->Release();
	if (IcePlanet) IcePlanet->Release();
	if (LastPlanet) LastPlanet->Release();
	if (vShipMesh) vShipMesh->Release();
	if (iShipMesh) iShipMesh->Release();
	if (ShipTex) ShipTex->Release();
	if (ShipVShader) ShipVShader->Release();
	if (ShipPShader) ShipPShader->Release();
	if (vIslandMesh) vIslandMesh->Release();
	if (iIslandMesh) iIslandMesh->Release();
	if (SandTexture) SandTexture->Release();
	if (TreeTex) TreeTex->Release();
	if (vTreeMesh) vTreeMesh->Release();
	if (iTreeMesh) iTreeMesh->Release();
	if (vWaterPlane) vWaterPlane->Release();
	if (iWaterPlane) iWaterPlane->Release();
	if (WaterT) WaterT->Release();
	if (WaterVertex) WaterVertex->Release();
	if (WaterPixel) WaterPixel->Release();
	if (myBlend) myBlend->Release();
}

void Drawingthings::Init(HWND& hwnd)
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

	subData.pSysMem = tri2;

	hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuff1);

	subData.pSysMem = tri3;

	hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuff2);

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

	hr = myDevice->CreateVertexShader(MyVMeshShader, sizeof(MyVMeshShader), nullptr, &vMeshShader);
	myDevice->CreatePixelShader(MYPMeshShader, sizeof(MYPMeshShader), nullptr, &pMeshShader);

	// make new input layout for new shape because data format is different

	D3D11_INPUT_ELEMENT_DESC MeshiDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	hr = myDevice->CreateInputLayout(MeshiDesc, 3, MyVMeshShader, sizeof(MyVMeshShader), &myMeshLayout);

#pragma region z Buffer

	// making a z buffer
	D3D11_TEXTURE2D_DESC zDesc;
	ZeroMemory(&zDesc, sizeof(zDesc));

	zDesc.ArraySize = 1;
	zDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	zDesc.Width = swap.BufferDesc.Width;
	zDesc.Height = swap.BufferDesc.Height;
	zDesc.Usage = D3D11_USAGE_DEFAULT;
	zDesc.Format = DXGI_FORMAT_D32_FLOAT;
	zDesc.MipLevels = 1;
	zDesc.SampleDesc.Count = 1;

	hr = myDevice->CreateTexture2D(&zDesc, nullptr, &zBuffer);

	D3D11_DEPTH_STENCIL_DESC dDesc;
	ZeroMemory(&dDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	dDesc.DepthEnable = true;
	dDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
	dDesc.StencilEnable = false;
	dDesc.StencilReadMask = 0xFF;
	dDesc.StencilWriteMask = 0xFF;

	dDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	dDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	hr = myDevice->CreateDepthStencilState(&dDesc, &zBuffState);

	hr = myDevice->CreateDepthStencilView(zBuffer, nullptr, &zBufferView);

#pragma endregion

	hr = CreateDDSTextureFromFile(myDevice, L"./Assets/StoneHenge.dds", nullptr, &meshTexture);

	hr = myDevice->CreateVertexShader(ComplexVertexShader, sizeof(ComplexVertexShader), nullptr, &ComplexvMeshShader);
	myDevice->CreatePixelShader(ComplexPShader, sizeof(ComplexPShader), nullptr, &ComplexpMeshShader);

	D3D11_INPUT_ELEMENT_DESC ComplexMeshiDesc[] =
	{
		{ "POSITION"	, 0, DXGI_FORMAT_R32G32B32_FLOAT,	  0,  0, D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "NORMAL"		, 0, DXGI_FORMAT_R32G32B32_FLOAT,	  0, 12, D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "TEXCOORD"	, 0, DXGI_FORMAT_R32G32_FLOAT,		  0, 24, D3D11_INPUT_PER_VERTEX_DATA,	0 },
	};

	hr = myDevice->CreateInputLayout(ComplexMeshiDesc, 3, ComplexVertexShader, sizeof(ComplexVertexShader), &myComplexMeshLayout);

	CreateModel(simpleMesh, "./Assets/Axe.mesh", &vBuffCMesh, &iBuffCMesh);
	

	hr = CreateDDSTextureFromFile(myDevice, L"./Assets/axeTexture.dds", nullptr, &CmeshTexture);
	hr = CreateDDSTextureFromFile(myDevice, L"./Assets/SunsetSkybox.dds", (ID3D11Resource**)&Skybox, &SkyboxTextureDefault);
	hr = CreateDDSTextureFromFile(myDevice, L"./Assets/SkyboxOcean.dds", nullptr, &SkyboxTextureIsland);
	hr = CreateDDSTextureFromFile(myDevice, L"./Assets/Space.dds", nullptr, &SkyboxTextureSpace);
	
	CreateModel(simplecube, "./Assets/cube.mesh", &vBuffCube, &iBuffCube);

	// set raterizerstate
	D3D11_RASTERIZER_DESC rDesc;
	ZeroMemory(&rDesc, sizeof(D3D11_RASTERIZER_DESC));
	rDesc.AntialiasedLineEnable = true;
	rDesc.CullMode = D3D11_CULL_BACK;
	rDesc.DepthBias = 0;
	rDesc.DepthBiasClamp = 1;
	rDesc.DepthClipEnable = true;
	rDesc.FillMode = D3D11_FILL_SOLID;
	rDesc.FrontCounterClockwise = false;
	rDesc.MultisampleEnable = true;
	rDesc.SlopeScaledDepthBias = 0;

	hr = myDevice->CreateRasterizerState(&rDesc, &myRasterizer);

	hr = myDevice->CreateVertexShader(SkyboxVertex, sizeof(SkyboxVertex), nullptr, &SkyVShader);
	hr = myDevice->CreatePixelShader(SkyShader, sizeof(SkyShader), nullptr, &SkyPShader);

	D3D11_INPUT_ELEMENT_DESC SkyiDesc[] =
	{
		{ "POSITION"	, 0, DXGI_FORMAT_R32G32B32_FLOAT,	  0,  0, D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "NORMAL"		, 0, DXGI_FORMAT_R32G32B32_FLOAT,	  0, 12, D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "TEXCOORD"	, 0, DXGI_FORMAT_R32G32_FLOAT,		  0, 24, D3D11_INPUT_PER_VERTEX_DATA,	0 },
	};

	hr = myDevice->CreateInputLayout(SkyiDesc, 3, SkyboxVertex, sizeof(SkyboxVertex), &SkyLayout);

	//instancing
	vector<WVP> instanceMatracies;
	XMFLOAT4X4 temp;
	XMStoreFloat4x4(&temp, XMMatrixMultiply(XMMatrixRotationZ(180.0f), XMMatrixTranslation(1, 5, 0)));
	//instanceMatracies.vMatrix = camera.getView();

	ZeroMemory(&bDesc, sizeof(bDesc));
	ZeroMemory(&subData, sizeof(subData));

	bDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bDesc.ByteWidth = sizeof(instance);
	bDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bDesc.MiscFlags = 0;
	bDesc.StructureByteStride = 0;
	bDesc.Usage = D3D11_USAGE_DYNAMIC;

	subData.pSysMem = &instancDate;

	hr = myDevice->CreateBuffer(&bDesc, &subData, &instanceBuff);

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(D3D11_SAMPLER_DESC));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = myDevice->CreateSamplerState(&sampDesc, &mySampler);

	CreateModel(Planet, "./Assets/planet1.mesh", &vPlanetMesh, &iPlanetMesh);
	hr = CreateDDSTextureFromFile(myDevice, L"./Assets/planet1T.dds", nullptr, &PlanetTexture);
	hr = CreateDDSTextureFromFile(myDevice, L"./Assets/fireplanetbump.dds", nullptr, &PlanetHeight);
	hr = CreateDDSTextureFromFile(myDevice, L"./Assets/blank.dds", nullptr, &NoHeight);
	hr = CreateDDSTextureFromFile(myDevice, L"./Assets/moon.dds", nullptr, &MoonTexture);
	hr = CreateDDSTextureFromFile(myDevice, L"./Assets/iceplanet.dds", nullptr, &IcePlanet);
	hr = CreateDDSTextureFromFile(myDevice, L"./Assets/planet2.dds", nullptr, &LastPlanet);

	myDevice->CreateVertexShader(PlanetShader, sizeof(PlanetShader), nullptr, &PlanetVShader);
	myDevice->CreatePixelShader(PlanetPixelShader, sizeof(PlanetPixelShader), nullptr, &PlanetPShader);

	CreateModel(SpaceShip, "./Assets/spaceShip.mesh", &vShipMesh, &iShipMesh);
	hr = CreateDDSTextureFromFile(myDevice, L"./Assets/shipT.dds", nullptr, &ShipTex);

	myDevice->CreateVertexShader(ShipVertex, sizeof(ShipVertex), nullptr, &ShipVShader);
	myDevice->CreatePixelShader(ShipPixel, sizeof(ShipPixel), nullptr, &ShipPShader);
	
	CreateModel(Island, "./Assets/island.mesh", &vIslandMesh, &iIslandMesh);
	hr = CreateDDSTextureFromFile(myDevice, L"./Assets/sand.dds", nullptr, &SandTexture);
	hr = CreateDDSTextureFromFile(myDevice, L"./Assets/PalmT.dds", nullptr, &TreeTex);

	CreateModel(Tree, "./Assets/PTree.mesh", &vTreeMesh, &iTreeMesh);

	CreateModel(waterP, "./Assets/WaterP.mesh", &vWaterPlane, &iWaterPlane);
	hr = CreateDDSTextureFromFile(myDevice, L"./Assets/waterT.dds", nullptr, &WaterT);

	myDevice->CreateVertexShader(WaterShader, sizeof(WaterShader), nullptr, &WaterVertex);
	myDevice->CreatePixelShader(WaterPixelShader, sizeof(WaterPixelShader), nullptr, &WaterPixel);

	D3D11_BLEND_DESC blendDesc;

	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));

	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = myDevice->CreateBlendState( &blendDesc, &myBlend);
}

void Drawingthings::Render()
{

	MyMatracies.lights[1].position.z = 10 * (sinf(rot));

	XMVECTOR Spotlighttemp = XMLoadFloat4(&MyMatracies.lights[2].lightDirection);
	XMStoreFloat4(&MyMatracies.lights[2].lightDirection, XMVector4Transform(Spotlighttemp, XMMatrixRotationY(-0.01f)));
#pragma region controls

	if (GetAsyncKeyState(0x4A) && 0x8000)
	{
		zoom += 0.1f;
		if (zoom > 6.0f)
			zoom = 6.0f;
	}
	if (GetAsyncKeyState(0x4B) && 0x8000)
	{
		zoom -= 0.1f;
		if (zoom < 2.0f)
			zoom = 2.0f;
	}
	if (GetAsyncKeyState(0x4E) && 0x8000)
	{
		nearplane += 0.01f;
		if (nearplane > 3.0f)
			nearplane = 3.0f;
	}
	if (GetAsyncKeyState(0x4D) && 0x8000)
	{
		nearplane -= 0.01f;
		if (nearplane < 0.1f)
			nearplane = 0.1f;
	}
	if (GetAsyncKeyState(0x43) && 0x8000)
	{
		farplane += 5;
		if (nearplane > 1000)
			farplane = 1000;
	}
	if (GetAsyncKeyState(0x56) && 0x8000)
	{
		farplane -= 5;
		if (farplane <= (nearplane + 1))
			farplane = nearplane + 1;
	}
	if (GetAsyncKeyState(VK_LEFT) && 0x8000)
	{
		XMVECTOR lighttemp = XMLoadFloat4(&MyMatracies.lights[0].lightDirection);
		XMStoreFloat4(&MyMatracies.lights[0].lightDirection, XMVector4Transform(lighttemp, XMMatrixRotationY(-0.01f)));
		ShipZ += 0.01f;
		if (ShipZ >= (3.14f / 4))
			ShipZ = 3.14f / 4;
	}
	else if (GetAsyncKeyState(VK_RIGHT) && 0x8000)
	{
		XMVECTOR lighttemp = XMLoadFloat4(&MyMatracies.lights[0].lightDirection);
		XMStoreFloat4(&MyMatracies.lights[0].lightDirection, XMVector4Transform(lighttemp, XMMatrixRotationY(0.01f)));
		ShipZ -= 0.01f;
		if (ShipZ <= -(3.14f / 4))
			ShipZ = -(3.14f / 4);
	}
	else if (ShipZ < 0)
	{
		ShipZ += 0.01f;
	}
	else if (ShipZ > 0)
	{
		ShipZ -= 0.01f;
	}

	if (GetAsyncKeyState(VK_DOWN) && 0x8000)
	{
		ShipX += 0.01f;
		if (ShipX >= (3.14f / 8))
			ShipX = 3.14f / 8;
	}
	else if (GetAsyncKeyState(VK_UP) && 0x8000)
	{
		ShipX -= 0.01f;
		if (ShipX <= -(3.14f / 8))
			ShipX = -(3.14f / 8);
	}
	else if (ShipX < 0)
	{
		ShipX += 0.01f;
	}
	else if (ShipX > 0)
	{
		ShipX -= 0.01f;
	}

	if (GetAsyncKeyState(0x31) && 0x8000)
	{
		CurrScene = STUPID;
		camera.Reset();
	}
	if (GetAsyncKeyState(0x32) && 0x8000)
	{
		CurrScene = ISLAND;
		MyMatracies.lights[0]._constant = 0;
		camera.Reset();
	}
	if (GetAsyncKeyState(0x33) && 0x8000)
	{
		CurrScene = SPACE;
		camera.Reset();
		ShipX = 0;
		ShipZ = 0;
	}
#pragma endregion

#pragma region Initial setup

	float color[] = { 0, 1, 1, 1 };
	// output merger
	ID3D11RenderTargetView* tempRTv[] = { myTargetv };
	myContext->OMSetRenderTargets(1, tempRTv, zBufferView);

	float blendfactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	UINT mask = 0xffffffff;

	myContext->ClearRenderTargetView(myTargetv, color);
	//clear z buffer
	myContext->ClearDepthStencilView(zBufferView, D3D11_CLEAR_DEPTH, 1, 1);
	myContext->OMSetBlendState(myBlend, blendfactor, mask);
	// setup the pipeline)
	myContext->RSSetState(myRasterizer);
	// rasterizer
	myContext->RSSetViewports(1, &myPort);
	// sampler
	myContext->PSSetSamplers(0, 1, &mySampler);

	UINT mesh_strides[] = { sizeof(_OBJ_VERT_) };
	UINT mesh_offsets[] = { 0 };
	ID3D11Buffer* meshVB[] = { vBuffMesh };

	UINT Instance_strides[] = { sizeof(SimpleVertex), sizeof(instance) };
	UINT Instance_offsets[] = { 0 };
	ID3D11Buffer* CmeshVB[] = { vBuffCMesh };

	UINT strides[] = { sizeof(MyVertex) };
	UINT offset[] = {0};

	ID3D11Buffer* transperancy[] = { vBuff,vBuff1,vBuff2 };

	ID3D11ShaderResourceView* HeightMaps[] = { PlanetHeight, NoHeight };
	ID3D11ShaderResourceView* PlanetInstancingTextures[] = { PlanetTexture, MoonTexture, LastPlanet, IcePlanet };
	
	XMMATRIX triWorld[] =
	{
		XMMatrixMultiply(XMMatrixScaling(2, 2, 2), XMMatrixTranslation(0, 3, -5)),
		XMMatrixMultiply(XMMatrixScaling(2, 2, 2), XMMatrixTranslation(0, 3, -6)),
		XMMatrixMultiply(XMMatrixScaling(2, 2, 2), XMMatrixTranslation(0, 3, -7)),
	};

	XMVECTOR camdepth = camera.getPositionV();
	XMVECTOR tri1depth = XMVector4Transform({tri[0].pos[0] ,tri[0].pos[1] , tri[0].pos[2] , tri[0].pos[3] }, triWorld[0]);
	XMVECTOR tri2depth = XMVector4Transform({tri2[0].pos[0] ,tri2[0].pos[1] , tri2[0].pos[2] , tri2[0].pos[3] }, triWorld[1]);
	XMVECTOR tri3depth = XMVector4Transform({tri3[0].pos[0] ,tri3[0].pos[1] , tri3[0].pos[2] , tri3[0].pos[3] }, triWorld[2]);

	tri1depth = XMVectorSubtract(camdepth, tri1depth);
	tri2depth = XMVectorSubtract(camdepth, tri2depth);
	tri3depth = XMVectorSubtract(camdepth, tri3depth);

	tri1depth = XMVector4Dot(tri1depth, tri1depth);
	tri2depth = XMVector4Dot(tri2depth, tri2depth);
	tri3depth = XMVector4Dot(tri3depth, tri3depth);

	float mags[3] = { tri1depth.m128_f32[2], tri2depth.m128_f32[2], tri3depth.m128_f32[2] };
	depth[0] = 0;
	depth[1] = 1;
	depth[2] = 2;
	
	if (mags[1] > mags[0])
	{
		float tmpf = mags[0];
		mags[0] = mags[1];
		mags[1] = tmpf;

		int tempi = depth[0];
		depth[0] = depth[1];
		depth[1] = tempi;
	}
	if (mags[2] > mags[1])
	{
		float tmpf = mags[1];
		mags[1] = mags[2];
		mags[2] = tmpf;

		int tempi = depth[1];
		depth[1] = depth[2];
		depth[2] = tempi;
		if (mags[1] > mags[0])
		{
			float tmpf = mags[0];
			mags[0] = mags[1];
			mags[1] = tmpf;

			int tempi = depth[0];
			depth[0] = depth[1];
			depth[1] = tempi;
		}
	}

#pragma endregion

#pragma region InputAssembler

	// Input Assembler

	//world m
	XMMATRIX temp = XMMatrixTranslation(3, 2, -5);
	XMStoreFloat4x4(&MyMatracies.wMatrix, XMMatrixMultiply(XMMatrixRotationY(rot), temp));
	//view m
	MyMatracies.vMatrix = camera.getView();
	//projection m
	XMStoreFloat4x4(&MyMatracies.pMatrix, XMMatrixPerspectiveFovLH(3.14f / zoom, aspectRatio, nearplane, farplane));


	//upload matracies to video card
	D3D11_MAPPED_SUBRESOURCE gpuBuff;
	D3D11_MAPPED_SUBRESOURCE gpuInBuff;
	HRESULT hr =  myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuff);
	memcpy(gpuBuff.pData, &MyMatracies, sizeof(WVP));
	myContext->Unmap(cBuff, 0);

	//connect constant buff to pipeline
	ID3D11Buffer* constants[] = { cBuff, instanceBuff };
	myContext->VSSetConstantBuffers(0, 2, constants);
	myContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

#pragma endregion

#pragma region SkyBox

	UINT Cmesh_strides[] = { sizeof(SimpleVertex) };
	UINT Cmesh_offsets[] = { 0 };

	myContext->IASetInputLayout(SkyLayout);
	myContext->IASetVertexBuffers(0, 1, &vBuffCube, Cmesh_strides, Cmesh_offsets);
	myContext->IASetIndexBuffer(iBuffCube, DXGI_FORMAT_R32_UINT, 0);
	myContext->VSSetShader(SkyVShader, 0, 0);
	myContext->PSSetShader(SkyPShader, 0, 0);
	MyMatracies.wMatrix = camera.getPosition();
	hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuff);
	memcpy(gpuBuff.pData, &MyMatracies, sizeof(WVP));
	myContext->Unmap(cBuff, 0);


#pragma endregion

	switch (CurrScene)
	{
	case Drawingthings::STUPID:
		myContext->PSSetShaderResources(0, 1, &SkyboxTextureDefault);
		myContext->DrawIndexed(simplecube.indicesList.size(), 0, 0);
		myContext->ClearDepthStencilView(zBufferView, D3D11_CLEAR_DEPTH, 1, 1);
#pragma region StoneHenge

	//drawing second item
	myContext->IASetInputLayout(myMeshLayout);

	myContext->IASetVertexBuffers(0, 1, meshVB, mesh_strides, mesh_offsets);
	myContext->IASetIndexBuffer(iBuffMesh, DXGI_FORMAT_R32_UINT, 0);
	myContext->VSSetShader(vMeshShader, 0, 0);
	myContext->PSSetShader(pMeshShader, 0, 0);
	myContext->PSSetShaderResources(0, 1, &meshTexture);

	//change world matrix
	XMStoreFloat4x4(&MyMatracies.wMatrix, XMMatrixTranslation(0, 0, 0));
	//upload new matrix to video card
	hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuff);
	memcpy(gpuBuff.pData, &MyMatracies, sizeof(WVP));
	myContext->Unmap(cBuff, 0);
	myContext->PSSetConstantBuffers(0, 1, constants);

	myContext->DrawIndexed(2532, 0, 0);

#pragma endregion

#pragma region Instanced

	myContext->IASetInputLayout(myComplexMeshLayout);
	myContext->IASetVertexBuffers(0, 1, CmeshVB, Instance_strides, Instance_offsets);
	myContext->IASetIndexBuffer(iBuffCMesh, DXGI_FORMAT_R32_UINT, 0);
	myContext->VSSetShader(ComplexvMeshShader, 0, 0);
	myContext->PSSetShader(ComplexpMeshShader, 0, 0);
	myContext->PSSetShaderResources(0, 1, &CmeshTexture);

	XMStoreFloat4x4(&MyMatracies.wMatrix, XMMatrixTranslation(0, 5, 0));
	//upload new matrix to video card
	hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuff);
	memcpy(gpuBuff.pData, &MyMatracies, sizeof(WVP));
	myContext->Unmap(cBuff, 0);

	//instance data constant buffer
	hr = myContext->Map(instanceBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuInBuff);
	memcpy(gpuInBuff.pData, &instancDate, sizeof(instance));
	myContext->Unmap(instanceBuff, 0);

	myContext->DrawIndexedInstanced(simpleMesh.indicesList.size(), 10, 0, 0, 0);

#pragma endregion

#pragma region triangles

	for (int i = 0; i < 3; i++)
	{
		myContext->IASetInputLayout(myLayout);

		myContext->IASetVertexBuffers(0, 1, &transperancy[depth[i]], strides, offset);
		myContext->VSSetShader(vShader, 0, 0);
		myContext->PSSetShader(pShader, 0, 0);

		//change world matrix
		XMStoreFloat4x4(&MyMatracies.wMatrix, triWorld[depth[i]]);
		//upload new matrix to video card
		hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuff);
		memcpy(gpuBuff.pData, &MyMatracies, sizeof(WVP));
		myContext->Unmap(cBuff, 0);
		myContext->PSSetConstantBuffers(0, 1, constants);

		myContext->Draw(12, 0);
	}


#pragma endregion


		break;
	case Drawingthings::SPACE:
		myContext->PSSetShaderResources(0, 1, &SkyboxTextureSpace);
		myContext->DrawIndexed(simplecube.indicesList.size(), 0, 0);
		myContext->ClearDepthStencilView(zBufferView, D3D11_CLEAR_DEPTH, 1, 1);

#pragma region Planet
		myContext->IASetInputLayout(myComplexMeshLayout);
		myContext->IASetVertexBuffers(0, 1, &vPlanetMesh, Instance_strides, Instance_offsets);
		myContext->IASetIndexBuffer(iPlanetMesh, DXGI_FORMAT_R32_UINT, 0);
		myContext->VSSetShader(PlanetVShader, 0, 0);
		myContext->VSSetShaderResources(0, 2, HeightMaps);
		myContext->PSSetShader(PlanetPShader, 0, 0);
		myContext->PSSetShaderResources(0, 4, PlanetInstancingTextures);

		//placing first planet
		XMMATRIX temp = XMMatrixMultiply(XMMatrixRotationY(rot), XMMatrixRotationZ(-10));
		temp = XMMatrixMultiply(temp, XMMatrixTranslation(0,0,50));
		XMStoreFloat4x4(&PlanetsData.position[0], XMMatrixMultiply(XMMatrixScaling(3, 3, 3), temp));


		//rotating second planet around first
		temp = XMMatrixTranslation(temp.r[3].m128_f32[0], temp.r[3].m128_f32[1], temp.r[3].m128_f32[2]);
		temp = XMMatrixMultiply(XMMatrixRotationY(rot), temp);
		temp = XMMatrixMultiply(XMMatrixScaling(0.75,0.75,0.75), temp);
		temp = XMMatrixMultiply(XMMatrixTranslation(20, 0, 0), temp);
		XMStoreFloat4x4(&PlanetsData.position[1], XMMatrixMultiply(XMMatrixRotationY(rot), temp));

		//setting up third and fourth planets
		temp = XMMatrixMultiply(XMMatrixRotationZ(rot * 1.25f),XMMatrixTranslation(0, 0, 100));
		temp = XMMatrixMultiply(XMMatrixScaling(2, 2, 2), temp);
		XMStoreFloat4x4(&PlanetsData.position[2], XMMatrixMultiply(XMMatrixTranslation(-50,0,0), temp));
		XMStoreFloat4x4(&PlanetsData.position[3], XMMatrixMultiply(XMMatrixTranslation(50,0,0), temp));

		//instance data constant buffer
		hr = myContext->Map(instanceBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuInBuff);
		memcpy(gpuInBuff.pData, &PlanetsData, sizeof(instance));
		myContext->Unmap(instanceBuff, 0);

		myContext->DrawIndexedInstanced(Planet.indicesList.size(), 4, 0, 0, 0);

#pragma endregion

#pragma region SpaceShip

		myContext->IASetInputLayout(myComplexMeshLayout);
		myContext->IASetVertexBuffers(0, 1, &vShipMesh, Instance_strides, Instance_offsets);
		myContext->IASetIndexBuffer(iShipMesh, DXGI_FORMAT_R32_UINT, 0);
		myContext->VSSetShader(ShipVShader, 0, 0);
		myContext->PSSetShader(ShipPShader, 0, 0);
		myContext->PSSetShaderResources(0, 1, &ShipTex);

		//MyMatracies.wMatrix = camera.getPosition();
		XMMATRIX Shiptemp = XMMatrixMultiply(XMMatrixTranslation(0, -2, 5), XMLoadFloat4x4(&camera.getPositionRotation()));
		Shiptemp = XMMatrixMultiply(XMMatrixRotationX(ShipX), Shiptemp);
		Shiptemp = XMMatrixMultiply(XMMatrixRotationZ(ShipZ), Shiptemp);
		XMStoreFloat4x4(&MyMatracies.wMatrix, Shiptemp);
		//XMStoreFloat4x4(&MyMatracies.wMatrix, XMMatrixIdentity());
		hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuff);
		memcpy(gpuBuff.pData, &MyMatracies, sizeof(WVP));
		myContext->Unmap(cBuff, 0);

		myContext->DrawIndexed(SpaceShip.indicesList.size(), 0, 0);

#pragma endregion


		break;
	case Drawingthings::ISLAND:
		myContext->PSSetShaderResources(0, 1, &SkyboxTextureIsland);
		myContext->DrawIndexed(simplecube.indicesList.size(), 0, 0);
		myContext->ClearDepthStencilView(zBufferView, D3D11_CLEAR_DEPTH, 1, 1);

#pragma region Island

		myContext->IASetInputLayout(myComplexMeshLayout);
		myContext->IASetVertexBuffers(0, 1, &vIslandMesh, Instance_strides, Instance_offsets);
		myContext->IASetIndexBuffer(iIslandMesh, DXGI_FORMAT_R32_UINT, 0);
		myContext->VSSetShader(ShipVShader, 0, 0);
		myContext->PSSetShader(ShipPShader, 0, 0);
		myContext->PSSetShaderResources(0, 1, &SandTexture);

		XMStoreFloat4x4(&MyMatracies.wMatrix,XMMatrixMultiply(XMMatrixScaling(2,1,2), XMMatrixIdentity()));
		hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuff);
		memcpy(gpuBuff.pData, &MyMatracies, sizeof(WVP));
		myContext->Unmap(cBuff, 0);

		myContext->DrawIndexed(Island.indicesList.size(), 0, 0);

#pragma endregion

#pragma region PlamTree

		myContext->IASetInputLayout(myComplexMeshLayout);
		myContext->IASetVertexBuffers(0, 1, &vTreeMesh, Instance_strides, Instance_offsets);
		myContext->IASetIndexBuffer(iTreeMesh, DXGI_FORMAT_R32_UINT, 0);
		myContext->VSSetShader(ShipVShader, 0, 0);
		myContext->PSSetShader(ShipPShader, 0, 0);
		myContext->PSSetShaderResources(0, 1, &TreeTex);

		XMStoreFloat4x4(&MyMatracies.wMatrix, XMMatrixTranslation(0,3.3f,0));
		hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuff);
		memcpy(gpuBuff.pData, &MyMatracies, sizeof(WVP));
		myContext->Unmap(cBuff, 0);

		myContext->DrawIndexed(Tree.indicesList.size(), 0, 0);

#pragma endregion


#pragma region Water

		myContext->IASetInputLayout(myComplexMeshLayout);
		myContext->IASetVertexBuffers(0, 1, &vWaterPlane, Instance_strides, Instance_offsets);
		myContext->IASetIndexBuffer(iWaterPlane, DXGI_FORMAT_R32_UINT, 0);
		myContext->VSSetShader(WaterVertex, 0, 0);
		myContext->VSSetShaderResources(0, 1, &WaterT);
		myContext->PSSetShader(WaterPixel, 0, 0);
		myContext->PSSetShaderResources(0, 1, &WaterT);

		MyMatracies.lights[0]._constant += 0.01;
		XMStoreFloat4x4(&MyMatracies.wMatrix, XMMatrixMultiply(XMMatrixScaling(10, 1, 10), XMMatrixTranslation(0,1,0)));
		hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuff);
		memcpy(gpuBuff.pData, &MyMatracies, sizeof(WVP));
		myContext->Unmap(cBuff, 0);

		myContext->DrawIndexed(waterP.indicesList.size(), 0, 0);

#pragma endregion


		break;
	default:
		break;
	}



	mySwapper->Present(1, 0);
}

void Drawingthings::CameraMove()
{
	camera.Movement();
}

void Drawingthings::Resize(float width, float height)
{
	if (!myContext)
		return;

	myContext->OMSetRenderTargets(0, 0, 0);

	myTargetv->Release();

	HRESULT hr;

	hr = mySwapper->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);

	ID3D11Texture2D* pBuffer;
	hr = mySwapper->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);

	hr = myDevice->CreateRenderTargetView(pBuffer, NULL,&myTargetv);

	pBuffer->Release();

	zBufferView->Release();
	zBuffer->Release();

	D3D11_TEXTURE2D_DESC zDesc;
	ZeroMemory(&zDesc, sizeof(D3D11_TEXTURE2D_DESC));

	zDesc.ArraySize = 1;
	zDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	zDesc.Width = width;
	zDesc.Height = height;
	zDesc.Usage = D3D11_USAGE_DEFAULT;
	zDesc.Format = DXGI_FORMAT_D32_FLOAT;
	zDesc.MipLevels = 1;
	zDesc.SampleDesc.Count = 1;

	hr = myDevice->CreateTexture2D(&zDesc, nullptr, &zBuffer);
	hr = myDevice->CreateDepthStencilView(zBuffer, nullptr, &zBufferView);

	//myContext->OMSetRenderTargets(1, &myTargetv, NULL);

	aspectRatio = width / static_cast<float>(height);

	
	myPort.Width = width;
	myPort.Height = height;
	myPort.MinDepth = 0.0f;
	myPort.MaxDepth = 1.0f;
	myPort.TopLeftX = 0;
	myPort.TopLeftY = 0;
	myContext->RSSetViewports(1, &myPort);

}

void Drawingthings::LoadMesh(const char* meshFileName, SimpleMesh& mesh)
{
	std::fstream file{ meshFileName, std::ios_base::in | std::ios_base::binary };

	assert(file.is_open());

	uint32_t player_index_count;
	file.read((char*)&player_index_count, sizeof(uint32_t));

	mesh.indicesList.resize(player_index_count);

	file.read((char*)mesh.indicesList.data(), sizeof(uint32_t) * player_index_count);
	uint32_t player_vertex_count;
	file.read((char*)&player_vertex_count, sizeof(uint32_t));

	mesh.vertexList.resize(player_vertex_count);

	file.read((char*)mesh.vertexList.data(), sizeof(SimpleVertex) * player_vertex_count);

	// Example mesh conditioning if needed - this flips handedness
	for (auto& v : mesh.vertexList)
	{
		v.Pos.x = -v.Pos.x;
		v.Normal.x = -v.Normal.x;
		v.Tex.y = 1.0f - v.Tex.y;
	}

	int tri_count = (int)(mesh.indicesList.size() / 3);

	for (int i = 0; i < tri_count; ++i)
	{
		int* tri = mesh.indicesList.data() + i * 3;

		int temp = tri[0];
		tri[0] = tri[2];
		tri[2] = temp;
	}
	file.close();
}

void Drawingthings::CreateModel(SimpleMesh& meshStruct, const char* modelName, ID3D11Buffer** vetrex, ID3D11Buffer** index)
{
	LoadMesh(modelName, meshStruct);
	D3D11_BUFFER_DESC bDesc;
	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&bDesc, sizeof(bDesc));
	ZeroMemory(&subData, sizeof(subData));

	bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bDesc.ByteWidth = sizeof(SimpleVertex) * meshStruct.vertexList.size();
	bDesc.CPUAccessFlags = 0;
	bDesc.MiscFlags = 0;
	bDesc.StructureByteStride = 0;
	bDesc.Usage = D3D11_USAGE_IMMUTABLE;

	subData.pSysMem = meshStruct.vertexList.data();

	myDevice->CreateBuffer(&bDesc, &subData, vetrex); // vertex buffer

	//index buffer
	ZeroMemory(&subData, sizeof(subData));

	bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bDesc.ByteWidth = sizeof(int) * meshStruct.indicesList.size();
	subData.pSysMem = meshStruct.indicesList.data();

	myDevice->CreateBuffer(&bDesc, &subData, index);
}