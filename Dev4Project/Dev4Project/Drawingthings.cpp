#include "Drawingthings.h"

Drawingthings::Drawingthings()
{
}

Drawingthings::~Drawingthings()
{
	if (myDevice) myDevice->Release();
	if (mySwapper) mySwapper->Release();
	if (myContext) myContext->Release();
	if (myTargetv) myTargetv->Release();
	if (myLayout) myLayout->Release();
	if (myMeshLayout) myMeshLayout->Release();
	if (vBuff) vBuff->Release();
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

	D3D11_DEPTH_STENCIL_VIEW_DESC dDesc;
	ZeroMemory(&dDesc, sizeof(dDesc));

	hr = myDevice->CreateDepthStencilView(zBuffer, nullptr, &zBufferView);

	hr = CreateDDSTextureFromFile(myDevice, L"./Assets/StoneHenge.dds", nullptr, &meshTexture);

	hr = myDevice->CreateVertexShader(ComplexVertexShader, sizeof(ComplexVertexShader), nullptr, &ComplexvMeshShader);
	myDevice->CreatePixelShader(ComplexPShader, sizeof(ComplexPShader), nullptr, &ComplexpMeshShader);

	D3D11_INPUT_ELEMENT_DESC ComplexMeshiDesc[] =
	{
		 { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = myDevice->CreateInputLayout(ComplexMeshiDesc, 3, ComplexVertexShader, sizeof(ComplexVertexShader), &myComplexMeshLayout);

	LoadMesh("./Assets/Axe.mesh", simpleMesh);

	ZeroMemory(&bDesc, sizeof(bDesc));
	ZeroMemory(&subData, sizeof(subData));

	bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bDesc.ByteWidth = sizeof(SimpleVertex) * simpleMesh.vertexList.size();
	bDesc.CPUAccessFlags = 0;
	bDesc.MiscFlags = 0;
	bDesc.StructureByteStride = 0;
	bDesc.Usage = D3D11_USAGE_IMMUTABLE;

	subData.pSysMem = simpleMesh.vertexList.data();

	hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuffCMesh); // vertex buffer

	//index buffer
	ZeroMemory(&subData, sizeof(subData));

	bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bDesc.ByteWidth = sizeof(int) * simpleMesh.indicesList.size();
	subData.pSysMem = simpleMesh.indicesList.data();

	hr = myDevice->CreateBuffer(&bDesc, &subData, &iBuffCMesh);

	hr = CreateDDSTextureFromFile(myDevice, L"./Assets/axeTexture.dds", nullptr, &CmeshTexture);
}

void Drawingthings::Render()
{
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
		if (nearplane <0.1f)
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
	aspectRatio = swap.BufferDesc.Width / static_cast<float>(swap.BufferDesc.Height);
	float color[] = { 0, 1, 1, 1 };
	myContext->ClearRenderTargetView(myTargetv, color);

	// setup the pipeline)

	// output merger
	ID3D11RenderTargetView* tempRTv[] = { myTargetv };
	myContext->OMSetRenderTargets(1, tempRTv, zBufferView);

	//clear z buffer
	myContext->ClearDepthStencilView(zBufferView, D3D11_CLEAR_DEPTH, 1, 1);

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
	XMMATRIX temp = XMMatrixTranslation(3, 2, -5);
	XMStoreFloat4x4(&MyMatracies.wMatrix, XMMatrixMultiply(XMMatrixRotationY(rot), temp));
	//view m
	MyMatracies.vMatrix = camera.getView();
	//projection m
	XMStoreFloat4x4(&MyMatracies.pMatrix, XMMatrixPerspectiveFovLH(3.14f / zoom, aspectRatio, nearplane, farplane));
	//light Direction
	XMVECTOR templight = { 0, 1, 0, 1 };
	//templight = XMVector4Transform(templight, XMLoadFloat4x4(&MyMatracies.wMatrix));
	//templight = XMVector4Transform(templight, XMLoadFloat4x4(&MyMatracies.vMatrix));
	//templight = XMVector4Transform(templight, XMLoadFloat4x4(&MyMatracies.pMatrix));
	MyMatracies.lights[0].lightDirection = { -1, -1, 0, 0 };
	MyMatracies.lights[0].lightColor = { 0.75f, 0, 0, 1 };
	XMStoreFloat4(&MyMatracies.lights[1].position, templight);
	MyMatracies.lights[1].lightColor = { 1, 1, 1, 1 };
	MyMatracies.lights[1].lightRadius = 10;

//	MyMatracies.lights[0]. = { 1, 1, 1, 1 };

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


	//drawing second item
	myContext->IASetInputLayout(myMeshLayout);
	UINT mesh_strides[] = { sizeof(_OBJ_VERT_) };
	UINT mesh_offsets[] = { 0 };
	ID3D11Buffer* meshVB[] = { vBuffMesh };

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

	myContext->IASetInputLayout(myComplexMeshLayout);
	UINT Cmesh_strides[] = { sizeof(SimpleVertex) };
	UINT Cmesh_offsets[] = { 0 };
	ID3D11Buffer* CmeshVB[] = { vBuffCMesh };
	myContext->IASetVertexBuffers(0, 1, CmeshVB, Cmesh_strides, Cmesh_offsets);
	myContext->IASetIndexBuffer(iBuffCMesh, DXGI_FORMAT_R32_UINT, 0);
	myContext->VSSetShader(ComplexvMeshShader, 0, 0);
	myContext->PSSetShader(ComplexpMeshShader, 0, 0);
	myContext->PSSetShaderResources(0, 1, &CmeshTexture);

	XMStoreFloat4x4(&MyMatracies.wMatrix, XMMatrixTranslation(0, 5, 0));
	//upload new matrix to video card
	hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuff);
	memcpy(gpuBuff.pData, &MyMatracies, sizeof(WVP));
	myContext->Unmap(cBuff, 0);

	myContext->DrawIndexed(simpleMesh.indicesList.size(), 0, 0);

	mySwapper->Present(1, 0);
}

void Drawingthings::CameraMove()
{
	camera.Movement();
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