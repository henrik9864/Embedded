#include <algorithm>
#include <cstdint>
#include <array>

extern std::uint8_t _sdata;
extern std::uint8_t _edata;
extern std::uint8_t _sidata;

extern std::uint8_t _spio0;
extern std::uint8_t _epio0;
extern std::uint8_t _sipio0;

extern std::uint8_t _spio1;
extern std::uint8_t _epio1;
extern std::uint8_t _sipio1;

extern std::uint8_t _sbss;
extern std::uint8_t _ebss;

typedef void (*function_t)();
extern function_t _preinit_array_start;
extern function_t _preinit_array_end;

extern function_t _init_array_start;
extern function_t _init_array_end;

extern function_t _fini_array_start;
extern function_t _fini_array_end;

extern int main();

/*
Initialize data section
*/
void CopyData()
{
    std::size_t size = static_cast<size_t>(&_edata - &_sdata);
    std::copy(&_sidata, &_sidata + size, &_sdata);
}

/*
Initialize pio cores
*/
void CopyPio()
{
    std::size_t size = static_cast<size_t>(&_epio0 - &_spio0);
    std::copy(&_sipio0, &_sipio0 + size, &_spio0);

    size = static_cast<size_t>(&_epio1 - &_spio1);
    std::copy(&_sipio1, &_sipio1 + size, &_spio1);
}

/*
Init Bss
*/
void InitBss()
{
    std::fill(&_sbss, &_ebss, 0x00);
}

/*
Initialize static objects by calling their constructors
*/
void InitStaticObjects() {
    std::for_each(&_preinit_array_start, &_preinit_array_end, [](const function_t pfn) {
        pfn();
        });

    std::for_each(&_init_array_start, &_init_array_end, [](const function_t pfn) {
        pfn();
        });
}

/*
Destroy static objects by calling their destructors
*/
void DestroyStaticObjects()
{
    std::for_each(&_fini_array_start, &_fini_array_end, [](const function_t pfn) {
        pfn();
        });
}

/*
Entry point for program.
*/
void ResetHandler() {
    CopyData();
    CopyPio();
    InitBss();
    InitStaticObjects();

    main();

    DestroyStaticObjects();
}