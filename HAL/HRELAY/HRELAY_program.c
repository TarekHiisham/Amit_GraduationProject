/***************************************************************************************************/
/*                                             Includes                                            */
/***************************************************************************************************/

#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "MDIO_interface.h"
#include "HRELAY_cfg.h"
#include "HRELAY_interface.h"


/***************************************************************************************************/
/*                                       Functions' definitions                                    */
/***************************************************************************************************/

void hrelay_init(void)
{

    /*setting relay pin status*/
    mdio_setPinStatus(config_RELAY_PORT , config_RELAY_PIN , OUTPUT);

    /*Return Function*/
    return;
}

void hrelay_switchON(void)
{

    /*switch on pin value when swetching*/
    mdio_setPinValue(config_RELAY_PORT , config_RELAY_PIN , HIGH );
    
    /*Return Function*/
    return;
}

void hrelay_switchOFF(void)
{

    /*swetch off pin value when swetching*/
    mdio_setPinValue(config_RELAY_PORT , config_RELAY_PIN , LOW);
    
    /*Return Function*/
    return;
}