protocol Material {}
protocol Geometry {}

struct Object {
    var geometry: Geometry
    var material: Material
}

struct Scene {
    var objects: [Object]
}
