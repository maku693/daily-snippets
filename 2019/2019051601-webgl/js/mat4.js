export function create() {
  const mat = new Float32Array(16);
  identity(mat);
  return mat;
}

export function multiply(out, l, r) {
  const m11 = l[0] * r[0] + l[4] * r[1] + l[8] * r[2] + l[12] * r[3];
  const m21 = l[1] * r[0] + l[5] * r[1] + l[9] * r[2] + l[13] * r[3];
  const m31 = l[2] * r[0] + l[6] * r[1] + l[10] * r[2] + l[14] * r[3];
  const m41 = l[3] * r[0] + l[7] * r[1] + l[11] * r[2] + l[15] * r[3];
  const m12 = l[0] * r[4] + l[4] * r[5] + l[8] * r[6] + l[12] * r[7];
  const m22 = l[1] * r[4] + l[5] * r[5] + l[9] * r[6] + l[13] * r[7];
  const m32 = l[2] * r[4] + l[6] * r[5] + l[10] * r[6] + l[14] * r[7];
  const m42 = l[3] * r[4] + l[7] * r[5] + l[11] * r[6] + l[15] * r[7];
  const m13 = l[0] * r[8] + l[4] * r[9] + l[8] * r[10] + l[12] * r[11];
  const m23 = l[1] * r[8] + l[5] * r[9] + l[9] * r[10] + l[13] * r[11];
  const m33 = l[2] * r[8] + l[6] * r[9] + l[10] * r[10] + l[14] * r[11];
  const m43 = l[3] * r[8] + l[7] * r[9] + l[11] * r[10] + l[15] * r[11];
  const m14 = l[0] * r[12] + l[4] * r[13] + l[8] * r[14] + l[12] * r[15];
  const m24 = l[1] * r[12] + l[5] * r[13] + l[9] * r[14] + l[13] * r[15];
  const m34 = l[2] * r[12] + l[6] * r[13] + l[10] * r[14] + l[14] * r[15];
  const m44 = l[3] * r[12] + l[7] * r[13] + l[11] * r[14] + l[15] * r[15];
  out[0] = m11;
  out[1] = m21;
  out[2] = m31;
  out[3] = m41;
  out[4] = m12;
  out[5] = m22;
  out[6] = m32;
  out[7] = m42;
  out[8] = m13;
  out[9] = m23;
  out[10] = m33;
  out[11] = m43;
  out[12] = m14;
  out[13] = m24;
  out[14] = m34;
  out[15] = m44;
  return out;
}

export function identity(out) {
  out[0] = 1;
  out[1] = 0;
  out[2] = 0;
  out[3] = 0;
  out[4] = 0;
  out[5] = 1;
  out[6] = 0;
  out[7] = 0;
  out[8] = 0;
  out[9] = 0;
  out[10] = 1;
  out[11] = 0;
  out[12] = 0;
  out[13] = 0;
  out[14] = 0;
  out[15] = 1;
  return out;
}

export function translate(out, movement) {
  out[0] = 1;
  out[1] = 0;
  out[2] = 0;
  out[3] = 0;
  out[4] = 0;
  out[5] = 1;
  out[6] = 0;
  out[7] = 0;
  out[8] = 0;
  out[9] = 0;
  out[10] = 1;
  out[11] = 0;
  out[12] = movement[0];
  out[13] = movement[1];
  out[14] = movement[2];
  out[15] = 1;

  return out;
}

export function rotate(out, axis, rad) {
  const x = axis[0],
    y = axis[1],
    z = axis[2];
  const sin = Math.sin(rad),
    cos = Math.cos(rad);
  const a = 1 - cos;
  const m11 = x * x * a + cos,
    m21 = x * y * a - z * sin,
    m31 = x * z * a + y * sin,
    m12 = y * x * a + z * sin,
    m22 = y * y * a + cos,
    m32 = y * z * a - x * sin,
    m13 = z * x * a - y * sin,
    m23 = z * y * a + x * sin,
    m33 = z * z * a + cos;

  out[0] = m11;
  out[1] = m21;
  out[2] = m31;
  out[3] = 0;
  out[4] = m12;
  out[5] = m22;
  out[6] = m32;
  out[7] = 0;
  out[8] = m13;
  out[9] = m23;
  out[10] = m33;
  out[11] = 0;
  out[12] = 0;
  out[13] = 0;
  out[14] = 0;
  out[15] = 1;

  return out;
}

export function scale(out, factor) {
  const m11 = factor[0],
    m22 = factor[1],
    m33 = factor[2];

  out[0] = m11;
  out[1] = 0;
  out[2] = 0;
  out[3] = 0;
  out[4] = 0;
  out[5] = m22;
  out[6] = 0;
  out[7] = 0;
  out[8] = 0;
  out[9] = 0;
  out[10] = m33;
  out[11] = 0;
  out[12] = 0;
  out[13] = 0;
  out[14] = 0;
  out[15] = 1;

  return out;
}

export function perspective(out, fovy, aspect, near, far) {
  const f = 1 / Math.tan(fovy * 0.5),
    nf = 1 / (near - far);
  const m11 = f / aspect,
    m22 = f,
    m33 = (near + far) * nf,
    m34 = near * far * nf * 2;

  out[0] = m11;
  out[1] = 0;
  out[2] = 0;
  out[3] = 0;
  out[4] = 0;
  out[5] = m22;
  out[6] = 0;
  out[7] = 0;
  out[8] = 0;
  out[9] = 0;
  out[10] = m33;
  out[11] = -1;
  out[12] = 0;
  out[13] = 0;
  out[14] = m34;
  out[15] = 0;

  return out;
}

export function orthographic(out, left, right, top, bottom, near, far) {
  const m11 = 2 / (right - left),
    m22 = 2 / (top - bottom),
    m33 = 2 / (far - near),
    m14 = (right + left) / (left - right),
    m24 = (top + bottom) / (bottom - top),
    m34 = (far + near) / (near - far);

  out[0] = m11;
  out[1] = 0;
  out[2] = 0;
  out[3] = 0;
  out[4] = 0;
  out[5] = m22;
  out[6] = 0;
  out[7] = 0;
  out[8] = 0;
  out[9] = 0;
  out[10] = m33;
  out[11] = 0;
  out[12] = m14;
  out[13] = m24;
  out[14] = m34;
  out[15] = 1;

  return out;
}

export function lookAt(out, eye, target, up) {}
