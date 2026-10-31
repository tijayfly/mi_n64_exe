// Data overrides: replace decoded Burp archive entries with files from a folder, so level edits can be loaded without
// changing the ROM (the app rejects modified ROMs). Called from hooks at the end of Burp_LoadTo and Burp_Load
// (mi.us.toml), after an entry has been decoded into RAM and before the game reads or relocates it.
//
// MI_OVERRIDE_DIR=dir (or Debug > Load Data Overrides, which reads <app folder>/overrides): dir/rom_XXXXXXXX.bin
// replaces the entry whose data starts at ROM address XXXXXXXX (8 hex digits, as listed by scripts/levels/burp.py).
// The file is the decoded entry in the N64's (big-endian) byte order and must be the same size as the original for now.
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <unordered_map>
#include <vector>

#include "mi_config.h"

namespace {
    std::unordered_map<uint32_t, std::vector<uint8_t>> load_overrides() {
        std::unordered_map<uint32_t, std::vector<uint8_t>> overrides;
        std::string dir;
        if (const char* env = std::getenv("MI_OVERRIDE_DIR")) {
            dir = env;
        }
        else if (mi::get_load_overrides()) {
            dir = mi::get_overrides_dir();
            std::fprintf(stderr, "Override folder: %s\n", dir.c_str());
        }
        if (dir.empty()) {
            return overrides;
        }
        std::error_code ec;
        for (const auto& file : std::filesystem::directory_iterator(dir, ec)) {
            std::string name = file.path().filename().string();
            unsigned int rom_address = 0;
            if (std::sscanf(name.c_str(), "rom_%8X.bin", &rom_address) != 1) {
                continue;
            }
            std::ifstream in(file.path(), std::ios::binary);
            overrides[rom_address] = std::vector<uint8_t>(std::istreambuf_iterator<char>(in), {});
            std::fprintf(stderr, "Override: %s (%zu bytes)\n", name.c_str(), overrides[rom_address].size());
        }
        return overrides;
    }

    uint32_t ram_u32(uint8_t* rdram, uint32_t addr) {
        return *reinterpret_cast<uint32_t*>(rdram + (addr - 0x80000000u));
    }
}

// entry: the archive entry (0x14 bytes: +0 decoded size, +0xC ROM address of the data); buffer: where it was decoded.
extern "C" void mi_override_entry(uint8_t* rdram, uint32_t entry, uint32_t buffer) {
    static const auto overrides = load_overrides();
    if (overrides.empty() || entry < 0x80000000u || buffer < 0x80000000u) {
        return;
    }
    uint32_t rom_address = ram_u32(rdram, entry + 0xC);
    auto it = overrides.find(rom_address);
    if (it == overrides.end()) {
        return;
    }
    uint32_t size = ram_u32(rdram, entry + 0x0);
    if (it->second.size() != size) {
        std::fprintf(stderr, "Override rom_%08X.bin skipped: %zu bytes, the entry is %u\n", rom_address, it->second.size(), size);
        return;
    }
    // RDRAM keeps 32-bit words in native byte order, so byte n of a big-endian buffer lives at address n ^ 3.
    uint32_t offset = buffer - 0x80000000u;
    for (uint32_t i = 0; i < size; i++) {
        rdram[(offset + i) ^ 3] = it->second[i];
    }
    std::fprintf(stderr, "Override applied: rom_%08X.bin -> 0x%08X (%u bytes)\n", rom_address, buffer, size);
}

// Fork credits: two entries added at the end of the game's credits. The credits text is entry 4 of the text archive
// (handle D_80093AB0); a line ending in ':' is drawn grey and the others white, and entries are separated by two blank
// lines. Credits_LoadText allocates the entry's decoded size and the credits screen counts lines over it, so grow the
// size in the archive's entry table before the load, then write the extra lines after the original text.
namespace {
    constexpr uint32_t text_archive_handle_addr = 0x80093AB0;
    constexpr uint32_t credits_entry_index = 4;
    constexpr uint32_t credits_rom_address = 0x30FDD0;
    constexpr uint32_t credits_size = 0x894;
    constexpr char fork_credits[] =
        "\r\n"
        "Windows port by :\r\n"
        "TiJayFLY\r\n"
        "\r\n\r\n"
        "Based on a Linux port by :\r\n"
        "nickallevato\r\n"
        "\r\n";
    constexpr uint32_t fork_credits_size = sizeof(fork_credits) - 1;
    bool credits_grown = false;

    uint32_t credits_entry(uint8_t* rdram) {
        uint32_t handle = ram_u32(rdram, text_archive_handle_addr);
        if (handle < 0x80000000u || ram_u32(rdram, handle + 0x0) <= credits_entry_index) {
            return 0;
        }
        uint32_t entry = ram_u32(rdram, handle + 0x4) + credits_entry_index * 0x14;
        return ram_u32(rdram, entry + 0xC) == credits_rom_address ? entry : 0;
    }
}

extern "C" void mi_credits_before_load(uint8_t* rdram) {
    credits_grown = false;
    uint32_t entry = credits_entry(rdram);
    if (entry == 0) {
        return;
    }
    uint32_t& size = *reinterpret_cast<uint32_t*>(rdram + (entry - 0x80000000u));
    if (size == credits_size) {
        size = credits_size + fork_credits_size;
    }
    credits_grown = size == credits_size + fork_credits_size;
}

extern "C" void mi_credits_after_load(uint8_t* rdram, uint32_t buffer) {
    if (!credits_grown || buffer < 0x80000000u) {
        return;
    }
    uint32_t offset = buffer - 0x80000000u + credits_size;
    for (uint32_t i = 0; i < fork_credits_size; i++) {
        rdram[(offset + i) ^ 3] = static_cast<uint8_t>(fork_credits[i]);
    }
}
