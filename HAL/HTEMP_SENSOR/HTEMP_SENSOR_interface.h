/*Header file guard*/
#ifndef __HTEMP_SENSOR_INTERFACE_H__
#define __HTEMP_SENSOR_INTERFACE_H__

/***************************************************************************************************/
/*                                         Interfacing macros                                      */
/***************************************************************************************************/

/***************************************************************************************************/
/*                                        Functions' prototypes                                    */
/***************************************************************************************************/

/**
 * @brief This Function to initialize sensor pins 
 * 
 */
void htemp_sensor_init(void);


/**
 * @brief This Function to read analog signal from specified Pin
 * 
 * @param u8_temp 
 */
void htemp_sensor_Read(u8_t* u8_temp);


#endif /*__HTEMP_SENSOR_INTERFACE_H__*/