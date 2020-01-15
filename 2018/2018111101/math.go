package math

import "math"

// A Vec3 represents three-component vector.
type Vec3 [3]float64

// Length returns length (magnitude) of v.
func (v *Vec3) Length() float64 {
	return math.Sqrt(v.Length2())
}

// Length2 returns squared length of v.
func (v *Vec3) Length2() float64 {
	return v.Dot(v)
}

// Normalize sets v to normalized vector of x, and returns it.
func (v *Vec3) Normalize(x *Vec3) *Vec3 {
	return v.Scale(x, 1.0/x.Length())
}

// Add sets component-wize sum of x and y to v, and returns it.
func (v *Vec3) Add(x, y *Vec3) *Vec3 {
	for i := range v {
		v[i] = x[i] + y[i]
	}
	return v
}

// Sub sets component-wize difference of x and y to v, and returns it.
func (v *Vec3) Sub(x, y *Vec3) *Vec3 {
	for i := range v {
		v[i] = x[i] - y[i]
	}
	return v
}

// Scale sets scalar multiplication of x and y to v, and returns it.
func (v *Vec3) Scale(x *Vec3, y float64) *Vec3 {
	for i := range v {
		v[i] = x[i] * y
	}
	return v
}

// Dot returns dot product of v and x.
func (v *Vec3) Dot(x *Vec3) float64 {
	f := float64(0)
	for i := range v {
		f += v[i] * x[i]
	}
	return f
}

// Cross sets cross product of x and y to v, and returns it.
func (v *Vec3) Cross(x, y *Vec3) *Vec3 {
	v[0] = x[1]*y[2] - x[2]*y[1]
	v[1] = x[2]*y[0] - x[0]*y[2]
	v[2] = x[0]*y[1] - x[1]*y[0]
	return v
}
