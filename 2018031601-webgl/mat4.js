export default function createMat4(array) {
    let values = new Float32Array(array && array.length == 16 ? array : 16)

    function toFloat32Array() {
        return values
    }

    function transform(movement) {
        // TODO:
    }

    function rotate(axis, rad) {
        // TODO:
    }

    function scale(factor) {
        // TODO:
    }

    function lookAt(camera, target, up) {
        // TODO:
    }

    function persepective(fovy, aspect, near, far) {
        // TODO:
    }

    function multiply(other) {
        const a0  = values[0],  a1  = values[1],  a2  = values[2],  a3  = values[3],
              a4  = values[4],  a5  = values[5],  a6  = values[6],  a7  = values[7],
              a8  = values[8],  a9  = values[9],  a10 = values[10], a11 = values[11],
              a12 = values[12], a13 = values[13], a14 = values[14], a15 = values[15]
        const b0  = other[0],   b1  = other[1],   b2  = other[2],   b3  = other[3],
              b4  = other[4],   b5  = other[5],   b6  = other[6],   b7  = other[7],
              b8  = other[8],   b9  = other[9],   b10 = other[10],  b11 = other[11],
              b12 = other[12],  b13 = other[13],  b14 = other[14],  b15 = other[15]

        return createMat4([
            a0  * b0  + a1  * b4  + a2  * b8  + a3  * b12,
            a0  * b1  + a1  * b5  + a2  * b9  + a3  * b13,
            a0  * b2  + a1  * b6  + a2  * b10 + a3  * b14,
            a0  * b3  + a1  * b7  + a2  * b11 + a3  * b15,
            a4  * b0  + a5  * b4  + a6  * b8  + a7  * b12,
            a4  * b1  + a5  * b5  + a6  * b9  + a7  * b13,
            a4  * b2  + a5  * b6  + a6  * b10 + a7  * b14,
            a4  * b3  + a5  * b7  + a6  * b11 + a7  * b15,
            a8  * b0  + a9  * b4  + a10 * b8  + a11 * b12,
            a8  * b1  + a9  * b5  + a10 * b9  + a11 * b13,
            a8  * b2  + a9  * b6  + a10 * b10 + a11 * b14,
            a8  * b3  + a9  * b7  + a10 * b11 + a11 * b15,
            a12 * b0  + a13 * b4  + a14 * b8  + a15 * b12,
            a12 * b1  + a13 * b5  + a14 * b9  + a15 * b13,
            a12 * b2  + a13 * b6  + a14 * b10 + a15 * b14,
            a12 * b3  + a13 * b7  + a14 * b11 + a15 * b15,
        ])
    }

    return {
        toFloat32Array,
        transform,
        rotate,
        scale,
        lookAt,
        persepective,
        multiply,
    }
}

export function createIdentityMat4() {
    return createMat4([
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0,
    ])
}