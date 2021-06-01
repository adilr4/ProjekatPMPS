#include "adc.h"
#include "delay.h"
#include "pwm.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "usart.h"

void initADC1();
void initADC2();
void initPWM();
uint32_t getADC1();
uint32_t getADC2();
void setPWM(uint32_t, uint32_t, uint32_t, uint32_t);

uint32_t adc_timer;

void ldr() {
  adc_timer = getSYSTIM();
  uint32_t adc_value = getADC1();
  /* printUSART2("-> ADC: Value D[%d] V[%d]\n", adc_value, */
  /*             (adc_value * 3000) / 4095); */
  if (adc_value < 3000)
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, 0x0);
  else
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, 0x1);
}

void temp() {
  adc_timer = getSYSTIM();
  uint32_t adc_value = getADC2();
  /* printUSART2("-> ADC: Value D[%d] V[%d]\n", adc_value, */
  /*             (adc_value * 3000) / 4095); */
}

int main(void) {
  HAL_Init();

  GPIO_InitTypeDef GPIO_InitStruct;
  __HAL_RCC_GPIOD_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  initUSART2(921600);
  initSYSTIM();
  initADC2();
  initADC1();
  initPWM();

  adc_timer = getSYSTIM();
  uint16_t arr[3] = {600, 1500, 2100};
  int i = 0;

  while (1) {
    /* if (chk4TimeoutSYSTIM(adc_timer, 500) == SYSTIM_TIMEOUT) { */
    /*   ldr(); */
    /*   temp(); */
    setPWM(arr[i], 0, 0, 0);
    i = (++i % 3);
    delay_ms(700);
    printUSART2("Value: %d\n", arr[i]);
    /* } */
  }
}

