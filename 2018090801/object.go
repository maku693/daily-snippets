package main

type Object struct {
	Shape    Shape
	Material Material
}

func (o Object) Trace() Ray {
}
