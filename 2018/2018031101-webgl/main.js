import createAnimationLoop, { timestampToDelta } from './createAnimationLoop.js'

const gl = c.getContext('webgl')
gl.clearColor(0.0, 0.0, 0.0, 1.0)
gl.enable(gl.DEPTH_TEST)
gl.depthFunc(gl.LEQUAL)
gl.clearDepth(1.0)

function draw(delta) {
  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT)
}

const animationLoop = createAnimationLoop(timestampToDelta(draw))

animationLoop.start()
