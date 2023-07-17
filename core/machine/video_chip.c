//
// Copyright 2016-2020 Timo Kloss
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

#include "video_chip.h"
#include "core.h"
#include <string.h>

#define OVERLAY_FLAG (1<<6)

// FAMICUBE
uint32_t better_palette[]={ 0x000000, 0xe03c28, 0xffffff, 0xd7d7d7, 0xa8a8a8, 0x7b7b7b, 0x343434, 0x151515, 0x0d2030, 0x415d66, 0x71a6a1, 0xbdffca, 0x25e2cd, 0x0a98ac, 0x005280, 0x00604b, 0x20b562, 0x58d332, 0x139d08, 0x004e00, 0x172808, 0x376d03, 0x6ab417, 0x8cd612, 0xbeeb71, 0xeeffa9, 0xb6c121, 0x939717, 0xcc8f15, 0xffbb31, 0xffe737, 0xf68f37, 0xad4e1a, 0x231712, 0x5c3c0d, 0xae6c37, 0xc59782, 0xe2d7b5, 0x4f1507, 0x823c3d, 0xda655e, 0xe18289, 0xf5b784, 0xffe9c5, 0xff82ce, 0xcf3c71, 0x871646, 0xa328b3, 0xcc69e4, 0xd59cfc, 0xfec9ed, 0xe2c9ff, 0xa675fe, 0x6a31ca, 0x5a1991, 0x211640, 0x3d34a5, 0x6264dc, 0x9ba0ef, 0x98dcff, 0x5ba8ff, 0x0a89ff, 0x024aca, 0x00177d, };

int video_getCharacterPixel(struct Character *character, int x, int y)
{
    int b0 = (character->data[y] >> (7 - x)) & 0x01;
    int b1 = (character->data[y | 8] >> (7 - x)) & 0x01;
    return b0 | (b1 << 1);
}

void video_renderPlane(struct Character *characters, struct Plane *plane, int sizeMode, int y, int scrollX, int scrollY, int pixelFlag, uint8_t *scanlineBuffer)
{
    int divShift = sizeMode ? 4 : 3;
    int planeY = y + scrollY;
    int row = (planeY >> divShift) & 31;
    int cellY = planeY & 7;
    
    int x = 0;
    int b = 0;
    uint8_t d0 = 0;
    uint8_t d1 = 0;
    uint8_t pal = 0;
    uint8_t pri = 0;
    
    int pre = scrollX & 7;
    
    while (x < SCREEN_WIDTH)
    {
        if (!b)
        {
            int planeX = x + scrollX;
            int column = (planeX >> divShift) & COLS_MASK;
            struct Cell *cell = &plane->cells[row][column];
            
            int index = cell->character;
            if (sizeMode)
            {
                index += (cell->attr.flipX ? (planeX >> 3) + 1 : planeX >> 3) & 1;
                index += ((cell->attr.flipY ? (planeY >> 3) + 1 : planeY >> 3) & 1) << 4;
            }
            
            struct Character *character = &characters[index];
            pal = cell->attr.palette << 2;
            pri = cell->attr.priority << 7;
            
            int fcy = cell->attr.flipY ? (7 - cellY) : cellY;
            d0 = character->data[fcy];
            d1 = character->data[fcy | 8];
            if (cell->attr.flipX)
            {
                // reverse bits hack from http://graphics.stanford.edu/~seander/bithacks.html#ReverseByteWith32Bits
                d0 = ((d0 * 0x0802LU & 0x22110LU) | (d0 * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;
                d1 = ((d1 * 0x0802LU & 0x22110LU) | (d1 * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;
            }
        }
        
        if (pre)
        {
            --pre;
        }
        else
        {
            if (pri >= (*scanlineBuffer >> 7))
            {
                int pixel = ((d0 >> 7) & 1) | ((d1 >> 6) & 2);
                if (pixel)
                {
                    *scanlineBuffer = pixel | pal | pri | pixelFlag;
                }
            }
            ++scanlineBuffer;
            ++x;
        }

        d0 <<= 1;
        d1 <<= 1;
        b = (b + 1) & 7;
    }
}

void video_renderSprites(struct SpriteRegisters *reg, struct VideoRam *ram, int y, uint8_t *scanlineBuffer, uint8_t *scanlineSpriteBuffer)
{
    for (int i = NUM_SPRITES - 1; i >= 0; i--)
    {
        struct Sprite *sprite = &reg->sprites[i];
        if (sprite->x != 0 || sprite->y != 0)
        {
            int spriteY = y - sprite->y + SPRITE_OFFSET_Y;
            int size = (sprite->attr.size + 1) << 3;
            if (spriteY >= 0 && spriteY < size)
            {
                if (sprite->attr.flipY)
                {
                    spriteY = size - spriteY - 1;
                }
                int charIndex = sprite->character + ((spriteY >> 3) << 4);
                if (sprite->attr.flipX)
                {
                    charIndex += sprite->attr.size;
                }
                int minX = sprite->x - SPRITE_OFFSET_X;
                int maxX = minX + size;
                if (minX < 0)
                {
                    int skip = -minX >> 3;
                    if (sprite->attr.flipX)
                    {
                        charIndex -= skip;
                    }
                    else
                    {
                        charIndex += skip;
                    }
                }
                if (minX < 0) minX = 0;
                if (maxX > SCREEN_WIDTH) maxX = SCREEN_WIDTH;
                uint8_t *buffer = &scanlineSpriteBuffer[minX];
                int spriteX = minX - sprite->x + SPRITE_OFFSET_X;
                if (sprite->attr.flipX)
                {
                    spriteX = size - spriteX - 1;
                }
                struct Character *character = &ram->characters[charIndex];
                for (int x = minX; x < maxX; x++)
                {
                    int pixel = video_getCharacterPixel(character, spriteX & 0x07, spriteY & 0x07);
                    if (pixel)
                    {
                        *buffer = pixel | (sprite->attr.palette << 2) | (sprite->attr.priority << 7);
                    }
                    buffer++;
                    if (sprite->attr.flipX)
                    {
                        if (!(spriteX & 0x07))
                        {
                            character--;
                        }
                        spriteX--;
                    }
                    else
                    {
                        spriteX++;
                        if (!(spriteX & 0x07))
                        {
                            character++;
                        }
                    }
                }
            }
        }
    }
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        int pixel = *scanlineSpriteBuffer;
        if (pixel && (pixel >> 7) >= (*scanlineBuffer >> 7))
        {
            *scanlineBuffer = pixel;
        }
        scanlineSpriteBuffer++;
        scanlineBuffer++;
    }
}

void video_renderScreen(struct Core *core, uint32_t *outputRGB)
{
    uint8_t scanlineBuffer[SCREEN_WIDTH];
    uint8_t scanlineSpriteBuffer[SCREEN_WIDTH];
    uint32_t *outputPixel = outputRGB;
    
    struct VideoRam *ram = &core->machine->videoRam;
    struct VideoRegisters *reg = &core->machine->videoRegisters;
    struct SpriteRegisters *sreg = &core->machine->spriteRegisters;
    struct ColorRegisters *creg = &core->machine->colorRegisters;
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        reg->rasterLine = y;
        itp_runInterrupt(core, InterruptTypeRaster);
        memset(scanlineBuffer, 0, sizeof(scanlineBuffer));
        
        bool skip = (core->interpreter->interruptOverCycles > 0);
        if (!skip)
        {
            if (reg->attr.planeBEnabled)
            {
                int scrollX = reg->scrollBX | (reg->scrollMSB.bX << 8);
                int scrollY = reg->scrollBY | (reg->scrollMSB.bY << 8);
                video_renderPlane(ram->characters, &ram->planeB, reg->attr.planeBCellSize, y, scrollX, scrollY, 0, scanlineBuffer);
            }
            if (reg->attr.planeAEnabled)
            {
                int scrollX = reg->scrollAX | (reg->scrollMSB.aX << 8);
                int scrollY = reg->scrollAY | (reg->scrollMSB.aY << 8);
                video_renderPlane(ram->characters, &ram->planeA, reg->attr.planeACellSize, y, scrollX, scrollY, 0, scanlineBuffer);
            }
            if (reg->attr.spritesEnabled)
            {
                memset(scanlineSpriteBuffer, 0, sizeof(scanlineSpriteBuffer));
                video_renderSprites(sreg, ram, y, scanlineBuffer, scanlineSpriteBuffer);
            }
        }
        
        // overlay
        video_renderPlane((struct Character *)overlayCharacters, &core->overlay->plane, 0, y, 0, 0, OVERLAY_FLAG, scanlineBuffer);
        
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            int colorIndex = scanlineBuffer[x] & 0x1F;
            int color = (scanlineBuffer[x] & OVERLAY_FLAG) ? overlayColors[colorIndex] : skip ? 0 : creg->colors[colorIndex];

            uint32_t c = better_palette[color & 63];
            *outputPixel = c;
            ++outputPixel;
        }
    }
}
