package main

import "image/draw"

type Camera struct {
	Position  Vec3
	Direction Vec3
	FocalLen  float64
	Samples   int
	Film      draw.Image
}

func (c Camera) NextRay() bool {}
