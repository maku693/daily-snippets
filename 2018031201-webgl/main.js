import createAnimationLoop, { timestampToDelta } from './createAnimationLoop.js'
import { fragmentShaderSource, vertexShaderSource } from './shaders.js'

const gl = c.getContext('webgl')
gl.clearColor(0.0, 0.0, 0.0, 1.0)
gl.enable(gl.DEPTH_TEST)
gl.depthFunc(gl.LEQUAL)
gl.clearDepth(1.0)

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

function draw(delta) {
  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT)
}

const animationLoop = createAnimationLoop(timestampToDelta(draw))

animationLoop.start()
