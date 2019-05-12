#include <rtthread.h>
#include <stdlib.h>
#include <AD7746.h>

unsigned char c[2];

static void ad7746_read_temperature(int argc,char *argv[])
{
    // Initialization
    AD7746 ad7746;
    ad7746.begin();

    // Setup VT
    c[0] = 0x81;
    ad7746.write(AD7746_REG_VT_SETUP, c, 1);

    // Setup Sample
    c[0] = 0xA1;
    ad7746.write(AD7746_REG_CFG, c, 1);

    // Print Temperature
    for(int i = 0; i< 5; i++)
    {
        rt_kprintf("\nCurrent Temperature: %d\n", ad7746.getVTData() / 2048 - 4096);
        rt_thread_mdelay(1000);
    }
}
MSH_CMD_EXPORT(ad7746_read_temperature, ad7746 read temperature example);

static void ad7746_read(int argc,char *argv[])
{
    AD7746 ad7746;
    rt_uint8_t addr = atoi(argv[1]);
    ad7746.begin();
    c[0] = 0;
    c[1] = 0;
    ad7746.read(addr, c, 1);
    rt_kprintf("Reading from %d\n", addr);
    rt_kprintf("%02X\n", c[0]);
}
MSH_CMD_EXPORT(ad7746_read, ad7746 read command);

static void ad7746_write(int argc,char *argv[])
{
    AD7746 ad7746;
    rt_uint8_t addr = atoi(argv[1]);
    ad7746.begin();
    c[0] = atoi(argv[2]);
    c[1] = 0;
    ad7746.write(addr, c, 1);
    rt_kprintf("Writing to %d:%02X\n", addr, c[0]);
}
MSH_CMD_EXPORT(ad7746_write, ad7746 write command);