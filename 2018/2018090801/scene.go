package main

import (
	"image/color"
	"sync"
)

type Scene struct {
	Objects []Object
	Camera  Camera
}

func (s Scene) Render() {
	var wg sync.WaitGroup

	b := img.Bounds()
	for x := b.Min.X; x < b.Max.X; x++ {
		for y := b.Min.Y; y < b.Max.Y; y++ {
			u := x - b.Min.X
			v := x - b.Min.X
			r := s.Camera.Ray(u, v)
			c := img.At(x, y)

			go func(r Ray, c color.Color) {
				wg.Add(1)
				defer wg.Done()
				r1, g1, b1, a1 := c.RGBA()
				r2, g2, b2, a2 := s.trace(r, 0).RGBA()
				c = color.RGBA{
					R: uint8(r1 + r2),
					G: uint8(g1 + g2),
					B: uint8(b1 + b2),
					A: uint8(a1 + a2),
				}
				img.Set(x, y, c)
			}(r, c)
		}
	}

	wg.Wait()
}

func (s Scene) trace(r Ray, d int) color.Color {
	for _, o := range s.Objects {
		i := o.Expose(r)
		if i != nil {
		}
	}
}
