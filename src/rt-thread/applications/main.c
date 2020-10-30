
#include <rtthread.h>
#include <rtdevice.h>
#include "HAL_device.h"
#include "task.h"


int main(void)
{
    KEY_Task_Init();
    Blue_Task_Init();
    PWN_Task_Init();
}
