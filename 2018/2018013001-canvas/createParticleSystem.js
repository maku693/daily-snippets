export default function createParticleSystem(config) {
    const defaultConfig = {
        acceleration: {
            angle: { min: 0, max: 0 },
            speed: { min: 0, max: 0 },
        },
        area: {
            x: { min: 0, max: 0 },
            y: { min: 0, max: 0 },
        },
        maxCount: 0,
        birthRate: 0,
        life: { min: 0, max: 0 },
        velocity: {
            angle: { min: 0, max: 0 },
            speed: { min: 0, max: 0 },
        },
    }

    config = Object.assign(defaultConfig, config)

    let particles = []

    function update(delta) {
        particles = particles.filter(particle => particle.life > 0)

        particles = [
            ...particles,
            ...emit(delta),
        ]
        
        for (let particle of particles) {
            particle.life -= delta * 0.001
            particle.velocity.x += particle.acceleration.x * delta * 0.001
            particle.velocity.y += particle.acceleration.y * delta * 0.001
            particle.position.x += particle.velocity.x * delta * 0.001
            particle.position.y += particle.velocity.y * delta * 0.001
        }
    }

    let numEmittedParticles = 0
    let deltaFromLastEmission = 0

    function emit(delta) {
        if (config.numParticlesToEmit <= numEmittedParticles) {
            return []
        }

        deltaFromLastEmission += delta
        const numNewParticles = config.birthRate * deltaFromLastEmission * 0.001
        if (numNewParticles > 1) {
            deltaFromLastEmission = 0
        }
        numEmittedParticles += numNewParticles
        return Array.from( { length: numNewParticles }, createParticle )
    }

    function createParticle() {
        function randomMinMax(min, max) {
            return Math.random() * (max - min) + min
        }

        function decomposeVector(angle, speed) {
            return {
                x: speed * Math.cos(angle),
                y: speed * Math.sin(angle),
            }
        }

        return {
            acceleration: decomposeVector(
                randomMinMax(config.acceleration.angle.min, config.acceleration.angle.max),
                randomMinMax(config.acceleration.speed.min, config.acceleration.speed.max)
            ),
            life: randomMinMax(config.life.min, config.life.max),
            position: {
                x: randomMinMax(config.area.x.min, config.area.x.max),
                y: randomMinMax(config.area.y.min, config.area.y.max),
            },
            velocity: decomposeVector(
                randomMinMax(config.velocity.angle.min, config.velocity.angle.max),
                randomMinMax(config.velocity.speed.min, config.velocity.speed.max)
            ),
        }
    }

    function getParticles() {
        return particles
    }

    return { getParticles, update }
}