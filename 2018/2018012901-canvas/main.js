import createCanvas2DApp from './createCanvas2DApp.js'
import createParticleSystem from './createParticleSystem.js'

const ctx = c.getContext('2d')

function createParticleSystemConfig() {
    return {
        acceleration: { 
            angle: { min: Math.PI * 0.5, max: Math.PI * 0.5 },
            speed: { min: 500, max: 500 },
        },
        area: {
            x: { min: 240, max: 260 },
            y: { min: 200, max: 220 },
        },
        birthRate: 1000,
        life: { min: 2, max: 2 },
        velocity: {
            angle: { min: Math.PI * -0.6, max: Math.PI * -0.4 },
            speed: { min: 100, max: 200 },
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