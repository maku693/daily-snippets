export default function createMat4(array) {
  return new Float32Array(array && array.length == 16 ? array : 16)
}

export function multiply(lhs, rhs) {
  const l = lhs, r = rhs
  return createMat4([
      l[0] * r[0]  + l[4] * r[1]  + l[8]  * r[2]  + l[12] * r[3],
      l[1] * r[0]  + l[5] * r[1]  + l[9]  * r[2]  + l[13] * r[3],
      l[2] * r[0]  + l[6] * r[1]  + l[10] * r[2]  + l[14] * r[3],
      l[3] * r[0]  + l[7] * r[1]  + l[11] * r[2]  + l[15] * r[3],
      l[0] * r[4]  + l[4] * r[5]  + l[8]  * r[6]  + l[12] * r[7],
      l[1] * r[4]  + l[5] * r[5]  + l[9]  * r[6]  + l[13] * r[7],
      l[2] * r[4]  + l[6] * r[5]  + l[10] * r[6]  + l[14] * r[7],
      l[3] * r[4]  + l[7] * r[5]  + l[11] * r[6]  + l[15] * r[7],
      l[0] * r[8]  + l[4] * r[9]  + l[8]  * r[10] + l[12] * r[11],
      l[1] * r[8]  + l[5] * r[9]  + l[9]  * r[10] + l[13] * r[11],
      l[2] * r[8]  + l[6] * r[9]  + l[10] * r[10] + l[14] * r[11],
      l[3] * r[8]  + l[7] * r[9]  + l[11] * r[10] + l[15] * r[11],
      l[0] * r[12] + l[4] * r[13] + l[8]  * r[14] + l[12] * r[15],
      l[1] * r[12] + l[5] * r[13] + l[9]  * r[14] + l[13] * r[15],
      l[2] * r[12] + l[6] * r[13] + l[10] * r[14] + l[14] * r[15],
      l[3] * r[12] + l[7] * r[13] + l[11] * r[14] + l[15] * r[15],
  ])
}

export function createIdentityMat4() {
  return createMat4([
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1,
  ])
}

export function createTranslateMat4(movement) {
  const m14 = movement[0], m24 = movement[1], m34 = movement[2]
  return createMat4([
    1,   0,   0,   0,
    0,   1,   0,   0,
    0,   0,   1,   0,
    m14, m24, m34, 1,
  ])
}

export function createRotateMat4(axis, rad) {
  const x = axis[0],
    y = axis[1],
    z = axis[2]
  const sin = Math.sin(rad),
    cos = Math.cos(rad)
  const a = (1 - cos)
  const
    m11 = x * x * a + cos,
    m12 = x * y * a + y * sin,
    m13 = x * z * a + z * sin,
    m21 = y * x * a + z * sin,
    m22 = y * y * a + cos,
    m23 = y * z * a + x * sin,
    m31 = z * x * a + y * sin,
    m32 = z * y * a + x * sin,
    m33 = z * z * a + cos
  return createMat4([
    m11, m21, m31, 0,
    m12, m22, m33, 0,
    m13, m23, m33, 0,
    0,   0,   0,   1,
  ])
}

export function createYRotateMat4(rad) {
  const s = Math.sin(rad)
  const c = Math.cos(rad)

  return createMat4([
    c, 0, -s, 0,
    0, 1, 0, 0,
    s, 0, c, 0,
    0, 0, 0, 1,
  ])
}

export function createXRotateMat4(rad) {
  const s = Math.sin(rad)
  const c = Math.cos(rad)

  return createMat4([
    1, 0, 0, 0,
    0, c, s, 0,
    0, -s, c, 0,
    0, 0, 0, 1,
  ])
}

export function createScaleMat4(factor) {
  const m11 = factor[0], m22 = factor[1], m33 = factor[2]
  return createMat4([
    m11, 0,   0,   0,
    0,   m22, 0,   0,
    0,   0,   m33, 0,
    0,   0,   0,   1,
  ])
}

export function createLookAtMat4(camera, target, up) {
  // TODO:
}

export function createPersepectiveMat4(fovy, aspect, near, far) {
  const f = 1 / Math.tan(fovy * 0.5),
    nf = 1 / (near - far)
  const m11 = f / aspect,
    m22 = f,
    m33 = (near + far) * nf,
    m34 = near * far * nf * 2
  return createMat4([
    m11, 0,   0,   0,
    0,   m22, 0,   0,
    0,   0,   m33, -1,
    0,   0,   m34, 0,
  ])
}

export function createOrthographicMat4(left, right, top, bottom, near, far) {
  const m11 = 2 / (right - left),
    m22 = 2 / (top - bottom),
    m33 = 2 / (far - near),
    m14 = (right + left) / (left - right),
    m24 = (top + bottom) / (bottom - top),
    m34 = (far + near) / (near - far)
  return createMat4([
    m11, 0,   0,   0,
    0,   m22, 0,   0,
    0,   0,   m33, 0,
    m14, m24, m34, 1,
  ])
}
