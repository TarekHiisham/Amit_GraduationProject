#include "LBIT_MATH.h"
#include "LSTD_TYPES.h"
#include "ACTR_MODE_interface.h"


int main(void)
{ 
    /*Initializing all system */
    actr_mode_init_System();

    /*Super Loop*/
    while(1)
    {
        actr_mode_controlmode(); 
    }
    
    return 0;
}