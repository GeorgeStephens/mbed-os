#include "stm32f7xx_hal.h"

/**
 * Override HAL Eth Init function
 */
void HAL_ETH_MspInit(ETH_HandleTypeDef* heth)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    if (heth->Instance == ETH) {
        /* Disable DCache for STM32F7 family */
        SCB_DisableDCache();

        /* Enable GPIOs clocks */
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();
        __HAL_RCC_GPIOG_CLK_ENABLE();

        /** ETH GPIO Configuration
          MII_ETH_MDC -----------------------> PC1
          MII_ETH_CRS -----------------------> PA0/WKUP
          MII_ETH_MDIO ----------------------> PA2
          MII_ETH_COL -----------------------> PA3
          MII_ETH_RX_CLK --------------------> PA1
          MII_ETH_RX_DV ---------------------> PA7
          MII_ETH_RXD0 ----------------------> PC4
          MII_ETH_RXD1 ----------------------> PC5
          MII_ETH_RXD2 ----------------------> PB0
          MII_ETH_RXD3 ----------------------> PB1
          MII_ETH_TX_CLK --------------------> PC3
          MII_ETH_TX_EN ---------------------> PB11
          MII_ETH_TXD0 ----------------------> PB12
          MII_ETH_TXD1 ----------------------> PB13
          MII_ETH_TXD2 ----------------------> PC2
          MII_ETH_TXD3 ----------------------> PE2
        */

        /* Configure PA0, PA1, PA2, PA3 and PA7 */
        GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_7;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* Configure PB0, PB1, PB11, PB12 and PB13 */
        GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* Configure PC1, PC2, PC3, PC4 and PC5 */
        GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        /* Configure PE2 */
        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
        HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

        /* Enable the Ethernet global Interrupt */
        HAL_NVIC_SetPriority(ETH_IRQn, 0x7, 0);
        HAL_NVIC_EnableIRQ(ETH_IRQn);
        
        /* Enable ETHERNET clock  */
        __HAL_RCC_ETH_CLK_ENABLE();
    }
}

/**
 * Override HAL Eth DeInit function
 */
void HAL_ETH_MspDeInit(ETH_HandleTypeDef* heth)
{
    if (heth->Instance == ETH) {
        /* Peripheral clock disable */
        __HAL_RCC_ETH_CLK_DISABLE();

        /** ETH GPIO Configuration
          MII_ETH_MDC -----------------------> PC1
          MII_ETH_CRS -----------------------> PA0/WKUP
          MII_ETH_MDIO ----------------------> PA2
          MII_ETH_COL -----------------------> PA3
          MII_ETH_RX_CLK --------------------> PA1
          MII_ETH_RX_DV ---------------------> PA7
          MII_ETH_RXD0 ----------------------> PC4
          MII_ETH_RXD1 ----------------------> PC5
          MII_ETH_RXD2 ----------------------> PB0
          MII_ETH_RXD3 ----------------------> PB1
          MII_ETH_TX_CLK --------------------> PC3
          MII_ETH_TX_EN ---------------------> PB11
          MII_ETH_TXD0 ----------------------> PB12
          MII_ETH_TXD1 ----------------------> PB13
          MII_ETH_TXD2 ----------------------> PC2
          MII_ETH_TXD3 ----------------------> PE2
        */
        HAL_GPIO_DeInit(GPIOE, GPIO_PIN_2);

        HAL_GPIO_DeInit(GPIOC, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);
        
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_7);
        
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13);

        /* Disable the Ethernet global Interrupt */
        NVIC_DisableIRQ(ETH_IRQn);
    }
}
