 /*****************************************************************************/
 /***************************  NAME  :  ahmed hassan **************************/
 /***************************  VERSION :  1.0        **************************/
 /*****************************************************************************/

#ifndef HAL_NRF24L01_INCLUDES_NRF24L01_H_
#define HAL_NRF24L01_INCLUDES_NRF24L01_H_

/*=====================================================================================================================
                                       < User-defined Data Types >
=====================================================================================================================*/

typedef enum
{
    NRF24L01_NO_ERRORS,
    NRF24L01_NULL_PTR_ERROR,
    NRF24L01_DATA_PIPE_ERROR,
    NRF24L01_CHANNEL_NUMBER_ERROR,
}NRF24L01_errorStatusType;

typedef enum
{
    NRF24L01_DATA_PIPE_0,
    NRF24L01_DATA_PIPE_1,
    NRF24L01_DATA_PIPE_2,
    NRF24L01_DATA_PIPE_3,
    NRF24L01_DATA_PIPE_4,
    NRF24L01_DATA_PIPE_5,
}NRF24L01_dataPipeType;

typedef enum
{
    NRF24L01_BUFFER_EMPTY,
    NRF24L01_BUFFER_NOT_EMPTY,
}NRF24L01_bufferStatusType;

/*=====================================================================================================================
                                         < Functions Prototypes >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : NRF24L01_init
 * [Description]   : Initialize the NRF24L01 module.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void NRF24L01_init(void);

/*=====================================================================================================================
 * [Function Name] : NRF24L01_reset
 * [Description]   : Reset the NRF24L01 module by resetting its registers.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void NRF24L01_reset(void);

/*=====================================================================================================================
 * [Function Name] : NRF24L01_switchToTransmitterMode
 * [Description]   : Reconfigure the NRF24L01 module to work in transmitter mode.
 * [Arguments]     : <a_channel>      -> Indicates to the transmission channel number.
 * [return]        : The function returns error status: - No Errors.
 *                                                      - Channel Number Error.
 ====================================================================================================================*/
NRF24L01_errorStatusType NRF24L01_switchToTransmitterMode(u8 a_channel);

/*=====================================================================================================================
 * [Function Name] : NRF24L01_switchToReceiverMode
 * [Description]   : Reconfigure the NRF24L01 module to work in receiver mode.
 * [Arguments]     : <a_channel>      -> Indicates to the transmission channel number.
 *                   <a_dataPipe>     -> Indicates to the required data pipe to be enabled.
 * [return]        : The function returns error status: - No Errors.
 *                                                      - Channel Number Error.
 *                                                      - Data Pipe Error.
 ====================================================================================================================*/
NRF24L01_errorStatusType NRF24L01_switchToReceiverMode(u8 a_channel, NRF24L01_dataPipeType a_dataPipe);

/*=====================================================================================================================
 * [Function Name] : NRF24L01_checkTransmitterBuffer
 * [Description]   : Check if the Transmitter buffer is empty or not.
 *                   <a_ptr2status>    -> Pointer to a variable to store the buffer status.
 * [return]        : The function returns error status: - No Errors.
 *                                                      - Data Pipe Error.
 *                                                      - Null Pointer Error.
 ====================================================================================================================*/
NRF24L01_errorStatusType NRF24L01_checkTransmitterBuffer(NRF24L01_bufferStatusType* a_ptr2bufferStatus);

/*=====================================================================================================================
 * [Function Name] : NRF24L01_checkReceiverBuffer
 * [Description]   : Check if the Receiver buffer of a specific data pipe is empty or not.
 * [Arguments]     : <a_dataPipe>          -> Indicates to the required data pipe to be checked.
 *                   <a_ptr2bufferStatus>  -> Pointer to a variable to store the buffer status.
 * [return]        : The function returns error status: - No Errors.
 *                                                      - Data Pipe Error.
 *                                                      - Null Pointer Error.
 ====================================================================================================================*/
NRF24L01_errorStatusType NRF24L01_checkReceiverBuffer(NRF24L01_dataPipeType a_dataPipe, NRF24L01_bufferStatusType* a_ptr2bufferStatus);

/*=====================================================================================================================
 * [Function Name] : NRF24L01_sendData
 * [Description]   : Transmit data through the NRF24L01 module.
 * [Arguments]     : <a_ptr2data>    -> Pointer to the required data to be transmitted.
 *                   <a_size>        -> Indicates to the size of the data.
 * [return]        : The function returns error status: - No Errors.
 *                                                      - Null Pointer Error.
 ====================================================================================================================*/
NRF24L01_errorStatusType NRF24L01_sendData(u8* a_ptr2data, u8 a_size);

/*=====================================================================================================================
 * [Function Name] : NRF24L01_readData
 * [Description]   : Read data from the NRF24L01 receiver buffer.
 * [Arguments]     : <a_ptr2data>    -> Pointer to array to store the received data.
 *                   <a_size>        -> Indicates to the size of the data.
 * [return]        : The function returns error status: - No Errors.
 *                                                      - Null Pointer Error.
 ====================================================================================================================*/
NRF24L01_errorStatusType NRF24L01_readData(u8* a_ptr2data, u8 a_size);

/*=====================================================================================================================
 * [Function Name] : NRF24L01_flushTransmitterBuffer
 * [Description]   : Flush the transmitter buffer after sending the data.
 * [Arguments]     : The function takes no argument.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void NRF24L01_flushTransmitterBuffer(void);

/*=====================================================================================================================
 * [Function Name] : NRF24L01_flushReceiverBuffer
 * [Description]   : Flush the receiver buffer after reading the received data.
 * [Arguments]     : The function takes no argument.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void NRF24L01_flushReceiverBuffer(void);

#endif /* HAL_NRF24L01_INCLUDES_NRF24L01_H_ */
