#include "particles_lib.h"

#include "core.h"
#include "machine.h"

void prtclib_setupPool(struct ParticlesLib *lib,int firstSprite,int poolCount,int particleAddr)
{
    lib->first_sprite_id=firstSprite;
    lib->pool_count=poolCount;
    lib->pool_next_id=0;
    lib->particles_data_addr=particleAddr;
}

void prtclib_setApperanceLabel(struct ParticlesLib *lib,int apperanceId,struct Token *label)
{
    lib->apperances_label[apperanceId]=label;
}

void prtclib_update(struct ParticlesLib *lib)
{
    // update particles

    int peek1,peek2;

    for(int i=0; i<lib->pool_count; ++i)
    {
        peek1=machine_peek(lib->core, lib->particles_data_addr);
        peek2=machine_peek(lib->core, lib->particles_data_addr+1);
        if(peek1<0 || peek2<0) continue;
        int16_t x=peek1|(peek2<<8);

        int16_t y=0;

        int n=lib->first_sprite_id+i;

        struct Sprite *spr=&lib->core->machine->spriteRegisters.sprites[n];
        spr->x=(int)((x+SPRITE_OFFSET_X)*16)&0x1FFF;
        spr->y=(int)((y+SPRITE_OFFSET_Y)*16)&0x1FFF;
        spr->character=1;
    }
}
