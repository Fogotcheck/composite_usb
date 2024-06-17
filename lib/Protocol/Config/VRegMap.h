#ifndef __VRegMap_h__
#define __VRegMap_h__

#define VR_OFSET_WORD 4
#define VR_SET_OFSET(X) (X + VR_OFSET_WORD)

enum VRegs_System_Map
{
    VRS_TIME_HEX,
    VRS_SIZE = VR_SET_OFSET(VRS_TIME_HEX),
    VRS_ERR = VR_SET_OFSET(VRS_SIZE),
    VRS_VERSION = VR_SET_OFSET(VRS_ERR),
};

enum VRegs_User_Map
{
    VRU_ADC_0 = VR_SET_OFSET(VRS_VERSION),
    VRU_ADC_1 = VR_SET_OFSET(VRU_ADC_0),
    VRU_ADC_2 = VR_SET_OFSET(VRU_ADC_1),
    VRU_ADC_3 = VR_SET_OFSET(VRU_ADC_2),

    VRU_SIGNAL = VR_SET_OFSET(VRU_ADC_3),

    VRU_USB_STATE = VR_SET_OFSET(VRU_SIGNAL),
};

#endif //__VRegMap_h__