/*******************************************************************************
* File Name: COZIR_SPI_UART.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_COZIR_H)
#define CY_SCB_SPI_UART_COZIR_H

#include "COZIR.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define COZIR_SPI_MODE                   (0u)
#define COZIR_SPI_SUB_MODE               (0u)
#define COZIR_SPI_CLOCK_MODE             (0u)
#define COZIR_SPI_OVS_FACTOR             (16u)
#define COZIR_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define COZIR_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define COZIR_SPI_RX_DATA_BITS_NUM       (8u)
#define COZIR_SPI_TX_DATA_BITS_NUM       (8u)
#define COZIR_SPI_WAKE_ENABLE            (0u)
#define COZIR_SPI_BITS_ORDER             (1u)
#define COZIR_SPI_TRANSFER_SEPARATION    (1u)
#define COZIR_SPI_NUMBER_OF_SS_LINES     (1u)
#define COZIR_SPI_RX_BUFFER_SIZE         (8u)
#define COZIR_SPI_TX_BUFFER_SIZE         (8u)

#define COZIR_SPI_INTERRUPT_MODE         (0u)

#define COZIR_SPI_INTR_RX_MASK           (0u)
#define COZIR_SPI_INTR_TX_MASK           (0u)

#define COZIR_SPI_RX_TRIGGER_LEVEL       (7u)
#define COZIR_SPI_TX_TRIGGER_LEVEL       (0u)

#define COZIR_SPI_BYTE_MODE_ENABLE       (0u)
#define COZIR_SPI_FREE_RUN_SCLK_ENABLE   (0u)
#define COZIR_SPI_SS0_POLARITY           (0u)
#define COZIR_SPI_SS1_POLARITY           (0u)
#define COZIR_SPI_SS2_POLARITY           (0u)
#define COZIR_SPI_SS3_POLARITY           (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define COZIR_UART_SUB_MODE              (0u)
#define COZIR_UART_DIRECTION             (3u)
#define COZIR_UART_DATA_BITS_NUM         (8u)
#define COZIR_UART_PARITY_TYPE           (2u)
#define COZIR_UART_STOP_BITS_NUM         (2u)
#define COZIR_UART_OVS_FACTOR            (8u)
#define COZIR_UART_IRDA_LOW_POWER        (0u)
#define COZIR_UART_MEDIAN_FILTER_ENABLE  (0u)
#define COZIR_UART_RETRY_ON_NACK         (0u)
#define COZIR_UART_IRDA_POLARITY         (0u)
#define COZIR_UART_DROP_ON_FRAME_ERR     (0u)
#define COZIR_UART_DROP_ON_PARITY_ERR    (0u)
#define COZIR_UART_WAKE_ENABLE           (0u)
#define COZIR_UART_RX_BUFFER_SIZE        (16u)
#define COZIR_UART_TX_BUFFER_SIZE        (16u)
#define COZIR_UART_MP_MODE_ENABLE        (0u)
#define COZIR_UART_MP_ACCEPT_ADDRESS     (0u)
#define COZIR_UART_MP_RX_ADDRESS         (2u)
#define COZIR_UART_MP_RX_ADDRESS_MASK    (255u)

#define COZIR_UART_INTERRUPT_MODE        (0u)

#define COZIR_UART_INTR_RX_MASK          (0u)
#define COZIR_UART_INTR_TX_MASK          (0u)

#define COZIR_UART_RX_TRIGGER_LEVEL      (7u)
#define COZIR_UART_TX_TRIGGER_LEVEL      (0u)

#define COZIR_UART_BYTE_MODE_ENABLE      (1u)
#define COZIR_UART_CTS_ENABLE            (0u)
#define COZIR_UART_CTS_POLARITY          (0u)
#define COZIR_UART_RTS_POLARITY          (0u)
#define COZIR_UART_RTS_FIFO_LEVEL        (4u)

/* SPI mode enum */
#define COZIR_SPI_SLAVE  (0u)
#define COZIR_SPI_MASTER (1u)

/* UART direction enum */
#define COZIR_UART_RX    (1u)
#define COZIR_UART_TX    (2u)
#define COZIR_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(COZIR_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define COZIR_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define COZIR_RX_DIRECTION           (1u)
    #define COZIR_TX_DIRECTION           (1u)
    #define COZIR_UART_RX_DIRECTION      (1u)
    #define COZIR_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define COZIR_INTERNAL_RX_SW_BUFFER   (0u)
    #define COZIR_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define COZIR_RX_BUFFER_SIZE (COZIR_rxBufferSize)
    #define COZIR_TX_BUFFER_SIZE (COZIR_txBufferSize)

    /* Return true if buffer is provided */
    #define COZIR_CHECK_RX_SW_BUFFER (NULL != COZIR_rxBuffer)
    #define COZIR_CHECK_TX_SW_BUFFER (NULL != COZIR_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define COZIR_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define COZIR_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define COZIR_SPI_WAKE_ENABLE_CONST  (1u)
    #define COZIR_CHECK_SPI_WAKE_ENABLE  (0u != COZIR_scbEnableWake)
    #define COZIR_UART_WAKE_ENABLE_CONST (1u)

    /* SPI/UART: TX or RX FIFO size */
    #if (COZIR_CY_SCBIP_V0 || COZIR_CY_SCBIP_V1)
        #define COZIR_SPI_UART_FIFO_SIZE (COZIR_FIFO_SIZE)
    #else
        #define COZIR_SPI_UART_FIFO_SIZE (COZIR_GET_FIFO_SIZE(COZIR_CTRL_REG & \
                                                                                    COZIR_CTRL_BYTE_MODE))
    #endif /* (COZIR_CY_SCBIP_V0 || COZIR_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (COZIR_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define COZIR_SPI_RX_DIRECTION (1u)
        #define COZIR_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #if (COZIR_CY_SCBIP_V0 || COZIR_CY_SCBIP_V1)
            #define COZIR_SPI_UART_FIFO_SIZE    (COZIR_FIFO_SIZE)
        #else
            #define COZIR_SPI_UART_FIFO_SIZE \
                                           COZIR_GET_FIFO_SIZE(COZIR_SPI_BYTE_MODE_ENABLE)

        #endif /* (COZIR_CY_SCBIP_V0 || COZIR_CY_SCBIP_V1) */

        /* SPI internal RX and TX buffers */
        #define COZIR_INTERNAL_SPI_RX_SW_BUFFER  (COZIR_SPI_RX_BUFFER_SIZE > \
                                                                COZIR_SPI_UART_FIFO_SIZE)
        #define COZIR_INTERNAL_SPI_TX_SW_BUFFER  (COZIR_SPI_TX_BUFFER_SIZE > \
                                                                COZIR_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define COZIR_INTERNAL_RX_SW_BUFFER  (COZIR_INTERNAL_SPI_RX_SW_BUFFER)
        #define COZIR_INTERNAL_TX_SW_BUFFER  (COZIR_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define COZIR_RX_BUFFER_SIZE         (COZIR_SPI_RX_BUFFER_SIZE + 1u)
        #define COZIR_TX_BUFFER_SIZE         (COZIR_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define COZIR_SPI_WAKE_ENABLE_CONST  (0u != COZIR_SPI_WAKE_ENABLE)
        #define COZIR_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define COZIR_UART_RX_DIRECTION (0u != (COZIR_UART_DIRECTION & COZIR_UART_RX))
        #define COZIR_UART_TX_DIRECTION (0u != (COZIR_UART_DIRECTION & COZIR_UART_TX))

        /* Get FIFO size */
        #if (COZIR_CY_SCBIP_V0 || COZIR_CY_SCBIP_V1)
            #define COZIR_SPI_UART_FIFO_SIZE    (COZIR_FIFO_SIZE)
        #else
            #define COZIR_SPI_UART_FIFO_SIZE \
                                           COZIR_GET_FIFO_SIZE(COZIR_UART_BYTE_MODE_ENABLE)
        #endif /* (COZIR_CY_SCBIP_V0 || COZIR_CY_SCBIP_V1) */

        /* UART internal RX and TX buffers */
        #define COZIR_INTERNAL_UART_RX_SW_BUFFER  (COZIR_UART_RX_BUFFER_SIZE > \
                                                                COZIR_SPI_UART_FIFO_SIZE)
        #define COZIR_INTERNAL_UART_TX_SW_BUFFER  (COZIR_UART_TX_BUFFER_SIZE > \
                                                                    COZIR_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define COZIR_INTERNAL_RX_SW_BUFFER  (COZIR_INTERNAL_UART_RX_SW_BUFFER)
        #define COZIR_INTERNAL_TX_SW_BUFFER  (COZIR_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define COZIR_RX_BUFFER_SIZE         (COZIR_UART_RX_BUFFER_SIZE + 1u)
        #define COZIR_TX_BUFFER_SIZE         (COZIR_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define COZIR_SPI_WAKE_ENABLE_CONST  (0u)
        #define COZIR_UART_WAKE_ENABLE_CONST (0u != COZIR_UART_WAKE_ENABLE)

    #endif /* (COZIR_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define COZIR_SPI_MASTER_CONST   (COZIR_SPI_MODE == COZIR_SPI_MASTER)

    /* Direction */
    #define COZIR_RX_DIRECTION ((COZIR_SCB_MODE_SPI_CONST_CFG) ? \
                                            (COZIR_SPI_RX_DIRECTION) : (COZIR_UART_RX_DIRECTION))

    #define COZIR_TX_DIRECTION ((COZIR_SCB_MODE_SPI_CONST_CFG) ? \
                                            (COZIR_SPI_TX_DIRECTION) : (COZIR_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define COZIR_CHECK_RX_SW_BUFFER (COZIR_INTERNAL_RX_SW_BUFFER)
    #define COZIR_CHECK_TX_SW_BUFFER (COZIR_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define COZIR_INTERNAL_RX_SW_BUFFER_CONST    (COZIR_INTERNAL_RX_SW_BUFFER)
    #define COZIR_INTERNAL_TX_SW_BUFFER_CONST    (COZIR_INTERNAL_TX_SW_BUFFER)

    /* Wakeup for SPI */
    #define COZIR_CHECK_SPI_WAKE_ENABLE  (COZIR_SPI_WAKE_ENABLE_CONST)

#endif /* End (COZIR_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/* COZIR_SPI_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 submode;
    uint32 sclkMode;
    uint32 oversample;
    uint32 enableMedianFilter;
    uint32 enableLateSampling;
    uint32 enableWake;
    uint32 rxDataBits;
    uint32 txDataBits;
    uint32 bitOrder;
    uint32 transferSeperation;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableFreeRunSclk;
    uint8 polaritySs;
} COZIR_SPI_INIT_STRUCT;

/* COZIR_UART_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 direction;
    uint32 dataBits;
    uint32 parity;
    uint32 stopBits;
    uint32 oversample;
    uint32 enableIrdaLowPower;
    uint32 enableMedianFilter;
    uint32 enableRetryNack;
    uint32 enableInvertedRx;
    uint32 dropOnParityErr;
    uint32 dropOnFrameErr;
    uint32 enableWake;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableMultiproc;
    uint32 multiprocAcceptAddr;
    uint32 multiprocAddr;
    uint32 multiprocAddrMask;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableCts;
    uint8 ctsPolarity;
    uint8 rtsRxFifoLevel;
    uint8 rtsPolarity;
} COZIR_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(COZIR_SCB_MODE_UNCONFIG_CONST_CFG)
    void COZIR_SpiInit(const COZIR_SPI_INIT_STRUCT *config);
#endif /* (COZIR_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(COZIR_SCB_MODE_SPI_INC)
    #define COZIR_SpiIsBusBusy() ((uint32) (0u != (COZIR_SPI_STATUS_REG & \
                                                              COZIR_SPI_STATUS_BUS_BUSY)))

    #if (COZIR_SPI_MASTER_CONST)
        void COZIR_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(COZIR_SPI_MASTER_CONST) */

    #if !(COZIR_CY_SCBIP_V0 || COZIR_CY_SCBIP_V1)
        void COZIR_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(COZIR_CY_SCBIP_V0 || COZIR_CY_SCBIP_V1) */
#endif /* (COZIR_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(COZIR_SCB_MODE_UNCONFIG_CONST_CFG)
    void COZIR_UartInit(const COZIR_UART_INIT_STRUCT *config);
#endif /* (COZIR_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(COZIR_SCB_MODE_UART_INC)
    void COZIR_UartSetRxAddress(uint32 address);
    void COZIR_UartSetRxAddressMask(uint32 addressMask);

    /* UART RX direction APIs */
    #if(COZIR_UART_RX_DIRECTION)
        uint32 COZIR_UartGetChar(void);
        uint32 COZIR_UartGetByte(void);

        #if !(COZIR_CY_SCBIP_V0 || COZIR_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void COZIR_UartSetRtsPolarity(uint32 polarity);
            void COZIR_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(COZIR_CY_SCBIP_V0 || COZIR_CY_SCBIP_V1) */
    #endif /* (COZIR_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(COZIR_UART_TX_DIRECTION)
        #define COZIR_UartPutChar(ch)    COZIR_SpiUartWriteTxData((uint32)(ch))
        void COZIR_UartPutString(const char8 string[]);
        void COZIR_UartPutCRLF(uint32 txDataByte);

        #if !(COZIR_CY_SCBIP_V0 || COZIR_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void COZIR_UartEnableCts(void);
            void COZIR_UartDisableCts(void);
            void COZIR_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(COZIR_CY_SCBIP_V0 || COZIR_CY_SCBIP_V1) */
    #endif /* (COZIR_UART_TX_DIRECTION) */
#endif /* (COZIR_SCB_MODE_UART_INC) */

/* Common APIs RX direction */
#if(COZIR_RX_DIRECTION)
    uint32 COZIR_SpiUartReadRxData(void);
    uint32 COZIR_SpiUartGetRxBufferSize(void);
    void   COZIR_SpiUartClearRxBuffer(void);
#endif /* (COZIR_RX_DIRECTION) */

/* Common APIs TX direction */
#if(COZIR_TX_DIRECTION)
    void   COZIR_SpiUartWriteTxData(uint32 txData);
    void   COZIR_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    void   COZIR_SpiUartClearTxBuffer(void);
    uint32 COZIR_SpiUartGetTxBufferSize(void);
#endif /* (COZIR_TX_DIRECTION) */

CY_ISR_PROTO(COZIR_SPI_UART_ISR);

#if(COZIR_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(COZIR_UART_WAKEUP_ISR);
#endif /* (COZIR_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(COZIR_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   COZIR_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 COZIR_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   COZIR_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 COZIR_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(COZIR_INTERNAL_RX_SW_BUFFER_CONST)
        #define COZIR_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    COZIR_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define COZIR_GetWordFromRxBuffer(idx) COZIR_rxBufferInternal[(idx)]

    #endif /* (COZIR_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(COZIR_INTERNAL_TX_SW_BUFFER_CONST)
        #define COZIR_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        COZIR_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define COZIR_GetWordFromTxBuffer(idx) COZIR_txBufferInternal[(idx)]

    #endif /* (COZIR_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (COZIR_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define COZIR_SPI_MODE_MOTOROLA      (0x00u)
#define COZIR_SPI_MODE_TI_COINCIDES  (0x01u)
#define COZIR_SPI_MODE_TI_PRECEDES   (0x11u)
#define COZIR_SPI_MODE_NATIONAL      (0x02u)
#define COZIR_SPI_MODE_MASK          (0x03u)
#define COZIR_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define COZIR_SPI_MODE_NS_MICROWIRE  (COZIR_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define COZIR_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define COZIR_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define COZIR_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define COZIR_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define COZIR_BITS_ORDER_LSB_FIRST   (0u)
#define COZIR_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define COZIR_SPI_TRANSFER_SEPARATED     (0u)
#define COZIR_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define COZIR_SPI_SLAVE_SELECT0    (COZIR_SCB__SS0_POSISTION)
#define COZIR_SPI_SLAVE_SELECT1    (COZIR_SCB__SS1_POSISTION)
#define COZIR_SPI_SLAVE_SELECT2    (COZIR_SCB__SS2_POSISTION)
#define COZIR_SPI_SLAVE_SELECT3    (COZIR_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define COZIR_SPI_SS_ACTIVE_LOW  (0u)
#define COZIR_SPI_SS_ACTIVE_HIGH (1u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define COZIR_UART_MODE_STD          (0u)
#define COZIR_UART_MODE_SMARTCARD    (1u)
#define COZIR_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define COZIR_UART_RX    (1u)
#define COZIR_UART_TX    (2u)
#define COZIR_UART_TX_RX (3u)

/* UART parity enum */
#define COZIR_UART_PARITY_EVEN   (0u)
#define COZIR_UART_PARITY_ODD    (1u)
#define COZIR_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define COZIR_UART_STOP_BITS_1   (2u)
#define COZIR_UART_STOP_BITS_1_5 (3u)
#define COZIR_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define COZIR_UART_IRDA_LP_OVS16     (16u)
#define COZIR_UART_IRDA_LP_OVS32     (32u)
#define COZIR_UART_IRDA_LP_OVS48     (48u)
#define COZIR_UART_IRDA_LP_OVS96     (96u)
#define COZIR_UART_IRDA_LP_OVS192    (192u)
#define COZIR_UART_IRDA_LP_OVS768    (768u)
#define COZIR_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define COZIR_UART_MP_MARK       (0x100u)
#define COZIR_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define COZIR_UART_CTS_ACTIVE_LOW    (0u)
#define COZIR_UART_CTS_ACTIVE_HIGH   (1u)
#define COZIR_UART_RTS_ACTIVE_LOW    (0u)
#define COZIR_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define COZIR_INTR_RX_ERR        (COZIR_INTR_RX_OVERFLOW    | \
                                             COZIR_INTR_RX_UNDERFLOW   | \
                                             COZIR_INTR_RX_FRAME_ERROR | \
                                             COZIR_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for COZIR_UartGetByte() */
#define COZIR_UART_RX_OVERFLOW       (COZIR_INTR_RX_OVERFLOW << 8u)
#define COZIR_UART_RX_UNDERFLOW      (COZIR_INTR_RX_UNDERFLOW << 8u)
#define COZIR_UART_RX_FRAME_ERROR    (COZIR_INTR_RX_FRAME_ERROR << 8u)
#define COZIR_UART_RX_PARITY_ERROR   (COZIR_INTR_RX_PARITY_ERROR << 8u)
#define COZIR_UART_RX_ERROR_MASK     (COZIR_UART_RX_OVERFLOW    | \
                                                 COZIR_UART_RX_UNDERFLOW   | \
                                                 COZIR_UART_RX_FRAME_ERROR | \
                                                 COZIR_UART_RX_PARITY_ERROR)


/***************************************
*     Vars with External Linkage
***************************************/

#if(COZIR_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const COZIR_SPI_INIT_STRUCT  COZIR_configSpi;
    extern const COZIR_UART_INIT_STRUCT COZIR_configUart;
#endif /* (COZIR_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define COZIR_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & COZIR_INTR_SLAVE_SPI_BUS_ERROR)
#define COZIR_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & COZIR_INTR_MASTER_SPI_DONE)
#define COZIR_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~COZIR_INTR_SLAVE_SPI_BUS_ERROR)

#define COZIR_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~COZIR_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define COZIR_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((COZIR_UART_IRDA_LP_OVS16   == (oversample)) ? COZIR_CTRL_OVS_IRDA_LP_OVS16 : \
         ((COZIR_UART_IRDA_LP_OVS32   == (oversample)) ? COZIR_CTRL_OVS_IRDA_LP_OVS32 : \
          ((COZIR_UART_IRDA_LP_OVS48   == (oversample)) ? COZIR_CTRL_OVS_IRDA_LP_OVS48 : \
           ((COZIR_UART_IRDA_LP_OVS96   == (oversample)) ? COZIR_CTRL_OVS_IRDA_LP_OVS96 : \
            ((COZIR_UART_IRDA_LP_OVS192  == (oversample)) ? COZIR_CTRL_OVS_IRDA_LP_OVS192 : \
             ((COZIR_UART_IRDA_LP_OVS768  == (oversample)) ? COZIR_CTRL_OVS_IRDA_LP_OVS768 : \
              ((COZIR_UART_IRDA_LP_OVS1536 == (oversample)) ? COZIR_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          COZIR_CTRL_OVS_IRDA_LP_OVS16)))))))

#define COZIR_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (COZIR_UART_RX & (direction))) ? \
                                                                     (COZIR_RX_CTRL_ENABLED) : (0u))

#define COZIR_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (COZIR_UART_TX & (direction))) ? \
                                                                     (COZIR_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define COZIR_CTRL_SPI      (COZIR_CTRL_MODE_SPI)
#define COZIR_SPI_RX_CTRL   (COZIR_RX_CTRL_ENABLED)
#define COZIR_SPI_TX_CTRL   (COZIR_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define COZIR_SPI_SS_POLARITY \
             (((uint32) COZIR_SPI_SS0_POLARITY << COZIR_SPI_SLAVE_SELECT0) | \
              ((uint32) COZIR_SPI_SS1_POLARITY << COZIR_SPI_SLAVE_SELECT1) | \
              ((uint32) COZIR_SPI_SS2_POLARITY << COZIR_SPI_SLAVE_SELECT2) | \
              ((uint32) COZIR_SPI_SS3_POLARITY << COZIR_SPI_SLAVE_SELECT3))

#if(COZIR_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define COZIR_SPI_DEFAULT_CTRL \
                    (COZIR_GET_CTRL_OVS(COZIR_SPI_OVS_FACTOR) | \
                     COZIR_GET_CTRL_BYTE_MODE (COZIR_SPI_BYTE_MODE_ENABLE) | \
                     COZIR_GET_CTRL_EC_AM_MODE(COZIR_SPI_WAKE_ENABLE)      | \
                     COZIR_CTRL_SPI)

    #define COZIR_SPI_DEFAULT_SPI_CTRL \
                    (COZIR_GET_SPI_CTRL_CONTINUOUS    (COZIR_SPI_TRANSFER_SEPARATION)       | \
                     COZIR_GET_SPI_CTRL_SELECT_PRECEDE(COZIR_SPI_SUB_MODE &                   \
                                                                  COZIR_SPI_MODE_TI_PRECEDES_MASK)     | \
                     COZIR_GET_SPI_CTRL_SCLK_MODE     (COZIR_SPI_CLOCK_MODE)                | \
                     COZIR_GET_SPI_CTRL_LATE_MISO_SAMPLE(COZIR_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     COZIR_GET_SPI_CTRL_SCLK_CONTINUOUS(COZIR_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     COZIR_GET_SPI_CTRL_SSEL_POLARITY (COZIR_SPI_SS_POLARITY)               | \
                     COZIR_GET_SPI_CTRL_SUB_MODE      (COZIR_SPI_SUB_MODE)                  | \
                     COZIR_GET_SPI_CTRL_MASTER_MODE   (COZIR_SPI_MODE))

    /* RX direction */
    #define COZIR_SPI_DEFAULT_RX_CTRL \
                    (COZIR_GET_RX_CTRL_DATA_WIDTH(COZIR_SPI_RX_DATA_BITS_NUM)     | \
                     COZIR_GET_RX_CTRL_BIT_ORDER (COZIR_SPI_BITS_ORDER)           | \
                     COZIR_GET_RX_CTRL_MEDIAN    (COZIR_SPI_MEDIAN_FILTER_ENABLE) | \
                     COZIR_SPI_RX_CTRL)

    #define COZIR_SPI_DEFAULT_RX_FIFO_CTRL \
                    COZIR_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(COZIR_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define COZIR_SPI_DEFAULT_TX_CTRL \
                    (COZIR_GET_TX_CTRL_DATA_WIDTH(COZIR_SPI_TX_DATA_BITS_NUM) | \
                     COZIR_GET_TX_CTRL_BIT_ORDER (COZIR_SPI_BITS_ORDER)       | \
                     COZIR_SPI_TX_CTRL)

    #define COZIR_SPI_DEFAULT_TX_FIFO_CTRL \
                    COZIR_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(COZIR_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define COZIR_SPI_DEFAULT_INTR_SPI_EC_MASK   (COZIR_NO_INTR_SOURCES)

    #define COZIR_SPI_DEFAULT_INTR_I2C_EC_MASK   (COZIR_NO_INTR_SOURCES)
    #define COZIR_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (COZIR_SPI_INTR_RX_MASK & COZIR_INTR_SLAVE_SPI_BUS_ERROR)

    #define COZIR_SPI_DEFAULT_INTR_MASTER_MASK \
                    (COZIR_SPI_INTR_TX_MASK & COZIR_INTR_MASTER_SPI_DONE)

    #define COZIR_SPI_DEFAULT_INTR_RX_MASK \
                    (COZIR_SPI_INTR_RX_MASK & (uint32) ~COZIR_INTR_SLAVE_SPI_BUS_ERROR)

    #define COZIR_SPI_DEFAULT_INTR_TX_MASK \
                    (COZIR_SPI_INTR_TX_MASK & (uint32) ~COZIR_INTR_MASTER_SPI_DONE)

#endif /* (COZIR_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define COZIR_CTRL_UART      (COZIR_CTRL_MODE_UART)
#define COZIR_UART_RX_CTRL   (COZIR_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define COZIR_UART_TX_CTRL   (COZIR_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(COZIR_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(COZIR_UART_MODE_IRDA == COZIR_UART_SUB_MODE)

        #define COZIR_DEFAULT_CTRL_OVS   ((0u != COZIR_UART_IRDA_LOW_POWER) ?              \
                                (COZIR_UART_GET_CTRL_OVS_IRDA_LP(COZIR_UART_OVS_FACTOR)) : \
                                (COZIR_CTRL_OVS_IRDA_OVS16))

    #else

        #define COZIR_DEFAULT_CTRL_OVS   COZIR_GET_CTRL_OVS(COZIR_UART_OVS_FACTOR)

    #endif /* (COZIR_UART_MODE_IRDA == COZIR_UART_SUB_MODE) */

    #define COZIR_UART_DEFAULT_CTRL \
                                (COZIR_GET_CTRL_BYTE_MODE  (COZIR_UART_BYTE_MODE_ENABLE)  | \
                                 COZIR_GET_CTRL_ADDR_ACCEPT(COZIR_UART_MP_ACCEPT_ADDRESS) | \
                                 COZIR_DEFAULT_CTRL_OVS                                              | \
                                 COZIR_CTRL_UART)

    #define COZIR_UART_DEFAULT_UART_CTRL \
                                    (COZIR_GET_UART_CTRL_MODE(COZIR_UART_SUB_MODE))

    /* RX direction */
    #define COZIR_UART_DEFAULT_RX_CTRL_PARITY \
                                ((COZIR_UART_PARITY_NONE != COZIR_UART_PARITY_TYPE) ?      \
                                  (COZIR_GET_UART_RX_CTRL_PARITY(COZIR_UART_PARITY_TYPE) | \
                                   COZIR_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define COZIR_UART_DEFAULT_UART_RX_CTRL \
                    (COZIR_GET_UART_RX_CTRL_MODE(COZIR_UART_STOP_BITS_NUM)                    | \
                     COZIR_GET_UART_RX_CTRL_POLARITY(COZIR_UART_IRDA_POLARITY)                | \
                     COZIR_GET_UART_RX_CTRL_MP_MODE(COZIR_UART_MP_MODE_ENABLE)                | \
                     COZIR_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(COZIR_UART_DROP_ON_PARITY_ERR) | \
                     COZIR_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(COZIR_UART_DROP_ON_FRAME_ERR)   | \
                     COZIR_UART_DEFAULT_RX_CTRL_PARITY)

    #define COZIR_UART_DEFAULT_RX_CTRL \
                                (COZIR_GET_RX_CTRL_DATA_WIDTH(COZIR_UART_DATA_BITS_NUM)        | \
                                 COZIR_GET_RX_CTRL_MEDIAN    (COZIR_UART_MEDIAN_FILTER_ENABLE) | \
                                 COZIR_GET_UART_RX_CTRL_ENABLED(COZIR_UART_DIRECTION))

    #define COZIR_UART_DEFAULT_RX_FIFO_CTRL \
                                COZIR_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(COZIR_UART_RX_TRIGGER_LEVEL)

    #define COZIR_UART_DEFAULT_RX_MATCH_REG  ((0u != COZIR_UART_MP_MODE_ENABLE) ?          \
                                (COZIR_GET_RX_MATCH_ADDR(COZIR_UART_MP_RX_ADDRESS) | \
                                 COZIR_GET_RX_MATCH_MASK(COZIR_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define COZIR_UART_DEFAULT_TX_CTRL_PARITY (COZIR_UART_DEFAULT_RX_CTRL_PARITY)

    #define COZIR_UART_DEFAULT_UART_TX_CTRL \
                                (COZIR_GET_UART_TX_CTRL_MODE(COZIR_UART_STOP_BITS_NUM)       | \
                                 COZIR_GET_UART_TX_CTRL_RETRY_NACK(COZIR_UART_RETRY_ON_NACK) | \
                                 COZIR_UART_DEFAULT_TX_CTRL_PARITY)

    #define COZIR_UART_DEFAULT_TX_CTRL \
                                (COZIR_GET_TX_CTRL_DATA_WIDTH(COZIR_UART_DATA_BITS_NUM) | \
                                 COZIR_GET_UART_TX_CTRL_ENABLED(COZIR_UART_DIRECTION))

    #define COZIR_UART_DEFAULT_TX_FIFO_CTRL \
                                COZIR_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(COZIR_UART_TX_TRIGGER_LEVEL)

    #define COZIR_UART_DEFAULT_FLOW_CTRL \
                        (COZIR_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(COZIR_UART_RTS_FIFO_LEVEL) | \
                         COZIR_GET_UART_FLOW_CTRL_RTS_POLARITY (COZIR_UART_RTS_POLARITY)   | \
                         COZIR_GET_UART_FLOW_CTRL_CTS_POLARITY (COZIR_UART_CTS_POLARITY)   | \
                         COZIR_GET_UART_FLOW_CTRL_CTS_ENABLE   (COZIR_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define COZIR_UART_DEFAULT_INTR_I2C_EC_MASK  (COZIR_NO_INTR_SOURCES)
    #define COZIR_UART_DEFAULT_INTR_SPI_EC_MASK  (COZIR_NO_INTR_SOURCES)
    #define COZIR_UART_DEFAULT_INTR_SLAVE_MASK   (COZIR_NO_INTR_SOURCES)
    #define COZIR_UART_DEFAULT_INTR_MASTER_MASK  (COZIR_NO_INTR_SOURCES)
    #define COZIR_UART_DEFAULT_INTR_RX_MASK      (COZIR_UART_INTR_RX_MASK)
    #define COZIR_UART_DEFAULT_INTR_TX_MASK      (COZIR_UART_INTR_TX_MASK)

#endif /* (COZIR_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define COZIR_SPIM_ACTIVE_SS0    (COZIR_SPI_SLAVE_SELECT0)
#define COZIR_SPIM_ACTIVE_SS1    (COZIR_SPI_SLAVE_SELECT1)
#define COZIR_SPIM_ACTIVE_SS2    (COZIR_SPI_SLAVE_SELECT2)
#define COZIR_SPIM_ACTIVE_SS3    (COZIR_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_COZIR_H */


/* [] END OF FILE */
