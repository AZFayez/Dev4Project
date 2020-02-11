// rule of 3
// 3 things must match
// 1. C++ Vertex struct 
// 2. Input Layout
// 3. HLSL Vertext struct

//#pragma pack_matrix(row_major)  used to change all incoming shit to row major

struct MyVertex
{
    float3 pos : POSITION;
    float3 uvw : TEXCOORD; 
    float3 nrm : NORMAL; 
};

struct OutputVert
{
    float4 pos : SV_POSITION;
    float3 uvw : OTEXCOORD;
    float3 nrm : ONORMAL;
    
};

struct Lights
{
    float4 position, lightDirection;
    float4 ambient, diffuse, specular;
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

OutputVert main( MyVertex input)
{
    OutputVert Myout = (OutputVert)0;
    Myout.pos = float4(input.pos, 1);
    Myout.nrm = input.nrm;
    Myout.uvw = input.uvw;
    
    //Math goes below
    
    Myout.pos = mul(worldMatrix, Myout.pos);
    Myout.pos = mul(viewMatrix, Myout.pos);
    Myout.pos = mul(projMatrix, Myout.pos);
    
	return Myout;
}