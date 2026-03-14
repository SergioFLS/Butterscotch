#pragma once

#include "renderer.h"
#include <gsKit.h>

// ===[ Atlas Entry (from ATLAS.BIN TPAG entries) ]===
typedef struct {
    uint16_t atlasId;   // TEX atlas index (0xFFFF = not mapped)
    uint16_t atlasX;    // X offset within the atlas
    uint16_t atlasY;    // Y offset within the atlas
    uint16_t width;     // Image width in the atlas
    uint16_t height;    // Image height in the atlas
    uint16_t clutIndex; // CLUT index within the corresponding CLUT file
    uint8_t bpp;        // 4 or 8
} AtlasTPAGEntry;

// ===[ Per-atlas VRAM state ]===
typedef struct {
    bool loaded;        // true if uploaded to VRAM
    uint32_t vramAddr;  // VRAM address of pixel data
    uint32_t tbw;       // Texture buffer width
    uint8_t bpp;        // 4 or 8 (from TEX header)
} AtlasVRAMSlot;

// ===[ GsRenderer Struct ]===
typedef struct {
    Renderer base; // Must be first field for struct embedding

    GSGLOBAL* gsGlobal;

    // View transform state
    float scaleX;
    float scaleY;
    float offsetX;
    float offsetY;
    int32_t viewX;
    int32_t viewY;

    // Z counter for depth ordering
    uint16_t zCounter;

    // ATLAS.BIN data
    uint16_t atlasTPAGCount;
    uint16_t atlasTileCount;
    AtlasTPAGEntry* atlasTPAGEntries;
    // Tile entries will be added later

    // CLUT VRAM addresses (one per CLUT, individually uploaded)
    uint32_t clut4Count;       // Number of 4bpp CLUTs
    uint32_t* clut4VramAddrs;  // Per-CLUT VRAM addresses [clut4Count]

    uint32_t clut8Count;       // Number of 8bpp CLUTs
    uint32_t* clut8VramAddrs;  // Per-CLUT VRAM addresses [clut8Count]

    // Per-atlas texture state
    uint16_t atlasSlotCount; // Number of atlas slots allocated
    AtlasVRAMSlot* atlasSlots;

    // VRAM base pointer (start of texture area, after framebuffers/fontm)
    uint32_t vramBase;
} GsRenderer;

Renderer* GsRenderer_create(GSGLOBAL* gsGlobal);
