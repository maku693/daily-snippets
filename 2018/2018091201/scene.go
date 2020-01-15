package main

import "image/color"

type Scene []Object

func (s Scene) trace(r Ray, d int) color.Color {
	for _, o := range s {
		i := o.Shape.Expose(r)
		if i == nil {
			return color.RGBA{}
		}
	}
}
