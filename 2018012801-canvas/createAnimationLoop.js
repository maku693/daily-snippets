export default function createAnimationLoop(cb) {
    let requestID = undefined
    let lastTimestamp = 0
    
    function start(timestamp = 0) {
        requestID = requestAnimationFrame(start)
        const delta = timestamp - lastTimestamp
        cb(delta)
        lastTimestamp = timestamp
    }

    function stop() {
        cancelAnimationFrame(requestID)
    }

    return { start, stop }
}