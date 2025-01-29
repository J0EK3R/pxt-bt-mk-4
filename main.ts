/// <reference no-default-lib="true"/>
/**
 * Support for M0uld K1ng Module 4.0.
 */
//% color=#0c3000 weight=100 icon="\uf294" block="MK Module 4.0"
namespace MK
{
    /**
    *  M0uld K1ng Module 4.0 init
    * @param moduleNo moduleNo, eg: "Module 1"
    */
    //% blockId=mk4_init
    //% block="MK4.0 %moduleNo init"
    //% shim=mk_module_4_0::init
    //% blockGap=8 weight=60
    export function init(moduleNo: MK4.Module): void
    {
        return;
    }

    /**
    *  M0uld K1ng Module 4.0 SetChannel
    * @param moduleNo moduleNo, eg: "Module 1"
    * @param channel channel, eg: "Channel A"
    * @param value -127..127, eg: "value 0"
    */
    //% blockId=mk4_setchannel 
    //% block="MK4.0 %moduleNo set %channel to value %value"
    //% shim=mk_module_4_0::setChannel
    //% blockGap=8 weight=60
    export function setChannel(moduleNo: MK4.Module, channel: MK4.Channel, value: number): void
    {
        return;
    }

    /**
    *  M0uld K1ng Module 4.0 SetChannelOffset
    * @param moduleNo moduleNo, eg: "Module 1"
    * @param channel channel, eg: "Channel A"
    * @param offset -127..127, eg: "value 0"
    */
    //% blockId=mk4_setchanneloffset
    //% block="MK4.0 %moduleNo set %channel offset to value %offset"
    //% shim=mk_module_4_0::setChannelOffset
    //% blockGap=8 weight=60
    export function setChannelOffset(moduleNo: MK4.Module, channel: MK4.Channel, offset: number): void
    {
        return;
    }

    /**
    *  M0uld K1ng Module 4.0 SendData
    * @param moduleNo moduleNo, eg: "Module 1"
    */
    //% blockId=mk4_senddata 
    //% block="MK4.0 %moduleNo send data"
    //% shim=mk_module_4_0::sendData
    //% blockGap=8 weight=60
    export function senddata(moduleNo: MK4.Module): void
    {
        return;
    }

    /**
     * M0uld K1ng Module 4.0 stop advertising
     * @param moduleNo moduleNo, eg: "Module 1"
     */
    //% blockId=mk4_stop
    //% block="MK4.0 %moduleNo stop"
    //% shim=mk_module_4_0::stop
    //% weight=10 blockGap=8
    export function stop(moduleNo: MK4.Module): void
    {
        return;
    };


    /**
    *  M0uld K1ng Module 4.0 get Version
    * @param moduleNo moduleNo, eg: "Module 1"
    */
    //% blockId=mk4_getversion 
    //% block="MK4.0 %moduleNo get Version"
    //% shim=mk_module_4_0::getVersion
    //% blockGap=8 weight=60 advanced=true
    export function getversion(moduleNo: MK4.Module): number
    {
        return 0;
    }
}