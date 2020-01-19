//--------------------------------------------------------------------------------------
// File: Tutorial04.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR0;
};

Texture2D txDiffuse : register(t0);
Texture2D txDiffuse1 : register(t1);

SamplerState samLinear : register(s0);

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{
    float2 uv = input.Color.xy;
    
    float4 tx0 = txDiffuse.Sample(samLinear, input.Color.xy);
    //float4 tx1 = txDiffuse1.Sample(samLinear, input.Color.xy);

    return tx0;
}
