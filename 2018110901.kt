import kotlin.math.sqrt

data class Vec3(var x: Double, var y: Double, var z: Double) {
    fun unaryMinus() = Vec3(-x, -y, -z)

    fun plus(other: Vec3) = Vec3(x + other.x, y + other.y, z + other.z)
    fun minus(other: Vec3) = Vec3(x - other.x, y - other.y, z - other.z)

    infix fun scale(multiplier: Double) = Vec3(
        x * multiplier,
        y * multiplier,
        z * multiplier
    )
    infix fun dot(other: Vec3) = x * other.x + y * other.y + z * other.z
    infix fun cross(other: Vec3) = Vec3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    )

    fun length2() = this dot this
    fun length() = sqrt(length2())
    fun normalized() = this scale 1 / length()
}

fun main() {
    println(Vec3(1.0, 0.0, 0.0) dot Vec3(1.0, 0.0, 0.0))
    println(Vec3(4.2, 0.0, 0.0).normalized())
}
