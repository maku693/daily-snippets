package main

import "math"

// A Vec3 represents three-component vector.
type Vec3 [3]float64

// Length returns length (magnitude) of x.
func (x *Vec3) Length() float64 {
	return math.Sqrt(x.Length2())
}

// Length2 returns squared length of x.
func (x *Vec3) Length2() float64 {
	return x.Dot(x)
}

// Normalize sets z to normalized vector of x, and returns it.
func (z *Vec3) Normalize(x *Vec3) *Vec3 {
	return z.Scale(x, 1.0/x.Length())
}

// Add sets component-wize sum of x and y to z, and returns it.
func (z *Vec3) Add(x, y *Vec3) *Vec3 {
	for i := range z {
		z[i] = x[i] + y[i]
	}
	return z
}

// Sub sets component-wize difference of x and y to z, and returns it.
func (z *Vec3) Sub(x, y *Vec3) *Vec3 {
	for i := range z {
		z[i] = x[i] - y[i]
	}
	return z
}

// Scale sets scalar multiplication of x and y to z, and returns it.
func (z *Vec3) Scale(x *Vec3, y float64) *Vec3 {
	for i := range z {
		z[i] = x[i] * y
	}
	return z
}

// Dot returns dot product of x and y.
func (x *Vec3) Dot(y *Vec3) float64 {
	z := float64(0)
	for i := range x {
		z += x[i] * y[i]
	}
	return z
}

// Cross sets cross product of x and y to z, and returns it.
func (z *Vec3) Cross(x, y *Vec3) *Vec3 {
	z[0] = x[1]*y[2] - x[2]*y[1]
	z[1] = x[2]*y[0] - x[0]*y[2]
	z[2] = x[0]*y[1] - x[1]*y[0]
	return z
}
