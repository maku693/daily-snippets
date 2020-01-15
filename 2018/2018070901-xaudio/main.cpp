#pragma comment(lib, "windowsapp")
#pragma comment(lib, "xaudio2")

#include <chrono>
#include <cstdint>
#include <thread>
#include <winrt/base.h>
#include <xaudio2.h>

template <class F> class final_action {
public:
  final_action(F &&f) : f_(f) {}
  ~final_action() { f_(); }

private:
  F f_;
};

template <class F> auto finally(F &&f) noexcept {
  return final_action{std::forward<F>(f)};
}

int main() {
  winrt::init_apartment();

  winrt::com_ptr<IXAudio2> xaudio{};
  winrt::check_hresult(
      XAudio2Create(xaudio.put(), 0, XAUDIO2_DEFAULT_PROCESSOR));

  XAUDIO2_DEBUG_CONFIGURATION debug_conf{};
  debug_conf.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
  xaudio->SetDebugConfiguration(&debug_conf, 0);

  IXAudio2MasteringVoice *mastering_voice{};
  winrt::check_hresult(
      xaudio->CreateMasteringVoice(&mastering_voice, 2, 48000));
  const auto destroy_mastering_voice =
      finally([&mastering_voice] { mastering_voice->DestroyVoice(); });

  const int sample_rate = 44100;
  const int buffer_duration = 1;
  const int wave_size = sample_rate * buffer_duration;
  uint16_t wave[wave_size];
  for (int i = 0; i < wave_size; i++) {
    wave[i] = (i % 100) * 60;
  }
  for (int i = 0; i < wave_size; i++) {
    wave[i] += (i % 120) * 60;
  }
  for (int i = 0; i < wave_size; i++) {
    wave[i] += (i % 150) * 60;
  }

  WAVEFORMATEX format{};
  format.wFormatTag = WAVE_FORMAT_PCM;
  format.nChannels = 1;
  format.nSamplesPerSec = sample_rate;
  format.nAvgBytesPerSec = sizeof(uint16_t) * sample_rate;
  format.wBitsPerSample = 16;
  format.nBlockAlign = format.nChannels * format.wBitsPerSample / 8;

  IXAudio2SourceVoice *source_voice{};
  winrt::check_hresult(xaudio->CreateSourceVoice(&source_voice, &format));
  const auto destroy_source_voice =
      finally([&source_voice] { source_voice->DestroyVoice(); });

  XAUDIO2_BUFFER buffer{};
  buffer.Flags = XAUDIO2_END_OF_STREAM;
  buffer.AudioBytes = sizeof(wave);
  buffer.pAudioData = reinterpret_cast<BYTE *>(wave);
  winrt::check_hresult(source_voice->SubmitSourceBuffer(&buffer));

  winrt::check_hresult(source_voice->Start());
  std::this_thread::sleep_for(std::chrono::seconds{2});

  return 0;
}
