struct OutputVert
{
    float4 pos : SV_Position;
    float4 clr : OCOLOR;
};

float4 main(OutputVert inputPixel) : SV_TARGET
{
	return inputPixel.clr;
}