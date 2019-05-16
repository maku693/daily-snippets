import * as mat4 from "./mat4.js";
import { createFrag, createVert } from "./tags.js";

const canvas = document.getElementById("canvas");
function fitCanvasToDisplaySize() {
  const { width, height } = canvas.getBoundingClientRect();
  canvas.width = width;
  canvas.height = height;
}
window.addEventListener("resize", fitCanvasToDisplaySize);
fitCanvasToDisplaySize();

const gl = canvas.getContext("webgl");
const frag = createFrag(gl);
const vert = createVert(gl);

gl.clearColor(0.0, 0.0, 0.0, 1.0);
gl.enable(gl.CULL_FACE);
gl.enable(gl.DEPTH_TEST);
gl.depthFunc(gl.LEQUAL);
gl.clearDepth(1.0);

const fs = frag`
precision mediump float;

varying vec3 vColor;

void main() {
  gl_FragColor = vec4(vColor, 1.0);
}
`;
const vs = vert`
attribute vec4 aPosition;
attribute vec3 aColor;

uniform mat4 uMVPMatrix;

varying mediump vec3 vColor;

void main() {
  gl_Position = uMVPMatrix * aPosition;
  vColor = aColor;
}
`;
const program = gl.createProgram();
gl.attachShader(program, vs);
gl.attachShader(program, fs);
gl.linkProgram(program);
gl.useProgram(program);

const aPositionLocation = gl.getAttribLocation(program, "aPosition");
gl.enableVertexAttribArray(aPositionLocation);
const aNormalLocation = gl.getAttribLocation(program, "aColor");
gl.enableVertexAttribArray(aNormalLocation);
const uMVPMatrixLocation = gl.getUniformLocation(program, "uMVPMatrix");

const vertexBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
// prettier-ignore
const vertices = new Float32Array([
  0, 0.41, 0,
  -0.5, -0.41, 0.29,
  0.5, -0.41, 0.29,
  0, -0.41, -0.57,
  1, 0, 0,
  0, 1, 0,
  0, 0, 1,
  1, 1, 1
]);
gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);
gl.vertexAttribPointer(aPositionLocation, 3, gl.FLOAT, false, 12, 0);
gl.vertexAttribPointer(aNormalLocation, 3, gl.FLOAT, false, 12, 48);

// IBO
const indexBuffer = gl.createBuffer();
gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
const indices = new Int16Array([0, 1, 2, 0, 2, 3, 0, 3, 1, 1, 3, 2]);
gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, indices, gl.STATIC_DRAW);

// matrices
const mMatrix = mat4.create();
const mtMatrix = mat4.create();
const mrMatrix = mat4.create();
const msMatrix = mat4.create();
const vMatrix = mat4.create();
const pMatrix = mat4.create();
const mvpMatrix = mat4.create();

function render(timestamp) {
  gl.viewport(0, 0, gl.canvas.width, gl.canvas.height);
  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

  mat4.perspective(
    pMatrix,
    Math.PI / 2,
    gl.canvas.width / gl.canvas.height,
    1,
    1000
  );

  mat4.translate(mtMatrix, [0, 0, 0]);
  mat4.rotate(mrMatrix, [0, 1, 0], timestamp * 0.001);
  mat4.scale(msMatrix, [200, 200, 200]);
  mat4.multiply(mMatrix, mtMatrix, mrMatrix);
  mat4.multiply(mMatrix, mMatrix, msMatrix);

  mat4.translate(vMatrix, [0, 0, -300]);

  mat4.multiply(mvpMatrix, pMatrix, vMatrix);
  mat4.multiply(mvpMatrix, mvpMatrix, mMatrix);

  gl.uniformMatrix4fv(uMVPMatrixLocation, false, mvpMatrix);

  gl.drawElements(gl.TRIANGLES, indices.length, gl.UNSIGNED_SHORT, 0);
  gl.flush();

  requestAnimationFrame(render);
}
requestAnimationFrame(render);
