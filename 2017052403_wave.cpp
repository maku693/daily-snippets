#include <cstdint>
#include <iostream>

int main()
{
    const size_t sampling_rate = 48000;
    const size_t buffer_duration = 1;

    const size_t wave_size = sampling_rate * buffer_duration;
    auto wave = new uint16_t[wave_size];

    for (int i = 0; i < wave_size; i++) {
        wave[i] = (i % 100) * 100;
    }

    std::cout.write(
        reinterpret_cast<char *>(wave),
        sizeof(uint16_t) / sizeof(char) * wave_size
    );

    delete[] wave;
}
