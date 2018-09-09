package main

type Ray struct {
	Origin    Vec3
	Direction Vec3
}

func NewRayThrough(a Vec3, b Vec3) *Ray {
	return &Ray{}
}
