struct Vertex {
  float3 Position : SV_Position;
  float4 Color : Color;
};

float4 main(Vertex v) : SV_Target { return v.Color; }
