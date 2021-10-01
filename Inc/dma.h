#ifndef __DMA_H
#define __DMA_H

#include "stm32f1xx_hal.h"
#include "main.h"

extern DMA_HandleTypeDef hdma_tim1_ch3;

// Init
void Init_DMA();

// Start and STOP DMA & PWN
HAL_StatusTypeDef HAL_TIM_PWM_Start_DMA_UPDATE(TIM_HandleTypeDef *htim, uint32_t Channel, uint8_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_PWM_Stop_DMA_UPDATE(TIM_HandleTypeDef *htim, uint32_t Channel);

// Callbacks
void DMA_TransferHalfHandler(DMA_HandleTypeDef *DmaHandle);
void DMA_TransferCompleteHandler(DMA_HandleTypeDef *DmaHandle);
void DMA_TransferError(DMA_HandleTypeDef *DmaHandle);

#endif /* __DMA_H */
