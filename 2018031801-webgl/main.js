import createAnimationLoop, { timestampToDelta } from './createAnimationLoop.js'
import { fragmentShaderSource, vertexShaderSource } from './shaders.js'
import * as mat4 from './mat4.js'

// Setup
const gl = c.getContext('webgl')
gl.clearColor(0.0, 0.0, 0.0, 1.0)
// gl.enable(gl.DEPTH_TEST)
// gl.depthFunc(gl.LEQUAL)
// gl.clearDepth(1.0)

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
const aPositionLocation = gl.getAttribLocation(program, 'aPosition')
const aColorLocation = gl.getAttribLocation(program, 'aColor')
const uMVPMatrixLocation = gl.getUniformLocation(program, 'uMVPMatrix')

// Bind VBO
const vertexBuffer = gl.createBuffer()
gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer)
const vertices = new Float32Array([
  // Position           // Color
   0.0,  0.5, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0,
   0.5, -0.5, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
  -0.5, -0.5, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,
])
gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW)

// MVP
const mvpMatrix = mat4.createIdentityMat4()

// Draw
function draw(delta) {
  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT)
  gl.useProgram(program)
  gl.enableVertexAttribArray(vertexBuffer)
  gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer)
  gl.vertexAttribPointer(aPositionLocation, 4, gl.FLOAT, false, 0, 0)
  gl.vertexAttribPointer(aColorLocation, 4, gl.FLOAT, false, 0, 0)
  gl.uniformMatrix4fv(uMVPMatrixLocation, false, mvpMatrix)
  gl.drawArrays(gl.TRIANGLES, 0, 3)
  // gl.flush()
}

const animationLoop = createAnimationLoop(timestampToDelta(draw))
animationLoop.start()
