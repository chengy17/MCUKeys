#ifndef _KEY__H
#define _KEY__H

/* 包含头文件 ----------------------------------------------------------------*/
#include "stm8s.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

//使用状态机模式
#define USE_KEY_STATE_MACHINE

//KEY1 配置
#define KEY1_GPIO_PORT	(GPIOC)
#define KEY1_GPIO_PINS	(GPIO_PIN_4)

#define KEY2_GPIO_PORT	(GPIOC)
#define KEY2_GPIO_PINS	(GPIO_PIN_3)

#define KEY3_GPIO_PORT	(GPIOA)
#define KEY3_GPIO_PINS	(GPIO_PIN_1)

#define KEY4_GPIO_PORT	(GPIOA)
#define KEY4_GPIO_PINS	(GPIO_PIN_2)



#define KEY_TICKS         5     /* 按键循环扫描周期(ms) keyscan()函数在哪个固定扫描周期中 该值就等于多少 原则上应该是10的公约数中的值 因为按键消抖是10ms*/

#define LIFT    (0)            /* 按键抬起 */
#define PRESS   (1)         /* 按键按下 */
#define KEY_COUNT    	4	   					/* 按键个数 */
#define KEY_STATUS      4                   /* 支持的按键事件   目前支持4种 按键按下、抬起、双击、长按*/

#define KEY_FILTER_TIME          10               // 按键消抖时间 10ms
#define KEY_LONG_TIME           2000			// 长按时间 2s
#define KEY_REPEAT_TIME       200         // 连发间隔200ms
#define KEY_DOUBLE_MIN        100         // 双击按键最小间隔 100ms
#define KEY_DOUBLE_MAX       300        // 双击按键最大间隔 300ms


#define KEY_FIFO_SIZE	50                     //按键FIFO缓冲大小

//上报事件标志
#define KEY_REPORT_DOWN     (1<<0)  //上报按键按下事件
#define KEY_REPORT_UP       (1<<1)  //上报按键抬起事件
#define KEY_REPORT_LONG     (1<<2)   //上报长按事件
#define KEY_REPORT_DOUBLE   (1<<3)  //上报双击事件
#define KEY_REPORT_REPEAT   (1<<4)  //上报连发事件

//定义按键事件
typedef enum _e_keys_status
{
    KEY_NONE = 0,			    /* 0 表示无按键事件 */

    KEY_1_DOWN,				/* 1键按下 */
    KEY_1_UP,				        /* 1键弹起 */
    KEY_1_LONG,				    /* 1键长按 */
    KEY_1_DOUBLE,             /* 1键双击*/

    KEY_2_DOWN,				/* 2键按下 */
    KEY_2_UP,				        /* 2键弹起 */
    KEY_2_LONG,			    	/* 2键长按 */
    KEY_2_DOUBLE,             /* 2键双击*/

    KEY_3_DOWN,				/* 3键按下 */
    KEY_3_UP,				        /* 3键弹起 */
    KEY_3_LONG,				    /* 3键长按 */
    KEY_3_DOUBLE,             /* 3键双击*/

    KEY_4_DOWN,				/* 4键按下 */
    KEY_4_UP,				        /* 4键弹起 */
    KEY_4_LONG,				    /* 4键长按 */
    KEY_4_DOUBLE,             /* 4键双击*/

    KEY_5_DOWN,				/* 5键按下 */
    KEY_5_UP,				        /* 5键弹起 */
    KEY_5_LONG,				    /* 5键长按 */
    KEY_5_DOUBLE,             /* 5键双击*/

    KEY_6_DOWN,				/* 6键按下 */
    KEY_6_UP,				        /* 6键弹起 */
    KEY_6_LONG,				    /* 6键长按 */
    KEY_6_DOUBLE,             /* 6键双击*/

    KEY_7_DOWN,				/* 7键按下 */
    KEY_7_UP,				        /* 7键弹起 */
    KEY_7_LONG,				    /* 7键长按 */
    KEY_7_DOUBLE,             /* 7键双击*/

    KEY_8_DOWN,				/* 8键按下 */
    KEY_8_UP,				        /* 8键弹起 */
    KEY_8_LONG,				    /* 8键长按 */
    KEY_8_DOUBLE,             /* 8键双击*/

    KEY_9_DOWN,				 /* 9键按下 */
    KEY_9_UP,				         /* 9键弹起 */
    KEY_9_LONG,				    /* 9键长按 */
    KEY_9_DOUBLE,             /* 9键双击*/

    KEY_10_DOWN,			/* 10键按下 */
    KEY_10_UP,				/* 10键弹起 */
    KEY_10_LONG,			/* 10键长按 */
    KEY_10_DOUBLE,             /* 10键双击*/
} e_keys_status;

/* 按键ID 只有注册了按键ID 才可以操作按键*/
typedef enum _e_keys_id
{
    KEY1_ID = 0,
    // 其他按键ID定义
	KEY2_ID,
	KEY3_ID,
	KEY4_ID,
    KEY_ID_MAX,
} e_keys_id;

#ifdef USE_KEY_STATE_MACHINE
//按键状态机
typedef enum _e_key_state
{
    KEY_NULL,   //无按键按下
    KEY_DOWN,
    KEY_DOWN_RECHECK,
    KEY_UP,
    KEY_UP_RECHECK,
    KEY_LONG,
    KEY_REPEAT,
    
}e_key_state;

#endif

//硬件描述符
struct _keys_hw_desc_t
{
	GPIO_TypeDef* GPIOx;
	GPIO_Pin_TypeDef GPIO_Pin;
	GPIO_Mode_TypeDef GPIO_Mode;
};

//按键结构体
typedef struct _t_keys
{
    /* 函数指针*/
    uint8_t (*get_key_status)(e_keys_id key_id);    /* 按键按下的判断函数,1表示按下 */
    void (*short_key_down)(void * skd_arg);     //按键短按下回调函数
    void * skd_arg;                                           //按键短按下回调函数传入的参数
    void(*short_key_up)(void * sku_arg);          //按键短按抬起回调函数
    void * sku_arg;                                           //按键短按下回调函数传入的参数
    void (*long_key_down)(void *lkd_arg);       //长按事件回调函数
    void *lkd_arg;                                            //长按事件回调函数参数
    void (*double_key_down)(void *dkd_arg);  //双击按下回调函数
    void * dkd_arg;                                          //双击事件回调函数参数
    void (*repeat_key_down)(void *rkd_arg);    //连发事件回调
    void *rkd_arg;                                            //连发事件回调函数参数

    uint8_t  count;			    /* 滤波器计数器 */
    uint16_t long_count;		/* 长按计数器 */
    uint16_t long_time;		/* 按键按下持续时间, 0表示不检测长按 */
    uint8_t  state;			    /* 按键当前状态（按下还是弹起） */
    uint8_t  repeat_speed;	/* 连续按键周期 */
    uint8_t  repeat_count;	/* 连续按键计数器 */

    uint16_t double_count;   /* 双击计数器*/
    uint8_t report_flag;       /* 上报事件标志*/
#ifdef USE_KEY_STATE_MACHINE	
    e_key_state key_state ; /* 按键状态机*/
    uint8_t prev_key_state; /* 上一次按键的状态 */
#endif
} t_keys;

extern t_keys keys[KEY_ID_MAX];

/* 按键FIFO用到变量 */
typedef struct _t_keys_fifo
{
    e_keys_status fifo_buffer[KEY_FIFO_SIZE];		/* 键值缓冲区 */
    uint8_t read;					                            /* 缓冲区读指针1 */
    uint8_t write;					                            /* 缓冲区写指针 */

} t_keys_fifo;





/***********************************************************************
* 函数名称： key_scan
* 函数功能： 按键扫描
* 输入参数： 无
* 返 回  值：  无
* 函数说明：  应该放在一个1ms的周期函数中
****************************************************************************/
void key_scan(void);

/***********************************************************************
* 函数名称： keys_init
* 函数功能： 按键模块初始化
* 输入参数：  无
* 返 回  值： 无
* 函数说明： 系统初始化时应当调用此函数
****************************************************************************/
void keys_init(void);


/***********************************************************************
* 函数名称： key_out_fifo
* 函数功能： 从按键FIFO中取出一个按键事件
* 输入参数：  无
* 返 回  值：  当前FIFO中缓冲的按键事件
* 函数说明：无
****************************************************************************/
e_keys_status key_out_fifo(void);


#endif


