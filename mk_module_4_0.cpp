#include "pxt.h"
#include <stdio.h>
#include <ctype.h>
#include "MicroBitConfig.h"
#include "Module_4_0_Service.h"
#include "BLEAdvManager.h"

using namespace pxt;

/**
 * Support for M0uld K1ng Module 4.0.
 */
namespace mk_Module_4_0 
{
    Module_4_0_Service* _pService[3] = 
    {
        NULL,
        NULL,
        NULL
    };


    //%
    Module_4_0_Service* getService(uint8_t moduleNo) 
    {
        Module_4_0_Service *pService = _pService[moduleNo];

        if (NULL == pService)
        {
            BLEAdvManager *p_BLEAdvManager = BLEAdvManager::getInstance();

            pService = new Module_4_0_Service(*p_BLEAdvManager, moduleNo);
            _pService[moduleNo] = pService;
        }

        return pService;
    }


    //%
    void init(uint8_t moduleNo) 
    {
        Module_4_0_Service *pService = getService(moduleNo);

        pService->connect();
    }


    //% 
    void setChannel(uint8_t moduleNo, uint8_t channel, float value) 
    {
        Module_4_0_Service *pService = getService(moduleNo);

        pService->setChannel(channel, value);
    }   


    //% 
    void setChannelOffset(uint8_t moduleNo, uint8_t channel, float value) 
    {
        Module_4_0_Service *pService = getService(moduleNo);

        pService->setChannelOffset(channel, value);
    }   


    //% 
    void setData(uint8_t moduleNo) 
    {
        Module_4_0_Service *pService = getService(moduleNo);

        pService->setData();
    }   


    //% 
    void stop(uint8_t moduleNo) 
    {
        Module_4_0_Service *pService = getService(moduleNo);

        if (NULL != pService) 
        {
            pService->stop();
        }        
    }   


    //% 
    uint8_t getVersion(uint8_t moduleNo) 
    {
        Module_4_0_Service *pService = getService(moduleNo);

        return pService->getVersion();
    }   
}