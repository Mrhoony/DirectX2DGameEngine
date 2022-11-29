#include "stdafx.h"
#include "Graphics.h"

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
	SAFE_RELEASE(render_target_view);
	SAFE_RELEASE(device_context);
	SAFE_RELEASE(device);
	SAFE_RELEASE(swap_chain);
}

void Graphics::Initialize()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	desc.BufferDesc.Width = 0;
	desc.BufferDesc.Height = 0;	
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferCount = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.OutputWindow = Settings::Get().GetWindowHandle();
	desc.Windowed = TRUE;	
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	std::vector<D3D_FEATURE_LEVEL> feature_levels
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,					// 비디오 카드 지정
		D3D_DRIVER_TYPE_HARDWARE,	// 디바이스 타입
		nullptr,					// 추가 소프트웨어
		0,							// 디바이스 생성시 추가기능
		feature_levels.data(),		// 피처레벨 시작주소
		feature_levels.size(),		// 피처레벨 개수
		D3D11_SDK_VERSION,
		&desc,
		&swap_chain,
		&device,
		nullptr,					// 선택된 피처레벨 반환
		&device_context
	);
	assert(SUCCEEDED(hr));
}

void Graphics::CreateBackBuffer(const uint width, const uint height)
{
	HRESULT hr = swap_chain->ResizeBuffers
	(
		0,
		width,
		height,
		DXGI_FORMAT_UNKNOWN,
		0
	);
	assert(SUCCEEDED(hr));

	ID3D11Texture2D* back_buffer = nullptr;
	hr = swap_chain->GetBuffer
	(
		0,										// 꺼낼 버퍼
		__uuidof(ID3D11Texture2D),				// 인터페이스 타입
		reinterpret_cast<void**>(&back_buffer)
	);
	assert(SUCCEEDED(hr));

	hr = device->CreateRenderTargetView
	(
		back_buffer,			// 뷰에서 접근할 리소스, RTV 생성
		nullptr,				// RTV의 desc
		&render_target_view
	);
	assert(SUCCEEDED(hr));

	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	SAFE_RELEASE(back_buffer);
}

void Graphics::Begin()
{
	device_context->OMSetRenderTargets(1, &render_target_view, nullptr);
	device_context->RSSetViewports(1, &viewport);
	device_context->ClearRenderTargetView(render_target_view, clear_color);
}

void Graphics::End()
{
	HRESULT hr = swap_chain->Present(1, 0);
	assert(SUCCEEDED(hr));
}
