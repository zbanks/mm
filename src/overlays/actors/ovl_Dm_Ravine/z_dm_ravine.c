/*
 * File: z_dm_ravine.c
 * Overlay: ovl_Dm_Ravine
 * Description: Link Riding Through Lost Woods Cutscene - Tree Trunk
 */

#include "z_dm_ravine.h"

#define FLAGS 0x00000030

#define THIS ((DmRavine*)thisx)

void DmRavine_Init(Actor* thisx, GlobalContext* globalCtx);
void DmRavine_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmRavine_Action(Actor* thisx, GlobalContext* globalCtx);
void DmRavine_Update(Actor* thisx, GlobalContext* globalCtx);
void DmRavine_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Dm_Ravine_InitVars = { ACTOR_DM_RAVINE,
                                       ACTORCAT_ITEMACTION,
                                       FLAGS,
                                       OBJECT_KEIKOKU_DEMO,
                                       sizeof(DmRavine),
                                       (ActorFunc)DmRavine_Init,
                                       (ActorFunc)DmRavine_Destroy,
                                       (ActorFunc)DmRavine_Update,
                                       (ActorFunc)DmRavine_Draw };

void DmRavine_Init(Actor* thisx, GlobalContext* globalCtx) {
    u8 flag;

    flag = gSaveContext.perm.weekEventReg[0];
    if (((flag & 0x10) | cREG(0)) != 0) {
        Actor_MarkForDeath(thisx);
        return;
    }

    THIS->loaded = false;
    globalCtx->roomContext.unk7A[0] = 1;
    globalCtx->roomContext.unk7A[1] = 0;
    THIS->state = 0;
    Actor_SetScale(thisx, 1.0f);
    THIS->actionFunc = &DmRavine_Action;
}

void DmRavine_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

// This function is unused, but takes two word-sized arguments
// `thisx` & `globalCtx` are guesses; but it could be something else
void DmRavine_Action(Actor* thisx, GlobalContext* globalCtx) {
}

void DmRavine_Update(Actor* thisx, GlobalContext* globalCtx) {
    RoomContext* roomCtx;

    switch (THIS->state) {
        case 0:
            return;
        case 1:
            THIS->loaded = true;
            globalCtx->roomContext.unk7A[1]++;
            if (globalCtx->roomContext.unk7A[1] > 254) {
                globalCtx->roomContext.unk7A[1] = 254;
                if (globalCtx->csCtx.frames > 700) {
                    globalCtx->roomContext.unk7A[1] = 255;
                    globalCtx->roomContext.unk7A[0] = 0;
                    THIS->state++;
                }
            }
            break;
        case 2:
            Actor_MarkForDeath(thisx);
            break;
    }
}

void DmRavine_Draw(Actor* thisx, GlobalContext* globalCtx) {
}
