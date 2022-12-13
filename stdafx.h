#pragma once

#define NOMINMAX

#ifdef _DEBUG
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

// Window
#include <Windows.h>
#include <assert.h>

// STL
#include <vector>
#include <iostream>

// DirectX
#include <d3dcompiler.h>
#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>

typedef unsigned int uint;

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dcompiler.lib")


// Macro Functions
#define SAFE_RELEASE(p) {if(p) { (p)->Release(); (p) = nullptr; }}
#define SAFE_DELETE(p) {if(p) { delete (p); (p) = nullptr; }}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[] (p); (p) = nullptr; }}

// Framework
/*
	Program.cpp			// ���α׷� ������
	Graphics.h			// DX�ڿ� ����
	Window.h			// ������ ����
*/
#include "Settings.h"	// DX <-> ������
#include "Graphics.h"
//#include "Execute.h"	// ������ ����������

#include "Vertex/D3D11_Vertex.h"				// ���ؽ� ������ ���� ����
#include "Vertex/D3D11_Geometry.h"				// ������Ʈ��(���ؽ� & �ε���) ������ ����

#include "InputAssembler/D3D11_VertexBuffer.h"	// ���ؽ� ���� ����
#include "InputAssembler/D3D11_IndexBuffer.h"	// �ε��� ���� ����
#include "InputAssembler/D3D11_InputLayout.h"	// ��ǲ ���̾ƿ� ����

#include "Shader/D3D11_Shader.h"				// VS, PS ����
#include "Shader/D3D11_ConstantBuffer.h"		// ���ҽ����� ����
#include "Shader/D3D11_Texture.h"				// �ؽ�ó(���̴����ҽ���) ����
#include "Shader/D3D11_SamplerState.h"			// ���÷� ������Ʈ ����

#include "Rasterizer/D3D11_RasterizerState.h"	// RS ����
#include "Rasterizer/D3D11_Viewport.h"			// ����Ʈ ����

#include "OutputMerger/D3D11_BlendState.h"		// ���� ������Ʈ ����