//
// Copyright 2017-2018 Timo Kloss
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

#include "overlay_data.h"

uint8_t overlayColors[] = {
    // gamepads
    0,
    2,
    3,
    4,
    // paused text
    0,
    2,
    0,
    0
};

uint8_t overlayCharacters[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x24, 0x24, 0x24, 0x24, 0x3C, 0x24, 0x3C,
    0xFE, 0xFE, 0xFE, 0xFE, 0x7E, 0x00, 0x00, 0x00, 0xFE, 0x92, 0x92, 0xDA, 0x7E, 0x00, 0x00, 0x00,
    0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x7E, 0xDB, 0x81, 0xDB, 0xDB, 0x81, 0xDB, 0x7E,
    0x1C, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x1C, 0x1C, 0x77, 0x41, 0x47, 0x71, 0x41, 0x77, 0x1C,
    0xF7, 0xFF, 0xFF, 0xFE, 0x7F, 0xFF, 0xFF, 0xEF, 0xF7, 0x9D, 0x9B, 0xF6, 0x6F, 0xD9, 0xB9, 0xEF,
    0x3E, 0x7E, 0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3E, 0x62, 0x4A, 0xC7, 0x91, 0x9B, 0xC5, 0x7F,
    0x3C, 0x3C, 0x7C, 0x7C, 0x78, 0x00, 0x00, 0x00, 0x3C, 0x24, 0x64, 0x4C, 0x78, 0x00, 0x00, 0x00,
    0x1E, 0x3E, 0x7E, 0x7C, 0x7C, 0x7E, 0x3E, 0x1E, 0x1E, 0x32, 0x66, 0x4C, 0x4C, 0x66, 0x32, 0x1E,
    0x78, 0x7C, 0x7E, 0x3E, 0x3E, 0x7E, 0x7C, 0x78, 0x78, 0x4C, 0x66, 0x32, 0x32, 0x66, 0x4C, 0x78,
    0x00, 0x7E, 0x7E, 0xFF, 0xFF, 0xFF, 0x7E, 0x7E, 0x00, 0x7E, 0x5A, 0xE7, 0x81, 0xE7, 0x5A, 0x7E,
    0x00, 0x3C, 0x3C, 0xFF, 0xFF, 0xFF, 0x3C, 0x3C, 0x00, 0x3C, 0x24, 0xE7, 0x81, 0xE7, 0x24, 0x3C,
    0x00, 0x00, 0x00, 0x3C, 0x3C, 0x7C, 0x7C, 0x78, 0x00, 0x00, 0x00, 0x3C, 0x24, 0x64, 0x4C, 0x78,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x81, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x3C, 0x3C, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x24, 0x24, 0x3C,
    0x0F, 0x1F, 0x3F, 0x7E, 0xFC, 0xF8, 0xF0, 0xE0, 0x0F, 0x19, 0x33, 0x66, 0xCC, 0x98, 0xB0, 0xE0,
    0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x7E, 0xC3, 0x99, 0x91, 0x89, 0x99, 0xC3, 0x7E,
    0x3C, 0x7C, 0x7C, 0x7C, 0x3C, 0xFF, 0xFF, 0xFF, 0x3C, 0x64, 0x44, 0x64, 0x24, 0xE7, 0x81, 0xFF,
    0x7E, 0xFF, 0xFF, 0xFF, 0x7E, 0xFF, 0xFF, 0xFF, 0x7E, 0xC3, 0x99, 0xF3, 0x66, 0xCF, 0x81, 0xFF,
    0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x7E, 0xC3, 0x99, 0xF3, 0xF9, 0x99, 0xC3, 0x7E,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x0F, 0x0F, 0xFF, 0x99, 0x99, 0x81, 0xF9, 0x09, 0x09, 0x0F,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0x81, 0x9F, 0x83, 0xF9, 0xF9, 0x83, 0xFE,
    0x3E, 0x7E, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3E, 0x62, 0xCE, 0x83, 0x99, 0x99, 0xC3, 0x7E,
    0xFF, 0xFF, 0xFF, 0x3F, 0x7E, 0x7C, 0x78, 0x78, 0xFF, 0x81, 0xF9, 0x33, 0x66, 0x4C, 0x48, 0x78,
    0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x7E, 0xC3, 0x99, 0xC3, 0x99, 0x99, 0xC3, 0x7E,
    0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x7E, 0xC3, 0x99, 0xC1, 0xF9, 0x99, 0xC3, 0x7E,
    0x00, 0x00, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x00, 0x00, 0x00, 0x3C, 0x24, 0x3C, 0x24, 0x3C, 0x00,
    0x00, 0x00, 0x3C, 0x3C, 0x3C, 0x7C, 0x7C, 0x78, 0x00, 0x00, 0x3C, 0x24, 0x3C, 0x64, 0x4C, 0x78,
    0x00, 0x1E, 0x3E, 0x7E, 0x7C, 0x7E, 0x3E, 0x1E, 0x00, 0x1E, 0x32, 0x66, 0x4C, 0x66, 0x32, 0x1E,
    0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x81, 0xFF, 0x81, 0xFF, 0x00,
    0x00, 0x78, 0x7C, 0x7E, 0x3E, 0x7E, 0x7C, 0x78, 0x00, 0x78, 0x4C, 0x66, 0x32, 0x66, 0x4C, 0x78,
    0x7E, 0xFF, 0xFF, 0xFF, 0x3E, 0x3C, 0x3C, 0x3C, 0x7E, 0xC3, 0x99, 0xF3, 0x26, 0x3C, 0x24, 0x3C,
    0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x7E, 0x7E, 0xC3, 0x99, 0x91, 0x91, 0x9F, 0xC2, 0x7E,
    0x3C, 0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3C, 0x66, 0xC3, 0x99, 0x81, 0x99, 0x99, 0xFF,
    0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0x83, 0x99, 0x83, 0x99, 0x99, 0x83, 0xFE,
    0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x7E, 0xC3, 0x99, 0x9F, 0x9F, 0x99, 0xC3, 0x7E,
    0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xFC, 0x86, 0x93, 0x99, 0x99, 0x93, 0x86, 0xFC,
    0xFF, 0xFF, 0xFF, 0xFC, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x81, 0x9F, 0x84, 0x9C, 0x9F, 0x81, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFC, 0xFC, 0xF0, 0xF0, 0xF0, 0xFF, 0x81, 0x9F, 0x84, 0x9C, 0x90, 0x90, 0xF0,
    0x7E, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x7E, 0xC2, 0x9F, 0x91, 0x99, 0x99, 0xC3, 0x7E,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x99, 0x99, 0x81, 0x99, 0x99, 0x99, 0xFF,
    0x7E, 0x7E, 0x7E, 0x3C, 0x3C, 0x7E, 0x7E, 0x7E, 0x7E, 0x42, 0x66, 0x24, 0x24, 0x66, 0x42, 0x7E,
    0x3F, 0x3F, 0x3F, 0x0F, 0xFF, 0xFF, 0xFF, 0x7E, 0x3F, 0x21, 0x39, 0x09, 0xF9, 0x99, 0xC3, 0x7E,
    0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x99, 0x93, 0x86, 0x86, 0x93, 0x99, 0xFF,
    0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xFF, 0xFF, 0xFF, 0xF0, 0x90, 0x90, 0x90, 0x90, 0x9F, 0x81, 0xFF,
    0xE7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0xBD, 0x99, 0x81, 0x81, 0x99, 0x99, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x99, 0x89, 0x81, 0x91, 0x99, 0x99, 0xFF,
    0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x7E, 0xC3, 0x99, 0x99, 0x99, 0x99, 0xC3, 0x7E,
    0xFE, 0xFF, 0xFF, 0xFF, 0xFE, 0xF0, 0xF0, 0xF0, 0xFE, 0x83, 0x99, 0x83, 0x9E, 0x90, 0x90, 0xF0,
    0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7E, 0xC3, 0x99, 0x99, 0x95, 0x93, 0xC1, 0x7F,
    0xFE, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFE, 0x83, 0x99, 0x83, 0x86, 0x93, 0x99, 0xFF,
    0x7F, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFE, 0x7F, 0xC1, 0x9F, 0xC3, 0x79, 0xF9, 0x83, 0xFE,
    0xFF, 0xFF, 0xFF, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xFF, 0x81, 0xE7, 0x24, 0x24, 0x24, 0x24, 0x3C,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0xFF, 0x99, 0x99, 0x99, 0x99, 0x99, 0xC3, 0x7E,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0xFF, 0x99, 0x99, 0x99, 0x99, 0xC3, 0x66, 0x3C,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0xFF, 0x99, 0x99, 0x81, 0x81, 0x99, 0xBD, 0xE7,
    0xFF, 0xFF, 0xFF, 0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x99, 0xC3, 0x66, 0xC3, 0x99, 0x99, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x3C, 0x3C, 0xFF, 0x99, 0x99, 0xC3, 0x66, 0x24, 0x24, 0x3C,
    0xFF, 0xFF, 0xFF, 0x7E, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x81, 0xF3, 0x66, 0xCC, 0x9F, 0x81, 0xFF,
    0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x7E, 0xC3, 0x99, 0xA5, 0xBD, 0xA5, 0xC3, 0x7E,
    0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x7E, 0xC3, 0xA1, 0xB9, 0xA5, 0xB9, 0xC3, 0x7E,
    0x3C, 0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x3C, 0x66, 0xE7, 0x81, 0x81, 0xE7, 0x66, 0x3C,
    0x3C, 0x7E, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x3C, 0x66, 0xC3, 0x99, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x81, 0xFF,
};
