/*
 * @breaf 
 *     
 */
#include "alg_demo.h"

#define COUNT_EVERY_ROW     16

/*
 * @breaf diaplay Hex Data by assic[0-9a-f]
 *     
 * @param
 *     @arg data
 *     @arg len
 */
void display(const uint8_t * data,uint32_t len)
{
    uint32_t i = 0;
    printf("->\n");
    for(i = 0; i < len; i++)
    {
        if(i != 0 && i % COUNT_EVERY_ROW == 0)
        {
            printf("\n");
        }
        printf("%02x ",*(data + i));
    }
    printf("\n");
}