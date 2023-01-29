/***************************************************************************************************/
/*                                             Includes                                            */
/***************************************************************************************************/

#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "MDIO_interface.h"
#include "MADC_interface.h"
#include "HTEMP_SENSOR_cfg.h"
#include "HTEMP_SENSOR_interface.h"


/***************************************************************************************************/
/*                                       Functions' definitions                                    */
/***************************************************************************************************/

void htemp_sensor_init(void)
{
    /*Intializing adc configuration to use*/
    madc_init(AVCC_MODE ,ADC_10_BITS , ADC_PRESCALER_16);

    /*set mode Pin used to read analog*/
    mdio_setPinStatus(config_TEMPSENSOR_PORT , config_TEMPSENSOR_PIN , INPUT_FLOAT);

    /*Return Function*/
    return ;
}

void htemp_sensor_Read(u8_t* p8_temp)
{
    static u16_t au16_reading ;
    static u32_t au32_Voult ;

    /*converting the reading*/
    madc_singleConversion(config_TEMPSENSOR_CHANNEL ,&au16_reading);
    
    /*converting to celesios*/
    au32_Voult = (u32_t)au16_reading * 500;

    *(p8_temp) = (u8_t)(au32_Voult / 1023);

    /*Return Function*/
    return;
}