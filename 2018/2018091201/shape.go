package main

import "math"

type Shape interface {
	Expose(Ray) *Intersection
}

type Intersection struct {
	Position *Vec3
	Normal   *Vec3
}

type Plane struct {
	Center *Vec3
	Normal *Vec3
}

func (p *Plane) Expose(r Ray) *Intersection {
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

	var pos *Vec3
	pos.Scale(r.Direction, t)
	pos.Add(r.Origin, pos)

	return &Intersection{
		Position: pos,
		Normal:   p.Normal,
	}
}

type Sphere struct {
	Center *Vec3
	Radius float64
}

func (s *Sphere) Expose(r Ray) *Intersection {
	v := Vec3{}
	v.Sub(r.Origin, s.Center)

	d2 := math.Pow(v.Dot(r.Direction), 2) - (v.Length2() - math.Pow(s.Radius, 2))
	if d2 < 0 {
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
	var d *Vec3
	d.Scale(r.Direction, t)

	var p *Vec3
	p.Add(r.Origin, d)

	var n *Vec3
	n.Sub(p, s.Center)
	n.Normalize(n)

	var pos *Vec3
	pos.Scale(r.Direction, t)
	pos.Add(r.Origin, pos)

	return &Intersection{
		Position: pos,
		Normal:   n,
	}
}
