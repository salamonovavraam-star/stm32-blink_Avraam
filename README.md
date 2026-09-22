# STM32 Blink
Мигание светодиодом на STM32F103C8T6 (Blue Pill)

## Zadanie 1: мигание светодиодом

Светодиод на PC13 мигает с периодом 1 сек

## Использую

- STM32CubeIDE 1.18+
- STM32F103C8T6 (Blue Pill)
- ST-Link V2
- STM32CubeProgrammer

## Сборка

1. Открыть проект в STM32CubeIDE.
2. `Project → Build All`.
3. В папке `Debug/` появится `blink_stm.hex`.

## Прошивка

1. Подключить ST-Link к Blue Pill:
   - SWDIO → SWDIO
   - SWCLK → SWCLK
   - GND → GND
   - 3.3V → 3.3V
2. Открыть STM32CubeProgrammer.
3. `Connect` (Reset mode: Hardware reset).
4. `Open File` → выбрать `Debug/blink_stm.hex`.
5. `Download`.
6. Нажать RESET на плате.

## Реализация

- CMSIS (без HAL)
- SysTick для точной задержки 1 мс.
- Тактирование 8 МГц

## Задание
Задание 1: мигание светодиодом
Задание 2: ШИМ (плавная яркость)
Задание 3: FreeRTOS
