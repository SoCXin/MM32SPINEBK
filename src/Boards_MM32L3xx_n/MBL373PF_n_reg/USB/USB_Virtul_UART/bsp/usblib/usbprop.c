
#include "usbprop.h"
#include "usb.h"

unsigned char *pucClassDrcData;


//虚拟串口参数
LINE_CODING linecoding =
{
    115200, /* baud rate*/
    0x00,   /* stop bits-1*/
    0x00,   /* parity - none*/
    0x08    /* no. of bits 8*/
};


/********************************************************************************************************
**函数信息 ：USBCDC_senddata(unsigned char *data,unsigned short length)
**功能描述 ：数据转换
**输入参数 ：unsigned char *data(转换的数据指针),unsigned short length(转换数据长度)
**输出参数 ：
**备    注 ：
********************************************************************************************************/
void USBCDC_senddata(unsigned char *data, unsigned short length)
{
    if(linecoding.datatype == 7)
    {
        while(length)
        {
            *data &= 0x7f;
            length--;
            data++;
        }
    }
    else if(linecoding.datatype == 8)							//不操作
    {
        while(length)
        {

        }
    }
}

/********************************************************************************************************
**函数信息 ：Class_Get_Line_Coding(void)
**功能描述 ：CDC Abstract Control Model(虚拟串口) 类请求，GET_LINE_CODING
**输入参数 ：
**输出参数 ：
**备    注 ：
********************************************************************************************************/
void Class_Get_Line_Coding(void)      							// bRequest = 0x21
{
    int count;
    switch( usb_running_ctrl_state )
    {
        case    USB_CTRL_SETUP :
            if(req_dir == USB_REQ_DIR_IN)
            {
                pucClassDrcData = (u8*)&linecoding;
                usb_running_ctrl_state = USB_CTRL_IN;
            }
            else
            {
                usb_running_ctrl_state = USB_IDLE;
            }
            break ;

        case    USB_CTRL_IN :

            while(USB->rEP0_CTRL & 0x80);
            for( count = 0; count < 7; count++ )
            {
                USB->rEP0_FIFO = *pucClassDrcData;
                pucClassDrcData ++;
            }
            USB->rEP0_CTRL = 0x87;

            usb_running_ctrl_state = USB_IDLE;
            break ;

        default :
            //		usb_running_ctrl_state = USB_IDLE ;
            break ;
    }
}
unsigned char baud_read [64];
/********************************************************************************************************
**函数信息 ：Class_Get_Line_Coding(void)
**功能描述 ：CDC Abstract Control Model(虚拟串口) 类请求，SET_LINE_CODING
**输入参数 ：
**输出参数 ：
**备    注 ：
********************************************************************************************************/
void Class_Set_Line_Coding(void)  // bRequest = 0x20
{
    int count, i;

    switch( usb_running_ctrl_state )
    {
        case    USB_CTRL_SETUP :
            if(req_dir == USB_REQ_DIR_OUT)
            {
                usb_running_ctrl_state = USB_CTRL_OUT;
            }
            else
            {
                usb_running_ctrl_state = USB_IDLE;
            }
            break ;

        case    USB_CTRL_OUT :
            count = USB->rEP0_AVIL;
            for(i = 0; i < count ; i++)
            {
                baud_read[i] = USB->rEP0_FIFO;
            }
            linecoding.bitrate = ((u32)baud_read[0] << 0) | ((u32)baud_read[1] << 8) | ((u32)baud_read[2] << 16) | ((u32)baud_read[3] << 24);
            uart_init(48, linecoding.bitrate);

            usb_running_ctrl_state = USB_CTRL_STATUS;
            break;

        default :
            //			usb_running_ctrl_state = USB_IDLE ;
            break ;
    }
}
/********************************************************************************************************
**函数信息 ：Class_Get_Line_Coding(void)
**功能描述 ：CDC Abstract Control Model(虚拟串口) 类请求，SET_LINE_CODING
**输入参数 ：
**输出参数 ：
**备    注 ：
********************************************************************************************************/

void Class_Set_Control_Line_State(void)      				// bRequest = 0x22
{
    int count, i;
    unsigned char state_temp;
    switch( usb_running_ctrl_state )
    {
        case    USB_CTRL_SETUP :							//控制传输状态阶段
            if(req_dir == USB_REQ_DIR_OUT)
            {
                usb_running_ctrl_state = USB_CTRL_OUT;
            }
            else
            {
                usb_running_ctrl_state = USB_IDLE;
            }
            break ;
        case    USB_CTRL_OUT :
            count = USB->rEP0_AVIL;
            for(i = 0; i < count ; i++)
            {
                state_temp = USB->rEP0_FIFO;				//此处为空数据(控制传输数据阶段)
            }
            usb_running_ctrl_state = USB_CTRL_STATUS;
            break;

        default :
            {
                //	        usb_running_ctrl_state = USB_IDLE ;
                break ;
            }
    }
}

unsigned char ep1_Tx_dataBuf[2048];			//USB 发送缓冲区,可自定义大小
unsigned int ui_curTxLen = 0;				//实时发送长度
unsigned int ep1_Tx_dataLen = 0;			//发送数据总长度(小于自定义缓冲区大小)
unsigned char ep1_tx_flag = 0;				//发送标志

/********************************************************************************************************
**函数信息 ：EP1_USB_IN_Data(void)
**功能描述 ：USB从发送缓冲区读数据通过IN端点发出
**输入参数 ：
**输出参数 ：
**备    注 ：USB数据发送时，数据超过最大端点size时，需要拆包发送
********************************************************************************************************/
void EP1_USB_IN_Data(void)      			// bRequest = 0x22
{
    int count, i;

    if(ep1_tx_flag != 0)						//tx_buf非空
    {
        while(USB->rEP1_CTRL & 0x80);
        if(ep1_Tx_dataLen > 64)				//USB数据拆分发送
        {
            count = 64;
            ep1_Tx_dataLen -= 64;
        }
        else
        {
            count = ep1_Tx_dataLen;
            ep1_Tx_dataLen = 0;
        }
        for(i = 0; i < count; i++)
        {
            USB->rEP1_FIFO = *(ep1_Tx_dataBuf + ui_curTxLen + i);
        }
        USB->rEP1_CTRL = 0x80 | count;
        if(ep1_Tx_dataLen == 0)
        {
            ep1_tx_flag = 0;
            ui_curTxLen = 0;
            usb_running_ctrl_state = USB_IDLE;
        }
        else
        {
            ui_curTxLen += count;
        }
    }

}
/********************************************************************************************************
**函数信息 ：UsbVcomSend(unsigned char*Info,unsigned int *infoLenth)
**功能描述 ：将要发送的数据写入USB发送缓冲区
**输入参数 ：unsigned char*Info(发送数据指针),unsigned int *infoLenth(发送数据长度指针)
**输出参数 ：return status(0表示发送完成,1表示正在发送);
**备    注 ：
********************************************************************************************************/
char UsbVcomSend(unsigned char*Info, unsigned int *infoLenth)
{
    unsigned int i, status = 0;
    if((ep1_tx_flag == 0) && (*infoLenth != 0))
    {
        ep1_Tx_dataLen = *infoLenth;
        *infoLenth = 0;
        for(i = 0; i < ep1_Tx_dataLen; i++)
        {
            ep1_Tx_dataBuf[i] = *(Info + i);
        }
        ep1_tx_flag = 1;
    }
    else
    {
        status = 1;
    }
    return status;
}
unsigned char ep3_rx_flag = 0;				//端点3接收标志
/********************************************************************************************************
**函数信息 ：EP3_USB_OUT_Data(void)
**功能描述 ：USB_OUT端点接收到有效数据,接收标志位置1
**输入参数 ：
**输出参数 ：
**备    注 ：
********************************************************************************************************/
void EP3_USB_OUT_Data(void)      			// bRequest = 0x22
{
    if (ep3_rx_flag == 0)					//rx_buf空
    {
        ep3_rx_flag = 1;
    }
    usb_running_ctrl_state = USB_IDLE;
}
/********************************************************************************************************
**函数信息 ：UsbVcomRec(unsigned char*rxInfo)
**功能描述 ：从USB device从 OUT端点接收数据
**输入参数 ：unsigned char*rxInfo(接收信息buf)
**输出参数 ：
**备    注 ：
********************************************************************************************************/
unsigned int UsbVcomRec(unsigned char*rxInfo)
{
    unsigned int i, temp_len;
    if(ep3_rx_flag == 1)					//接收buf非空
    {
        temp_len = USB->rEP3_AVIL & 0x7f;
        for(i = 0; i < temp_len; i++)
        {
            *(rxInfo + i) = USB->rEP3_FIFO;
        }
        ep3_rx_flag = 0;
    }
    else
    {
        return 0;
    }
    return temp_len;
}

