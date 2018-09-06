package main

type vec3 [3]float32
type mat4 [4][4]float32

type camera struct {
	transform mat4
	focalLen  float32
}
type material struct{}

type object interface {
	intersect(ray) hit
}

type ray struct {
	origin    vec3
	direction vec3
}

type hit struct {
	position vec3
	normal   vec3
}

func main() {
}
