import createAnimationLoop from './createAnimationLoop.js'

export default function createApp(canvas) {
    const ctx = canvas.getContext('2d')
    let particles = Array.from({length: 10000}, createParticle)
    let debug = false

    const loop = createAnimationLoop(delta => {
        update(delta)
        render()

        if (debug) {
            const text = `${(1000 / delta).toFixed(2)}fps`
            ctx.save()
            ctx.font = 'bold 10px monospace'
            ctx.fillStyle = 'black'
            ctx.fillText(text, 11, 21)
            ctx.fillStyle = 'lime'
            ctx.fillText(text, 10, 20)
            ctx.restore()
        }
    })

    function createParticle() {
        function randomMinMax(min, max) {
            return Math.random() * (max - min) + min
        }
        const norm = randomMinMax(100, 500)
        const angle = Math.random() * Math.PI * 2
        return {
            x: canvas.width * 0.5,
            y: canvas.height * 0.5,
            vx: norm * Math.cos(angle),
            vy: norm * Math.sin(angle),
            life: 1,
        }
    }

    function update(delta) {
        particles = particles.map(particle => {
            if (particle.life < 0) {
                return createParticle()
            }
            particle.x += particle.vx * delta * 0.001
            particle.y += particle.vy * delta * 0.001
            particle.life -= delta * 0.001
            return particle
        })
    }

    function render() {
        ctx.fillStyle = 'black'
        ctx.fillRect(0, 0, canvas.width, canvas.height)
        ctx.fillStyle = 'aqua'
        for (const { x, y } of particles) {
            ctx.fillRect(x - 1, y - 1, 2, 2)
        }
    }

    function run() {
        loop.start()
    }

    function showDebugInformation() {
        debug = true
    }

    return { run, showDebugInformation }
}
