/***************************************************************************************************/
/*                                             Includes                                            */
/***************************************************************************************************/
#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "util/delay.h"

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

#define READING              (10)
#define CHECK_TIME           (10)
#define SEV_SEGMENT_FREQ1    (10)
#define FIVE_DEGREE          (5)
/***************************************************************************************************/
/*                                       Functions' definitions                                    */
/***************************************************************************************************/

static u16_t reading_Avg = 0 ;
static u8_t  gu8_counter = 0 ; 

void arun_mode_checkTemp(void)
{
    /*getting reading of ADC*/
    htemp_sensor_Read(&curTEMP) ;

    /*store reading in array*/
    reading_Avg += curTEMP ;

    /*Increament counter*/
    gu8_counter++ ;

    hled_toggleLedValue(LED0);

    /*Return Function*/
    return;
}

void arun_mode_init(void)
{
    hled_init(LED0);

    /*ُEnable External Interrupt 2*/
    mexti_enableExternalInterrupt(INT2_REQ_NUM) ;

    /*Intializing Timer0*/
    mtimer_init(TIMER_CHANNEL_0 , TIMER0_DELAY_MODE , TIMER2_DELAY_PRESCALER);

    /*Serving ISR when press ON Button*/
    mexti_attachISR(INT2_REQ_NUM , FALLING_EDGE_MODE , actr_mode_switchStR);

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
        /*
            display current Temperature on 7seg 
        */    
        hsev_seg_displayNumber(curTEMP);
            
        /* after getting 10 reading in reading_Arr */
        if(gu8_counter == CHECK_TIME)
        {
            /*Calculate average of 10 reading*/
            reading_Avg /= READING ;

            /*
                -compare Average with set temperature
                - if Avg = setTemp for 3 second
                    - switchoff runMODE flag    
            */
            /*
                - if Avg > setTEMP by 5 degree 
                    -Turn On cooling , Turn Off Heating by switching Relay
            */
            if( (reading_Avg - setTEMP ) >= FIVE_DEGREE )
            {
                hrelay_switchON();
            }
            /*    
                - if Avg < setTEMP by 5 degree 
                    -Turn Off cooling , Turn On Heating by switching Relay
            */
            else if ((setTEMP - reading_Avg ) >= FIVE_DEGREE)
            {
                hrelay_switchOFF();
            }
            else 
            {
                /*Do Nothing*/
            }

            /*reset counter*/
            gu8_counter = 0 ;

            /*reset average*/
            reading_Avg = 0 ;
        }
        else 
        {
            /*Do Nothing*/
        }
    }

    /*Return Function*/
    return;
}
