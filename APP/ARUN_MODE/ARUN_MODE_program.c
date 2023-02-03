/***************************************************************************************************/
/*                                             Includes                                            */
/***************************************************************************************************/
#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "util/delay.h"

/*------------------------ Include modules interfaces used in setting mode ----------------------- */
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
#define RESET                (0)
#define ENDTIMEPROG          (5)
/***************************************************************************************************/
/*                                       Functions' definitions                                    */
/***************************************************************************************************/

static u16_t reading_Avg    = RESET ;
static u8_t  gu8_counter    = RESET ; 
static u8_t  gu8_endProcess = ENDTIMEPROG ;

void arun_mode_checkTemp(void)
{
    /*getting reading of ADC*/
    htemp_sensor_Read(&curTEMP) ;

    /*store reading in array*/
    reading_Avg += curTEMP ;

    /*Increament counter*/
    gu8_counter++ ;

    /* after getting 10 reading in reading_Arr */
    if(gu8_counter == CHECK_TIME)
        {

            /*Calculate average of 10 reading*/
            reading_Avg /= READING ;

            /* compare Average with set temperature  */

            /*
                -if average of reading = set temperature for 3 second
                    -turn off run mode 
            */
            if((u8_t)reading_Avg == setTEMP)
            {
                gu8_endProcess-- ;
                if(gu8_endProcess == RESET)
                { 
                    actr_mode_ResetSystem();
                }
                else
                {
                    /*Do Nothing*/
                }
            }
            /*
                - if Avg > setTEMP by 5 degree 
                    -Turn On cooling , Turn Off Heating by switching Relay
            */
            else if(((u8_t)reading_Avg - setTEMP) >= FIVE_DEGREE )
            {
                /*switch relay on to run cool ele.*/
                hrelay_switchON();  

                /*turn led on*/
                hled_ledValueON(LED0);

                /*reset end process time*/
                gu8_endProcess = ENDTIMEPROG ;              
            }
            /*    
                - if Avg < setTEMP by 5 degree 
                    -Turn Off cooling , Turn On Heating by switching Relay
            */
            else if ((setTEMP - (u8_t)reading_Avg) >= FIVE_DEGREE)
            {
                /*swetch relay off to run heat ele.*/
                hrelay_switchOFF();

                /*toggle led*/
                hled_toggleLedValue(LED0);

                /*reset end process time*/
                gu8_endProcess = ENDTIMEPROG ;              
            }
            
            else
            {
                /*Do Nothing*/
            }
            
            /*reset counter*/
            gu8_counter = RESET ;

            /*reset average*/
            reading_Avg = RESET ;
        }
        else 
        {
            /*Do Nothing*/
        }

    /*Return Function*/
    return;
}

void arun_mode_init(void)
{
    hled_init(LED0);

    /*ُEnable External Interrupt 2*/
    mexti_enableExternalInterrupt(INT0_REQ_NUM) ;

    /*Intializing Timer0*/
    mtimer_init(TIMER_CHANNEL_0 , TIMER0_DELAY_MODE , TIMER_DELAY_PRESCALER);

    /*Serving ISR when press ON Button*/
    mexti_attachISR(INT0_REQ_NUM , LOGICAL_CHANGE_MODE , actr_mode_switch);

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
    }

    /*Return Function*/
    return;
}
