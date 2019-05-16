import { createXORShift32 } from "./xorshift32.js";

export function createPerlinNoise1D(cellSize, repeat, seed) {
  const randomValues = createRandomValues(seed);
  function rand(x) {
    return randomValues[Math.abs(x) % randomValues.length];
  }
  function grad(i) {
    return [1, -1][rand(i) % 2];
  }
  return function(x) {
    const x_ = (x / cellSize) % repeat;
    const i = Math.floor(x_) % repeat;
    const i_ = Math.ceil(x_) % repeat;
    const xf = x_ - i;
    const u = fade(xf);
    const gi = grad(i);
    const gi_ = grad(i_);
    const a0 = gi * xf;
    const a1 = gi_ * (xf - 1);
    return lerp(u, a0, a1);
  };
}

const centerToEdge2D = Object.freeze([
  { x: 1, y: 0 },
  { x: -1, y: 0 },
  { x: 0, y: 1 },
  { x: 0, y: -1 }
]);
export function createPerlinNoise2D(cellSize, repeat, seed) {
  const randomValues = createRandomValues(seed);
  function rand(x, y) {
    const x_ = Math.abs(x);
    const y_ = Math.abs(y);
    const randX = randomValues[x_ % randomValues.length];
    return randomValues[(randX + y_) % randomValues.length];
  }
  function grad(i, j) {
    return centerToEdge2D[rand(i, j) % centerToEdge2D.length];
  }
  return function(x, y) {
    const x_ = (x / cellSize) % repeat;
    const y_ = (y / cellSize) % repeat;
    const i = Math.floor(x_) % repeat;
    const i_ = Math.ceil(x_) % repeat;
    const j = Math.floor(y_) % repeat;
    const j_ = Math.ceil(y_) % repeat;
    const xf = x_ - Math.floor(x_);
    const yf = y_ - Math.floor(y_);
    const u = fade(xf);
    const v = fade(yf);
    const g00 = grad(i, j);
    const g01 = grad(i, j_);
    const g10 = grad(i_, j);
    const g11 = grad(i_, j_);
    const a00 = g00.x * xf + g00.y * yf;
    const a01 = g01.x * xf + g01.y * (yf - 1);
    const a10 = g10.x * (xf - 1) + g10.y * yf;
    const a11 = g11.x * (xf - 1) + g11.y * (yf - 1);
    return lerp(v, lerp(u, a00, a10), lerp(u, a01, a11));
  };
}

const centerToEdge3D = Object.freeze([
  { x: 1, y: 1, z: 0 },
  { x: -1, y: 1, z: 0 },
  { x: 1, y: -1, z: 0 },
  { x: -1, y: -1, z: 0 },
  { x: 1, y: 0, z: 1 },
  { x: -1, y: 0, z: 1 },
  { x: 1, y: 0, z: -1 },
  { x: -1, y: 0, z: -1 },
  { x: 0, y: 1, z: 1 },
  { x: 0, y: -1, z: 1 },
  { x: 0, y: 1, z: -1 },
  { x: 0, y: -1, z: -1 }
]);
export function createPerlinNoise3D(cellSize, repeat, seed) {
  const randomValues = createRandomValues(seed);
  function rand(x, y, z) {
    const x_ = Math.abs(x);
    const y_ = Math.abs(y);
    const z_ = Math.abs(z);
    const randX = randomValues[x_ % randomValues.length];
    const randY = randomValues[(randX + y_) % randomValues.length];
    return randomValues[(randY + z_) % randomValues.length];
  }
  function grad(i, j, k) {
    return centerToEdge3D[rand(i, j, k) % centerToEdge3D.length];
  }
  return function(x, y, z) {
    const x_ = (x / cellSize) % repeat;
    const y_ = (y / cellSize) % repeat;
    const z_ = (z / cellSize) % repeat;
    const i = Math.floor(x_) % repeat;
    const i_ = Math.ceil(x_) % repeat;
    const j = Math.floor(y_) % repeat;
    const j_ = Math.ceil(y_) % repeat;
    const k = Math.floor(z_) % repeat;
    const k_ = Math.ceil(z_) % repeat;
    const xf = x_ - Math.floor(x_);
    const yf = y_ - Math.floor(y_);
    const zf = z_ - Math.floor(z_);
    const u = fade(xf);
    const v = fade(yf);
    const w = fade(zf);
    const g000 = grad(i, j, k);
    const g001 = grad(i, j, k_);
    const g010 = grad(i, j_, k);
    const g011 = grad(i, j_, k_);
    const g100 = grad(i_, j, k);
    const g101 = grad(i_, j, k_);
    const g110 = grad(i_, j_, k);
    const g111 = grad(i_, j_, k_);
    const a000 = g000.x * xf + g000.y * yf + g000.z * zf;
    const a001 = g001.x * xf + g001.y * yf + g001.z * (zf - 1);
    const a010 = g010.x * xf + g010.y * (yf - 1) + g010.z * zf;
    const a011 = g011.x * xf + g011.y * (yf - 1) + g011.z * (zf - 1);
    const a100 = g100.x * (xf - 1) + g100.y * yf + g100.z * zf;
    const a101 = g101.x * (xf - 1) + g101.y * yf + g101.z * (zf - 1);
    const a110 = g110.x * (xf - 1) + g110.y * (yf - 1) + g110.z * zf;
    const a111 = g111.x * (xf - 1) + g111.y * (yf - 1) + g111.z * (zf - 1);
    return lerp(
      w,
      lerp(v, lerp(u, a000, a100), lerp(u, a010, a110)),
      lerp(v, lerp(u, a001, a101), lerp(u, a011, a111))
    );
  };
}

function createRandomValues(seed) {
  const rng = createXORShift32(seed);
  const rand = new Array(256);
  for (let i = 0; i < rand.length; i++) {
    rand[i] = Math.abs(rng());
  }
  return rand;
}

function lerp(t, x, y) {
  return x + t * (y - x);
}

function fade(t) {
  return t * t * t * (t * (t * 6 - 15) + 10);
}
