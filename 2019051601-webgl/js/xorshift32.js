export function createXORShift32(seed = 316050595) {
  let value = seed;

  return function() {
    value ^= value << 13;
    value ^= value >> 17;
    value ^= value << 5;
    return value;
  };
}

const INT32_MIN = -2147483647;
const INT32_MAX = 2147483647;
