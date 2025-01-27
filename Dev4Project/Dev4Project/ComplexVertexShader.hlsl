struct VS_INPUT
{
    float3 Pos : POSITION;
    float3 Norm : NORMAL;
    float2 Tex : TEXCOORD;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Norm : ONORMAL;
    float2 Tex : OTEXCOORD1;
    float3 Tex3D : OTEXCOORD2;
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

cbuffer INSTANCE : register(b1)
{
    float4x4 worldMat[10];
}

PS_INPUT main(VS_INPUT input, uint id : SV_InstanceID) // uint id : SV_InstanceID
{
    PS_INPUT output = (PS_INPUT)0;
    
    output.Pos = float4(input.Pos, 1);
    output.Norm = mul(worldMat[id], float4(input.Norm, 0)).xyz;  // mul(worldMat[id], input.normal)
    output.Tex = input.Tex;
    output.Tex3D = input.Pos;
    
    output.Pos = mul(worldMat[id], output.Pos);
    output.Pos = mul(viewMatrix, output.Pos);
    output.Pos = mul(projMatrix, output.Pos);
    
	return output;
}