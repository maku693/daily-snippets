import createAnimationLoop from './createAnimationLoop.js'
import { fragmentShaderSource, vertexShaderSource } from './shaders.js'
import * as mat4 from './mat4.js'

// Setup
const gl = c.getContext('webgl')
gl.clearColor(0.0, 0.0, 0.0, 1.0)
gl.enable(gl.CULL_FACE)
gl.enable(gl.DEPTH_TEST)
gl.depthFunc(gl.LEQUAL)
gl.clearDepth(1.0)

// Load Shaders
const vertexShader = gl.createShader(gl.VERTEX_SHADER)
gl.shaderSource(vertexShader, vertexShaderSource)
gl.compileShader(vertexShader)
const fragmentShader = gl.createShader(gl.FRAGMENT_SHADER)
gl.shaderSource(fragmentShader, fragmentShaderSource)
gl.compileShader(fragmentShader)
const program = gl.createProgram()
gl.attachShader(program, vertexShader)
gl.attachShader(program, fragmentShader)
gl.linkProgram(program)
gl.useProgram(program)
const aPositionLocation = gl.getAttribLocation(program, 'aPosition')
gl.enableVertexAttribArray(aPositionLocation)
const aNormalLocation = gl.getAttribLocation(program, 'aColor')
gl.enableVertexAttribArray(aNormalLocation)
const uMVPMatrixLocation = gl.getUniformLocation(program, 'uMVPMatrix')
const uColorLocation = gl.getUniformLocation(program, 'uColor')
const uReverseLightDirectionLocation = gl.getUniformLocation(program, 'uReverseLightDirection')

// VBO
const vertexBuffer = gl.createBuffer()
gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer)
const vertices = new Float32Array([
  // Position         // Normal
  0,    0.41,  0,     1, 0, 0,
  -0.5, -0.41, 0.29,  0, 1, 0,
  0.5,  -0.41, 0.29,  0, 0, 1,
  0,    -0.41, -0.57, 1, 1, 1,
])
gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW)
gl.vertexAttribPointer(aPositionLocation, 3, gl.FLOAT, false, 24, 0)
gl.vertexAttribPointer(aNormalLocation, 3, gl.FLOAT, false, 24, 12)

// IBO
const indexBuffer = gl.createBuffer()
gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer)
const indices = new Int16Array([0, 1, 2, 0, 2, 3, 0, 3, 1, 1, 3, 2])
gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, indices, gl.STATIC_DRAW)

// Draw
function draw(timestamp = 0) {
  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT)

  const pMatrix = mat4.createPersepectiveMat4(
    Math.PI * 0.5,
    c.clientWidth / c.clientHeight,
    1, -1000
  )

  const vMatrix = mat4.createTranslateMat4([0, 0, -250])

  const mtMatrix = mat4.createTranslateMat4([0, 0, 0])
  const mrMatrix = mat4.createYRotateMat4(timestamp * 0.001)
  const msMatrix = mat4.createScaleMat4([200, 200, 200])
  const mMatrix = mat4.multiply(mtMatrix, mat4.multiply(mrMatrix, msMatrix))

  const mvpMatrix = mat4.multiply(pMatrix, mat4.multiply(vMatrix, mMatrix))

  gl.uniformMatrix4fv(uMVPMatrixLocation, false, mvpMatrix)
  gl.uniform4fv(uColorLocation, new Float32Array([0, 1, 1, 1]))
  gl.uniform4fv(uReverseLightDirectionLocation, new Float32Array([0, 1, 0, 1]))

  gl.drawElements(gl.TRIANGLES, indices.length, gl.UNSIGNED_SHORT, 0)
  gl.flush()
}

const animationLoop = createAnimationLoop(draw)
animationLoop.start()
