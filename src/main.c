#include <stdlib.h>

#include "stm32l1xx.h"
#include "stm32l1xx_conf.h"

void SystemClock_Config(void){

    /* Clock init stuff */ 
    
    LL_UTILS_PLLInitTypeDef sUTILS_PLLInitStruct = {LL_RCC_PLL_MUL_3, LL_RCC_PLL_DIV_3};
    LL_UTILS_ClkInitTypeDef sUTILS_ClkInitStruct = {LL_RCC_SYSCLK_DIV_1, LL_RCC_APB1_DIV_1, LL_RCC_APB2_DIV_1};
    
    LL_PLL_ConfigSystemClock_HSI(&sUTILS_PLLInitStruct, &sUTILS_ClkInitStruct);
    
    LL_Init1msTick(SystemCoreClock);
}

int main(void){

    /* Configure the system clock */
    SystemClock_Config();

    /* Let's pick a pin and toggle it */

    /* Use a structure for this (usually for bulk init), you can also use LL functions */   
    LL_GPIO_InitTypeDef GPIO_InitStruct;
    
    /* Enable the GPIO clock for GPIOA*/
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

    /* Enable clock for SYSCFG */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);

    /* Set up port A parameters */
    LL_GPIO_StructInit(&GPIO_InitStruct);                   // init the struct with some sensible defaults 
    GPIO_InitStruct.Pin = LL_GPIO_PIN_5;                    // GPIO pin 5; on Nucleo there is an LED
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;         // output speed
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;             // set as output 
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;   // make it a push pull
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);                  // initialize PORT A
 
    /* Toggle forever */
    while(1){
        LL_mDelay(250);
        LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_5);
    }

    return 0;
}
