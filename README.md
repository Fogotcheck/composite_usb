# **[Проект CompositeUsb CDC+HID](https://github.com/Fogotcheck/composite_usb.git)**

## *Клонирование репозитория*

Клонировать репозиторий вы можете следующим образом:

```console
git clone "https://github.com/Fogotcheck/composite_usb.git"
```
```console
git submodule update --init --recursive
```

## *Структура проекта*

```
├── AppMain                             // перенаправление main
|
├── cmake
|       ├── interface                   // дополнительные функции сборки
|       ├── toolchain                   // минимальный набор правил для сборки
|       └── utils                       // дополнительные утилиты сборки
|
├── lib                                 // библиотеки для проектов
|       ├── ...
|       └── CMakeLists.txt              // CMakeLists для сборки библиотек
|
├── St_CubeHal                          // папка для сборки main mcu + hal
|       ├── Core
|       ├── Drivers                     // CMSIS+HAL от stm32
|       ├── CompositeUsb_CMX.ioc        // файл для генерации STM32CubeMX
|       └── CMakeLists.txt              // основной файл для сборки платформы
|
|
├── CMakeLists.txt                      // основной файл для сборки проекта
|
└── README.md                           // Вы находитесь тут

```

## *Сборка проекта*

### Настройка сборки проекта

Минимальные требования для настройки сборки проекта - являются указание toolchain:

```console
CMAKE_TOOLCHAIN_FILE=./cmake/toolchain/toolchain_arm_cortex_m4.cmake
```
Таким образом настройка проекта для сборки arm-none-eabi будет выглядеть:

```console
cmake -DCMAKE_TOOLCHAIN_FILE=./cmake/toolchain/toolchain_arm_cortex_m4.cmake -B ./build
```

### Дополнительные опции настройки сборки

Опция для прошивки mcu при помощи [openocd](https://openocd.org/), по умолчанию OFF:

```console
OPENOCD_ENABLE=ON
```

Опция для генерации файлов настройки окружения [VScode](https://code.visualstudio.com/), по умолчанию OFF.

```console
ENVIRONMENT_VSCODE=ON
```

Таким образом настройка проекта с дополнительными опциями будет выглядеть:

```console
cmake -DOPENOCD_ENABLE=ON -DENVIRONMENT_VSCODE=ON -DCMAKE_TOOLCHAIN_FILE=./cmake/toolchain/toolchain_arm_cortex_m4.cmake -B./build 
```

### Сборка проекта

Сборка осуществляется командой:

```console
cmake --build ./build
```

## *Дополнительные ссылки*

* [issues](https://github.com/Fogotcheck/composite_usb/issues/new/choose)
