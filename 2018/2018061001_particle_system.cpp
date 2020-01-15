using float3 = float[3];

struct particle {
  float life;
  float3 accel;
  float3 position;
};

template <class T> struct value_range {
  T min;
  T max;
};

class particle_system {
public:
private:
  float max_particles_;
  float birth_rate_;
  float3 spawn_area_;
  value_range<float> life_;
  value_range<float3> initial_accel_;
  value_range<float3> initial_velocity_;
};
