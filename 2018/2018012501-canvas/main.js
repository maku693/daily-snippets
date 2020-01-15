const createInitialState = () => {
  let context = c.getContext('2d')
  context.strokeStyle = 'transparent'
  return {
    context: c.getContext('2d'),
    lastTimeStamp: 0,
    particles: setupParticles(),
  }
}

const setupParticles = () => {
  const count = 100
  const x = c.width * 0.5
  const y = c.height * 0.5
  const width = 100
  const height = 100

  const randomMinMax = (min, max) => {
    return Math.random() * (max - min) + min
  }
  return (new Array(count)).fill({
    x: randomMinMax(x - width * 0.5, x + width * 0.5),
    y: randomMinMax(y - height * 0.5, y + height * 0.5),
    vx: randomMinMax(-1.0, 1.0),
    vy: randomMinMax(-1.0, 1.0),
  })
}

const update = (state = createInitialState(), timeStamp = 0) => {
  const { lastTimeStamp, particles } = state
  const delta = timeStamp - lastTimeStamp

  for (let particle of particles) {
    updateParticle(particle, delta)
  }

  return {
    lastTimeStamp: timeStamp,
    particles: particles,
    ...state
  }
}

const updateParticle = (particle, delta) => {
  particle.x = particle.vx * delta * 0.001
  particle.y = particle.vy * delta * 0.001
  return particle
}

const render = ({ context, particles }) => {
  // context.fillStyle = 'black'
  // context.fillRect(0, 0, context.canvas.width, context.canvas.height);
  // context.fillStyle = 'white'
  for (let {x, y} of particles) {
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

