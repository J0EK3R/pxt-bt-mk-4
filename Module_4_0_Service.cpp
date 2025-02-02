#include "MicroBitConfig.h"
#include "Module_4_0_Service.h"
#include "CryptTool.h"

static uint8_t _ctxValue = 0x25; // CTXValue for Encryption
static uint8_t _addressArray[5]     = { 0xC1, 0xC2, 0xC3, 0xC4, 0xC5 };
static uint8_t _telegram_Connect[8] = { 0xAD, 0x7B, 0xA7, 0x80, 0x80, 0x80, 0x4F, 0x52, };


Module_4_0_Service::Module_4_0_Service(BLEAdvManager &_BLEAdvManager) : 
    m_bleAdvManager(_BLEAdvManager)
{

    m_bleAdvManager_handle = m_bleAdvManager.register_client(this);

    reset();
}


void Module_4_0_Service::reset() 
{
    m_isZero_hysteresis_pct = MK4_IS_ZERO_HYSTERESIS_DEFAULT;

    for(uint8_t index = 0; index < MK4_CHANNEL_COUNT; index++)
    {
        m_channelOffsets_pct[index] = MK4_CHANNEL_OFFSET_DEFAULT;
        m_channelMaximums_pct[index] = MK4_CHANNEL_MAXIMUM_DEFAULT;
    }

    for(uint8_t index = 0; index < MK4_SETVALUE_ARRAY_SIZE; index++)
    {
        m_channelValues_nibble[index] = MK4_CHANNEL_ZERO_VALUE;
    }
}


void Module_4_0_Service::connect() 
{
    if (m_bleAdvManager_handle != UNSET_HANDLE) 
    {
        // MICROBIT_DEBUG_DMESG("Module_4_0_Service::connect");

        get_rf_payload(_addressArray, 5, _telegram_Connect, 8, _ctxValue, m_pPayload);

        m_bleAdvManager.advertise(m_bleAdvManager_handle, m_pPayload);
    }
}


void Module_4_0_Service::stop() 
{
    m_bleAdvManager.advertise_stop(m_bleAdvManager_handle);
}


void Module_4_0_Service::setData() 
{
    if (m_bleAdvManager_handle != UNSET_HANDLE) {

        memcpy(&m_telegram_Data[3], m_channelValues_nibble, sizeof(uint8_t) * 6);

        get_rf_payload(_addressArray, 5, m_telegram_Data, 10, _ctxValue, m_pPayload);

        m_bleAdvManager.advertise(m_bleAdvManager_handle, m_pPayload);
    }
}


void Module_4_0_Service::setChannel(uint8_t channelNo, float value_pct) 
{
    // MICROBIT_DEBUG_DMESG("Module_4_0_Service::setChannel");

     // check 
    if (channelNo >= MK4_CHANNEL_COUNT)
    {
        return;
    }
   
    bool isHighNibble = (channelNo & 0x01) == 0x01; // is odd
    uint8_t channelOffset = channelNo >> 1;         // div 2
    uint8_t originValue_byte = m_channelValues_nibble[channelOffset];
    uint8_t setValue_nibble = 0x00;

    if (value_pct >= -m_isZero_hysteresis_pct && // is value_pct inside m_isZero_hysteresis_pct?
        value_pct <= m_isZero_hysteresis_pct) 
    {
        setValue_nibble = 0x08;
    }
    else if (value_pct < 0) 
    {
        float result_pct = fmax(value_pct - m_channelOffsets_pct[channelNo], -m_channelMaximums_pct[channelNo]);
        float result = result_pct * 0x08 / 100;

        setValue_nibble =  0x0F & (uint8_t)fmax(result + 0x08, 0);
    }
    else 
    {
        float result_pct = fmin(value_pct + m_channelOffsets_pct[channelNo], m_channelMaximums_pct[channelNo]);
        float result = result_pct * 0x80 / 100;

        setValue_nibble = 0x0F & (uint8_t)fmin(result + 0x08, 0x0F);
    }

    if (isHighNibble)
    {
        originValue_byte = (originValue_byte & 0x0F) + (setValue_nibble << 8);
    }
    else
    {
        originValue_byte = (originValue_byte & 0xF0) + setValue_nibble;
    }

    m_channelValues_nibble[channelOffset] = originValue_byte;
}


void Module_4_0_Service::setChannelOffset(uint8_t channelNo, float offset_pct) 
{
     // check 
    if (channelNo >= MK4_CHANNEL_COUNT)
    {
        return;
    }

    m_channelOffsets_pct[channelNo] = offset_pct;
}


/**
 *  set maximum value (in percent) of channel
 * @param channelNo [0..5]
 * @param maximum_pct [0..100], eg: "80"
 */
void Module_4_0_Service::setChannelMax(uint8_t channelNo, float maximum_pct) 
{
     // check 
    if (channelNo >= MK4_CHANNEL_COUNT)
    {
        return;
    }

    m_channelMaximums_pct[channelNo] = maximum_pct;
}


uint8_t Module_4_0_Service::getVersion() {

    return this->m_bleAdvManager_handle;
}
