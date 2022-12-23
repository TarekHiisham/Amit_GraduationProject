/*Header file guard*/
#ifndef __HTEMP_SENSOR_CFG_H__
#define __HTEMP_SENSOR_CFG_H__

/***************************************************************************************************/
/*                                       Configuration macros                                      */
/***************************************************************************************************/

/*  

    LM35 Tempreture Sensor used 
    Sensor gain (mV/Deg C)	10

*/

/*sensor connected to channel0 in microcontroller  */
#define config_TEMPSENSOR_CHANNEL        (ADC_CHANNEL_0)

/*sensor connected to PORTA*/
#define config_TEMPSENSOR_PORT           (PORTA)

/*sensor connected to pin0*/
#define config_TEMPSENSOR_PIN            (PIN0)


#endif /*__HTEMP_SENSOR_CFG_H__*/