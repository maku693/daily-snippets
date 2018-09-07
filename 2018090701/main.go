package main

import (
	"image"
	"image/color"
	"math"
	"sync"
)

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
	for i, _ := range z {
		z[i] = x[i] + y[i]
	}
	return z
}

// Sub sets component-wize difference of x and y to z, and returns it.
func (z *Vec3) Sub(x, y *Vec3) *Vec3 {
	for i, _ := range z {
		z[i] = x[i] - y[i]
	}
	return z
}

// Scale sets scalar multiplication of x and y to z, and returns it.
func (z *Vec3) Scale(x *Vec3, y float64) *Vec3 {
	for i, _ := range z {
		z[i] = x[i] * y
	}
	return z
}

// Dot returns dot product of x and y.
func (x *Vec3) Dot(y *Vec3) float64 {
	z := float64(0)
	for i, _ := range z {
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

type Scene struct {
	Objects []Object
	Camera  *Camera
}

func (s Scene) Render() {
	var wg sync.WaitGroup
	img := s.Camera.Film.Image
	b := img.Bounds()
	for x := b.Min.X; x < b.Max.X; x++ {
		for y := b.Min.Y; y < b.Max.Y; y++ {
			wg.Add(1)
			go func(x, y) {
				defer wg.Done()
				c := img.At(x, y)
				for i := 0; i < s.Camera.Config.Samples; i++ {
					// TODO: Generate ray
					var ray Ray
					r1, g1, b1, a1 := c.RGBA()
					r2, g2, b2, a2 := trace(ray, 0)
					c := colors.RGBA{
						R: r1 + r2,
						G: g1 + g2,
						B: b1 + b2,
						A: a1 + a2,
					}
					img.Set(x, y, c)
				}
			}(x, y)
		}
	}
	wg.Wait()
}

func (s Scene) trace(r Ray, d int) color.Color {
}

type Camera struct {
	Position  *Vec3
	Direction *Vec3
	Config    *CameraConfig
}

type CameraConfig struct {
	Film     Film
	FocalLen float64
	Samples  int
}

type Film struct {
	Image  image.Image
	Height float64
	Width  float64
}

type Object interface {
	Expose(Ray) *Intersection
}

type Ray struct {
	Origin    *Vec3
	Direction *Vec3
}

func NewRayThrough(a, b) Ray {
	return Ray{}
}

type Intersection struct {
	Position *Vec3
	Normal   *Vec3
	Material Material
}

type Material interface{}

type Plane struct {
	Center   *Vec3
	Normal   *Vec3
	Material Material
}

func (p Plane) Expose(r Ray) Intersection {
	dn := r.Direction.Dot(p.Normal)
	if 0 < dn {
		return nil
	}

	v := Vec3{}
	v.Sub(r.Origin, p.Center)

	vn := v.Dot(p.Normal)

	t := vn / dn * -1
	if t < 0 {
		return nil
	}

	return Intersection{
		Position: &t,
		Normal:   p.Normal,
		Material: p.Material,
	}
}

type Sphere struct {
	Center   *Vec3
	Radius   float64
	Material Material
}

func (s Sphere) Expose(r Ray) Intersection {
	v := Vec3{}
	v.Sub(r.Origin, p.Center)

	d2 := math.Pow(v.Dot(r.Direction), 2) - (v.Length2() - math.Pow(s.Radius, 2))
	if d < 0 {
		return nil
	}

	d := math.Sqrt(d2)
	t1 := -1*b - d
	t2 := -1*b + d
	if 0 < t1 {
		return s.intersection(r, t1)
	}
	if 0 < t2 {
		return s.intersection(r, t2)
	}

	return nil
}

func (s Sphere) intersection(r Ray, t float64) *Intersection {
	d := r.Direction.Scale(t)

	p := Vec3{}
	p.Add(r.Origin, d)

	n := Vec3{}
	n.Sub(p, s.Center)
	n.Normalize(n)

	return &Intersection{
		Position: t,
		Normal:   n,
		Material: s.Material,
	}
}

func main() {
}
