// swap_block.inc.c

#define SWAP_BLOCK_SCALE 1.0f
#define SWAP_BLOCK_SOUND_START_TIMER 150
#define SWAP_BLOCK_SOUND_TIMER 30
#define SWAP_BLOCK_BEEPS 3

// don't touch
#define SWAP_BLOCK_TIMER                    (SWAP_BLOCK_BEEPS * SWAP_BLOCK_SOUND_TIMER) + SWAP_BLOCK_SOUND_START_TIMER

void bhv_block(void) {
    
    obj_scale(o,SWAP_BLOCK_SCALE);
    
	// makes the block active value a different value so that the code at the bottom of the function doesn't
	// run every frame
    if (o->oBlockActive == 0) {
        o->oBlockActive = 2;
    } else if (o->oBlockActive == 1) {
        o->oBlockActive = 3;
    }
    
	// check to see if it should be the alternate beep block
    if (o->oBehParams == SWAP_BOX_BEEP_MODE_ALTERNATE && o->oAltBlockSwap == 0) {
        if (o->oTimer == 0) {
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
                
                if (o->oBehParams == SWAP_BOX_BEEP_MODE_WITH_SOUND) {
                    // play swap sound (find better sound effect)
                    play_sound(SOUND_GENERAL2_BOBOMB_EXPLOSION, gGlobalSoundSource);
                }
                
            }
			
			if (o->oTimer % SWAP_BLOCK_SOUND_TIMER == 0) {
                cur_obj_set_model(MODEL_NONE);
				
                if (o->oBehParams == SWAP_BOX_BEEP_MODE_WITH_SOUND) {
                    // play beep sound
                    play_sound(SOUND_GENERAL2_RIGHT_ANSWER, gGlobalSoundSource);
                }
            } else if (o->oTimer % SWAP_BLOCK_SOUND_TIMER == 10) {
				// fancy math to set the model back to the correct model
				cur_obj_set_model((0x53 + (o->oBlockActive * 2)) + o->oAltBlockSwap);
			}
				
        }
    } else {
        
        if (!(gMarioStates[0].action & ACT_FLAG_AIR) && gPlayer1Controller->buttonPressed & A_BUTTON) {
            // code for "jump mode" making it turn on and off when you jump (BUG: swimming will cause the blocks to activate)
            
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
		// adding oAltBlockSwap makes it become its alt as the alt blocks id is one higher than the base one
        cur_obj_set_model(MODEL_ZSWAP_BLOCK_ON + o->oAltBlockSwap);
		// spawns an object with no model but the collision of the box to make it seem like the box is solid
        o->oLoadedObject = spawn_object(o, MODEL_NONE, bhvSwapBoxOn);
        obj_scale(o->oLoadedObject,SWAP_BLOCK_SCALE);
		
    } else if (o->oBlockActive == 0) {
		
        cur_obj_set_model(MODEL_ZSWAP_BLOCK_OFF + o->oAltBlockSwap);
		// delete fake collision box when the model is off
        obj_mark_for_deletion(o->oLoadedObject);
    }
}
