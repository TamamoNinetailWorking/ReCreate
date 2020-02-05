#include "BaseHeader.hlsli"

cbuffer cbBuffer1 : register(b1)
{
    column_major float4x4 g_matWVP : packoffset(c0);
}

VS_OUT main(VS_IN In)
{
    VS_OUT Out;
    Out.sv_pos = mul(float4(In.pos, 1.0f), g_matWVP);
    Out.normal = In.normal;
    Out.texel = In.texel;
    Out.pos = In.pos;
    
    return Out;
}