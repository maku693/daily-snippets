package main

import (
	"image"
)

func main() {
	img := image.NewNRGBA(image.Rect(0, 0, 640, 480))
	var c Camera
	var s Scene
	c.Render(s)
}
