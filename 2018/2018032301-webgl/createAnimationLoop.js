export default function createAnimationLoop(cb) {
    let requestID = undefined

    function start(timestamp = 0) {
        requestID = requestAnimationFrame(start)
        cb(timestamp)
    }

    function stop() {
        cancelAnimationFrame(requestID)
    }

    return { start, stop }
}