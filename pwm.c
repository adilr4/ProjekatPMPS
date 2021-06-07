#include "pwm.h"

TIM_HandleTypeDef TIM4_HandleStruct;

void initPWM(void) {
  // Initialize pin PB6,PB7 -> PWM
  __HAL_RCC_GPIOB_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  //-------------------------------------------------------------------------------

  // Configure timer
  __HAL_RCC_TIM4_CLK_ENABLE();

  TIM_Base_InitTypeDef TIM_Base_InitStruct;
  TIM_Base_InitStruct.Prescaler = 83;
  TIM_Base_InitStruct.CounterMode = TIM_COUNTERMODE_UP;
  TIM_Base_InitStruct.Period = 20000;
  TIM_Base_InitStruct.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  TIM_Base_InitStruct.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

  TIM4_HandleStruct.Instance = TIM4;
  TIM4_HandleStruct.Init = TIM_Base_InitStruct;

  HAL_TIM_PWM_Init(&TIM4_HandleStruct);

  TIM_OC_InitTypeDef TIM_OC_InitStruct;
  TIM_OC_InitStruct.OCMode = TIM_OCMODE_PWM1;
  TIM_OC_InitStruct.Pulse = 500;
  TIM_OC_InitStruct.OCPolarity = TIM_OCPOLARITY_HIGH;
  TIM_OC_InitStruct.OCFastMode = TIM_OCFAST_DISABLE;

  HAL_TIM_PWM_ConfigChannel(&TIM4_HandleStruct, &TIM_OC_InitStruct,
                            TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&TIM4_HandleStruct, TIM_CHANNEL_1);
  HAL_TIM_PWM_ConfigChannel(&TIM4_HandleStruct, &TIM_OC_InitStruct,
                            TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&TIM4_HandleStruct, TIM_CHANNEL_2);
}

// for servo motor(PB6)
void setPWM1(uint32_t ccr) {
  __HAL_TIM_SET_COMPARE(&TIM4_HandleStruct, TIM_CHANNEL_1, ccr);
}

// for dc motor(PB7)
void setPWM2(uint32_t ccr) {
  __HAL_TIM_SET_COMPARE(&TIM4_HandleStruct, TIM_CHANNEL_2, ccr);
}

