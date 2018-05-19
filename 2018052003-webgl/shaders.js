export const vertexShaderSource = `\
attribute vec4 aPosition;
attribute vec3 aColor;

uniform mat4 uMVPMatrix;

varying mediump vec3 vColor;

void main() {
  gl_Position = uMVPMatrix * aPosition;
  vColor = aColor;
}
`
export const fragmentShaderSource = `\
precision mediump float;

varying vec3 vColor;

void main() {
  gl_FragColor = vec4(vColor, 1.0);
}
`
