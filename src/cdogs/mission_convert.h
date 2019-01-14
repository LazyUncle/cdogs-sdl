/*
    C-Dogs SDL
    A port of the legendary (and fun) action/arcade cdogs.
    Copyright (c) 2014, 2016, 2019 Cong Xu
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/
#pragma once

#include "mission.h"
#include "map.h"

void MissionConvertToType(Mission *m, Map *map, MapType type);
bool MissionTrySetTile(Mission *m, struct vec2i pos, const uint16_t tile);
uint16_t MissionGetTile(Mission *m, struct vec2i pos);

void MissionStaticLayout(Mission *m, struct vec2i oldSize);
bool MissionStaticTryAddItem(Mission *m, const MapObject *mo, const struct vec2i pos);
bool MissionStaticTryRemoveItemAt(Mission *m, const struct vec2i pos);
bool MissionStaticTryAddCharacter(Mission *m, int ch, struct vec2i pos);
bool MissionStaticTryRemoveCharacterAt(Mission *m, struct vec2i pos);
bool MissionStaticTryAddObjective(Mission *m, int idx, int idx2, struct vec2i pos);
bool MissionStaticTryRemoveObjectiveAt(Mission *m, struct vec2i pos);
bool MissionStaticTryAddKey(Mission *m, int k, struct vec2i pos);
bool MissionStaticTryRemoveKeyAt(Mission *m, struct vec2i pos);
bool MissionStaticTrySetKey(Mission *m, int k, struct vec2i pos);
bool MissionStaticTryUnsetKeyAt(Mission *m, struct vec2i pos);
