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
#include "Utility/Geometry_Generator.h"		// 지오메트리 생성 관리
#include "Utility/GUID_Generator.h"			// 자원 ID 생성 관리

// Framework
/*
	Program.cpp				// 프로그램 시작점
	Graphics.h				// DX자원 관리
	Window.h				// 윈도우 생성
*/
#include "Core/Settings.h"	// DX <-> 윈도우
#include "Core/Object.h"	// 객체 원본
#include "Core/Graphics.h"
//#include "Execute.h"		// 렌더링 파이프라인

#include "Core/D3D11/Vertex/D3D11_Vertex.h"					// 버텍스 데이터 설정 관리
#include "Core/D3D11/Vertex/D3D11_Geometry.h"				// 지오메트리(버텍스 & 인덱스) 데이터 관리

#include "Core/D3D11/InputAssembler/D3D11_VertexBuffer.h"	// 버텍스 버퍼 관리
#include "Core/D3D11/InputAssembler/D3D11_IndexBuffer.h"	// 인덱스 버퍼 관리
#include "Core/D3D11/InputAssembler/D3D11_InputLayout.h"	// 인풋 레이아웃 관리

#include "Core/D3D11/Shader/D3D11_Shader.h"					// VS, PS 관리
#include "Core/D3D11/Shader/D3D11_ConstantBuffer.h"			// 리소스버퍼 관리
#include "Core/D3D11/Shader/D3D11_Texture.h"				// 텍스처(쉐이더리소스뷰) 관리
#include "Core/D3D11/Shader/D3D11_SamplerState.h"			// 샘플러 스테이트 관리

#include "Core/D3D11/Rasterizer/D3D11_RasterizerState.h"	// RS 관리
#include "Core/D3D11/Rasterizer/D3D11_Viewport.h"			// 뷰포트 관리

#include "Core/D3D11/OutputMerger/D3D11_BlendState.h"		// 블렌드 스테이트 관리

#include "Core/D3D11/D3D11_Pipeline.h"						// 렌더링 파이프라인 관리