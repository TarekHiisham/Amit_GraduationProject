/*Header file guard*/
#ifndef __ACTR_MODE_INTERFACE_H__
#define __ACTR_MODE_INTERFACE_H__

/***************************************************************************************************/
/*                                         Interfacing macros                                      */
/***************************************************************************************************/

#define SWITCHOFF                            (0)
#define SWITCHON                             (1)

/*Default Setting Temperature*/
#define DEFAULT_SET_TEMP                     (60)

#define TURNOFF_MODE(MODE)                  (MODE = SWITCHOFF)
#define TURNON_MODE(MODE)                   (MODE = SWITCHON)

/***************************************************************************************************/
/*                                        Functions' prototypes                                    */
/***************************************************************************************************/

/*sharing two modes flags with source files*/
extern u8_t setMODE ;
extern u8_t runMODE ;

extern u8_t setTEMP ;
extern u8_t curTEMP ;

/**
 * @brief This Function to Initialize all System modules
 * 
 */
void actr_mode_init_System(void);


/**
 * @brief This Function switches from setting mode to runnig mode
 * 
*/
void actr_mode_switch(void) ;


/**
 * @brief Thish Function control which mode run 
 * 
 */
void actr_mode_controlmode(void) ;


#endif /*__ACTR_MODE_INTERFACE_H__*/