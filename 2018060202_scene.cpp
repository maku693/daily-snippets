#include <optional>
#include <vector>

struct mat4 {};
struct vec3 {};

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

struct camera {
    float yfov, aspect, znear, zfar;
};

struct mesh {
};
