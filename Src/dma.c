#include "dma.h"

DMA_HandleTypeDef hdma_tim1_ch3;

/**
  * @brief  Init DMA
  * @note   None
  * @param  None
  * @retval None
  */
void Init_DMA()
{
  HAL_DMA_DeInit(htim1.hdma[TIM_DMA_ID_CC3]);
  // Enable DMA1 CLOCK
  __HAL_RCC_DMA1_CLK_ENABLE();

  // DMA1 CHANNEL 5 for TIM1_UP Update Event
  hdma_tim1_ch3.Instance = DMA1_Channel5;

  // map variable to TIM1->CCR3
  hdma_tim1_ch3.Init.Direction = DMA_MEMORY_TO_PERIPH;

  // Don't increment periph memory, update only TIM1->CCR3 register
  hdma_tim1_ch3.Init.PeriphInc = DMA_PINC_DISABLE;

  // Increment memory, go through map variable
  hdma_tim1_ch3.Init.MemInc = DMA_MINC_ENABLE;

  // Get 8 bit per 8 bit on map, send 16bit to registre, otherwise 8 bit not work
  hdma_tim1_ch3.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
  hdma_tim1_ch3.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;

  // DMA STOP after copy
  hdma_tim1_ch3.Init.Mode = DMA_NORMAL;

  // Since there is only one DMA can be everithing you want low to very high
  hdma_tim1_ch3.Init.Priority = DMA_PRIORITY_VERY_HIGH;

  // Callback set but NOT USED
  hdma_tim1_ch3.XferHalfCpltCallback = DMA_TransferHalfHandler;
  hdma_tim1_ch3.XferCpltCallback  = DMA_TransferCompleteHandler;
  hdma_tim1_ch3.XferErrorCallback = DMA_TransferError;
 if (HAL_DMA_Init(&hdma_tim1_ch3) != HAL_OK)
    {
      Error_Handler();
    }
 // Trigger DMA request when CNT == ARR so compare register ready for the next period
  __HAL_LINKDMA(&htim1 ,hdma[TIM_DMA_ID_UPDATE], hdma_tim1_ch3);

  // Set IT for DMA1_Channel5_IRQn, only IT when it's end is use to stop waiting
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
}


/**
  * @brief  Start DMA and PWM
  * @note   Adaptation from ST lib, the one from st only trigger DMA for when CMT == CC, this one trigger DMA when CNT == ARR
  * @param  None
  * @retval None
  */
HAL_StatusTypeDef HAL_TIM_PWM_Start_DMA_UPDATE(TIM_HandleTypeDef *htim, uint32_t Channel, uint8_t *pData, uint16_t Length)
{
    /* Set the DMA Period elapsed callback */
    /* htim->hdma[TIM_DMA_ID_UPDATE]->XferCpltCallback = TIM_DMADelayPulseCplt; */
    htim->hdma[TIM_DMA_ID_UPDATE]->XferCpltCallback = DMA_TransferCompleteHandler;

        /* Set the DMA Period elapsed callback */
    htim->hdma[TIM_DMA_ID_UPDATE]->XferHalfCpltCallback = DMA_TransferHalfHandler;

    /* Set the DMA error callback */
    htim->hdma[TIM_DMA_ID_UPDATE]->XferErrorCallback = TIM_DMAError;

    /* /\* Enable the DMA channel *\/ */
 
    /* Enable the TIM UPDATE DMA request */
    __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_UPDATE);

    /* Enable the Capture compare channel */
    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);

    if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
    {
        /* Enable the main output */
        __HAL_TIM_MOE_ENABLE(htim);
    }
 
    /* Enable the Peripheral */
    HAL_DMA_Start_IT(htim1.hdma[TIM_DMA_ID_UPDATE], (uint32_t)pData, (uint32_t)&htim1.Instance->CCR3, Length);
    __HAL_TIM_ENABLE(htim);

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Stop DMA and PWM
  * @note  Adaptation from ST lib
  * @param  None
  * @retval None
  */
HAL_StatusTypeDef HAL_TIM_PWM_Stop_DMA_UPDATE(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_UPDATE);
    /* Disable the Capture compare channel */
    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_DISABLE);

    if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
    {
        /* Disable the Main Ouput */
        __HAL_TIM_MOE_DISABLE(htim);
    }

    /* Disable the Peripheral */
    __HAL_TIM_DISABLE(htim);

    /* Change the htim state */
    htim->State = HAL_TIM_STATE_READY;

    /* Return function status */
    return HAL_OK;
}

/**
  * @brief  DMA1 Channel5 IT Handler
  * @note   None
  * @param  None
  * @retval None
  */
void DMA1_Channel5_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hdma_tim1_ch3);
}

/**
  * @brief  DMA transferError callback
  * @note   Note use
  * @param  None
  * @retval None
  */
void DMA_TransferError(DMA_HandleTypeDef *DmaHandle)
{
  
}

/**
  * @brief  DMA transfer complete callback
  * @note   Stop PWM and DMA and set the variable that sait transmission is end
  * @param  None
  * @retval None
  */
void DMA_TransferCompleteHandler(DMA_HandleTypeDef *DmaHandle)
{
  HAL_TIM_PWM_Stop_DMA_UPDATE(&htim1, TIM_CHANNEL_3);
  dataSend = 1;
}

/**
  * @brief  DMA half transfer callback
  * @note   Note use
  * @param  None
  * @retval None
  */
void DMA_TransferHalfHandler(DMA_HandleTypeDef *DmaHandle)
{

}

