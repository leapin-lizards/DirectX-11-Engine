cbuffer myCbuffer : register(b0)
{
    float4x4 mat;
};
cbuffer myBuffer2 : register(b1)
{
    
    float x2;
    float y2;
}

struct VS_INPUT
{
    float3 inPos : POSITION;
    float2 inTexCoord : TEXCOORD;
    
};
struct VS_OUTPUT
{
    float4 outPos : SV_Position;
    float2 outTexCoord : TEXCOORD;
};
VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;
    output.outPos = mul(float4(input.inPos, 1.0f),mat);
    output.outTexCoord = input.inTexCoord;
    return output;
}