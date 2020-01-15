package main

import (
	"image"
	"image/color"
)

func main() {
	img := image.NewRGBA(image.Rect(0, 0, 100, 100))
	r := img.Rect
	for h := r.Min.Y; h < r.Max.Y; h++ {
		for v := r.Min.X; v < r.Max.X; v++ {
			img.Set(v, h, color.RGBA{255, 0, 0, 0})
		}
	}
}
