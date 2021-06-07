#include "adc.h"

ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;

void initADC1(void) {
  // ADC PC5 -> ADC1_IN15

  GPIO_InitTypeDef GPIO_InitStruct;
  __HAL_RCC_GPIOC_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  ADC_ChannelConfTypeDef sConfig = {0};

  __HAL_RCC_ADC1_CLK_ENABLE();
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  HAL_ADC_Init(&hadc1);

  sConfig.Channel = ADC_CHANNEL_15;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
}

void initADC2(void) {
  // ADC PC4 -> ADC1_IN14

  GPIO_InitTypeDef GPIO_InitStruct;
  __HAL_RCC_GPIOC_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  ADC_ChannelConfTypeDef sConfig = {0};

  __HAL_RCC_ADC2_CLK_ENABLE();
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc2.Init.Resolution = ADC_RESOLUTION_12B;
  hadc2.Init.ScanConvMode = DISABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.NbrOfConversion = 1;
  hadc2.Init.DMAContinuousRequests = DISABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  HAL_ADC_Init(&hadc2);

  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

  HAL_ADC_ConfigChannel(&hadc2, &sConfig);
}

uint16_t getADC1(void) {
  HAL_ADC_Start(&hadc1);
  while (HAL_ADC_PollForConversion(&hadc1, 10000) != HAL_OK)
    ;

  return HAL_ADC_GetValue(&hadc1);
}

uint16_t getADC2(void) {
  HAL_ADC_Start(&hadc2);
  while (HAL_ADC_PollForConversion(&hadc2, 10000) != HAL_OK)
    ;

  return HAL_ADC_GetValue(&hadc2);
}
