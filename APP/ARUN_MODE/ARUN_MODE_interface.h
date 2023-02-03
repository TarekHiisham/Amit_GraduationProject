/*Header file guard*/
#ifndef __ARUN_MODE_INTERFACE_H__
#define __ARUN_MODE_INTERFACE_H__

/***************************************************************************************************/
/*                                         Interfacing parameters                                  */
/***************************************************************************************************/

#define RESET                (0)
#define ENDTIMEPROG          (5)

extern u8_t  gu8_endProcess ;

/***************************************************************************************************/
/*                                        Functions' prototypes                                    */
/***************************************************************************************************/

/**
 * @brief This Function to init modules running in runMODE
 * 
 */
void arun_mode_init(void);


/**
 * @brief This Function to detect cuurent tempreture 
 * 
 */
void arun_mode_start(void);

/**
 * @brief This Function to check Temperature every 100 ms
 * 
 */
void arun_mode_checkTemp(void);


#endif /*__ARUN_MODE_INTERFACE_H__*/