const int NUM_SAMPLES = 8;

vec4 blur_texture(sampler2D texture, vec2 uv, vec2 direction)
{
  vec4 result = 0.0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    result += texture2D(texture, uv + direction * i);
  }
  return result;
}
