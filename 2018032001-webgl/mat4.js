export default function createMat4(array) {
  return new Float32Array(array && array.length == 16 ? array : 16)
}

// 11 21
// 12 22
//
// l11 * r11 + l12 * r21
// l21 * r11 + l22 * r21
// l11 * r12 + l12 * r22
// l21 * r12 + l22 * r22

// 11 21 31
// 12 22 32
// 13 23 33
//
// l11 * r11 + l12 * r21 + l13 * r31
// l21 * r11 + l22 * r21 + l23 * r31
// l31 * r11 + l32 * r21 + l33 * r31
// l11 * r12 + l12 * r22 + l13 * r32
// l21 * r12 + l22 * r22 + l23 * r32
// l31 * r12 + l32 * r22 + l33 * r32
// l11 * r13 + l12 * r23 + l13 * r33
// l21 * r13 + l22 * r23 + l23 * r33
// l31 * r13 + l32 * r23 + l33 * r33

// 11 21 31 41 |  0  1  2  3
// 12 22 32 42 |  4  5  6  7
// 13 23 33 43 |  8  9 10 11
// 14 24 34 44 | 12 13 14 15
//
// l11 * r11 + l12 * r21 + l13 * r31 + l14 * r41
// l21 * r11 + l22 * r21 + l24 * r31 + l24 * r41
// l31 * r11 + l32 * r21 + l34 * r31 + l34 * r41
// l41 * r11 + l42 * r21 + l44 * r31 + l44 * r41
// l11 * r12 + l12 * r22 + l13 * r32 + l14 * r42
// l21 * r12 + l22 * r22 + l24 * r32 + l24 * r42
// l31 * r12 + l32 * r22 + l34 * r32 + l34 * r42
// l41 * r12 + l42 * r22 + l44 * r32 + l44 * r42
// l11 * r13 + l12 * r23 + l13 * r33 + l14 * r43
// l21 * r13 + l22 * r23 + l24 * r33 + l24 * r43
// l31 * r13 + l32 * r23 + l34 * r33 + l34 * r43
// l41 * r13 + l42 * r23 + l44 * r33 + l44 * r43
// l11 * r14 + l12 * r24 + l13 * r34 + l14 * r44
// l21 * r14 + l22 * r24 + l24 * r34 + l24 * r44
// l31 * r14 + l32 * r24 + l34 * r34 + l34 * r44
// l41 * r14 + l42 * r24 + l44 * r34 + l44 * r44

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
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0,
  ])
}

export function createTranslateMat4(movement) {
  const m14 = movement[0], m24 = movement[1], m34 = movement[2]
  return createMat4([
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    m14, m24, m34, 1.0,
  ])
}

export function createRotateMat4(axis, rad) {
  // TODO:
}

export function createScaleMat4(factor) {
  const m11 = factor[0], m22 = factor[1], m33 = factor[2]
  return createMat4([
    m11, 0.0, 0.0, 0.0,
    0.0, m22, 0.0, 0.0,
    0.0, 0.0, m33, 0.0,
    0.0, 0.0, 0.0, 1.0,
  ])
  // [0.004, 0, 0, 0,
  //  0, 0.004, 0, 0,
  //  0, 0, -0.1, 0,
  //  -1, -1, 0, 1]
}

export function createLookAtMat4(camera, target, up) {
  // TODO:
}

export function createPersepectiveMat4(fovy, aspect, near, far) {
  // TODO:
}

export function createOrthographicMat4(left, right, top, bottom, near, far) {
  const m11 = 2 / (right - left),
    m22 = 2 / (bottom - top),
    m33 = 2 / (far - near),
    m14 = (left + right) / (left - right),
    m24 = (top + bottom) / (top - bottom),
    m34 = (near + far) / (near - far)
  return createMat4([
    m11, 0.0, 0.0, 0.0,
    0.0, m22, 0.0, 0.0,
    0.0, 0.0, m33, 0.0,
    m14, m24, m34, 1.0,
  ])
}