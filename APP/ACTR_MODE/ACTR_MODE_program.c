/***************************************************************************************************/
/*                                             Includes                                            */
/***************************************************************************************************/
#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "HEEP_interface.h"
#include "ASET_MODE_interface.h"
#include "ARUN_MODE_interface.h"
#include "ACTR_MODE_cfg.h"
#include "ACTR_MODE_interface.h"
#include "avr/interrupt.h"


/***************************************************************************************************/
/*                                       Functions' definitions                                    */
/***************************************************************************************************/

/*Intializing Two flags*/
u8_t setMODE = SWITCHOFF ;
u8_t runMODE = SWITCHOFF ;

/*intializing temperature with default*/
u8_t setTEMP = DEFAULT_SET_TEMP ;
u8_t curTEMP = DEFAULT_CUR_TEMP ;

void actr_mode_init_System(void)
{
    aset_mode_init();
    arun_mode_init();
    sei();

    /*Return Function*/
    return;
}

void actr_mode_switchStR(void)
{
    /*stooring setting Temp while switching*/
    heeprom_writeByte(EEPROM_BLOCK_0 , 10 ,setTEMP) ;

    /*turn off selected mode*/
    setMODE = SWITCHOFF ;

    /*turn on selected mode*/
    runMODE = SWITCHON ;

    /*Return Function*/
    return ;
}

void actr_mode_controlmode(void) 
{
    /*rum mode which its flag is raised*/

    /*if set mode flag raised*/
    if(setMODE == SWITCHON)
    {
        aset_mode_setTemp();
    }
    
    /*if set mode flag raised*/
    else if(runMODE == SWITCHON)
    {
        arun_mode_start();
    }
    
    else
    {
        /*run sleep mode*/
    }
    
    /*Return Function*/
    return ;
}