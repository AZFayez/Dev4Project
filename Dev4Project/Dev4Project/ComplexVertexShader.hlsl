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

struct Lights
{
    float4 position, lightDirection;
    float4 ambient, diffuse, specular, lightColor;
    float _constant, _linear, _exponent;
    unsigned int lightType;
    float cosineInnerCone, cosineOuterCone;
    float lightRadius;
    int lightOn;
};

cbuffer SHADER_VAR : register(b0)
{
    float4x4 worldMatrix;
    float4x4 viewMatrix;
    float4x4 projMatrix;
    Lights light[3];
};

PS_INPUT main( VS_INPUT input ) 
{
    PS_INPUT output = (PS_INPUT)0;
    output.Pos = input.Pos;
    output.Norm = mul(float4(input.Norm, 1), worldMatrix).xyz;
    output.Tex = input.Tex;
    
    output.Pos = mul(worldMatrix, output.Pos);
    output.Pos = mul(viewMatrix, output.Pos);
    output.Pos = mul(projMatrix, output.Pos);
    
	return output;
}