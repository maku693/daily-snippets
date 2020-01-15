export const vertexShaderSource = `\
attribute vec4 aPosition;
attribute vec4 aColor;

uniform mat4 uMVPMatrix;

varying mediump vec4 vColor;

void main() {
  gl_Position = aPosition * uMVPMatrix;
  vColor = aColor;
}
`
export const fragmentShaderSource = `\
precision mediump float;

varying vec4 vColor;

void main() {
  gl_FragColor = vColor;
}
`
