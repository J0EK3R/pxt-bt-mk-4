/**
 * Support for M0uld K1ng Module 4.0.
 */
//% color=#000c30 weight=100 icon="\uf294" block="MK Module 6.0"
namespace MK4
{
    export enum Module
    {
         //% block="MK4 1" enumval=0
         M1 = 0,
         //% block="MK4 2" enumval=1
         M2 = 1,
         //% block="MK4 3" enumval=2
         M3 = 2,
    }


    export enum Channel
    {
        //% block="Channel A" enumval=0
        A = 0,
        //% block="Channel B" enumval=1
        B = 1,
        //% block="Channel C" enumval=2
        C = 2,
        //% block="Channel D" enumval=3
        D = 3,
    }


    /**
     *  initialisation of the module
     * @param module module, eg: "Module.M1"
     */
    //% blockId=mk4_init
    //% block="$module init"
    //% group="M0uld K1ng Module 4.0"
    //% shim=mk_module_4_0::init
    //% blockGap=8 weight=60
    export function init(module: MK4.Module): void
    {
        return;
    }

    
    /**
     *  set value (in percent) of channel
     * @param module module, eg: "Module.M1"
     * @param channel channel, eg: "Channel.A"
     * @param value [-100..100], eg: "0"
     */
    //% blockId=mk4_setchannel 
    //% block="$module set value $channel to $value"
    //% group="M0uld K1ng Module 4.0"
    //% value.min=-100 value.max=100 value.defl=0
    //% shim=mk_module_4_0::setChannel
    //% blockGap=8 weight=60
    export function setChannel(module: MK4.Module, channel: MK4.Channel, value: number): void
    {
        return;
    }


    /**
     *  take over data to send
     * @param module module, eg: "Module.M1"
     */
    //% blockId=mk4_setdata 
    //% block="$module take over data to send"
    //% group="M0uld K1ng Module 4.0"
    //% shim=mk_module_4_0::setData
    //% blockGap=8 weight=60
    export function setData(module: MK4.Module): void
    {
        return;
    }


    /**
     * stop advertising
     * @param module module, eg: "Module.M1"
     */
    //% blockId=mk4_stop
    //% block="$module stop"
    //% group="M0uld K1ng Module 4.0"
    //% shim=mk_module_4_0::stop
    //% weight=10 blockGap=8
    export function stop(module: MK4.Module): void
    {
        return;
    };


    /**
     *  set offset value (in percent) of channel
     * @param module module, eg: "Module.M1"
     * @param channel channel, eg: "Channel.A"
     * @param offset [0..100], eg: "0"
     */
    //% blockId=mk4_setchanneloffset
    //% block="$module set offset $channel to $offset"
    //% group="M0uld K1ng Module 4.0 - finetune"
    //% offset.min=0 offset.max=100 offset.defl=0
    //% shim=mk_module_4_0::setChannelOffset
    //% blockGap=8 weight=60
    export function setChannelOffset(module: MK4.Module, channel: MK4.Channel, offset: number): void
    {
        return;
    }


    /**
     *  set maximum value (in percent) of channel
     * @param module module, eg: "Module.M1"
     * @param channel channel, eg: "Channel.A"
     * @param maximum [0..100], eg: "100"
     */
    //% blockId=mk4_setchannelmax
    //% block="$module set maximum $channel to $maximum"
    //% group="M0uld K1ng Module 4.0 - finetune"
    //% maximum.min=0 maximum.max=100 maximum.defl=100
    //% shim=mk_module_4_0::setChannelMax
    //% blockGap=8 weight=60
    export function setChannelMax(module: MK4.Module, channel: MK4.Channel, maximum: number = 100): void
    {
        return;
    }


    /**
     *  get Version
     * @param module module, eg: "Module.M1"
     */
    //% blockId=mk4_getversion 
    //% block="$module get Version"
    //% group="M0uld K1ng Module 4.0"
    //% shim=mk_module_4_0::getVersion
    //% blockGap=8 weight=60 
    //% advanced=true
    export function getVersion(module: MK4.Module): number
    {
        return 0;
    }
}