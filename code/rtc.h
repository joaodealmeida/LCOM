#ifndef _RTC__H
#define _RTC__H

#define RTC_ADDR_REG        0x70
#define RTC_DATA_REG        0x71
#define RTC_SECONDS         0x0
#define RTC_SECONDS_ALARM   0x1
#define RTC_MINUTES         0x2
#define RTC_MINUTES_ALARM   0x3
#define RTC_HOURS           0x4
#define RTC_HOURS_ALARM     0x5
#define RTC_DAY_OF_WEEK     0x6
#define RTC_DAY_OF_MONTH    0x7
#define RTC_MONTH           0x8
#define RTC_YEAR            0x9
#define RTC_REG_A           0xA
#define RTC_REG_B           0xB
#define RTC_REG_C           0xC
#define RTC_REG_D           0xD
/* RTC_REG_A BITS */
#define RTC_RS0_BIT         0
#define RTC_RS1_BIT         1
#define RTC_RS2_BIT         2
#define RTC_RS3_BIT         3
#define RTC_DV0_BIT         4
#define RTC_DV1_BIT         5
#define RTC_DV2_BIT         6
#define RTC_UIP_BIT         7
/* RTC_REG_B BITS */
#define RTC_DSE_BIT         0
#define RTC_MODE_BIT        1
#define RTC_DM_BIT          2
#define RTC_SQWE_BIT        3
#define RTC_UIE_BIT         4
#define RTC_AIE_BIT         5
#define RTC_PIE_BIT         6
#define RTC_SET_BIT         7
/* RTC_REG_C BITS */
#define RTC_UF_BIT          4
#define RTC_AF_BIT          5
#define RTC_PF_BIT          6
#define RTC_IRQF_BIT        7
/* RTC_REG_D BITS */
#define RTC_VRT_BIT         7
#define RTC_IRQ             0x8

//int rtc_test_conf(void);
unsigned int rtc_generate_seed(void);


#endif
