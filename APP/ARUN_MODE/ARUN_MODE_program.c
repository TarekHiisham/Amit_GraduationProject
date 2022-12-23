/***************************************************************************************************/
/*                                             Includes                                            */
/***************************************************************************************************/
#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"

/*------------------------------- Include modules interfaces used in setting mode ---------------- */
#include "MTIMER_interface.h"
#include "MEXTI_interface.h"
#include "HPBUTT_interface.h"
#include "HLED_interface.h"
#include "HTEMP_SENSOR_interface.h"
#include "HRELAY_interface.h"
#include "HSEV_SEG_interface.h"
/*-------------------------------------------------------------------------------------------------*/

#include "ARUN_MODE_cfg.h"
#include "ARUN_MODE_interface.h"
#include "ACTR_MODE_interface.h"


/***************************************************************************************************/
/*                                           Common Macros                                         */
/***************************************************************************************************/

#define READING        (10)
#define CHECK_TIME     (10)

/***************************************************************************************************/
/*                                       Functions' definitions                                    */
/***************************************************************************************************/

static u8_t reading_Avg = 0 ;
static u8_t gu8_counter = 0 ; 

static void arun_mode_checkTemp(void)
{
    /*getting reading of ADC*/
    htemp_sensor_Read(&curTEMP) ;

    /*store reading in array*/
    reading_Avg += curTEMP ;

    /*Increament counter*/
    gu8_counter++ ;

    /*Return Function*/
    return;
}

void arun_mode_init(void)
{
    /*ُEnable External Interrupt 0 , 1*/
    mexti_enableExternalInterrupt(INT2_REQ_NUM) ;

    /*Serving ISR when press ON Button*/
    mexti_attachISR(INT2_REQ_NUM , FALLING_EDGE_MODE , actr_mode_switchStR);

    /*checking on reading sensor temperature every 100 ms*/
    mtimer_delayMs_asynchronous(TIMER_CHANNEL_0 , PERIOD_CHECK , arun_mode_checkTemp , TIMER_PERIODIC_OPERATION) ;

    /*Intializing push Buttons Status*/
    hpbutt_init(PUSH_BUTTON_0);

    /*Intializing tempreture sensor*/
    htemp_sensor_init();

    /*initializing relay*/
    hrelay_init();
    
    /*Return Function*/
    return;
}

void arun_mode_start(void)
{
    /*while run flag is raised*/
    while(runMODE == SWITCHON)
    {

        /* after getting 10 reading in reading_Arr */
        if(gu8_counter == CHECK_TIME)
        {
            /*
                display current Temperature on 7seg 
            */
        
            /*Calculate average of 10 reading*/
            reading_Avg /= READING ;

            /*
                -compare Average with set temperature
                - if Avg = setTemp for 3 second
                    - switchoff runMODE flag

                - if Avg > setTEMP by 5 degree 
                    -Turn On cooling , Turn Off Heating by switching Relay
                
                - if Avg < setTEMP by 5 degree 
                    -Turn Off cooling , Turn On Heating by switching Relay
            */
        
            /*reset counter*/
            gu8_counter = 0 ;
        }
        else 
        {
            /*Do Nothing*/
        }
    }

    /*Return Function*/
    return;
}
