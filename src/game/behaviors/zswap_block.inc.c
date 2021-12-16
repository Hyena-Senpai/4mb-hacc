// swap_block.inc.c
#define BEH_PARAMS_BYTE_4 0xFF000000
#define BEH_PARAMS_BYTE_2 0x00FF0000

#define SWAP_BLOCK_SCALE 1
#define SWAP_BLOCK_SOUND_START_TIMER 150
#define SWAP_BLOCK_SOUND_TIMER 30
#define SWAP_BLOCK_BEEPS 3

// don't touch
#define SWAP_BLOCK_TIMER (SWAP_BLOCK_BEEPS * SWAP_BLOCK_SOUND_TIMER) + SWAP_BLOCK_SOUND_START_TIMER

void bhv_block(void) {
    
    obj_scale(o,SWAP_BLOCK_SCALE);
    
    if (o->oBlockActive == 0) {
        o->oBlockActive = 2;
    } else if (o->oBlockActive == 1) {
        o->oBlockActive = 3;
    }
    
    if (o->oBehParams == SWAP_BOX_BEEP_MODE_ALTERNATE && o->oAltBlockSwap == 0) {
        if (o->oTimer == 0) {
            cur_obj_set_model(MODEL_ZSWAPBLOCKON);
            o->oLoadedObject = spawn_object(o, MODEL_NONE, bhvSwapBoxOn);
            o->oAltBlockSwap = 1;
            o->oBlockActive = 3;
        }
    } 
    
    if (o->oBehParams != SWAP_BOX_JUMP_MODE) {
        if (o->oTimer >= SWAP_BLOCK_SOUND_START_TIMER) {
            if (o->oTimer == SWAP_BLOCK_TIMER) {
                switch(o->oBlockActive) {
                    case 3:
                        o->oBlockActive = 0;
                        break;
                    case 2:
                        o->oBlockActive = 1;
                        break;
                }
                
                o->oTimer = 0;
                
                if (o->oBehParams == 3) {
                    
                    play_sound(SOUND_GENERAL2_BOBOMB_EXPLOSION, gGlobalSoundSource);
                }
                
            } else if (o->oTimer % SWAP_BLOCK_SOUND_TIMER == 0) {
                
                if (o->oBehParams == 3) {
                    
                    play_sound(SOUND_GENERAL2_RIGHT_ANSWER, gGlobalSoundSource);
                }
            }
        }
    } else {
        
        if (!(gMarioStates[0].action & ACT_FLAG_AIR) && gPlayer1Controller->buttonPressed & A_BUTTON) {
            
            o->oJumpActive = 1;
            
            switch(o->oBlockActive) {
                case 3:
                    o->oBlockActive = 0;
                    break;
                case 2:
                    o->oBlockActive = 1;
                    break;
            }
        }
        
    }
    
    if (o->oBlockActive == 1) {
        cur_obj_set_model(MODEL_ZSWAPBLOCKON);
        o->oLoadedObject = spawn_object(o, MODEL_NONE, bhvSwapBoxOn);
        obj_scale(o->oLoadedObject,SWAP_BLOCK_SCALE);
    } else if (o->oBlockActive == 0) {
        cur_obj_set_model(MODEL_ZSWAPBLOCKOFF);
        obj_mark_for_deletion(o->oLoadedObject);
    }
}


/*//#define SWAP_BLOCK_SCALE 0.5f
#define SWAP_BLOCK_SOUND_START_TIMER 150
#define SWAP_BLOCK_SOUND_TIMER 30
#define SWAP_BLOCK_BEEPS 3

// don't touch
#define SWAP_BLOCK_TIMER (SWAP_BLOCK_BEEPS * SWAP_BLOCK_SOUND_TIMER) + SWAP_BLOCK_SOUND_START_TIMER

void bhv_block(void) {
    
    //obj_scale(o->SWAP_BLOCK_SCALE);


    
    if (o->oAction == 0) {
        o->oAction = 2;
    } else if (o->oAction == 1) {
        o->oAction = 3;
    }
    if (o->oBehParams == 0) {
        if (o->oTimer >= SWAP_BLOCK_SOUND_START_TIMER) {
            if (o->oTimer == SWAP_BLOCK_TIMER) {
                switch(o->oAction) {
                    case 3:
                        o->oAction = 0;
                        break;
                    case 2:
                        o->oAction = 1;
                        break;
                }
                
                o->oTimer = 0;
                
                if ((o->oBehParams2ndByte) != 0) {
                    
                    play_sound(SOUND_GENERAL2_BOBOMB_EXPLOSION, gGlobalSoundSource);
                }
                
            } else if (o->oTimer % SWAP_BLOCK_SOUND_TIMER == 0) {
                
                if ((o->oBehParams2ndByte) != 0) {
                    
                    play_sound(SOUND_GENERAL2_RIGHT_ANSWER, gGlobalSoundSource);
                }
            }
        }
    } 
    
    else {
        
        if (!(gMarioStates[0].action & ACT_FLAG_AIR) && gPlayer1Controller->buttonPressed & A_BUTTON) {
            
            o->oAction = 1;
            
            switch(o->oAction) {
                case 3:
                    o->oAction = 0;
                    break;
                case 2:
                    o->oAction = 1;
                    break;
            }
        }
        
    }
    
    if (o->oAction == 1) {
        cur_obj_set_model(MODEL_ZSWAPBLOCKON);
        o->oLoadedObject = spawn_object(o, MODEL_NONE, bhvSwapBoxOn);
        obj_scale(0, 100);
    } else if (o->oAction == 0) {
        cur_obj_set_model(MODEL_ZSWAPBLOCKOFF);
        obj_mark_for_deletion(o);
    }
}

/*behavior_data.h 
extern const BehaviorScript bhvSwapBox[];
extern const BehaviorScript bhvSwapBoxOn[];

behavior_data.c
const BehaviorScript bhvSwapBox[] = {
    BEGIN(OBJ_LIST_SURFACE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_block),
    END_LOOP(),
};

const BehaviorScript bhvSwapBoxOn[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(beat_block_on_collision),
    BEGIN_LOOP(),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

//behavior actions.h
void bhv_block(void)

//behavior actions c
#include "behaviors/zswap_block.inc.c"

behavior data
// zswap_block.inc.c


#define SWAP_BLOCK_SCALE 0.5f
#define SWAP_BLOCK_SOUND_START_TIMER 150
#define SWAP_BLOCK_SOUND_TIMER 30
#define SWAP_BLOCK_BEEPS 3

// don't touch
#define SWAP_BLOCK_TIMER (SWAP_BLOCK_BEEPS * SWAP_BLOCK_SOUND_TIMER) + SWAP_BLOCK_SOUND_START_TIMER

void bhv_block(void) {
    
    obj_scale(o,SWAP_BLOCK_SCALE);
    
    if (o->oBlockActive == 0) {
        o->oBlockActive = 2;
    } else if (o->oBlockActive == 1) {
        o->oBlockActive = 3;
    }
    if ((o->oBehParams & BEH_PARAMS_BYTE_1) != 0) {
        if (o->oTimer >= SWAP_BLOCK_SOUND_START_TIMER) {
            if (o->oTimer == SWAP_BLOCK_TIMER) {
                switch(o->oBlockActive) {
                    case 3:
                        o->oBlockActive = 0;
                        break;
                    case 2:
                        o->oBlockActive = 1;
                        break;
                }
                
                o->oTimer = 0;
                
                if ((o->oBehParams & BEH_PARAMS_BYTE_2) != 0) {
                    
                    play_sound(SOUND_GENERAL2_BOBOMB_EXPLOSION, gGlobalSoundSource);
                }
                
            } else if (o->oTimer % SWAP_BLOCK_SOUND_TIMER == 0) {
                
                if ((o->oBehParams & BEH_PARAMS_BYTE_2) != 0) {
                    
                    play_sound(SOUND_GENERAL2_RIGHT_ANSWER, gGlobalSoundSource);
                }
            }
        }
    } else {
        
        if (!(gMarioStates[0].action & ACT_FLAG_AIR) && gPlayer1Controller->buttonPressed & A_BUTTON) {
            
            o->oJumpActive = 1;
            
            switch(o->oBlockActive) {
                case 3:
                    o->oBlockActive = 0;
                    break;
                case 2:
                    o->oBlockActive = 1;
                    break;
            }
        }
        
    }
    
    if (o->oBlockActive == 1) {
        cur_obj_set_model(MODEL_BEAT_BLOCK_ON);
        o->oSpawnedBox = spawn_object(o, MODEL_NONE, bhvSwapBoxOn);
        obj_scale(o->oSpawnedBox,SWAP_BLOCK_SCALE);
    } else if (o->oBlockActive == 0) {
        cur_obj_set_model(MODEL_BEAT_BLOCK_OFF);
        mark_obj_for_deletion(o->oSpawnedBox);
    }
}

*/