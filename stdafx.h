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
#include <sstream>
#include <unordered_map>
#include <random>
#include <chrono>
#include <functional>
#include <memory>

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

// Math
#include "Math/Math.h"

// Timer
#include "Timer/Timer.h"

// Intersect
#include "Intersect/Intersect.h"

// Utility
#include "Utility/Geometry_Generator.h"		// ������Ʈ�� ���� ����
#include "Utility/GUID_Generator.h"			// �ڿ� ID ���� ����

// Framework
/*
	Program.cpp				// ���α׷� ������
	Graphics.h				// DX�ڿ� ����
	Window.h				// ������ ����
*/
#include "Core/Settings.h"	// DX <-> ������
#include "Core/Object.h"	// ��ü ����
#include "Core/Graphics.h"
//#include "Execute.h"		// ������ ����������

#include "Core/D3D11/Vertex/D3D11_Vertex.h"					// ���ؽ� ������ ���� ����
#include "Core/D3D11/Vertex/D3D11_Geometry.h"				// ������Ʈ��(���ؽ� & �ε���) ������ ����

#include "Core/D3D11/InputAssembler/D3D11_VertexBuffer.h"	// ���ؽ� ���� ����
#include "Core/D3D11/InputAssembler/D3D11_IndexBuffer.h"	// �ε��� ���� ����
#include "Core/D3D11/InputAssembler/D3D11_InputLayout.h"	// ��ǲ ���̾ƿ� ����

#include "Core/D3D11/Shader/D3D11_Shader.h"					// VS, PS ����
#include "Core/D3D11/Shader/D3D11_ConstantBuffer.h"			// ���ҽ����� ����
#include "Core/D3D11/Shader/D3D11_Texture.h"				// �ؽ�ó(���̴����ҽ���) ����
#include "Core/D3D11/Shader/D3D11_SamplerState.h"			// ���÷� ������Ʈ ����

#include "Core/D3D11/Rasterizer/D3D11_RasterizerState.h"	// RS ����
#include "Core/D3D11/Rasterizer/D3D11_Viewport.h"			// ����Ʈ ����

#include "Core/D3D11/OutputMerger/D3D11_BlendState.h"		// ���� ������Ʈ ����

#include "Core/D3D11/D3D11_Pipeline.h"						// ������ ���������� ����