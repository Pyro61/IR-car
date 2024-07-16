#include "soundsignal.h"
#include "driver_soundsignal.h"


void soundsignal_on_horn(void)
{
    driver_soundsignal_on_horn();
}


void soundsignal_on_turn(void)
{
    driver_soundsignal_on_turn();
}


void soundsignal_on_emergencylights(void)
{
    driver_soundsignal_on_emergencylights();
}


void soundsignal_on_distsensorblock(void)
{
    driver_soundsignal_on_distsensorblock();
}


void soundsignal_on_lowbattery(void)
{
    soundsignal_on_lowbattery();
}


void soundsignal_off_horn(void)
{
    driver_soundsignal_off_horn();
}


void soundsignal_off_turn(void)
{
    driver_soundsignal_off_turn();
}


void soundsignal_off_emergencylights(void)
{
    soundsignal_off_emergencylights();
}


void soundsignal_off_distsensorblock(void)
{
    driver_soundsignal_off_distsensorblock();
}


void soundsignal_off_lowbattery(void)
{
    driver_soundsignal_off_lowbattery();
}
