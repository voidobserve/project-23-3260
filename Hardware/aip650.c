#include "aip650.h"
#include <string.h>

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
}

/**
 * @brief  IIC sends 1 byte data function
 * @param  iic_data: IIC data
 * @param  flag: 0: None  1:send start   2:send stop
 * @retval Returns 1 and receives an ACK
 */
u8 iic_master_tx(u8 iic_data, u8 flag)
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

struct _650e_drv_ sg_650e_drv;

// 0 1 2 3 4 5 6 7 8 9 NULL -
u8 leddata[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x00, 0x40};

/*指令集*/
#define SYS_CMD 0x4801 // 48是系统指令，设置系统参数	；01是显示指令，设置为工作模式，8段显示，8级亮度，显示开

void aip650e_init(struct _650e_drv_ *drv)
{
    memset(drv->_buf, 0x00, AIP650E_SIZE);
    aip650e_update(drv); // 上电第一次清空显示
}

/*延时最小单元*/
// #define TIME_UINT 1

// static void delay_us(uint32_t nus)
// {
// 	uint32_t Delay = nus;
// 	do
// 	{
// 		__NOP();
// 	} while (Delay--);
// }

// IIC开始信号
// static void start_i2c(void)
// {
// 	SDA_SET;
// 	delay_us(TIME_UINT);
// 	SCL_SET;
// 	delay_us(TIME_UINT);
// 	SDA_RESET;
// 	delay_us(TIME_UINT);
// 	SCL_RESET;
// 	delay_us(TIME_UINT);
// }

// static void stop_i2c(void)
//  IIC停止信号
//{
//	SCL_SET;
//	delay_us(TIME_UINT);
//	SDA_RESET;
//	delay_us(TIME_UINT);
//	SDA_SET;
//	delay_us(TIME_UINT);
//	SDA_RESET;
//	SCL_RESET;
//}

// // 数据传输-传送一个字节, 先读高位
// static void send_byte(unsigned char dat)
// {
// 	unsigned char i;
// 	for (i = 0; i < 8; i++)
// 	{
// 		SCL_RESET;
// 		if (dat & 0x80)
// 		{
// 			SDA_SET;
// 		}
// 		else
// 		{
// 			SDA_RESET;
// 		}
// 		SCL_SET;
// 		dat = dat << 1;
// 	}
// 	SCL_RESET;
// 	delay_us(TIME_UINT);
// 	SDA_RESET; // ACK信号
// 	delay_us(TIME_UINT);
// 	SCL_SET;
// 	delay_us(TIME_UINT);
// 	delay_us(TIME_UINT);
// 	SCL_RESET;
// 	delay_us(TIME_UINT);
// }

static void writeCMD(u16 cmd)
{
    // start_i2c();
    // send_byte(cmd >> 8);
    // send_byte(cmd & 0xff);
    // wait_ack_i2c();

    iic_master_tx(cmd >> 8, 1);
    iic_master_tx(cmd & 0xFF, 2);
}

// /// @brief 显示数据更新
// /// @param drv

u8 test_i = 0;
u8 temp = 0;
void aip650e_display_update(struct _650e_drv_ *drv)
{
    temp = 1;
    // 温度显示
    switch (temp)
    {
    case 0:
        // 温度显示---
        drv->_buf[0] = (drv->_buf[0] & ~0x7f) | leddata[11]; // -
        drv->_buf[1] = (drv->_buf[1] & ~0x7f) | leddata[11];
        drv->_buf[2] = (drv->_buf[2] & ~0x7f) | leddata[11];
        break;
    case 1:
        // 温度显示60
        drv->_buf[0] = (drv->_buf[0] & ~0x7f) | leddata[10]; // null
        drv->_buf[1] = (drv->_buf[1] & ~0x7f) | leddata[6];
        drv->_buf[2] = (drv->_buf[2] & ~0x7f) | leddata[0];
        break;
    case 2:
        // 温度显示90
        drv->_buf[0] = (drv->_buf[0] & ~0x7f) | leddata[10]; // null
        drv->_buf[1] = (drv->_buf[1] & ~0x7f) | leddata[9];
        drv->_buf[2] = (drv->_buf[2] & ~0x7f) | leddata[0];
        break;
    case 3:
        // 温度显示120
        drv->_buf[0] = (drv->_buf[0] & ~0x7f) | leddata[1];
        drv->_buf[1] = (drv->_buf[1] & ~0x7f) | leddata[2];
        drv->_buf[2] = (drv->_buf[2] & ~0x7f) | leddata[0];
        break;
    default:
        break;
    }

#ifdef AIP650_TEST_MODE
    drv->_buf[0] = (drv->_buf[0] & ~0x7f) | leddata[test_i];
    drv->_buf[1] = (drv->_buf[1] & ~0x7f) | leddata[test_i];
    drv->_buf[2] = (drv->_buf[2] & ~0x7f) | leddata[test_i];

    test_i++;
    if (test_i > 9)
        test_i = 0;
#endif
}

/// @brief 刷新屏显
/// @param drv
void aip650e_update(struct _650e_drv_ *drv)
{
    writeCMD(SYS_CMD); // 开显示，8级显示(0x4801);睡眠使能。时钟停振(0x4804)

    writeCMD(0x6800 | drv->_buf[0]); // com0显示
    writeCMD(0x6A00 | drv->_buf[1]); // com1显示
    writeCMD(0x6C00 | drv->_buf[2]); // com2显示
    writeCMD(0x6E00 | drv->_buf[3]); // com3显示
}

#ifdef AIP650_TEST_MODE
static void test_display(u8 data1, u8 data2, u8 data3, u8 data4)
{
    writeCMD(SYS_CMD); // 开显示，8级显示(0x4801);睡眠使能。时钟停振(0x4804)

    writeCMD(0x6800 | data1); // com0 显示
    writeCMD(0x6A00 | data3); // com1显示
    writeCMD(0x6C00 | data2); // com2显示
    writeCMD(0x6E00 | data4); // com3显示
}

/// @brief 测试程序
/// @param
uint8 test_dat = 0x01;
void test_aip650e(void)
{
    test_display(test_dat,
                 test_dat,
                 test_dat,
                 test_dat);

    test_dat = test_dat << 1;

    if (test_dat == 0)
    {
        test_dat = 0x01;
    }
}
#endif

/**
 * @brief  IIC receive 1 byte data function
 * @param  ack_en: 0:Send NACK  1:Send ACK   2:Send stop
 * @retval Returns data
 */
// static u8 iic_master_rx(u8 flag)
// {
// #define NACK_FLAG (0)
// #define ACK_FLAG (1)
// #define STOP_FLAG (2)

//     u8 ack_flag = 0;
//     u8 iic_data = 0;

//     if (flag == ACK_FLAG)
//     {
//         // 接收完1byte数据发送ACK
//         I2C_CON |= I2C_ACK_NACK_BIT(0x1);
//         if (I2C_STA & I2C_SI_STA(0x1))
//         {
//             I2C_CON |= I2C_SI_CLEAR(0x1);
//         }
//     }

//     // 等待接收完成
//     while (!(I2C_STA & I2C_SI_STA(0x1)))
//         ;

//     if (flag == NACK_FLAG)
//     {
//         // 接收完1byte数据发送NACK
//         I2C_CON &= ~I2C_ACK_NACK_BIT(0x1);
//     }
//     if (flag == STOP_FLAG)
//     {
//         // 配置发送停止位
//         I2C_CON |= (I2C_STOP_BIT(0x1) | I2C_SI_CLEAR(0x1));
//     }

//     // 开发时此处的处理可注释掉
//     if ((I2C_STA & I2C_STA_FLAG(0x1F)) == 0x50)
//     {
//         // 成功发送 ACK
//         ack_flag = 1;
//     }
//     else if ((I2C_STA & I2C_STA_FLAG(0x1F)) == 0x58)
//     {
//         // 成功发送 NACK
//         ack_flag = 0;
//     }

//     return I2C_DATA;
// }