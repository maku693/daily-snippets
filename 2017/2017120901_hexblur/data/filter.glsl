uniform sampler2D texture;
uniform vec2 resolution;

const int BLUR_TAPS = 8;

vec4 blur(sampler2D sampler, vec2 uv, vec2 direction) {
  vec4 res = vec4(0.0);
  uv += direction * 0.5;
  for (int i = 0; i < BLUR_TAPS; i++) {
    res += texture2D(texture, uv + direction * i);
  }
  res /= BLUR_TAPS;
  return res;
}

void main() {
  vec2 position = gl_FragCoord.xy / resolution.xy;
  vec3 color = blur(texture, position, vec2(1.0, 0.0) * 0.05).xyz;
  gl_FragColor = vec4(color, 1.0);
}
