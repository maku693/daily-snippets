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
const aColorLocation = gl.getAttribLocation(program, 'aColor')
gl.enableVertexAttribArray(aColorLocation)
const uMVPMatrixLocation = gl.getUniformLocation(program, 'uMVPMatrix')

// Bind VBO
const vertexBuffer = gl.createBuffer()
gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer)
const vertices = new Float32Array([
  // Position          // Color
   0,   50, 0, 1, 1, 0, 0, 1,
  -50, -50, 0, 1, 0, 1, 0, 1,
   50, -50, 0, 1, 0, 0, 1, 1,
])
gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.DYNAMIC_DRAW)
gl.vertexAttribPointer(aPositionLocation, 4, gl.FLOAT, false, 32, 0)
gl.vertexAttribPointer(aColorLocation, 4, gl.FLOAT, false, 32, 16)

// Draw
function draw(timestamp = 0) {
  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT)
  
  const scaleFactor = 2.0 + Math.sin(timestamp * 0.001 * 2)
  const mvpMatrix = mat4.multiply(
    mat4.createScaleMat4([scaleFactor, scaleFactor, 1.0]),
    mat4.multiply(
      mat4.createTranslateMat4([1.0, 1.0, 0.0]),
      mat4.createOrthographicMat4(0, c.clientWidth, 0, c.clientHeight, -10, 10)
    )
  )
  gl.uniformMatrix4fv(uMVPMatrixLocation, false, mvpMatrix)

  gl.drawArrays(gl.TRIANGLES, 0, 3)
  gl.flush()
}

const animationLoop = createAnimationLoop(draw)
animationLoop.start()
