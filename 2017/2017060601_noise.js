const fade = t => t * t * t * (t * (t * 6 - 15) + 10)
const grad = x => Math.random()
const lerp = (x, a, b) => a + x * (b - a)

const noise1D = x => {
  const gx = x % 1
  const dx = x - Math.floor(x)
  const u = fade(dx);
  return lerp(u, grad(gx, x), grad(gx + 1, x-1));
}
