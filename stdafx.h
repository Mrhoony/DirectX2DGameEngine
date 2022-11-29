#pragma once

// Window
#include <Windows.h>
#include <assert.h>

// STL
#include <vector>

// DirectX
#include <d3dcompiler.h>
#include <d3d11.h>
#include <D3DX10math.h>

typedef unsigned int uint;

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")


// Macro Functions
#define SAFE_RELEASE(p) {if(p) { (p)->Release(); (p) = nullptr; }}
#define SAFE_DELETE(p) {if(p) { delete (p); (p) = nullptr; }}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[] (p); (p) = nullptr; }}

// Framework
/*
	Program.cpp			// 프로그램 시작점
	Graphics.h			// DX자원 관리
	Window.h			// 윈도우 생성
*/
#include "Settings.h"	// DX <-> 윈도우
#include "Execute.h"	// 렌더링 파이프라인