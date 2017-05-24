#include <windowsx.h>
#include <xaudio2.h>

#include <cstdint>
#include <memory>

class COMGuard {
public:
    COMGuard() noexcept
    {
        CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    }

    ~COMGuard() noexcept
    {
        CoUninitialize();
    }
};

template <class T>
class COMPointer {
public:
    constexpr COMPointer() noexcept
        : m_pointer(nullptr)
    { }

    explicit COMPointer(const COMPointer<T>& rhs) noexcept
        : m_pointer(&rhs)
    {
        if (m_pointer == nullptr)
            return;

        m_pointer->AddRef();
    }

    explicit COMPointer(COMPointer<T>&& rhs) noexcept
        : m_pointer(&rhs)
    { }

    ~COMPointer() noexcept
    {
        if (m_pointer == nullptr)
            return;

        m_pointer->Release();
    }

    constexpr T& operator*() noexcept
    {
        return *m_pointer;
    }

    constexpr T** operator&() noexcept
    {
        if (m_pointer != nullptr)
            // The resource should be released before passing it to
            // legacy API.
            m_pointer->Release();

        return &m_pointer;
    }

    constexpr auto operator->() noexcept
    {
        return m_pointer;
    }

    constexpr T* get() noexcept
    {
        return m_pointer;
    }

private:
    T* m_pointer;
};

int main()
{
    HRESULT res {};
    COMGuard guard {};

    COMPointer<IXAudio2> xAudio {};

    res = XAudio2Create(&xAudio, 0, XAUDIO2_DEFAULT_PROCESSOR);
    if (FAILED(res))
        return res;

    XAUDIO2_DEBUG_CONFIGURATION debug = {};
    debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
    xAudio->SetDebugConfiguration(&debug, 0);

    IXAudio2MasteringVoice* masteringVoice {};
    res = xAudio->CreateMasteringVoice(&masteringVoice, 2, 48000);
    if (FAILED(res))
        return res;

    WAVEFORMATEX sourceFormat {};
    sourceFormat.wFormatTag = WAVE_FORMAT_PCM;
    sourceFormat.nChannels = 1;
    sourceFormat.nSamplesPerSec = 48000;
    sourceFormat.nAvgBytesPerSec = sizeof(uint16_t) * 48000;
    sourceFormat.nBlockAlign = 2;
    sourceFormat.wBitsPerSample = 16;

    IXAudio2SourceVoice* sourceVoice;
    res = xAudio->CreateSourceVoice(&sourceVoice, &sourceFormat);
    if (FAILED(res))
        return res;

    auto wave = new uint16_t[48000];
    for (int i = 0; i < 48000; i++) {
        uint16_t sample = i % 100;
        wave[i] = sample;
    }

    XAUDIO2_BUFFER buffer {};
    buffer.AudioBytes = sizeof(wave);
    buffer.pAudioData = reinterpret_cast<BYTE *>(wave);
    res = sourceVoice->SubmitSourceBuffer(&buffer);
    if (FAILED(res)) {
        delete wave;
        return res;
    }

    res = sourceVoice->Start(0);
    if (FAILED(res)) {
        delete wave;
        return res;
    }

    delete wave;
    return 0;
}
