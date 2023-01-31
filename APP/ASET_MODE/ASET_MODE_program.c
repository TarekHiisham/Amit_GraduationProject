/***************************************************************************************************/
/*                                             Includes                                            */
/***************************************************************************************************/
#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"

/*------------------------------- Include modules interfaces used in setting mode ---------------- */
#include "MEXTI_interface.h"
#include "HEEP_interface.h"
#include "HPBUTT_interface.h"
#include "HSEV_SEG_interface.h"
/*-------------------------------------------------------------------------------------------------*/

#include "ASET_MODE_cfg.h"
#include "ASET_MODE_interface.h"
#include "ACTR_MODE_interface.h"
#include "util/delay.h"

/***************************************************************************************************/
/*                                       Functions' definitions                                    */
/***************************************************************************************************/

#define FIVE_DEGREE        (5)

/*private variables used here only*/
static u8_t gu8_validtime = VALID_RESET ;

static void Increament(void)
{
    /*enter setting mode for First Time*/
    if(setMODE == SWITCHOFF && runMODE == SWITCHOFF)
    {          
        /*raising set mode flag to ON*/
        setMODE = SWITCHON ;

        /*Reset Deafault of set temperature*/
        setTEMP = DEFAULT_SET_TEMP;
    }

    /*if set mode are already run*/
    else if (setMODE == SWITCHON)
    {
        /*reset valid time*/
        gu8_validtime = VALID_RESET ;
        
        /*if set temp reach max temp*/
        if( setTEMP == MAX_TEMP )
        {
            setTEMP = MAX_TEMP ;
        }
        else 
        { 
            /*increament by one*/        
            setTEMP += FIVE_DEGREE ;
        } 
    }
    else
    {
        /*Do Nothing*/
    }

    /*Return Function*/
    return;
}

static void Decreament(void)
{
    /*enter setting mode for First Time*/
    if(setMODE == SWITCHOFF && runMODE == SWITCHOFF)
    {
        /*raising set mode flag to ON*/
        setMODE = SWITCHON ;

        /*Reset Deafault of set temperature*/
        setTEMP = DEFAULT_SET_TEMP;
    }
    
    /*if set mode are already run*/
    else if (setMODE == SWITCHON)
    {
        /*reset valid time*/
        gu8_validtime = VALID_RESET ;
        
        /*if set temp reach min temp*/
        if(setTEMP == MIN_TEMP )
        {
            setTEMP = MIN_TEMP ;
        }
        else
        {
            setTEMP -= FIVE_DEGREE  ;
        }
    }
    else
    {
        /*Do Nothing*/
    }
    
    /*Return Function*/
    return;
}

void aset_mode_init(void)
{
    /*ُEnable External Interrupt 0 , 1*/
    mexti_enableExternalInterrupt(INT2_REQ_NUM);
    mexti_enableExternalInterrupt(INT1_REQ_NUM);

    /*Serving ISR when press + Button*/
    mexti_attachISR(INT2_REQ_NUM , FALLING_EDGE_MODE , Increament);
    
    /*Serving ISR when press - Button*/
    mexti_attachISR(INT1_REQ_NUM , FALLING_EDGE_MODE , Decreament );

    /*Intializing push Buttons Status*/
    hpbutt_init(PUSH_BUTTON_1);
    hpbutt_init(PUSH_BUTTON_2);

    /*Initializing 2 seven segments*/
    hsev_seg_init(SEV_SEG_1);
    hsev_seg_init(SEV_SEG_2);
   
    /*initialize EEPROM*/
    heeprom_init();

    /*Return Function*/
    return;
}

void aset_mode_setTemp(void)
{
    /*while setMODE flag is ON the program in setting Temp Mode*/
    while(setMODE  == SWITCHON)
    {

    /*display 1 second*/    
    for(u8_t i = 0 ; i < (BLINKING/20) ; i++)
    {    
        hsev_seg_displayNumber(setTEMP);
    }

    /*increament valid time in setting mode*/
    gu8_validtime ++ ;

    /*waiting for 5 second cause program time out*/
    if(gu8_validtime == VALID_MAX )
    {

      /*Reset validation time*/  
      gu8_validtime = VALID_RESET ;

      /*Reset setMODE flag*/
      setMODE  = SWITCHOFF ; 
      
      /*Reset system with default*/ 
      actr_mode_ResetSystem();    
    }
    else
    {
        /*Do Nothing*/
    }

    /*Blinking 1 second*/
    _delay_ms(BLINKING);
    } 
   
    /*Return Function*/
    return;
}