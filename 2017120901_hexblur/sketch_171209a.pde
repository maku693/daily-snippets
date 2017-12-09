PImage image;
PShader filter;

void setup() {
  size(500, 500, P2D);
  image = loadImage("image.png");
  filter = loadShader("filter.glsl");
  filter.set("resolution", float(width), float(height));
}

void draw() {
  image(image, 0, 0);
  filter(filter);
}