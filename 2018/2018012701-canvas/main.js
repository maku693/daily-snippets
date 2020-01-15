'use strict'

const createInitialState = () => {
  let context = c.getContext('2d')
  context.strokeStyle = 'transparent'
  return {
    context: context,
    lastTimeStamp: 0,
    particles: setupParticles(),
  }
}

const setupParticles = () => {
  const count = 100
  const centerOfCanvas = {
    x: c.width * 0.5,
    y: c.height * 0.5,
  }
  const velocityRange = {
    x: { min: c.width * -0.5, max: c.width * 0.5 },
    y: { min: c.height * -0.5, max: c.height * 0.5 },
  }

  const randomMinMax = (min, max) => {
    return Math.random() * (max - min) + min
  }

  let particles = Array.from({length: count}, () => ({
    x: centerOfCanvas.y,
    y: centerOfCanvas.x,
    vx: randomMinMax(velocityRange.x.min, velocityRange.x.max),
    vy: randomMinMax(velocityRange.y.min, velocityRange.y.max),
  }))

  return particles
}

const update = (state = createInitialState(), timeStamp = 0) => {
  const { lastTimeStamp, particles } = state
  const delta = timeStamp - lastTimeStamp

  for (let particle of particles) {
    updateParticle(particle, delta)
  }

  return {
    context: state.context,
    lastTimeStamp: timeStamp,
    particles: particles,
  }
}

const updateParticle = (particle, delta) => {
  particle.x += particle.vx * delta * 0.001
  particle.y += particle.vy * delta * 0.001
  return particle
}

const render = ({ context, particles }) => {
  context.fillStyle = 'black'
  context.fillRect(0, 0, context.canvas.width, context.canvas.height);
  context.fillStyle = 'white'
  for (const {x, y} of particles) {
    context.fillRect(x, y, 2, 2)
  }
  context.fill()
}

let state = undefined
const loop = (t = 0) => {
  state = update(state, t)
  render(state)
  window.requestAnimationFrame(nextT => loop(nextT, state))
}

loop()

