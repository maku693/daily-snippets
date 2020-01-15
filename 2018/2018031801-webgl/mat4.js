export default function createMat4(array) {
    return new Float32Array(array && array.length == 16 ? array : 16)
}

export function multiply(lhs, rhs) {
    const l = lhs, r = rhs
    return createMat4([
        l[0]  * r[0]  + l[1]  * r[4]  + l[2]  * r[8]  + l[3]  * r[12],
        l[0]  * r[1]  + l[1]  * r[5]  + l[2]  * r[9]  + l[3]  * r[13],
        l[0]  * r[2]  + l[1]  * r[6]  + l[2]  * r[10] + l[3]  * r[14],
        l[0]  * r[3]  + l[1]  * r[7]  + l[2]  * r[11] + l[3]  * r[15],
        l[4]  * r[0]  + l[5]  * r[4]  + l[6]  * r[8]  + l[7]  * r[12],
        l[4]  * r[1]  + l[5]  * r[5]  + l[6]  * r[9]  + l[7]  * r[13],
        l[4]  * r[2]  + l[5]  * r[6]  + l[6]  * r[10] + l[7]  * r[14],
        l[4]  * r[3]  + l[5]  * r[7]  + l[6]  * r[11] + l[7]  * r[15],
        l[8]  * r[0]  + l[9]  * r[4]  + l[10] * r[8]  + l[11] * r[12],
        l[8]  * r[1]  + l[9]  * r[5]  + l[10] * r[9]  + l[11] * r[13],
        l[8]  * r[2]  + l[9]  * r[6]  + l[10] * r[10] + l[11] * r[14],
        l[8]  * r[3]  + l[9]  * r[7]  + l[10] * r[11] + l[11] * r[15],
        l[12] * r[0]  + l[13] * r[4]  + l[14] * r[8]  + l[15] * r[12],
        l[12] * r[1]  + l[13] * r[5]  + l[14] * r[9]  + l[15] * r[13],
        l[12] * r[2]  + l[13] * r[6]  + l[14] * r[10] + l[15] * r[14],
        l[12] * r[3]  + l[13] * r[7]  + l[14] * r[11] + l[15] * r[15],
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

export function createTransformMat4(movement) {
    const m41 = movement[0], m42 = movement[1], m43 = movement[2]
    return createMat4([
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        m41, m42, m43, 1.0,
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
}

export function createLookAtMat4(camera, target, up) {
    // TODO:
}

export function createPersepectiveMat4(fovy, aspect, near, far) {
    // TODO:
}