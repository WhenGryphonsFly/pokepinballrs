#include "global.h"
#include "constants/ereader.h"
#include "constants/species.h"
#include "functions.h"
#include "m4a.h"
#include "main.h"

extern const u16 gWildMonLocations[][2][8];
extern const u16 gUnknown_086A4A38[2][26];

static inline u32 GetTimeAdjustedRandom()
{
    return Random() + (gMain.systemFrameCount + gMain.fieldFrameCount);
}

void sub_3219C(void)
{
    s16 i;
    u32 rand;
    u16 specialMons[6];

    if (gMain.eReaderBonus[EREADER_SPECIAL_GUESTS_CARD])
    {
        gMain.eReaderBonus[EREADER_SPECIAL_GUESTS_CARD] = 0;
        rand = GetTimeAdjustedRandom();
        rand %= NUM_BONUS_SPECIES;
        for (i = 0; i < NUM_BONUS_SPECIES; i++)
        {
            if (gMain_saveData.pokedexFlags[BONUS_SPECIES_START + ((i + rand) % NUM_BONUS_SPECIES)] < 4)
                break;
        }

        gUnknown_020314E0->unk598 = BONUS_SPECIES_START + ((i + rand) % NUM_BONUS_SPECIES);
    }
    else
    {
        rand = GetTimeAdjustedRandom();
        if (gMain.eReaderBonus[EREADER_ENCOUNTER_RATE_UP_CARD])
            rand %= 50;
        else
            rand %= 100;

        if (gUnknown_02031520.unk8 < 100)
            rand = 1;

        if ((rand == 0 && gUnknown_020314E0->unk5F0 >= 5) || gUnknown_020314E0->unk12B)
        {
            s16 numSpecialMons = 0;
            gUnknown_020314E0->unk598 = 0;
            if (gMain_saveData.pokedexFlags[SPECIES_AERODACTYL] != 8)
            {
                specialMons[numSpecialMons++] = SPECIES_AERODACTYL;
                if (gMain_saveData.pokedexFlags[SPECIES_AERODACTYL] < 4)
                    gUnknown_020314E0->unk598 = SPECIES_AERODACTYL;
            }

            if (gMain_saveData.pokedexFlags[SPECIES_CHIKORITA] != 8)
            {
                specialMons[numSpecialMons++] = SPECIES_CHIKORITA;
                if (gMain_saveData.pokedexFlags[SPECIES_CHIKORITA] < 4)
                    gUnknown_020314E0->unk598 = SPECIES_CHIKORITA;
            }

            if (gMain_saveData.pokedexFlags[SPECIES_TOTODILE] != 8)
            {
                specialMons[numSpecialMons++] = SPECIES_TOTODILE;
                if (gMain_saveData.pokedexFlags[SPECIES_TOTODILE] < 4)
                    gUnknown_020314E0->unk598 = SPECIES_TOTODILE;
            }

            if (gMain_saveData.pokedexFlags[SPECIES_CYNDAQUIL] != 8)
            {
                specialMons[numSpecialMons++] = SPECIES_CYNDAQUIL;
                if (gMain_saveData.pokedexFlags[SPECIES_CYNDAQUIL] < 4)
                    gUnknown_020314E0->unk598 = SPECIES_CYNDAQUIL;
            }

            if (!gMain.selectedField)
            {
                specialMons[numSpecialMons++] = SPECIES_LATIOS;
                if (gMain_saveData.pokedexFlags[SPECIES_LATIOS] < 4)
                    gUnknown_020314E0->unk598 = SPECIES_LATIOS;
            }
            else
            {
                specialMons[numSpecialMons++] = SPECIES_LATIAS;
                if (gMain_saveData.pokedexFlags[SPECIES_LATIAS] < 4)
                    gUnknown_020314E0->unk598 = SPECIES_LATIAS;
            }

            if (!gUnknown_020314E0->unk598)
            {
                rand = GetTimeAdjustedRandom();
                rand %= numSpecialMons;
                gUnknown_020314E0->unk598 = specialMons[rand];
            }
        }
        else
        {
            s16 rareMons;
            if (gUnknown_020314E0->unk73D == 3)
                rareMons = 1;
            else
                rareMons = 0;

            rand = GetTimeAdjustedRandom();
            rand %= gUnknown_020314E0->unk12E;
            for (i = 0; i < 8 && gUnknown_020314E0->unk130[i] <= rand; i++);

            gUnknown_020314E0->unk598 = gWildMonLocations[gUnknown_020314E0->area][rareMons][i];
        }
    }

    gUnknown_020314E0->unk59C = gUnknown_020314E0->unk598;
}

NAKED
void sub_32484(void)
{
    asm_unified("\n\
    push {r4, r5, r6, r7, lr}\n\
    mov r7, sl\n\
    mov r6, sb\n\
    mov r5, r8\n\
    push {r5, r6, r7}\n\
    ldr r0, _080324D4 @ =gUnknown_020314E0\n\
    ldr r1, [r0]\n\
    movs r3, #0x97\n\
    lsls r3, r3, #1\n\
    adds r2, r1, r3\n\
    movs r1, #0\n\
    strh r1, [r2]\n\
    movs r2, #0\n\
    ldr r4, _080324D8 @ =gMain\n\
    mov sb, r4\n\
    mov ip, sb\n\
    ldr r5, _080324DC @ =gUnknown_086AE5E0\n\
    mov sl, r5\n\
_080324A8:\n\
    lsls r2, r2, #0x10\n\
    asrs r1, r2, #0xf\n\
    mov r0, ip\n\
    ldrb r3, [r0, #4]\n\
    movs r0, #0x34\n\
    muls r0, r3, r0\n\
    adds r1, r1, r0\n\
    ldr r4, _080324E0 @ =gUnknown_086A4A38\n\
    adds r1, r1, r4\n\
    ldrh r5, [r1]\n\
    movs r4, #0\n\
    ldrsh r0, [r1, r4]\n\
    mov r8, r2\n\
    cmp r0, #0x57\n\
    bne _080324F4\n\
    cmp r3, #0\n\
    bne _080324E4\n\
    mov r0, ip\n\
    adds r0, #0xcd\n\
    ldrb r0, [r0]\n\
    b _080324E8\n\
    .align 2, 0\n\
_080324D4: .4byte gUnknown_020314E0\n\
_080324D8: .4byte gMain\n\
_080324DC: .4byte gUnknown_086AE5E0\n\
_080324E0: .4byte gUnknown_086A4A38\n\
_080324E4:\n\
    ldr r1, _080324F0 @ =gUnknown_0200B18E\n\
    ldrb r0, [r1]\n\
_080324E8:\n\
    lsls r0, r0, #1\n\
    add r0, sl\n\
    ldrh r3, [r0]\n\
    b _0803257C\n\
    .align 2, 0\n\
_080324F0: .4byte gUnknown_0200B18E\n\
_080324F4:\n\
    mov r1, sb\n\
    adds r1, #0x74\n\
    adds r0, r0, r1\n\
    ldrb r0, [r0]\n\
    lsls r0, r0, #1\n\
    add r0, sl\n\
    ldrh r3, [r0]\n\
    movs r2, #0\n\
    ldr r7, _080325CC @ =gUnknown_086A3700\n\
    ldr r6, _080325D0 @ =gUnknown_086AE5E0\n\
    adds r4, r1, #0\n\
_0803250A:\n\
    lsls r1, r5, #0x10\n\
    asrs r1, r1, #0x10\n\
    lsls r0, r1, #1\n\
    adds r0, r0, r1\n\
    lsls r0, r0, #3\n\
    adds r0, r0, r7\n\
    ldrb r5, [r0, #0x15]\n\
    adds r0, r5, #0\n\
    cmp r0, #0xcc\n\
    bgt _08032542\n\
    adds r0, r0, r4\n\
    ldrb r0, [r0]\n\
    lsls r0, r0, #1\n\
    adds r0, r0, r6\n\
    ldrh r0, [r0]\n\
    lsls r1, r3, #0x10\n\
    lsls r0, r0, #0x10\n\
    cmp r1, r0\n\
    bge _08032532\n\
    lsrs r3, r0, #0x10\n\
_08032532:\n\
    lsls r0, r2, #0x10\n\
    movs r1, #0x80\n\
    lsls r1, r1, #9\n\
    adds r0, r0, r1\n\
    lsrs r2, r0, #0x10\n\
    asrs r0, r0, #0x10\n\
    cmp r0, #1\n\
    ble _0803250A\n\
_08032542:\n\
    mov r4, r8\n\
    asrs r1, r4, #0xf\n\
    mov r5, ip\n\
    ldrb r2, [r5, #4]\n\
    movs r0, #0x34\n\
    muls r0, r2, r0\n\
    adds r1, r1, r0\n\
    ldr r0, _080325D4 @ =gUnknown_086A4A38\n\
    adds r1, r1, r0\n\
    ldrh r5, [r1]\n\
    ldr r1, _080325D8 @ =gUnknown_020314E0\n\
    ldr r0, [r1]\n\
    movs r4, #0xbe\n\
    lsls r4, r4, #3\n\
    adds r0, r0, r4\n\
    ldrh r0, [r0]\n\
    cmp r0, #0\n\
    bne _0803257C\n\
    lsls r0, r5, #0x10\n\
    asrs r0, r0, #0x10\n\
    lsls r1, r0, #1\n\
    adds r1, r1, r0\n\
    lsls r1, r1, #3\n\
    ldr r0, _080325CC @ =gUnknown_086A3700\n\
    adds r1, r1, r0\n\
    ldrb r0, [r1, #0x15]\n\
    cmp r0, #0xcc\n\
    bls _0803257C\n\
    movs r3, #0\n\
_0803257C:\n\
    ldr r1, _080325D8 @ =gUnknown_020314E0\n\
    ldr r4, [r1]\n\
    ldr r1, _080325DC @ =0x0000059E\n\
    adds r0, r4, r1\n\
    ldrh r1, [r0]\n\
    lsls r0, r5, #0x10\n\
    asrs r0, r0, #0x10\n\
    cmp r1, r0\n\
    bne _08032590\n\
    movs r3, #0\n\
_08032590:\n\
    movs r5, #0x97\n\
    lsls r5, r5, #1\n\
    adds r0, r4, r5\n\
    lsls r2, r3, #0x10\n\
    asrs r2, r2, #0x10\n\
    ldrh r1, [r0]\n\
    adds r2, r2, r1\n\
    strh r2, [r0]\n\
    mov r3, r8\n\
    asrs r1, r3, #0x10\n\
    lsls r3, r1, #1\n\
    adds r5, #2\n\
    adds r0, r4, r5\n\
    adds r0, r0, r3\n\
    strh r2, [r0]\n\
    adds r1, #1\n\
    lsls r1, r1, #0x10\n\
    lsrs r2, r1, #0x10\n\
    asrs r1, r1, #0x10\n\
    cmp r1, #0x18\n\
    bgt _080325BC\n\
    b _080324A8\n\
_080325BC:\n\
    pop {r3, r4, r5}\n\
    mov r8, r3\n\
    mov sb, r4\n\
    mov sl, r5\n\
    pop {r4, r5, r6, r7}\n\
    pop {r0}\n\
    bx r0\n\
    .align 2, 0\n\
_080325CC: .4byte gUnknown_086A3700\n\
_080325D0: .4byte gUnknown_086AE5E0\n\
_080325D4: .4byte gUnknown_086A4A38\n\
_080325D8: .4byte gUnknown_020314E0\n\
_080325DC: .4byte 0x0000059E");
}

void sub_325E0(void)
{
    s16 i;
    u32 rand;
    
    rand = GetTimeAdjustedRandom();
    if (gMain.eReaderBonus[EREADER_ENCOUNTER_RATE_UP_CARD])
        rand %= 50;
    else
        rand %= 100;
    
    if (gUnknown_020314E0->unk59E == SPECIES_PICHU)
        rand = 1;
    
    if ((rand == 0 && gUnknown_020314E0->unk5F0 >= 5) || gUnknown_020314E0->unk12C)
    {
        gUnknown_020314E0->unk598 = SPECIES_PICHU;
    }
    else
    {
        rand = GetTimeAdjustedRandom();
        rand %= gUnknown_020314E0->unk12E;
        
        for (i = 0; i < 25 && gUnknown_020314E0->unk130[i] <= rand; i++);
        
        gUnknown_020314E0->unk598 = gUnknown_086A4A38[gMain.selectedField][i];
    }
    
    gUnknown_020314E0->unk59E = gUnknown_020314E0->unk598;
}

void sub_326F4(void)
{
    gUnknown_020314E0->unk73D = 2;
    gUnknown_020314E0->unk1E5 = 0;
    gUnknown_020314E0->unk1E6 = 1;
    
    sub_1F2A4();
    sub_21B0C();
    sub_1F59C();
    sub_300D8();
    sub_30178();
    
    gUnknown_020314E0->unk1D8 = 0x100;
    gUnknown_020314E0->unk1DA = 0x100;
    
    sub_30480();
    sub_304C8();
    sub_31144();
    sub_313A0();
    sub_2E6AC();
    sub_31B30();
}

void sub_3276C(void)
{
    sub_19B90();
    sub_327C0();
    
    if (!gMain.unkF)
        sub_328C8();
    
    sub_32DF8();
    
    if (gUnknown_020314E0->unk29C)
    {
        gUnknown_020314E0->unk29C--;
        if (!gUnknown_020314E0->unk29C)
            m4aMPlayVolumeControl(&gMPlayInfo_BGM,0xffff,0x100);
    }
}

void sub_327C0(void)
{
    s32 temp;
    
    sub_4F814();
    sub_1A0F4();
    sub_2CA9C();
    
    if (gUnknown_020314E0->unk68 < 0x5a)
    {
        sub_304C8();
        sub_31498();
    }
    
    if (gUnknown_020314E0->unk13 < 3)
    {
        if ((gUnknown_020314E0->unk344 & 0xFFFF00) == 0x300)
        {
            gUnknown_020314E0->unk728 = 1;
        }
        else
        {
            gUnknown_020314E0->unk728 = 0;
        }
    }
    else
    {
        gUnknown_020314E0->unk728 = 0;
    }
    
    if (gUnknown_020314E0->unk68 < 0x96)
    {
        sub_2E6AC();
        sub_313A0();
    }
    if (gUnknown_020314E0->unk68 < 0xC4)
    {
        sub_30178();
        sub_2F140();
    }
    if (gUnknown_020314E0->unk68 < 0xCA)
    {
        sub_2FCD0();
    }
    if (gUnknown_020314E0->unk68 < 0xDC)
    {
        sub_1F59C();
    }
    
    sub_308DC();
    
    if (0x76 < gUnknown_020314E0->unk68)
    {
        sub_2F504();
        sub_30EB4();
    }
    
    sub_2CE80();
    
    if (0xA8 < gUnknown_020314E0->unk68)
        sub_2D104();
    
    sub_203CC();
    sub_21B0C();
    sub_1D128();
    sub_31B30();
    
    if (gUnknown_020314E0->unk194)
        sub_225F0();
    
    sub_472E4();
}

void sub_328C8(void)
{
    sub_300D8();
    sub_32968();
    sub_1F2A4();
    
    if (gUnknown_020314E0->unk600)
        gUnknown_020314E0->unk600--;
    
    sub_2F26C();
    sub_2E67C();
    sub_31144();
    
    if (!(gMain.unkF & 0x20))
        sub_2F79C();
}

void sub_32914(void)
{
    if (!gMain.unkF)
    {
        switch (gUnknown_020314E0->unk25)
        {
        case 1:
            sub_32B74();
            break;
        case 3:
            sub_329B0();
            break;
        case 4:
            sub_1C560();
            break;
        }
        
        gUnknown_020314E0->unk26 = 0x3C;
    }
}

void sub_32968(void)
{
    if (gUnknown_020314E0->unk26)
        gUnknown_020314E0->unk26--;
    
    switch (gUnknown_020314E0->unk25)
    {
    case 1:
        sub_32BE4();
        break;
    case 3:
        sub_329F4();
        break;
    case 4:
        sub_1C5AC();
        break;
    }
}

void sub_329B0(void)
{
    gUnknown_020314E0->unk28 = 0xB4;
    gUnknown_020314E0->unk1BA = 0xB4;
    gUnknown_020314E0->unk3C = 500000;
    gMain.blendControl = 0xCE;
    gMain.blendBrightness = 0;
    gUnknown_020314E0->unk5F7 = 1;
}
