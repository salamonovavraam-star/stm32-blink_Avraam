/*
 * сначала я написал код с define, но узнав что существует CMSIS
 * я решил что стоит использовать его, т.к это больше похоже на то
 * что я видел в библиотеке по работе с таймерами когда прогал stm32 на ардуине
 * я создал папку drivers положив туда все что нужно для CMSIS (ядро и устройство)
 * и переписал все для CMSIS
 * я сделал обычный счетчик для задержки, но так как в задание сказано 1сек
 * я подумал, что это стоит переписать. Буду использовать sysTick
 * stm32 работает на 8мгц не стал включать 72мгц тут и низкой скорости хватит
 */

#include "stm32f1xx.h"

// Счётчик миллисекунд (volatile — меняется в прерывании)
volatile uint32_t msTicks = 0;
#define LED_PIN     13
#define LED_PORT    GPIOC
#define DELAY_MS    1000
#define SYSTICK_1MS (8000 - 1)

// Обработчик прерывания SysTick — вызывается каждую 1 мс
void SysTick_Handler(void) {
    msTicks++;
}

// Настройка SysTick на 1 мс
void SysTick_Init(void) {
    // 8 мГц
    // 8000 тактов на 1 мс
    SysTick->LOAD = SYSTICK_1MS; //
    SysTick->VAL = 0; //начало
    SysTick->CTRL = 7;  // Включить прерывание такт от ядра 0b111
    // CTRL = 7 = 0b111:
    //   бит 0 (ENABLE)    = 1  включить SysTick
    //   бит 1 (TICKINT)   = 1  генерировать прерывание
    //   бит 2 (CLKSOURCE) = 1  такт от ядра (HCLK)
}
// Точная задержка в миллисекундах
void delay_ms(uint32_t ms) {
    uint32_t start = msTicks;
    while ((msTicks - start) < ms) {
        // Ждём
    }
}

int main(void) {
    SysTick_Init();
	// Включаем тактирование порта C
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    /*
     * RCC - reset и clock control
     * APB2ENT - это как щиток электрический включаем
     * тактирование на портах
     * а IOPCEN - это укаазывает что включаем именно порты C
     */

    // PC13 как выход push-pull, 2 мгц
    LEDPORT->CRH &= ~(0xF << 20); //очищаем
    LEDPORT->CRH |=  (0x2 << 20); //устанавливаем 0b0010
    /*
     * CRH - бит регистра конфигурации старший
     * 8 пинов для кадого 4 бита CNF1 CNF0 MODE1 MODE0
     * конкретно здесь настраиваем CNF1:CNF0 как 00
     * а MODE1:MODE0 как 10
     */

    while (1) {
        LEDPORT->ODR &= ~(1 << LED_PIN);  // LOW → горит на пин PC13
        delay_ms(DELAY_MS);

        LEDPORT->ODR |= (1 << LED_PIN);   // HIGH → не горит на пин PC13
        delay_ms(DELAY_MS);
    }
}
