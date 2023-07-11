//
// Copyright 2016 Timo Kloss
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#ifndef machine_h
#define machine_h

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "io_chip.h"
#include "video_chip.h"
#include "audio_chip.h"

#define VM_SIZE 0x20000
#define VM_MAX 0x1FFFF
#define PERSISTENT_RAM_SIZE 6144

struct Core;

// 128Kibi
struct Machine {
    
    // 0x00000..0x09000
    struct VideoRam videoRam; // 36Kibi

    // 0x09000..0x0E000
    uint8_t workingRam[0x05000]; // 20Kibi
    
    // 0x0E000..0x0F800
    uint8_t persistentRam[PERSISTENT_RAM_SIZE]; // 6Kibi
    
    // 0x0F800..0x0FB00
    uint8_t nothing2[0x0FB00-0x0F800]; // 768
    
    // 0x0FB00..0x0FF00
    struct SpriteRegisters spriteRegisters; // 1Kibi
    uint8_t nothing4[0x400 - sizeof(struct SpriteRegisters)];
    
    // 0x0FF00
    struct ColorRegisters colorRegisters; // 32Bytes
    
    // 0xFF20
    struct VideoRegisters videoRegisters;
    uint8_t nothing3[0x20 - sizeof(struct VideoRegisters)];
    
    // 0xFF40
    struct AudioRegisters audioRegisters;
    
    // 0xFF70
    struct IORegisters ioRegisters;
    uint8_t reservedIO[0x30 - sizeof(struct IORegisters)];
    
    // 0xFFA0
    uint8_t reservedRegisters[0x10000 - 0xFFA0];

    // 0x10000..0x20000
    uint8_t cartridgeRom[0x10000]; // 64Kibi
};

struct MachineInternals {
    struct AudioInternals audioInternals;
    bool hasAccessedPersistent;
    bool hasChangedPersistent;
    bool isEnergySaving;
    int energySavingTimer;
};

void machine_init(struct Core *core);
void machine_reset(struct Core *core, bool resetPersistent);
int machine_peek(struct Core *core, int address);
bool machine_poke(struct Core *core, int address, int value);
void machine_enableAudio(struct Core *core);
void machine_suspendEnergySaving(struct Core *core, int numUpdates);

#endif /* machine_h */
