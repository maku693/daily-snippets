export const vertexShaderSource = `
attribute vec3 aPosition;
attribute vec4 aColor;

uniform mat4 uMVPMatrix;

varying mediump vec4 vColor;

void main() {
  gl_Position = uMVPMatrix * vec4(aPosition, 1.0);
  vColor = aColor;
}
`
export const fragmentShaderSource = `
precision mediump float;

varying vec4 vColor;

void main() {
  gl_FragColor = vColor;
}
`
