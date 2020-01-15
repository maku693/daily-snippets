package main

import "image/color"

type Material interface {
	Color(Vec3) color.Color
}
