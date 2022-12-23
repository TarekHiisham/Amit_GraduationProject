/*Header file guard*/
#ifndef __HRELAY_INTERFACE_H__
#define __HRELAY_INTERFACE_H__

/***************************************************************************************************/
/*                                         Interfacing macros                                      */
/***************************************************************************************************/

/***************************************************************************************************/
/*                                        Functions' prototypes                                    */
/***************************************************************************************************/

/**
 * @brief This Function to initialize Relay pin status
 * 
 */
void hrelay_init(void);

/**
 * @brief This Function to switch relay on 
 * 
 */
void hrelay_switchON(void);

/**
 * @brief This Function to switch relay on
 * 
 */
void hrelay_switchOFF(void);

#endif /*__HRELAY_INTERFACE_H__*/