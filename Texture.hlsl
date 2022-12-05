struct VertexInput
{
	float4 position : POSITION0;
	float2 uv : TEXCOORD0;
};

struct PixelInput
{
	float4 position : SV_POSITION0;
	float2 uv : TEXCOORD0;
};

cbuffer TransformBuffer : register(b0)
{
	matrix world;
	matrix view;
	matrix proj;
}

// VS
PixelInput VS(VertexInput input)
{
	PixelInput output;

	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, proj);

	output.uv = input.uv;

	return output;
}

Texture2D source_texture1 : register(t0);
Texture2D source_texture2 : register(t1);
Texture2D source_texture3 : register(t2);
Texture2D source_texture4 : register(t3);
SamplerState samp : register(s0);

float4 PS(PixelInput input) : SV_Target
{
	float4 color = 0.0f;
	
	if (input.uv.x < 1.0f && input.uv.y < 1.0f)
		color = source_texture1.Sample(samp, input.uv);
	else if (input.uv.x >= 1.0f && input.uv.y < 1.0f)
		color = source_texture2.Sample(samp, float2(input.uv.x - 1.0f, input.uv.y));
	else if (input.uv.x < 1.0f && input.uv.y >= 1.0f)
		color = source_texture3.Sample(samp, float2(input.uv.x, input.uv.y - 1.0f));
	else if (input.uv.x >= 1.0f && input.uv.y >= 1.0f)
		color = source_texture4.Sample(samp, float2(input.uv.x - 1.0f, input.uv.y - 1.0f));

	return color;
}