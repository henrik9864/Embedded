#include <algorithm>
#include <cstdint>

extern std::uint8_t _sdata;
extern std::uint8_t _edata;
extern std::uint8_t _sidata;

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
    InitBss();
    InitStaticObjects();

    main();

    DestroyStaticObjects();
}