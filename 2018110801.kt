data class Vec3<T: Number>(var x: T, var y: T, var z: T)

fun main() {
    val v = Vec3(1, 2, 3)
    v.x = 10
    println(v)
}
