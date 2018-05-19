#include <vector>
#include <optional>

struct mat4;

struct scene;

struct node;

struct camera;

struct mesh;
struct material;

struct buffer;
struct buffer_view;

struct scene {
    std::vector<node> children;
};

struct node {
    mat4 matrix;
    std::optional<camera> camera;
    std::optional<mesh> mesh;
    std::vector<node> children;
};
