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
  const centerX = c.width * 0.5
  const centerY = c.height * 0.5
  const width = 100
  const height = 100

  const randomMinMax = (min, max) => {
    return Math.random() * (max - min) + min
  }

  let particles = (new Array(count)).fill({})
  for (let particle of particles) {
    particle.x = randomMinMax(centerX - width * 0.5, centerX + width * 0.5)
    particle.y = randomMinMax(centerY - height * 0.5, centerY + height * 0.5)
    particle.vx = randomMinMax(-1.0, 1.0)
    particle.vy = randomMinMax(-1.0, 1.0)
  }

  return particles
}

const update = (state = createInitialState(), timeStamp = 0) => {
  const { lastTimeStamp, particles } = state
  const delta = timeStamp - lastTimeStamp

  for (let particle of particles) {
    updateParticle(particle, delta)
  }

  return {
    ...state,
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
  // context.fillStyle = 'black'
  // context.fillRect(0, 0, context.canvas.width, context.canvas.height);
  // context.fillStyle = 'white'
  for (const {x, y} of particles) {
    context.fillRect(x, y, 1, 1)
  }
  // context.fill()
}

let state = undefined
const loop = (t = 0) => {
  state = update(state, t)
  render(state)
  window.requestAnimationFrame(loop)
}

loop()

