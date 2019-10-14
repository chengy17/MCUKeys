#ifndef _KEY__H
#define _KEY__H

/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "stm8s.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

//ʹ��״̬��ģʽ
#define USE_KEY_STATE_MACHINE

//KEY1 ����
#define KEY1_GPIO_PORT	(GPIOC)
#define KEY1_GPIO_PINS	(GPIO_PIN_4)

#define KEY2_GPIO_PORT	(GPIOC)
#define KEY2_GPIO_PINS	(GPIO_PIN_3)

#define KEY3_GPIO_PORT	(GPIOA)
#define KEY3_GPIO_PINS	(GPIO_PIN_1)

#define KEY4_GPIO_PORT	(GPIOA)
#define KEY4_GPIO_PINS	(GPIO_PIN_2)



#define KEY_TICKS         5     /* ����ѭ��ɨ������(ms) keyscan()�������ĸ��̶�ɨ�������� ��ֵ�͵��ڶ��� ԭ����Ӧ����10�Ĺ�Լ���е�ֵ ��Ϊ����������10ms*/

#define LIFT    (0)            /* ����̧�� */
#define PRESS   (1)         /* �������� */
#define KEY_COUNT    	4	   					/* �������� */
#define KEY_STATUS      4                   /* ֧�ֵİ����¼�   Ŀǰ֧��4�� �������¡�̧��˫��������*/

#define KEY_FILTER_TIME          10               // ��������ʱ�� 10ms
#define KEY_LONG_TIME           2000			// ����ʱ�� 2s
#define KEY_REPEAT_TIME       200         // �������200ms
#define KEY_DOUBLE_MIN        100         // ˫��������С��� 100ms
#define KEY_DOUBLE_MAX       300        // ˫����������� 300ms


#define KEY_FIFO_SIZE	50                     //����FIFO�����С

//�ϱ��¼���־
#define KEY_REPORT_DOWN     (1<<0)  //�ϱ����������¼�
#define KEY_REPORT_UP       (1<<1)  //�ϱ�����̧���¼�
#define KEY_REPORT_LONG     (1<<2)   //�ϱ������¼�
#define KEY_REPORT_DOUBLE   (1<<3)  //�ϱ�˫���¼�
#define KEY_REPORT_REPEAT   (1<<4)  //�ϱ������¼�

//���尴���¼�
typedef enum _e_keys_status
{
    KEY_NONE = 0,			    /* 0 ��ʾ�ް����¼� */

    KEY_1_DOWN,				/* 1������ */
    KEY_1_UP,				        /* 1������ */
    KEY_1_LONG,				    /* 1������ */
    KEY_1_DOUBLE,             /* 1��˫��*/

    KEY_2_DOWN,				/* 2������ */
    KEY_2_UP,				        /* 2������ */
    KEY_2_LONG,			    	/* 2������ */
    KEY_2_DOUBLE,             /* 2��˫��*/

    KEY_3_DOWN,				/* 3������ */
    KEY_3_UP,				        /* 3������ */
    KEY_3_LONG,				    /* 3������ */
    KEY_3_DOUBLE,             /* 3��˫��*/

    KEY_4_DOWN,				/* 4������ */
    KEY_4_UP,				        /* 4������ */
    KEY_4_LONG,				    /* 4������ */
    KEY_4_DOUBLE,             /* 4��˫��*/

    KEY_5_DOWN,				/* 5������ */
    KEY_5_UP,				        /* 5������ */
    KEY_5_LONG,				    /* 5������ */
    KEY_5_DOUBLE,             /* 5��˫��*/

    KEY_6_DOWN,				/* 6������ */
    KEY_6_UP,				        /* 6������ */
    KEY_6_LONG,				    /* 6������ */
    KEY_6_DOUBLE,             /* 6��˫��*/

    KEY_7_DOWN,				/* 7������ */
    KEY_7_UP,				        /* 7������ */
    KEY_7_LONG,				    /* 7������ */
    KEY_7_DOUBLE,             /* 7��˫��*/

    KEY_8_DOWN,				/* 8������ */
    KEY_8_UP,				        /* 8������ */
    KEY_8_LONG,				    /* 8������ */
    KEY_8_DOUBLE,             /* 8��˫��*/

    KEY_9_DOWN,				 /* 9������ */
    KEY_9_UP,				         /* 9������ */
    KEY_9_LONG,				    /* 9������ */
    KEY_9_DOUBLE,             /* 9��˫��*/

    KEY_10_DOWN,			/* 10������ */
    KEY_10_UP,				/* 10������ */
    KEY_10_LONG,			/* 10������ */
    KEY_10_DOUBLE,             /* 10��˫��*/
} e_keys_status;

/* ����ID ֻ��ע���˰���ID �ſ��Բ�������*/
typedef enum _e_keys_id
{
    KEY1_ID = 0,
    // ��������ID����
	KEY2_ID,
	KEY3_ID,
	KEY4_ID,
    KEY_ID_MAX,
} e_keys_id;

#ifdef USE_KEY_STATE_MACHINE
//����״̬��
typedef enum _e_key_state
{
    KEY_NULL,   //�ް�������
    KEY_DOWN,
    KEY_DOWN_RECHECK,
    KEY_UP,
    KEY_UP_RECHECK,
    KEY_LONG,
    KEY_REPEAT,
    
}e_key_state;

#endif

//Ӳ��������
struct _keys_hw_desc_t
{
	GPIO_TypeDef* GPIOx;
	GPIO_Pin_TypeDef GPIO_Pin;
	GPIO_Mode_TypeDef GPIO_Mode;
};

//�����ṹ��
typedef struct _t_keys
{
    /* ����ָ��*/
    uint8_t (*get_key_status)(e_keys_id key_id);    /* �������µ��жϺ���,1��ʾ���� */
    void (*short_key_down)(void * skd_arg);     //�����̰��»ص�����
    void * skd_arg;                                           //�����̰��»ص���������Ĳ���
    void(*short_key_up)(void * sku_arg);          //�����̰�̧��ص�����
    void * sku_arg;                                           //�����̰��»ص���������Ĳ���
    void (*long_key_down)(void *lkd_arg);       //�����¼��ص�����
    void *lkd_arg;                                            //�����¼��ص���������
    void (*double_key_down)(void *dkd_arg);  //˫�����»ص�����
    void * dkd_arg;                                          //˫���¼��ص���������
    void (*repeat_key_down)(void *rkd_arg);    //�����¼��ص�
    void *rkd_arg;                                            //�����¼��ص���������

    uint8_t  count;			    /* �˲��������� */
    uint16_t long_count;		/* ���������� */
    uint16_t long_time;		/* �������³���ʱ��, 0��ʾ����ⳤ�� */
    uint8_t  state;			    /* ������ǰ״̬�����»��ǵ��� */
    uint8_t  repeat_speed;	/* ������������ */
    uint8_t  repeat_count;	/* �������������� */

    uint16_t double_count;   /* ˫��������*/
    uint8_t report_flag;       /* �ϱ��¼���־*/
#ifdef USE_KEY_STATE_MACHINE	
    e_key_state key_state ; /* ����״̬��*/
    uint8_t prev_key_state; /* ��һ�ΰ�����״̬ */
#endif
} t_keys;

extern t_keys keys[KEY_ID_MAX];

/* ����FIFO�õ����� */
typedef struct _t_keys_fifo
{
    e_keys_status fifo_buffer[KEY_FIFO_SIZE];		/* ��ֵ������ */
    uint8_t read;					                            /* ��������ָ��1 */
    uint8_t write;					                            /* ������дָ�� */

} t_keys_fifo;





/***********************************************************************
* �������ƣ� key_scan
* �������ܣ� ����ɨ��
* ��������� ��
* �� ��  ֵ��  ��
* ����˵����  Ӧ�÷���һ��1ms�����ں�����
****************************************************************************/
void key_scan(void);

/***********************************************************************
* �������ƣ� keys_init
* �������ܣ� ����ģ���ʼ��
* ���������  ��
* �� ��  ֵ�� ��
* ����˵���� ϵͳ��ʼ��ʱӦ�����ô˺���
****************************************************************************/
void keys_init(void);


/***********************************************************************
* �������ƣ� key_out_fifo
* �������ܣ� �Ӱ���FIFO��ȡ��һ�������¼�
* ���������  ��
* �� ��  ֵ��  ��ǰFIFO�л���İ����¼�
* ����˵������
****************************************************************************/
e_keys_status key_out_fifo(void);


#endif


