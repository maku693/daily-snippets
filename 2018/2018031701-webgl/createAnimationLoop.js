export default function createAnimationLoop(cb) {
    let requestID = undefined

    function start(timestamp) {
        requestID = requestAnimationFrame(start)
        cb(timestamp)
    }

    function stop() {
        cancelAnimationFrame(requestID)
    }

    return { start, stop }
}

export function timestampToDelta(cb) {
  let lastTimestamp = 0

  return function(timestamp) {
    const delta = timestamp - lastTimestamp
    lastTimestamp = timestamp

    cb(delta)
  }
}
