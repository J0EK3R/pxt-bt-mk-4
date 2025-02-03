#ifndef MODULE_4_0_SERVICE_H
#define MODULE_4_0_SERVICE_H

#include "MicroBitConfig.h"
#include "pxt.h"
#include "BLEAdvManager.h"

#define MK4_CHANNEL_COUNT 12                // number of channels
#define MK4_SETVALUE_ARRAY_SIZE 6           // size of setvalue array
#define MK4_IS_ZERO_HYSTERESIS_DEFAULT 1.0  // default value of iszero hysteresis
#define MK4_CHANNEL_OFFSET_DEFAULT 0.0      // default  of channel offset hysteresis
#define MK4_CHANNEL_MAXIMUM_DEFAULT 100.0   // default of channel maximum value
#define MK4_CHANNEL_ZERO_VALUE 0x88         // means stop

class Module_4_0_Service : public IBLEAdvClient
{
    public:
    /**
      * Constructor.
      * Create a representation of the Module_4_0_Service
      * @param _BLEAdvManager The instance of a BLEAdvManager that we're running on.
      * @param moduleNo Number of the MK4 Module.
      */
    Module_4_0_Service(BLEAdvManager &_BLEAdvManager);

    void connect();
    void stop();

    void reset();

    void setChannel(uint8_t channelNo, float value_pct);
    void setData();

    void setChannelOffset(uint8_t channelNo, float offset_pct);
    void setChannelMax(uint8_t channelNo, float maximum_pct);

    uint8_t getVersion();

  private:

    // advertising manager
    BLEAdvManager &m_bleAdvManager;
    
    // handle from bleAdvManager returned on registration
    uint8_t m_bleAdvManager_handle;
    
    // left/right border in percent of a hysteresis taking a setvalue as zero
    float m_isZero_hysteresis_pct = MK4_IS_ZERO_HYSTERESIS_DEFAULT;

    // array of channel specific offsets in percent beeing added to a channels setvalue (to finetune)
    float m_channelOffsets_abs_pct[MK4_CHANNEL_COUNT] = {
        MK4_CHANNEL_OFFSET_DEFAULT, MK4_CHANNEL_OFFSET_DEFAULT, MK4_CHANNEL_OFFSET_DEFAULT, MK4_CHANNEL_OFFSET_DEFAULT, MK4_CHANNEL_OFFSET_DEFAULT, MK4_CHANNEL_OFFSET_DEFAULT,
        MK4_CHANNEL_OFFSET_DEFAULT, MK4_CHANNEL_OFFSET_DEFAULT, MK4_CHANNEL_OFFSET_DEFAULT, MK4_CHANNEL_OFFSET_DEFAULT, MK4_CHANNEL_OFFSET_DEFAULT, MK4_CHANNEL_OFFSET_DEFAULT };

    // array of channel specific maximums in percent to limit a channels setvalue (to finetune)
    float m_channelMaximums_abs_pct[MK4_CHANNEL_COUNT] = {
        MK4_CHANNEL_MAXIMUM_DEFAULT, MK4_CHANNEL_MAXIMUM_DEFAULT, MK4_CHANNEL_MAXIMUM_DEFAULT, MK4_CHANNEL_MAXIMUM_DEFAULT, MK4_CHANNEL_MAXIMUM_DEFAULT, MK4_CHANNEL_MAXIMUM_DEFAULT, 
        MK4_CHANNEL_MAXIMUM_DEFAULT, MK4_CHANNEL_MAXIMUM_DEFAULT, MK4_CHANNEL_MAXIMUM_DEFAULT, MK4_CHANNEL_MAXIMUM_DEFAULT, MK4_CHANNEL_MAXIMUM_DEFAULT, MK4_CHANNEL_MAXIMUM_DEFAULT };

    // array of absolute (finetuned) setvalues to be sent - one nibble per channel
    uint8_t m_channelValues_nibble[MK4_SETVALUE_ARRAY_SIZE] = {
        MK4_CHANNEL_ZERO_VALUE, MK4_CHANNEL_ZERO_VALUE, MK4_CHANNEL_ZERO_VALUE, MK4_CHANNEL_ZERO_VALUE, MK4_CHANNEL_ZERO_VALUE, MK4_CHANNEL_ZERO_VALUE, };

    uint8_t m_pPayload[31] = {
        0x02, // length: 0x2 (2)
        0x01, // type:   flags (0x01)
        0x06, // 0x06,

        0x1b, // length: 0x1b (27)
        0xff, // type:   manufacturer specific (0xff)
        0xf0, 0xff, // company Id: unkown 0xfff0
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
      };
      
      uint8_t m_telegram_Data[10] = { 
        0x7D, 0x7B, 0xA7, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x82 }; // connect
};

#endif // MODULE_4_0_SERVICE_H