/*******************************************************************************
* File Name: COZIR_UART.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "COZIR_PVT.h"
#include "COZIR_SPI_UART_PVT.h"


#if(COZIR_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const COZIR_UART_INIT_STRUCT COZIR_configUart =
    {
        COZIR_UART_SUB_MODE,
        COZIR_UART_DIRECTION,
        COZIR_UART_DATA_BITS_NUM,
        COZIR_UART_PARITY_TYPE,
        COZIR_UART_STOP_BITS_NUM,
        COZIR_UART_OVS_FACTOR,
        COZIR_UART_IRDA_LOW_POWER,
        COZIR_UART_MEDIAN_FILTER_ENABLE,
        COZIR_UART_RETRY_ON_NACK,
        COZIR_UART_IRDA_POLARITY,
        COZIR_UART_DROP_ON_PARITY_ERR,
        COZIR_UART_DROP_ON_FRAME_ERR,
        COZIR_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        COZIR_UART_MP_MODE_ENABLE,
        COZIR_UART_MP_ACCEPT_ADDRESS,
        COZIR_UART_MP_RX_ADDRESS,
        COZIR_UART_MP_RX_ADDRESS_MASK,
        (uint32) COZIR_SCB_IRQ_INTERNAL,
        COZIR_UART_INTR_RX_MASK,
        COZIR_UART_RX_TRIGGER_LEVEL,
        COZIR_UART_INTR_TX_MASK,
        COZIR_UART_TX_TRIGGER_LEVEL,
        (uint8) COZIR_UART_BYTE_MODE_ENABLE,
        (uint8) COZIR_UART_CTS_ENABLE,
        (uint8) COZIR_UART_CTS_POLARITY,
        (uint8) COZIR_UART_RTS_POLARITY,
        (uint8) COZIR_UART_RTS_FIFO_LEVEL
    };


    /*******************************************************************************
    * Function Name: COZIR_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void COZIR_UartInit(const COZIR_UART_INIT_STRUCT *config)
    {
        uint32 pinsConfig;

        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Get direction to configure UART pins: TX, RX or TX+RX */
            pinsConfig  = config->direction;

        #if !(COZIR_CY_SCBIP_V0 || COZIR_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (COZIR_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)         ? (COZIR_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(COZIR_CY_SCBIP_V0 || COZIR_CY_SCBIP_V1) */

            /* Configure pins */
            COZIR_SetPins(COZIR_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            COZIR_scbMode       = (uint8) COZIR_SCB_MODE_UART;
            COZIR_scbEnableWake = (uint8) config->enableWake;
            COZIR_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            COZIR_rxBuffer      =         config->rxBuffer;
            COZIR_rxDataBits    = (uint8) config->dataBits;
            COZIR_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            COZIR_txBuffer      =         config->txBuffer;
            COZIR_txDataBits    = (uint8) config->dataBits;
            COZIR_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure UART interface */
            if(COZIR_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                COZIR_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (COZIR_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (COZIR_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                COZIR_CTRL_REG  = COZIR_GET_CTRL_OVS(config->oversample);
            }

            COZIR_CTRL_REG     |= COZIR_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             COZIR_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             COZIR_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            COZIR_UART_CTRL_REG = COZIR_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            COZIR_UART_RX_CTRL_REG = COZIR_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        COZIR_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        COZIR_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        COZIR_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        COZIR_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(COZIR_UART_PARITY_NONE != config->parity)
            {
               COZIR_UART_RX_CTRL_REG |= COZIR_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    COZIR_UART_RX_CTRL_PARITY_ENABLED;
            }

            COZIR_RX_CTRL_REG      = COZIR_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                COZIR_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                COZIR_GET_UART_RX_CTRL_ENABLED(config->direction);

            COZIR_RX_FIFO_CTRL_REG = COZIR_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            COZIR_RX_MATCH_REG     = COZIR_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                COZIR_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            COZIR_UART_TX_CTRL_REG = COZIR_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                COZIR_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(COZIR_UART_PARITY_NONE != config->parity)
            {
               COZIR_UART_TX_CTRL_REG |= COZIR_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    COZIR_UART_TX_CTRL_PARITY_ENABLED;
            }

            COZIR_TX_CTRL_REG      = COZIR_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                COZIR_GET_UART_TX_CTRL_ENABLED(config->direction);

            COZIR_TX_FIFO_CTRL_REG = COZIR_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(COZIR_CY_SCBIP_V0 || COZIR_CY_SCBIP_V1)
            COZIR_UART_FLOW_CTRL_REG = COZIR_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            COZIR_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            COZIR_GET_UART_FLOW_CTRL_RTS_POLARITY(config->rtsPolarity)   | \
                                            COZIR_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(COZIR_CY_SCBIP_V0 || COZIR_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (COZIR_ISR_NUMBER);
            CyIntSetPriority(COZIR_ISR_NUMBER, COZIR_ISR_PRIORITY);
            (void) CyIntSetVector(COZIR_ISR_NUMBER, &COZIR_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(COZIR_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (COZIR_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(COZIR_RX_WAKE_ISR_NUMBER, COZIR_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(COZIR_RX_WAKE_ISR_NUMBER, &COZIR_UART_WAKEUP_ISR);
        #endif /* (COZIR_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            COZIR_INTR_I2C_EC_MASK_REG = COZIR_NO_INTR_SOURCES;
            COZIR_INTR_SPI_EC_MASK_REG = COZIR_NO_INTR_SOURCES;
            COZIR_INTR_SLAVE_MASK_REG  = COZIR_NO_INTR_SOURCES;
            COZIR_INTR_MASTER_MASK_REG = COZIR_NO_INTR_SOURCES;
            COZIR_INTR_RX_MASK_REG     = config->rxInterruptMask;
            COZIR_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Clear RX buffer indexes */
            COZIR_rxBufferHead     = 0u;
            COZIR_rxBufferTail     = 0u;
            COZIR_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            COZIR_txBufferHead = 0u;
            COZIR_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: COZIR_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void COZIR_UartInit(void)
    {
        /* Configure UART interface */
        COZIR_CTRL_REG = COZIR_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        COZIR_UART_CTRL_REG = COZIR_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        COZIR_UART_RX_CTRL_REG = COZIR_UART_DEFAULT_UART_RX_CTRL;
        COZIR_RX_CTRL_REG      = COZIR_UART_DEFAULT_RX_CTRL;
        COZIR_RX_FIFO_CTRL_REG = COZIR_UART_DEFAULT_RX_FIFO_CTRL;
        COZIR_RX_MATCH_REG     = COZIR_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        COZIR_UART_TX_CTRL_REG = COZIR_UART_DEFAULT_UART_TX_CTRL;
        COZIR_TX_CTRL_REG      = COZIR_UART_DEFAULT_TX_CTRL;
        COZIR_TX_FIFO_CTRL_REG = COZIR_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(COZIR_CY_SCBIP_V0 || COZIR_CY_SCBIP_V1)
        COZIR_UART_FLOW_CTRL_REG = COZIR_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(COZIR_CY_SCBIP_V0 || COZIR_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(COZIR_SCB_IRQ_INTERNAL)
        CyIntDisable    (COZIR_ISR_NUMBER);
        CyIntSetPriority(COZIR_ISR_NUMBER, COZIR_ISR_PRIORITY);
        (void) CyIntSetVector(COZIR_ISR_NUMBER, &COZIR_SPI_UART_ISR);
    #endif /* (COZIR_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(COZIR_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (COZIR_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(COZIR_RX_WAKE_ISR_NUMBER, COZIR_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(COZIR_RX_WAKE_ISR_NUMBER, &COZIR_UART_WAKEUP_ISR);
    #endif /* (COZIR_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        COZIR_INTR_I2C_EC_MASK_REG = COZIR_UART_DEFAULT_INTR_I2C_EC_MASK;
        COZIR_INTR_SPI_EC_MASK_REG = COZIR_UART_DEFAULT_INTR_SPI_EC_MASK;
        COZIR_INTR_SLAVE_MASK_REG  = COZIR_UART_DEFAULT_INTR_SLAVE_MASK;
        COZIR_INTR_MASTER_MASK_REG = COZIR_UART_DEFAULT_INTR_MASTER_MASK;
        COZIR_INTR_RX_MASK_REG     = COZIR_UART_DEFAULT_INTR_RX_MASK;
        COZIR_INTR_TX_MASK_REG     = COZIR_UART_DEFAULT_INTR_TX_MASK;

    #if(COZIR_INTERNAL_RX_SW_BUFFER_CONST)
        COZIR_rxBufferHead     = 0u;
        COZIR_rxBufferTail     = 0u;
        COZIR_rxBufferOverflow = 0u;
    #endif /* (COZIR_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(COZIR_INTERNAL_TX_SW_BUFFER_CONST)
        COZIR_txBufferHead = 0u;
        COZIR_txBufferTail = 0u;
    #endif /* (COZIR_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (COZIR_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: COZIR_UartSetRxAddress
********************************************************************************
*
* Summary:
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
* Parameters:
*  address: Address for hardware address detection.
*
* Return:
*  None
*
*******************************************************************************/
void COZIR_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = COZIR_RX_MATCH_REG;

    matchReg &= ((uint32) ~COZIR_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & COZIR_RX_MATCH_ADDR_MASK)); /* Set address  */

    COZIR_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: COZIR_UartSetRxAddressMask
********************************************************************************
*
* Summary:
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
* Parameters:
*  addressMask: Address mask.
*   0 - address bit does not care while comparison.
*   1 - address bit is significant while comparison.
*
* Return:
*  None
*
*******************************************************************************/
void COZIR_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = COZIR_RX_MATCH_REG;

    matchReg &= ((uint32) ~COZIR_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << COZIR_RX_MATCH_MASK_POS));

    COZIR_RX_MATCH_REG = matchReg;
}


#if(COZIR_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: COZIR_UartGetChar
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *  This function is designed for ASCII characters and returns a char
    *  where 1 to 255 are valid characters and 0 indicates an error occurred or
    *  no data present.
    *  - The RX software buffer is disabled: returns the data element
    *    retrieved from the RX FIFO.
    *    Undefined data will be returned if the RX FIFO is empty.
    *  - The RX software buffer is enabled: returns the data element from
    *    the software receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The next data element from the receive buffer.
    *  ASCII character values from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Side Effects:
    *  The errors bits may not correspond with reading characters due to RX FIFO
    *  and software buffer usage.
    *  RX software buffer is enabled: The internal software buffer overflow
    *  does not treat as an error condition.
    *  Check SCB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 COZIR_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if(0u != COZIR_SpiUartGetRxBufferSize())
        {
            rxData = COZIR_SpiUartReadRxData();
        }

        if(COZIR_CHECK_INTR_RX(COZIR_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            COZIR_ClearRxInterruptSource(COZIR_INTR_RX_ERR);
        }

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: COZIR_UartGetByte
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer, returns the
    *  received byte and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved
    *     from the RX FIFO. Undefined data will be returned if the RX FIFO is
    *     empty.
    *   - The RX software buffer is enabled: returns data element from the
    *     software receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Bits 7-0 contain the next data element from the receive buffer and
    *  other bits contain the error condition.
    *
    * Side Effects:
    *  The errors bits may not correspond with reading characters due to RX FIFO
    *  and software buffer usage.
    *  RX software buffer is disabled: The internal software buffer overflow
    *  is not returned as status by this function.
    *  Check SCB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 COZIR_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;
        uint32 intSourceMask;

        intSourceMask = COZIR_SpiUartDisableIntRx();

        if(0u != COZIR_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            COZIR_SpiUartEnableIntRx(intSourceMask);

            /* Get received byte */
            rxData = COZIR_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the case
            * of empty. Otherwise the first received byte will be read.
            */
            rxData = COZIR_RX_FIFO_RD_REG;

            /* Enables interrupt to receive more bytes.
            * The RX_NOT_EMPTY interrupt is cleared by the interrupt routine
            * in case the byte was received and read by code above.
            */
            COZIR_SpiUartEnableIntRx(intSourceMask);
        }

        /* Get and clear RX error mask */
        tmpStatus = (COZIR_GetRxInterruptSource() & COZIR_INTR_RX_ERR);
        COZIR_ClearRxInterruptSource(COZIR_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return(rxData);
    }


    #if !(COZIR_CY_SCBIP_V0 || COZIR_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: COZIR_UartSetRtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of RTS output signal.
        *
        * Parameters:
        *  polarity: Active polarity of RTS output signal.
        *   COZIR_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   COZIR_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void COZIR_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                COZIR_UART_FLOW_CTRL_REG |= (uint32)  COZIR_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                COZIR_UART_FLOW_CTRL_REG &= (uint32) ~COZIR_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: COZIR_UartSetRtsFifoLevel
        ********************************************************************************
        *
        * Summary:
        *  Sets level in the RX FIFO for RTS signal activation.
        *  While the RX FIFO has fewer entries than the RX FIFO level the RTS signal
        *  remains active, otherwise the RTS signal becomes inactive.
        *
        * Parameters:
        *  level: Level in the RX FIFO for RTS signal activation.
        *         The range of valid level values is between 0 and RX FIFO depth - 1.
        *         Setting level value to 0 disables RTS signal activation.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void COZIR_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = COZIR_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~COZIR_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (COZIR_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            COZIR_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(COZIR_CY_SCBIP_V0 || COZIR_CY_SCBIP_V1) */

#endif /* (COZIR_UART_RX_DIRECTION) */


#if(COZIR_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: COZIR_UartPutString
    ********************************************************************************
    *
    * Summary:
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  string: pointer to the null terminated string array to be placed in the
    *          transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void COZIR_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            COZIR_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: COZIR_UartPutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data followed by a carriage return (0x0D) and
    *  line feed (0x0A) into the transmit buffer.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  txDataByte : the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void COZIR_UartPutCRLF(uint32 txDataByte)
    {
        COZIR_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        COZIR_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        COZIR_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(COZIR_CY_SCBIP_V0 || COZIR_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: COZIRSCB_UartEnableCts
        ********************************************************************************
        *
        * Summary:
        *  Enables usage of CTS input signal by the UART transmitter.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void COZIR_UartEnableCts(void)
        {
            COZIR_UART_FLOW_CTRL_REG |= (uint32)  COZIR_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: COZIR_UartDisableCts
        ********************************************************************************
        *
        * Summary:
        *  Disables usage of CTS input signal by the UART transmitter.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void COZIR_UartDisableCts(void)
        {
            COZIR_UART_FLOW_CTRL_REG &= (uint32) ~COZIR_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: COZIR_UartSetCtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of CTS input signal.
        *
        * Parameters:
        *  polarity: Active polarity of CTS output signal.
        *   COZIR_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   COZIR_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void COZIR_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                COZIR_UART_FLOW_CTRL_REG |= (uint32)  COZIR_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                COZIR_UART_FLOW_CTRL_REG &= (uint32) ~COZIR_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(COZIR_CY_SCBIP_V0 || COZIR_CY_SCBIP_V1) */

#endif /* (COZIR_UART_TX_DIRECTION) */


#if(COZIR_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: COZIR_UartSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Clears and enables interrupt on a falling edge of the Rx input. The GPIO
    *  event wakes up the device and SKIP_START feature allows the UART continue
    *  receiving data bytes properly. The GPIO interrupt does not track in the
    *  active mode therefore requires to be cleared by this API.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void COZIR_UartSaveConfig(void)
    {
        /* Clear interrupt activity:
        *  - set skip start and disable RX. At GPIO wakeup RX will be enabled.
        *  - clear rx_wake interrupt source as it triggers during normal operation.
        *  - clear wake interrupt pending state as it becomes pending in active mode.
        */

        COZIR_UART_RX_CTRL_REG |= COZIR_UART_RX_CTRL_SKIP_START;

    #if(COZIR_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(COZIR_MOSI_SCL_RX_WAKE_PIN)
            (void) COZIR_spi_mosi_i2c_sda_uart_rx_wake_ClearInterrupt();
        #endif /* (COZIR_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(COZIR_UART_RX_WAKE_PIN)
            (void) COZIR_rx_wake_ClearInterrupt();
        #endif /* (COZIR_UART_RX_WAKE_PIN) */
    #endif /* (COZIR_SCB_MODE_UNCONFIG_CONST_CFG) */

    #if(COZIR_UART_RX_WAKEUP_IRQ)
        COZIR_RxWakeClearPendingInt();
        COZIR_RxWakeEnableInt();
    #endif /* (COZIR_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: COZIR_UartRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void COZIR_UartRestoreConfig(void)
    {
    /* Disable RX GPIO interrupt: no more triggers in active mode */
    #if(COZIR_UART_RX_WAKEUP_IRQ)
        COZIR_RxWakeDisableInt();
    #endif /* (COZIR_UART_RX_WAKEUP_IRQ) */
    }
#endif /* (COZIR_UART_WAKE_ENABLE_CONST) */


#if(COZIR_UART_RX_WAKEUP_IRQ)
    /*******************************************************************************
    * Function Name: COZIR_UART_WAKEUP_ISR
    ********************************************************************************
    *
    * Summary:
    *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
    *  event. This event is configured to trigger on a falling edge of the RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    CY_ISR(COZIR_UART_WAKEUP_ISR)
    {
        /* Clear interrupt source: the event becomes multi triggered and is
        * only disabled by COZIR_UartRestoreConfig() call.
        */
    #if(COZIR_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(COZIR_MOSI_SCL_RX_WAKE_PIN)
            (void) COZIR_spi_mosi_i2c_sda_uart_rx_wake_ClearInterrupt();
        #endif /* (COZIR_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(COZIR_UART_RX_WAKE_PIN)
            (void) COZIR_rx_wake_ClearInterrupt();
        #endif /* (COZIR_UART_RX_WAKE_PIN) */
    #endif /* (COZIR_SCB_MODE_UNCONFIG_CONST_CFG) */
    }
#endif /* (COZIR_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
