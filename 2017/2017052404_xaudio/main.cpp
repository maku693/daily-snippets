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
    if (FAILED(res)) {
        masteringVoice->DestroyVoice();
        return res;
    }

    const size_t samplingRate = 48000;
    const size_t bufferDuration = 1;
    const size_t waveSize = samplingRate * bufferDuration;
    auto wave = new uint16_t[waveSize];
    for (int i = 0; i < waveSize; i++) {
        wave[i] = (i % 100) * 100;
    }

    WAVEFORMATEX sourceFormat {};
    sourceFormat.wFormatTag = WAVE_FORMAT_PCM;
    sourceFormat.nChannels = 1;
    sourceFormat.nSamplesPerSec = samplingRate;
    sourceFormat.nAvgBytesPerSec = sizeof(uint16_t) * samplingRate;
    sourceFormat.wBitsPerSample = 16;
    sourceFormat.nBlockAlign = sourceFormat.nChannels * sourceFormat.wBitsPerSample / 8;

    IXAudio2SourceVoice* sourceVoice;
    res = xAudio->CreateSourceVoice(&sourceVoice, &sourceFormat);
    if (FAILED(res)) {
        delete[] wave;
        sourceVoice->DestroyVoice();
        masteringVoice->DestroyVoice();
        return res;
    }

    XAUDIO2_BUFFER buffer {};
    buffer.Flags = XAUDIO2_END_OF_STREAM;
    buffer.AudioBytes = sizeof(wave);
    buffer.pAudioData = reinterpret_cast<BYTE *>(wave);
    res = sourceVoice->SubmitSourceBuffer(&buffer);
    if (FAILED(res)) {
        delete[] wave;
        sourceVoice->DestroyVoice();
        masteringVoice->DestroyVoice();
        return res;
    }

    res = sourceVoice->Start();
    if (FAILED(res)) {
        delete[] wave;
        sourceVoice->DestroyVoice();
        masteringVoice->DestroyVoice();
        return res;
    }

    delete[] wave;
    return 0;
}
