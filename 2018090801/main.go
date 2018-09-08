package main

import (
	"image"
)

func main() {
	img := image.NewNRGBA(image.Rect(0, 0, 640, 480))
	s := Scene{
		Camera:  nil,
		Objects: nil,
	}
	s.RenderTo(img)
}
