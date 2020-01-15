export const vertexShaderSource = `\
attribute vec4 aPosition;
attribute vec3 aColor;
attribute vec3 aNormal;

uniform mat4 uMVPMatrix;

varying mediump vec4 vColor;

void main() {
  gl_Position = uMVPMatrix * aPosition;
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
