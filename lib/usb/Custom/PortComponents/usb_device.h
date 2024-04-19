/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : usb_device.h
 * @version        : v3.0_Cube
 * @brief          : Header for usb_device.c file.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_DEVICE__H__
#define __USB_DEVICE__H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbxx.h"
#include "stm32wbxx_hal.h"
#include "usbd_def.h"

/* USER CODE BEGIN INCLUDE */
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"
#include "usbd_hid.h"
#include "usbd_composite_builder.h"
  /* USER CODE END INCLUDE */

  /** @addtogroup USBD_OTG_DRIVER
   * @{
   */

  /** @defgroup USBD_DEVICE USBD_DEVICE
   * @brief Device file for Usb otg low level driver.
   * @{
   */

  /** @defgroup USBD_DEVICE_Exported_Variables USBD_DEVICE_Exported_Variables
   * @brief Public variables.
   * @{
   */

  /* Private variables ---------------------------------------------------------*/
  /* USER CODE BEGIN PV */
  extern uint8_t HID_InstID;
  /* USER CODE END PV */

  /* Private function prototypes -----------------------------------------------*/
  /* USER CODE BEGIN PFP */

  /* USER CODE END PFP */

  /*
   * -- Insert your variables declaration here --
   */
  /* USER CODE BEGIN VARIABLES */

  /* USER CODE END VARIABLES */
  /**
   * @}
   */

  /** @defgroup USBD_DEVICE_Exported_FunctionsPrototype USBD_DEVICE_Exported_FunctionsPrototype
   * @brief Declaration of public functions for Usb device.
   * @{
   */

  /** USB Device initialization function. */
  void MX_USB_Device_Init(void);

  /*
   * -- Insert functions declaration here --
   */
  /* USER CODE BEGIN FD */

  /* USER CODE END FD */
  /**
   * @}
   */

  /**
   * @}
   */

  /**
   * @}
   */

#ifdef __cplusplus
}
#endif

#endif /* __USB_DEVICE__H__ */