/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : usb_device.c
 * @version        : v3.0_Cube
 * @brief          : This file implements the USB Device
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

/* Includes ------------------------------------------------------------------*/

#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

extern void Error_Handler(void);
/* USB Device Core handle declaration. */
USBD_HandleTypeDef hUsbDeviceFS;

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN 0 */
uint8_t HID_EpAdress = HID_EPIN_ADDR;
uint8_t CDC_EpAdd_Inst1[3] = {CDC_IN_EP, CDC_OUT_EP, CDC_CMD_EP};

uint8_t CDC_InstID, HID_InstID = 0;
extern USBD_DescriptorsTypeDef Composite_Desc;

/* USER CODE END 0 */

/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
 * Init USB device Library, add supported class and start the library
 * @retval None
 */
void MX_USB_Device_Init(void)
{
  /* USER CODE BEGIN USB_Device_Init_PreTreatment */

  /* USER CODE END USB_Device_Init_PreTreatment */

  /* Init Device Library, add supported class and start the library. */
  // if (USBD_Init(&hUsbDeviceFS, &CDC_Desc, DEVICE_FS) != USBD_OK)
  // {
  //   Error_Handler();
  // }
  // if (USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC) != USBD_OK)
  // {
  //   Error_Handler();
  // }
  // if (USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS) != USBD_OK)
  // {
  //   Error_Handler();
  // }
  // if (USBD_Start(&hUsbDeviceFS) != USBD_OK)
  // {
  //   Error_Handler();
  // }

  // if (USBD_Init(&hUsbDeviceFS, &Composite_Desc, DEVICE_FS) != USBD_OK)
  // {
  //   Error_Handler();
  // }
  // HID_InstID = hUsbDeviceFS.classId;
  // if (USBD_RegisterClassComposite(&hUsbDeviceFS, &USBD_HID, CLASS_TYPE_HID, &HID_EpAdress))
  // {
  //   Error_Handler();
  // }
  // CDC_InstID = hUsbDeviceFS.classId;
  // if (USBD_RegisterClassComposite(&hUsbDeviceFS, USBD_CDC_CLASS, CLASS_TYPE_CDC, CDC_EpAdd_Inst1))
  // {
  //   Error_Handler();
  // }
  // if (USBD_CMPSIT_SetClassID(&hUsbDeviceFS, CLASS_TYPE_CDC, 0) != 0xFF)
  // {
  //   USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS);
  // }
  // if (USBD_Start(&hUsbDeviceFS) != USBD_OK)
  // {
  //   Error_Handler();
  // }
  if (USBD_Init(&hUsbDeviceFS, &Composite_Desc, DEVICE_FS) != USBD_OK)
  {
    Error_Handler();
  }
  HID_InstID = hUsbDeviceFS.classId;
  if (USBD_RegisterClassComposite(&hUsbDeviceFS, &USBD_HID, CLASS_TYPE_HID, &HID_EpAdress))
  {
    Error_Handler();
  }
  CDC_InstID = hUsbDeviceFS.classId;
  if (USBD_RegisterClassComposite(&hUsbDeviceFS, USBD_CDC_CLASS, CLASS_TYPE_CDC, CDC_EpAdd_Inst1))
  {
    Error_Handler();
  }
  if (USBD_CMPSIT_SetClassID(&hUsbDeviceFS, CLASS_TYPE_CDC, 0) != 0xFF)
  {
    USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS);
  }

  if (USBD_Start(&hUsbDeviceFS) != USBD_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_Device_Init_PostTreatment */

  /* USER CODE END USB_Device_Init_PostTreatment */
}

/**
 * @}
 */

/**
 * @}
 */
