/*Header file guard*/
#ifndef __ASET_MODE_CFG_H__
#define __ASET_MODE_CFG_H__

/***************************************************************************************************/
/*                                         configuration macros                                    */
/***************************************************************************************************/

/*maximum validation time to stay in setting Mode*/
#define VALID_MAX               (5)                                 //validitaion time 5 second

/*minimum validation time to stay in setting Mode*/
#define VALID_RESET             (0)

/*Blinking time of 7seg*/
#define BLINKING                (1000)                               //7seg blink by 1 second

/*maximum temperature could setting*/
#define MAX_TEMP                (75)

/*minimum temperature could setting*/
#define MIN_TEMP                (35)

#endif /*__ASET_MODE_CFG_H__*/