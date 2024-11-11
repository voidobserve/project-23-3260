#include "aip650.h"
#include <string.h>

// 0 1 2 3 4 5 6 7 8 9 NULL -
// u8 leddata[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x00, 0x40};

/*
    //[0]-- com1显示--连接到第二个数码管(从左往右数)
    //[1]-- com2显示--连接到按键对应的LED
    //[2]-- com3显示--连接到第一个数码管(从左往右数)
*/
u8 aip650_show_buff[3] = {0}; // aip650显示缓冲区（显存）

// 存放要显示的内容
const u8 aip650_data_map_buf[] = {
    0xE7, // 0
    0x81, // 1
    0x75, // 2
    0xB5, // 3
    0x93, // 4
    0xB6, // 5
    0xF6, // 6
    0x85, // 7
    0xF7, // 8
    0xB7, // 9

    0x66, // 大写 "C"
    0xF1, // 小写 "d"
    0x56, // 大写 "F"
    0xD3, // 大写 "H"
    0x62, // 大写 "L"
    0xC7, // 小写 "n"
};

/*指令集*/

// 4801--系统使能，8段显示，8级亮度
#define SYS_CMD 0x4801

void aip650_config(void)
{
    // 14脚-P16-IIC_DATA
    // 15脚-P15-IIC_CLK
    P1_MD1 &= ~((GPIO_P15_MODE_SEL(0x03)) | (GPIO_P16_MODE_SEL(0x03))); //
    P1_MD1 |= ((GPIO_P15_MODE_SEL(0x02)) | (GPIO_P16_MODE_SEL(0x02)));  // 配置为数字复用模式
    P1_PU |= (GPIO_P15_PULL_UP(0x01) | GPIO_P16_PULL_UP(0x01));         // 上拉
    P1_ODN |= (GPIO_P15_ODN_EN(0x01) | GPIO_P16_ODN_EN(0x01));          // 开漏
    P1_AF0 |= (GPIO_P15_FUNC_SEL(0x01) | GPIO_P16_FUNC_SEL(0x01));      // P15作为IIC_CLK, P16作为IIC_DATA

    I2C_CON = I2C_CR_SEL(0x02); // 配置波特率，可根据表格自行选择
    I2C_CON |= I2C_EN(0x1);     // 使能模块

    // memset(sg_650e_drv._buf, 0x00, AIP650E_SIZE);
    // aip650e_update(&sg_650e_drv); // 上电第一次清空显示
}

/**
 * @brief  IIC sends 1 byte data function
 * @param  iic_data: IIC data
 * @param  flag: 0: None  1:send start   2:send stop
 * @retval Returns 1 and receives an ACK
 */
static u8 iic_master_tx(u8 iic_data, u8 flag)
{
#define START_FLAG (1)
#define STOP_FLAG (2)

    u8 ack_flag = 0;

    if (flag == START_FLAG)
    {
        // 配置发送起始位
        I2C_CON |= (I2C_START_BIT(0x1) | I2C_SI_CLEAR(0x1));
        // 等待 SI 置 1， 起始位发送成功时会置 1， 其它情况也可能会置 1， 需要注意
        while (!(I2C_STA & I2C_SI_STA(0x1)))
            ;
        I2C_CON &= ~I2C_START_BIT(0x1);

        // 判断模块状态
        if (!(((I2C_STA & I2C_STA_FLAG(0x1F)) == 0x08) ||
              ((I2C_STA & I2C_STA_FLAG(0x1F)) == 0x10)))
        {
            return 0;
        }
    }

    // 写入目标从机地址
    I2C_DATA = iic_data;
    // 等待地址发送完成
    while (!(I2C_STA & I2C_SI_STA(0x1)))
        ;

    // 判断是否收到 ACK
    if (((I2C_STA & I2C_STA_FLAG(0x1F)) == 0x18) ||
        ((I2C_STA & I2C_STA_FLAG(0x1F)) == 0x28) ||
        ((I2C_STA & I2C_STA_FLAG(0x1F)) == 0x40))
    {
        ack_flag = 1;
    }
    else
    {
        ack_flag = 0;
    }

    if (flag == STOP_FLAG)
    {
        // 配置发送停止位
        I2C_CON |= (I2C_STOP_BIT(0x1) | I2C_SI_CLEAR(0x1));
    }

    return ack_flag;
}

static void aip650_write_cmd(u16 cmd) //
{
    iic_master_tx(cmd >> 8, 1);
    iic_master_tx(cmd & 0xFF, 2);
}

// // 更新aip650的显存
// void aip650_show_buff_update(u8 *buff)
// {
//     aip650_show_buff[0] = (aip650_show_buff[0] & ~0xFF) | buff[0];
//     aip650_show_buff[1] = (aip650_show_buff[1] & ~0xFF) | buff[1];
//     aip650_show_buff[2] = (aip650_show_buff[2] & ~0xFF) | buff[2];
// }

// 刷新aip650要显示的内容(将aip650显存的内容更新到外设上)
void aip650_show_refresh(void)
{
    aip650_write_cmd(SYS_CMD); // 开显示，8级显示(0x4801);睡眠使能。时钟停振(0x4804)

    // aip650_write_cmd(0x6800 | aip650_show_buff[0]); // com0显示--未连接任何硬件
    aip650_write_cmd(0x6A00 | aip650_show_buff[0]); // com1显示--连接到第二个数码管(从左往右数)
    aip650_write_cmd(0x6C00 | aip650_show_buff[1]); // com2显示--连接到按键对应的LED
    aip650_write_cmd(0x6E00 | aip650_show_buff[2]); // com3显示--连接到第一个数码管(从左往右数)
}

// 向aip650的显存写入要显示的数字,
// 如果传参 == 0xFF，则清空要显示的数字，不影响小数点的显示
// 如果传入了超出范围的参数，整个aip650显存将被清空
void aip650_show_data(u8 data_bit1, u8 data_bit0)
{
    if ((0xFF != data_bit0 && data_bit0 > (sizeof(aip650_data_map_buf) - 1)) ||
        (0xFF != data_bit1 && data_bit1 > (sizeof(aip650_data_map_buf) - 1)))
    {
        // 数值超出了LED能够显示的范围，清空显示
        aip650_show_buff[2] = 0;
        aip650_show_buff[0] = 0;
        // aip650_show_refresh();
        return;
    }

    if (0xFF == data_bit0)
    {
        aip650_show_buff[0] &= ~0xF7;
    }

    if (0xFF == data_bit1)
    {
        aip650_show_buff[2] &= ~0xF7;
    }

    if (0xFF != data_bit0)
    {
        aip650_show_buff[0] = aip650_data_map_buf[data_bit0];
    }

    if (0xFF != data_bit1)
    {
        aip650_show_buff[2] = aip650_data_map_buf[data_bit1];
    }
}

// 向aip650显存写入要显示的小数点
// 参数-locate， 0--不显示小数点，
//              1--显示第一个小数点（从左往右数）,
//              2--显示第二个小数点(从左往右数),
//              3--两个小数点都显示
//             如果传入了超出范围的参数，整个aip650显存将被清空
void aip650_show_point(u8 locate)
{
    if (0 == locate)
    {
        aip650_show_buff[2] &= ~0x08;
        aip650_show_buff[0] &= ~0x08;
    }
    else if (1 == locate)
    {
        aip650_show_buff[2] |= 0x08;
        aip650_show_buff[0] &= ~0x08;
    }
    else if (2 == locate)
    {
        aip650_show_buff[2] &= ~0x08;
        aip650_show_buff[0] |= 0x08;
    }
    else if (3 == locate)
    {
        aip650_show_buff[2] |= 0x08;
        aip650_show_buff[0] |= 0x08;
    }
    else
    {
        aip650_show_buff[0] = 0;
        aip650_show_buff[1] = 0;
        aip650_show_buff[2] = 0;
    }

    // aip650_show_refresh();
}

// 向aip650显存写入要点亮的触摸按键的对应的LED
// 参数：led_data, 范围：0x00~0x1F,第0bit表示按键K1对应的LED的状态，
//                                第4bit表示按键K5对应的LED的状态，
//                                0表示熄灭，1表示点亮
//      如果传入了超出范围的参数，整个aip650显存将被清空
void aip650_show_led_of_touch(u8 led_data)
{   
    aip650_show_buff[1] = 0; // 清空原来的数据

    if (led_data > 0x1F)
    {
        // 传入的数据格式有误，清空显示
        aip650_show_buff[0] = 0;
        // aip650_show_buff[1] = 0;
        aip650_show_buff[2] = 0;
        return;
    }

    if (led_data & 0x01) // 按键K1
    {
        aip650_show_buff[1] |= 0x04;
    }
    else if ((led_data & 0x01) == 0)
    {
        aip650_show_buff[1] &= ~0x04;
    }

    if ((led_data >> 1) & 0x01) // 按键K2
    {
        aip650_show_buff[1] |= 0x02;
    }
    else if (((led_data >> 1) & 0x01) == 0)
    {
        aip650_show_buff[1] &= ~0x02;
    }

    if ((led_data >> 2) & 0x01) // 按键K3
    {
        aip650_show_buff[1] |= 0x80;
    }
    else if (((led_data >> 2) & 0x01) == 0)
    {
        aip650_show_buff[1] &= ~0x80;
    }

    if ((led_data >> 3) & 0x01) // 按键K4
    {
        aip650_show_buff[1] |= 0x40;
    }
    else if (((led_data >> 3) & 0x01) == 0)
    {
        aip650_show_buff[1] &= ~0x40;
    }

    if ((led_data >> 4) & 0x01) // 按键K5
    {
        aip650_show_buff[1] |= 0x20;
    }
    else if (((led_data >> 4) & 0x01) == 0)
    {
        aip650_show_buff[1] &= ~0x20;
    }
}
