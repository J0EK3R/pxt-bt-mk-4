#include "MicroBitConfig.h"
#include "Module_4_0_Service.h"
#include "CryptTool.h"

static uint8_t _ctxValue = 0x25; // CTXValue for Encryption
static uint8_t _addressArray[5]     = { 0xC1, 0xC2, 0xC3, 0xC4, 0xC5 };
static uint8_t _telegram_Connect[8] = { 0x6D, 0x7B, 0xA7, 0x80, 0x80, 0x80, 0x80, 0x92, };


Module_4_0_Service::Module_4_0_Service(BLEAdvManager &_BLEAdvManager, uint8_t moduleNo) : 
    m_bleAdvManager(_BLEAdvManager), 
    m_moduleNo(moduleNo) 
{

    m_bleAdvManager_handle = m_bleAdvManager.register_client(this);

    m_telegram_Data[0] = 0x61 + m_moduleNo;
    m_telegram_Data[9] = 0x9E - m_moduleNo;
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

        memcpy(&m_telegram_Data[3], m_channelValues_pct, sizeof(uint8_t) * 6);

        get_rf_payload(_addressArray, 5, m_telegram_Data, 10, _ctxValue, m_pPayload);

        m_bleAdvManager.advertise(m_bleAdvManager_handle, m_pPayload);
    }
}


void Module_4_0_Service::setChannel(uint8_t channelNo, float value_pct) 
{
    // MICROBIT_DEBUG_DMESG("Module_4_0_Service::setChannel");

    if (value_pct == 0) 
    {
        m_channelValues_pct[channelNo] = 0x80;
    }
    else if (value_pct < 0) 
    {
        float result_pct = fmax(value_pct - m_channelOffsets_pct[channelNo], -m_channelMaximums_pct[channelNo]);
        float result = result_pct * 0x80 / 100;

        m_channelValues_pct[channelNo] = (uint8_t)fmax(result + 0x80, 0);
    }
    else 
    {
        float result_pct = fmin(value_pct + m_channelOffsets_pct[channelNo], m_channelMaximums_pct[channelNo]);
        float result = result_pct * 0x80 / 100;

        m_channelValues_pct[channelNo] = (uint8_t)fmin(result + 0x80, 0xFF);
    }
}


void Module_4_0_Service::setChannelOffset(uint8_t channelNo, float offset_pct) {

    m_channelOffsets_pct[channelNo] = offset_pct;
}


/**
 *  set maximum value (in percent) of channel
 * @param channelNo [0..5]
 * @param maximum_pct [0..100], eg: "80"
 */
void Module_4_0_Service::setChannelMax(uint8_t channelNo, float maximum_pct) 
{
    // no range check of channelNo is done because it's an enum value

    m_channelMaximums_pct[channelNo] = maximum_pct;
}


uint8_t Module_4_0_Service::getVersion() {

    return this->m_bleAdvManager_handle;
}
