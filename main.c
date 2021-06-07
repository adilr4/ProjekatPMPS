#include "adc.h"
#include "delay.h"
#include "pwm.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "usart.h"

#define SHORT_DELAY 50
#define LONG_DELAY 500

void initADC1();
void initADC2();
void initPWM();
void setPWM1(uint32_t);
void setPWM2(uint32_t);
uint32_t getADC1();
uint32_t getADC2();

GPIO_InitTypeDef GPIO_InitStruct;

const int min_width = 1050, max_width = 1950;
const int max_temp = 40;
const int lm35_scaling = 10;

void init() {
  HAL_Init();

  // PD5 -> diode
  __HAL_RCC_GPIOD_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  // PA0(button) -> simulating humidity 
  __HAL_RCC_GPIOA_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  initUSART2(921600);
  initADC2();
  initADC1();
  initPWM();
}

void ldr() {
  delay_ms(SHORT_DELAY);
  uint32_t adc_value = getADC1();
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, !(adc_value < 2850));
}

uint32_t temp() {
  delay_ms(SHORT_DELAY);
  uint32_t current_temp = 0;
  int i = 10;
  while (i--) {
    delay_ms(20);
    current_temp += getADC2();
  }
  current_temp /= (10 * lm35_scaling);
  printUSART2("Value: %d\n", current_temp);
  return current_temp;
}

void servo(uint32_t current_temp) {
  setPWM1(((current_temp > max_temp && HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0))
               ? max_width
               : min_width));
  delay_ms(LONG_DELAY);
}

void dc(uint32_t current_temp) {
  delay_ms(SHORT_DELAY);
  int percentage = (current_temp / max_temp) * 100;
  setPWM2(20000 * percentage / 100);
}

int main(void) {
  init();
  while (1) {
    ldr();
    uint32_t current_temp = temp();
    servo(current_temp);
    dc(current_temp);
  }
}

