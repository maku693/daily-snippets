import createCanvas2DApp from './createCanvas2DApp.js'
import createParticleSystem from './createParticleSystem.js'

const ctx = c.getContext('2d')

function createParticleSystemConfig() {
    return {
        area: {
            x: { min: 250, max: 250 },
            y: { min: 250, max: 250 },
        },
        birthRate: 1000,
        numParticlesToEmit: 10,
        life: { min: 100, max: 100 },
        velocity: {
            angle: { min: 0, max: Math.PI * 2 },
            speed: { min: 50, max: 100 },
        },
    }
}

const particleSystem = createParticleSystem(createParticleSystemConfig())

const app = createCanvas2DApp(ctx, delta => {
    particleSystem.update(delta)
    ctx.fillStyle = 'navy'
    ctx.fillRect(0, 0, c.width, c.height)
    for (const { position, velocity } of particleSystem.getParticles()) {
        ctx.fillStyle = 'white'
        ctx.fillRect(position.x - 1, position.y - 1, 2, 2)
    }
    console.log(particleSystem.getParticles().length)
})
app.start()

let pause = false
c.onclick = () => {
    pause = !pause
    if (pause) {
        app.stop()
    } else {
        app.start()
    }
}

document.onchangevisibility = e => {
    switch (e.target.visibilityState) {
        case 'visible':
            app.start()
            break;
        case 'hidden':
            app.stop()
            break;
    }
}