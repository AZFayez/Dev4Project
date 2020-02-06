// rule of 3
// 3 things must match
// 1. C++ Vertex struct 
// 2. Input Layout
// 3. HLSL Vertext struct

//#pragma pack_matrix(row_major)  used to change all incoming shit to row major

struct MyVertex
{
    float4 pos : POSITION;
    float4 clr : COLOR; 
};

struct OutputVert
{
    float4 pos : SV_POSITION;
    float4 clr : OCOLOR;
};

cbuffer SHADER_VAR : register(b0)
{
    float4x4 worldMatrix;
    float4x4 viewMatrix;
    float4x4 projMatrix;
};

OutputVert main( MyVertex input)
{
    OutputVert Myout = (OutputVert)0;
    Myout.pos = input.pos;
    Myout.clr = input.clr;
    
    //Math goes below
    
    Myout.pos = mul(worldMatrix, Myout.pos);
    Myout.pos = mul(viewMatrix, Myout.pos);
    Myout.pos = mul(projMatrix, Myout.pos);
    
	return Myout;
}