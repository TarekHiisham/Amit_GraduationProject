/*Header file guard*/
#ifndef __HSEV_SEG_INTERFACE_H__
#define __HSEV_SEG_INTERFACE_H__

/***************************************************************************************************/
/*                                         Interfacing macros                                      */
/***************************************************************************************************/

/*System seven segments*/
#define SEV_SEG_1    (0)
#define SEV_SEG_2    (1)

/*Seven segment displaying numbers*/
#define NUMBER_0     (0)
#define NUMBER_1     (1)
#define NUMBER_2     (2)
#define NUMBER_3     (3)
#define NUMBER_4     (4)
#define NUMBER_5     (5)
#define NUMBER_6     (6)
#define NUMBER_7     (7)
#define NUMBER_8     (8)
#define NUMBER_9     (9)

#define SEV_SEGMENT_FREQ    (10)

/***************************************************************************************************/
/*                                        Functions' prototypes                                    */
/***************************************************************************************************/

/**
 * @brief This function is responsible for initializing specific seven segment
 * 
 * @param au8_sev_segNumber 
 */
void hsev_seg_init(u8_t au8_sev_segNumber);

/**
 * @brief This Function to display number on 7seg
 * 
 * @param au8_number 
 */
void hsev_seg_displayNumber(u8_t au8_number);

#endif /*__HSEV_SEG_INTERFACE_H__*/