cmake_minimum_required(VERSION 3.22)

add_library(St_Usb INTERFACE)
target_compile_definitions(
    St_Usb
    INTERFACE
    "USE_USBD_COMPOSITE"
    "USBD_CMPSIT_ACTIVATE_HID=1"
    "USBD_CMPSIT_ACTIVATE_CDC=1"
)
set(StUsbPath
    "${CMAKE_CURRENT_SOURCE_DIR}/STusb"
)
set(UsbCustPath
    "${CMAKE_CURRENT_SOURCE_DIR}/Custom"
)
target_link_libraries(St_Usb INTERFACE St_Interface)

target_include_directories(
    St_Usb
    SYSTEM INTERFACE
    "${StUsbPath}/Core/Inc"

    # Custom
    "${UsbCustPath}/CoreComponents"
    "${UsbCustPath}/PortComponents"

    # cdc
    "${UsbCustPath}/ClassComponents/cdc"

    # hid
    "${UsbCustPath}/ClassComponents/hid"

    # composite
    "${StUsbPath}/Class/CompositeBuilder/Inc"
)
add_library(St_UsbCore
    "${StUsbPath}/Core/Src/usbd_core.c"
    "${StUsbPath}/Core/Src/usbd_ctlreq.c"
    "${StUsbPath}/Core/Src/usbd_ioreq.c"

    # Custom
    "${UsbCustPath}/CoreComponents/usbd_conf.c"
)
target_link_libraries(St_UsbCore St_Usb)

add_library(_UsbClass

    # cdc
    "${UsbCustPath}/ClassComponents/cdc/usbd_cdc.c"
    "${UsbCustPath}/ClassComponents/cdc/usbd_cdc_if.c"

    # hid
    "${UsbCustPath}/ClassComponents/hid/usbd_hid.c"

    # composite
    "${StUsbPath}/Class/CompositeBuilder/Src/usbd_composite_builder.c"
)
target_link_libraries(_UsbClass St_Usb)

add_library(_UsbPort
    "${UsbCustPath}/PortComponents/usb_device.c"
    "${UsbCustPath}/PortComponents/usbd_desc.c"
)
target_link_libraries(_UsbPort St_Usb)

target_link_libraries(St_Usb
    INTERFACE
    St_UsbCore
    _UsbClass
    _UsbPort
)