#pragma once

/*
c++ junk generator
check https://github.com/freshnddope/junk-code-generator for updates
leave a star on the repository ^^^
*/

static_assert(sizeof(void*) == 8, "x64 build");

consteval unsigned fshiftrandom() {
    unsigned short lfsr = __TIME__[7] * 2;
    unsigned bit;
    bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
    return lfsr = (lfsr >> 1) | (bit << 15);
}

void junkcallme() {}
float junkcallme2() { return 3.402823466e+38F + 1; };

constexpr int compiledrand = fshiftrandom() % 100;
constexpr int compiledrand2 = fshiftrandom() % 1337;
constexpr int compiledrandMAX = fshiftrandom() % 2147483647;

template <size_t N>
struct CPUIDCOMPILE {
    static void gen() {
        int cpuInfo[4];
        __cpuid(cpuInfo, 0);
        if constexpr (N > 0) CPUIDCOMPILE<N - 1>::gen();
    }
};

template <size_t N>
struct RDTSCOMPILE {
    static void gen() {
        volatile unsigned __int64 tsc = __rdtsc();
        (void)tsc;
        if constexpr (N > 0) RDTSCOMPILE<N - 1>::gen();
    }
};

template <size_t N>
struct NOPCOMPILE {
    static void gen() {
        if constexpr (N > 0) {
            __nop();
            NOPCOMPILE<N - 1>::gen();
        }
    }
};

template <size_t N>
struct WINDFUNCSCOMPILE {
    static void gen() {
        rand();
        FindWindowA(reinterpret_cast<LPCSTR>(90 + (fshiftrandom() % 30)), NULL);
        GetCurrentProcessId();
        GetCurrentProcess();
        GetProcessHeap();
        if constexpr (N > 0) WINDFUNCSCOMPILE<N - 1>::gen();
    }
};

template <size_t N>
struct NULLSUBCOMPILE {
    static void gen() {
        junkcallme();
        if constexpr (N > 0) NULLSUBCOMPILE<N - 1>::gen();
    }
};

template <size_t N>
struct IFCOMPILE {
    static void gen() {
        volatile int al = compiledrand2;
        if (al < compiledrand) {
            al = 1;
            junkcallme2();
            al = compiledrand2 - 1;
        }
        else {
            volatile int ah = CHAR_MAX;
            ah ^= al;
        }
        al++;
        al ^= compiledrand;
        if constexpr (N > 0) IFCOMPILE<N - 1>::gen();
    }
};

template <size_t N>
struct JMPCOMPILE {
    static void gen() {
        if constexpr (N > 0) JMPCOMPILE<N - 1>::gen();
    }
};

template <size_t N>
struct MEMTOUCHCOMPILE {
    static void gen() {
        const size_t block = 4096 * 8;
        void* p = VirtualAlloc(NULL, block, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        if (p) {
            volatile unsigned char* vp = reinterpret_cast<unsigned char*>(p);
            for (size_t i = 0; i < block; i += 64) {
                vp[i] = static_cast<unsigned char>((i ^ fshiftrandom()) & 0xFF);
            }
            VirtualFree(p, 0, MEM_RELEASE);
        }
        if constexpr (N > 0) MEMTOUCHCOMPILE<N - 1>::gen();
    }
};

template <size_t N>
struct SSECOMPILE {
    static void gen() {
        __m128 a = _mm_set_ps1(static_cast<float>(compiledrand));
        __m128 b = _mm_set_ps1(static_cast<float>(compiledrand2));
        __m128 c = _mm_add_ps(a, b);
        c = _mm_mul_ps(c, _mm_shuffle_ps(c, c, _MM_SHUFFLE(2, 1, 0, 3)));
        float out[4];
        _mm_storeu_ps(out, c);
        volatile float sink = out[0] + out[1] + out[2] + out[3];
        (void)sink;
        if constexpr (N > 0) SSECOMPILE<N - 1>::gen();
    }
};

template <size_t N>
struct ATOMICCOMPILE {
    static void gen() {
        static std::atomic<unsigned long long> v{ 0xDEADBEEFDEADBEEFULL ^ compiledrandMAX };
        v.fetch_add(1, std::memory_order_relaxed);
        _InterlockedIncrement64(reinterpret_cast<volatile long long*>(&v));
        unsigned long long prev = v.load(std::memory_order_relaxed);
        (void)prev;
        if constexpr (N > 0) ATOMICCOMPILE<N - 1>::gen();
    }
};

template <size_t N, size_t ITER = 1024>
struct LOOPCOMPILE {
    static void gen() {
        volatile unsigned long long x = fshiftrandom();
        for (size_t i = 0; i < ITER; ++i) {
            if ((x ^ i) & 1) {
                x = _rotr64(x + i, (unsigned)(i & 63));
            }
            else {
                x = _rotl64(x + i, (unsigned)((i + 13) & 63));
            }
            _mm_pause();
        }
        (void)x;
        if constexpr (N > 0) LOOPCOMPILE<N - 1, ITER>::gen();
    }
};

template <size_t N>
struct FOOLPAGECOMPILE {
    static void gen() {
        SIZE_T sz = 4096;
        BYTE* mem = reinterpret_cast<BYTE*>(VirtualAlloc(nullptr, sz, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
        if (mem) {
            for (SIZE_T i = 0; i < sz; i += 16) {
                mem[i] = static_cast<BYTE>((i ^ fshiftrandom()) & 0xFF);
            }
            DWORD old;
            VirtualProtect(mem, sz, PAGE_READONLY, &old);
            volatile BYTE v = mem[0];
            (void)v;
            VirtualFree(mem, 0, MEM_RELEASE);
        }
        if constexpr (N > 0) FOOLPAGECOMPILE<N - 1>::gen();
    }
};

template <size_t N>
struct TIMERCOMPILE {
    static void gen() {
        LARGE_INTEGER f, t1, t2;
        QueryPerformanceFrequency(&f);
        QueryPerformanceCounter(&t1);
        for (int i = 0; i < 16; ++i) {
            QueryPerformanceCounter(&t2);
            volatile LONGLONG diff = t2.QuadPart - t1.QuadPart;
            (void)diff;
        }
        if constexpr (N > 0) TIMERCOMPILE<N - 1>::gen();
    }
};

template <size_t N>
struct THREADCOMPILE {
    static DWORD WINAPI threadProc(LPVOID lpParam) {
        volatile unsigned seed = static_cast<unsigned>(reinterpret_cast<uintptr_t>(lpParam) ^ fshiftrandom());
        for (int i = 0; i < 32; ++i) {
            seed = (seed * 1664525u) + 1013904223u + (i ^ compiledrand);
            _mm_pause();
        }
        return static_cast<DWORD>(seed & 0xFFFFFFFF);
    }

    static void gen() {
        HANDLE h = CreateThread(nullptr, 0, threadProc, reinterpret_cast<LPVOID>(static_cast<uintptr_t>(compiledrand2)), 0, nullptr);
        if (h) {
            WaitForSingleObject(h, 10);
            CloseHandle(h);
        }
        if constexpr (N > 0) THREADCOMPILE<N - 1>::gen();
    }
};

template <size_t N>
struct MIXEDCOMPILE {
    static void gen() {
        MEMTOUCHCOMPILE<1>::gen();
        SSECOMPILE<1>::gen();
        ATOMICCOMPILE<1>::gen();
        LOOPCOMPILE<1>::gen();
        FOOLPAGECOMPILE<1>::gen();
        TIMERCOMPILE<1>::gen();
        THREADCOMPILE<1>::gen();
        if constexpr (N > 0) MIXEDCOMPILE<N - 1>::gen();
    }
};

template <size_t N>
struct PREFETCHCOMPILE {
    static void gen() {
        const size_t S = 4096;
        unsigned char* buf = static_cast<unsigned char*>(_aligned_malloc(S, 64));
        if (buf) {
            for (size_t i = 0; i < S; i += 64) {
                _mm_prefetch(reinterpret_cast<const char*>(&buf[i]), _MM_HINT_T0);
            }
            for (size_t i = 0; i < S; i += 16) {
                buf[i] = static_cast<unsigned char>((buf[i] + fshiftrandom()) & 0xFF);
            }
            _aligned_free(buf);
        }
        if constexpr (N > 0) PREFETCHCOMPILE<N - 1>::gen();
    }
};

template <size_t N>
struct HASHCOMPILE {
    static void gen() {
        unsigned long long a = 1469598103934665603ull ^ static_cast<unsigned long long>(compiledrandMAX);
        for (int i = 0; i < 256; ++i) {
            a ^= (static_cast<unsigned long long>(fshiftrandom()) + (i * 0x9e3779b97f4a7c15ull));
            a *= 0x100000001b3ull;
            a = _rotl64(a, (unsigned)(i & 63));
        }
        volatile unsigned long long sink = a;
        (void)sink;
        if constexpr (N > 0) HASHCOMPILE<N - 1>::gen();
    }
};

template <size_t N>
struct STACKPROBECOMPILE {
    static void gen() {
        const size_t SZ = 4096;
        volatile char* probe = reinterpret_cast<volatile char*>(_alloca(SZ));
        for (size_t i = 0; i < SZ; i += 128) {
            probe[i] = static_cast<char>((i ^ fshiftrandom()) & 0x7F);
        }
        if constexpr (N > 0) STACKPROBECOMPILE<N - 1>::gen();
    }
};

template <size_t N>
struct EXCEPTIONCOMPILE {
    static void gen() {
        for (int i = 0; i < 8; ++i) {
            try {
                if ((fshiftrandom() & 3) == 0) {
                    throw std::runtime_error("noise");
                }
                else {
                    volatile int x = compiledrand ^ compiledrand2;
                    (void)x;
                }
            }
            catch (...) {
                volatile int y = CHAR_MAX;
                y ^= compiledrand;
                (void)y;
            }
        }
        if constexpr (N > 0) EXCEPTIONCOMPILE<N - 1>::gen();
    }
};

#define JUNK_GENERATE(amount) \
    _Pragma("message(\"[Junk] Generating Junk Code...\")") \
    NOPCOMPILE<amount>::gen(); \
    WINDFUNCSCOMPILE<amount>::gen(); \
    NULLSUBCOMPILE<amount>::gen(); \
    IFCOMPILE<amount>::gen(); \
    JMPCOMPILE<amount>::gen(); \
    CPUIDCOMPILE<amount>::gen(); \
    RDTSCOMPILE<amount>::gen(); \
    MEMTOUCHCOMPILE<amount>::gen(); \
    SSECOMPILE<amount>::gen(); \
    ATOMICCOMPILE<amount>::gen(); \
    LOOPCOMPILE<amount>::gen(); \
    FOOLPAGECOMPILE<amount>::gen(); \
    TIMERCOMPILE<amount>::gen(); \
    THREADCOMPILE<amount>::gen(); \
    MIXEDCOMPILE<amount>::gen(); \
    PREFETCHCOMPILE<amount>::gen(); \
    HASHCOMPILE<amount>::gen(); \
    STACKPROBECOMPILE<amount>::gen(); \
    EXCEPTIONCOMPILE<amount>::gen();
