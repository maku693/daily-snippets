import createAnimationLoop, { timestampToDelta } from './createAnimationLoop.js'
import { fragmentShaderSource, vertexShaderSource } from './shaders.js'
import { mat4, vec3 } from './node_modules/gl-matrix/src/gl-matrix.js'

// Setup
const gl = c.getContext('webgl')
gl.clearColor(0.0, 0.0, 0.0, 1.0)
gl.enable(gl.DEPTH_TEST)
gl.depthFunc(gl.LEQUAL)
gl.clearDepth(1.0)

// Load Shaders
function loadShader(type, source) {
  const shader = gl.createShader(type)
  gl.shaderSource(shader, source)
  gl.compileShader(shader)
  return shader
}
const vertexShader = loadShader(gl.VERTEX_SHADER, vertexShaderSource)
const fragmentShader = loadShader(gl.FRAGMENT_SHADER, fragmentShaderSource)
const program = gl.createProgram()
gl.attachShader(program, vertexShader)
gl.attachShader(program, fragmentShader)
gl.linkProgram(program)
gl.useProgram(program)
const aPositionLocation = gl.getAttribLocation(program, 'aPosition')
const aColorLocation = gl.getAttribLocation(program, 'aColor')
const uMVPMatrixLocation = gl.getUniformLocation(program, 'uMVPMatrix')

// Bind VBO
const vertexBuffer = gl.createBuffer()
gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer)
const vertices = new Float32Array([
  // Position         // Color
   0.0,  1,0,  0.0,   1.0,  0.0,  0.0,
   1.0,  0.0,  0.0,   0.0,  1.0,  0.0,
  -1.0,  0.0,  0.0,   0.0,  0.0,  1.0,
])
gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW)

// MVP
const mMatrix = mat4.identity(mat4.create())
const vMatrix = mat4.identity(mat4.create())
mat4.lookAt(
  vMatrix,
  vec3.fromValues(0.0, 1.0, 3.0),
  vec3.fromValues(0, 0, 0),
  vec3.fromValues(0, 1, 0)
)
const pMatrix = mat4.identity(mat4.create())
mat4.perspective(pMatrix, 90, c.width / c.height, 0.01, 100)
const mvpMatrix = mat4.identity(mat4.create())
mat4.mul(mvpMatrix, pMatrix, vMatrix)
mat4.mul(mvpMatrix, mMatrix, mvpMatrix)

// Draw
gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT)
gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer)
gl.enableVertexAttribArray(vertexBuffer)
gl.vertexAttribPointer(aPositionLocation, 3, gl.FLOAT, false, 32, 0)
gl.vertexAttribPointer(aColorLocation, 3, gl.FLOAT, false, 32, 32)
gl.uniformMatrix4fv(uMVPMatrixLocation, false, mvpMatrix)
gl.drawArrays(gl.TRIANGLES, 0, 3)
gl.flush()

// function draw(delta) {}
//
// const animationLoop = createAnimationLoop(timestampToDelta(draw))
//
// animationLoop.start()
