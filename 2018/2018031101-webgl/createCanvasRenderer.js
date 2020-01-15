import createAnimationLoop from './createAnimationLoop.js'

export default function createCanvasRenderer(context, draw = () => {}) {
    let lastTimestamp = 0

    const loop = createAnimationLoop(timestamp => {
        const delta = timestamp - lastTimestamp
        lastTimestamp = timestamp

        draw(delta)
    })

    function start() {
        lastTimestamp = performance.now()
        loop.start(lastTimestamp)
    }

    function stop() {
        loop.stop()
    }

    return { start, stop }
}
