struct VS_INPUT
{
    float4 Pos : POSITION;
    float3 Norm : NORMAL;
    float2 Tex : TEXCOORD;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Norm : ONORMAL;
    float2 Tex : OTEXCOORD1;
};

cbuffer SHADER_VAR : register(b0)
{
    float4x4 worldMatrix;
    float4x4 viewMatrix;
    float4x4 projMatrix;
};

PS_INPUT main( VS_INPUT input ) 
{
    PS_INPUT output = (PS_INPUT)0;
    output.Pos = input.Pos;
    output.Norm = input.Norm;
    output.Tex = input.Tex;
    
    output.Pos = mul(worldMatrix, output.Pos);
    output.Pos = mul(viewMatrix, output.Pos);
    output.Pos = mul(projMatrix, output.Pos);
    
	return output;
}