 /*****************************************************************************/
 /***************************  NAME  :  ahmed hassan **************************/
 /***************************  VERSION :  1.0        **************************/
 /*****************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "Timer_init.h"
#include "Timer_register.h"
#include "Timer_private.h"
#include "Timer_conf.h"

u8 channel1_set=0;
u8 channel2_set=0;

void MTimer_voidInit (u8 A_u8TimerSelected)
{
	/* initialization RCC */
	//MRCC_voidInit() ;

	/* Enable pinout of ADC (PortA , PORTB) from RCC */
	//MRCC_voidEnablePerephiralClock(RCC_AHB1 , RCC_EN_GPIOA) ;
	//MRCC_voidEnablePerephiralClock(RCC_AHB1 , RCC_EN_GPIOB) ;

	switch (A_u8TimerSelected)
	{
	case TIM1_TYPE  :
		/******************************************************************************/
		/**                             Init TIM1                                    **/
		/******************************************************************************/

			/* Select the Direction */
            #if   TIM1_DIRECTION == UP_COUNTER
			      CLR_BIT(TIM_1->CR1 , TIM1_CR1_DIR_BIT) ;
            #elif TIM1_DIRECTION == DOWN_COUNTER
			      SET_BIT(TIM_1 , TIM1_CR1_DIR_BIT) ;
            #else
                  #error "Invalid Selection of TIM1_DIRECTION"
            #endif

			/* Edge-aligned mode */
			CLR_BIT(TIM_1->CR1 , TIM1_CR1_CMS_BIT0) ;
			CLR_BIT(TIM_1->CR1 , TIM1_CR1_CMS_BIT1) ;

			/* set the timer division */
            #if   TIM1_DIVISION == tCK_INT_x_1
			      CLR_BIT(TIM_1->CR1 , TIM1_CR1_CKD_BIT0) ;
			      CLR_BIT(TIM_1->CR1 , TIM1_CR1_CKD_BIT1) ;
            #elif TIM1_DIVISION == tCK_INT_x_2
			      SET_BIT(TIM_1->CR1 , TIM1_CR1_CKD_BIT0) ;
			      CLR_BIT(TIM_1->CR1 , TIM1_CR1_CKD_BIT1) ;
            #elif TIM1_DIVISION == tCK_INT_x_4
			      CLR_BIT(TIM_1->CR1 , TIM1_CR1_CKD_BIT0) ;
			      SET_BIT(TIM_1->CR1 , TIM1_CR1_CKD_BIT1) ;
            #else
                  #error "Invalid Selection of TIM1_DIVISION"
            #endif

			/* set the timer prescaller */
            #if    TIM1_PRESCALLER <= MAX_TIM_PRESCALLER
            	   TIM_1 ->PSC = TIM1_PRESCALLER ;
            #else
                   #error "TIM1_PRESCALLER out of range"
            #endif

            /* Enable auto-reload preload */
            SET_BIT(TIM_1->CR1 , TIM1_CR1_ARPE_BIT) ;

            /* Set the Auto-reload value */
            #if  TIM1_PRELOAD_VALUE <= MAX_TIM_PRELOAD_VALUE
            	   TIM_1->ARR = TIM1_PRELOAD_VALUE ;
            #else
                  #error "TIM1_PRELOAD_VALUE out of range"
            #endif

            /* Set the Repetition Counter value */
           // #if REPETATION_COUNTER <= MAX_TIM_REPETATION_COUNTER
            	  // TIM_1 -> RCR = REPETATION_COUNTER ;
           // #else
           //       #error "REPETATION_COUNTER out of range"
           // #endif

            /* Generate an update event to reload the Prescaler
            and the repetition counter(only for TIM1 and TIM5) value immediately */
            SET_BIT(TIM_1->EGR , TIM1_EGR_UG_BIT );

		break ;
	case TIM2_TYPE  :
		/******************************************************************************/
		/**                             Init TIM2                                    **/
		/******************************************************************************/

			/* Disable slave mode to clock the prescaler directly with the internal clock */
			SET_BIT(TIM_2 -> SMCR , TIM2_TO_TIM5_SMCR_MSM_BIT );

			/* Select the Direction */
            #if   TIM2_DIRECTION == UP_COUNTER
			      CLR_BIT(TIM_2->CR1 , TIM2_TO_TIM5_CR1_DIR_BIT) ;
            #elif TIM2_DIRECTION == DOWN_COUNTER
			      SET_BIT(TIM_2->CR1 , TIM2_TO_TIM5_CR1_DIR_BIT) ;
            #else
                  #error "Invalid Selection of TIM2_DIRECTION"
            #endif

			/* Edge-aligned mode */
			CLR_BIT(TIM_2->CR1 , TIM2_TO_TIM5_CR1_CMS_BIT0) ;
			CLR_BIT(TIM_2->CR1 , TIM2_TO_TIM5_CR1_CMS_BIT1) ;

			/* set the timer division */
			#if   TIM2_DIVISION == tCK_INT_x_1
		      CLR_BIT(TIM_2->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT0) ;
		      CLR_BIT(TIM_2->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT1) ;
			#elif TIM1_DIVISION == tCK_INT_x_2
		      SET_BIT(TIM_2->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT0) ;
		      CLR_BIT(TIM_2->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT1) ;
			#elif TIM1_DIVISION == tCK_INT_x_4
		      CLR_BIT(TIM_2->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT0) ;
		      SET_BIT(TIM_2->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT1) ;
			#else
			      #error "Invalid Selection of TIM2_DIVISION"
			#endif

		    /* set the timer prescaller */
	        #if    TIM2_PRESCALLER <= MAX_TIM_PRESCALLER
	        	   TIM_2 ->PSC = TIM2_PRESCALLER ;
	        #else
	               #error "TIM2_PRESCALLER out of range"
	        #endif

	        /* Enable auto-reload preload */
	        SET_BIT(TIM_2->CR1 , TIM2_TO_TIM5_CR1_ARPE_BIT) ;

	        /* Set the Auto-reload value */
	        #if  TIM2_PRELOAD_VALUE <= MAX_TIM_PRELOAD_VALUE
	        	   TIM_2->ARR = TIM2_PRELOAD_VALUE ;
	        #else
	              #error "TIM2_PRELOAD_VALUE out of range"
	        #endif

	        /* Generate an update event to reload the Prescaler
	         and the repetition counter(only for TIM1 and TIM5) value immediately */
	        SET_BIT(TIM_2->EGR , TIM2_TO_TIM5_EGR_UG_BIT );

		break ;
	case TIM3_TYPE  :
		/******************************************************************************/
		/**                             Init TIM3                                    **/
		/******************************************************************************/

			/* Disable slave mode to clock the prescaler directly with the internal clock */
			SET_BIT(TIM_3 -> SMCR , TIM2_TO_TIM5_SMCR_MSM_BIT );

			/* Select the Direction */
            #if   TIM3_DIRECTION == UP_COUNTER
	           CLR_BIT(TIM_3->CR1 , TIM2_TO_TIM5_CR1_DIR_BIT) ;
            #elif TIM3_DIRECTION == DOWN_COUNTER
	           SET_BIT(TIM_3->CR1 , TIM2_TO_TIM5_CR1_DIR_BIT) ;
            #else
                  #error "Invalid Selection of TIM3_DIRECTION"
            #endif

	        /* Edge-aligned mode */
	        CLR_BIT(TIM_3->CR1 , TIM2_TO_TIM5_CR1_CMS_BIT0) ;
	        CLR_BIT(TIM_3->CR1 , TIM2_TO_TIM5_CR1_CMS_BIT1) ;

			/* set the timer division */
			#if   TIM3_DIVISION == tCK_INT_x_1
		      CLR_BIT(TIM_3->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT0) ;
		      CLR_BIT(TIM_3->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT1) ;
			#elif TIM3_DIVISION == tCK_INT_x_2
		      SET_BIT(TIM_3->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT0) ;
		      CLR_BIT(TIM_3->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT1) ;
			#elif TIM3_DIVISION == tCK_INT_x_4
		      CLR_BIT(TIM_3->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT0) ;
		      SET_BIT(TIM_3->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT1) ;
			#else
			      #error "Invalid Selection of TIM3_DIVISION"
			#endif

			/* set the timer prescaller */
		    #if    TIM3_PRESCALLER <= MAX_TIM_PRESCALLER
		    	   TIM_3 ->PSC = TIM3_PRESCALLER ;
		    #else
		           #error "TIM3_PRESCALLER out of range"
		    #endif

		    /* Enable auto-reload preload */
			SET_BIT(TIM_3->CR1 , TIM2_TO_TIM5_CR1_ARPE_BIT) ;

			/* Set the Auto-reload value */
			#if  TIM3_PRELOAD_VALUE <= MAX_TIM_PRELOAD_VALUE
				   TIM_3->ARR = TIM3_PRELOAD_VALUE ;
			#else
			      #error "TIM3_PRELOAD_VALUE out of range"
			#endif

			/* Generate an update event to reload the Prescaler
			 and the repetition counter(only for TIM1 and TIM5) value immediately */
			SET_BIT(TIM_3->EGR , TIM2_TO_TIM5_EGR_UG_BIT );

		break ;
	case TIM4_TYPE  :
		/******************************************************************************/
		/**                             Init TIM4                                    **/
		/******************************************************************************/

			/* Disable slave mode to clock the prescaler directly with the internal clock */
			SET_BIT(TIM_4 -> SMCR , TIM2_TO_TIM5_SMCR_MSM_BIT );

			/* Select the Direction */
			#if   TIM4_DIRECTION == UP_COUNTER
			     CLR_BIT(TIM_4->CR1 , TIM2_TO_TIM5_CR1_DIR_BIT) ;
			#elif TIM4_DIRECTION == DOWN_COUNTER
			     SET_BIT(TIM_4->CR1 , TIM2_TO_TIM5_CR1_DIR_BIT) ;
			#else
			      #error "Invalid Selection of TIM4_DIRECTION"
			#endif

			/* Edge-aligned mode */
			CLR_BIT(TIM_4->CR1 , TIM2_TO_TIM5_CR1_CMS_BIT0) ;
			CLR_BIT(TIM_4->CR1 , TIM2_TO_TIM5_CR1_CMS_BIT1) ;

			/* set the timer division */
			#if   TIM4_DIVISION == tCK_INT_x_1
		      CLR_BIT(TIM_4->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT0) ;
		      CLR_BIT(TIM_4->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT1) ;
			#elif TIM4_DIVISION == tCK_INT_x_2
		      SET_BIT(TIM_4->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT0) ;
		      CLR_BIT(TIM_4->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT1) ;
			#elif TIM4_DIVISION == tCK_INT_x_4
		      CLR_BIT(TIM_4->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT0) ;
		      SET_BIT(TIM_4->CR1 , TIM2_TO_TIM5_CR1_CKD_BIT1) ;
			#else
			      #error "Invalid Selection of TIM4_DIVISION"
			#endif

		    /* set the timer prescaller */
			#if    TIM4_PRESCALLER <= MAX_TIM_PRESCALLER
				   TIM_4 ->PSC = TIM4_PRESCALLER ;
			#else
			       #error "TIM4_PRESCALLER out of range"
			#endif

			/* Enable auto-reload preload */
			SET_BIT(TIM_4->CR1 , TIM2_TO_TIM5_CR1_ARPE_BIT) ;

			/* Set the Auto-reload value */
			#if  TIM4_PRELOAD_VALUE <= MAX_TIM_PRELOAD_VALUE
				   TIM_4->ARR = TIM4_PRELOAD_VALUE ;
			#else
			      #error "TIM4_PRELOAD_VALUE out of range"
			#endif

		    /* Generate an update event to reload the Prescaler
		    	  and the repetition counter(only for TIM1 and TIM5) value immediately */
		    SET_BIT(TIM_4->EGR , TIM2_TO_TIM5_EGR_UG_BIT );
		break ;
	}
}

void MTimer_voidPWM (u8 A_u8TimerSelected , u8 A_u8Channel , u16 A_u16CompareValue)
{
	if (A_u8TimerSelected == TIM1_TYPE)
	{
		if (A_u8Channel == TIM_CHANNEL_1)
		{
			if (channel1_set==0)
			{
				GPIO_voidSetPinMode(GPIO_PORTA,GPIO_PIN8,GPIO_OUTPUT_10M_AF_PP);
				channel1_set=1;
			}

			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
		    u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 1: Reset the CC1E Bit */
			CLR_BIT(TIM_1->CCER , TIM1_CCER_CC1E_BIT) ;

			/* Get the TIM CCER register value */
			L_u32TempCCMRX = TIM_1->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_1->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_1->CCMR1;

			/* Reset the Output Compare Mode Bits */
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_OC1M_BIT0) ;
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_OC1M_BIT1) ;
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_OC1M_BIT2) ;
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_CC1S_BIT0) ;
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_CC1S_BIT1) ;
			/* Select the Output Compare Mode1 */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 4U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM1_CCER_CC1P_BIT);

			/* Set the Output N Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM1_CCER_CC1NP_BIT) ;
			/* Reset the Output N State */
			CLR_BIT(L_u32TempCCER , TIM1_CCER_CC1NE_BIT) ;

			/* Reset the Output Compare and Output Compare N IDLE State */
			CLR_BIT(L_u32TempCR2 , TIM1_CR2_OIS1N_BIT) ;
			CLR_BIT(L_u32TempCR2 , TIM1_CR2_OIS1N_BIT) ;

			/* Write to TIM CR2 */
			TIM_1->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR1 */
			TIM_1->CCMR1 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_1->CCR1 = A_u16CompareValue ;

			/* Write to TIM CCER */
			TIM_1->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel1 */
			SET_BIT (TIM_1->CCMR1 , TIM1_CCMR1_OC1PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_1->CCMR1 , TIM1_CCMR1_OC1FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_1-> CCER , TIM1_CCER_CC1E_BIT) ;

			/* Enable the main output */
			SET_BIT(TIM_1 ->BDTR , TIM1_BDTR_MOE_BIT ) ;

			/* Enable the timer */
			SET_BIT(TIM_1 -> CR1 , TIM1_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_2)
		{
			if (channel2_set==0)
				{
					GPIO_voidSetPinMode(GPIO_PORTA,GPIO_PIN9,GPIO_OUTPUT_10M_AF_PP);
					channel2_set=1;
				}
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
		    u32 L_u32TempCR2   = 0 ;

		    /* Disable the Channel 2: Reset the CC2E Bit */
		    CLR_BIT(TIM_1->CCER , TIM1_CCER_CC2E_BIT);

		    /* Get the TIM CCER register value */
		    L_u32TempCCER = TIM_1->CCER;
		    /* Get the TIM CR2 register value */
		    L_u32TempCR2 = TIM_1->CR2;

		    /* Get the TIM CCMR1 register value */
		    L_u32TempCCMRX = TIM_1->CCMR1;

		    /* Reset the Output Compare mode and Capture/Compare selection Bits */
		    CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_OC2M_BIT0);
		    CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_OC2M_BIT1);
		    CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_CC2S_BIT0);
		    CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_CC2S_BIT1);

		    /* Select the Output Compare Mode */
		    L_u32TempCCMRX |= (TIM_PWM_MODE1 << 12U) ;

		    /* Set the Output Compare Polarity as active high */
		    CLR_BIT(L_u32TempCCER , TIM1_CCER_CC2P_BIT);

		    /* Set the Output N Polarity as active high */
		    CLR_BIT(L_u32TempCCER , TIM1_CCER_CC2NP_BIT) ;

		    /* Set the Output N Polarity as active high */
		    CLR_BIT(L_u32TempCCER , TIM1_CCER_CC2NP_BIT) ;
		    /* Reset the Output N State */
		    CLR_BIT(L_u32TempCCER , TIM1_CCER_CC2NE_BIT);

		    /* Reset the Output Compare and Output Compare N IDLE State */
		    CLR_BIT(L_u32TempCR2 , TIM1_CR2_OIS2_BIT);
		    CLR_BIT(L_u32TempCR2 , TIM1_CR2_OIS2N_BIT);

		    /* Write to TIM CR2 */
		    TIM_1->CR2 = L_u32TempCR2;

		    /* Write to TIM CCMR1 */
		    TIM_1->CCMR1 = L_u32TempCCMRX;

		    /* Set the Capture Compare Register value */
		    TIM_1->CCR2 = A_u16CompareValue;

		    /* Write to TIM CCER */
		    TIM_1->CCER = L_u32TempCCER;

		    /* Set the Preload enable bit for channel2 */
		    SET_BIT (TIM_1->CCMR1 , TIM1_CCMR1_OC2PE_BIT);

		    /* Configure the Output Fast mode */
		    SET_BIT (TIM_1->CCMR1 , TIM1_CCMR1_OC2FE_BIT) ;

		    /* Enable the Capture compare channel */
		    SET_BIT(TIM_1-> CCER , TIM1_CCER_CC2E_BIT) ;

		    /* Enable the main output */
		    SET_BIT(TIM_1 ->BDTR , TIM1_BDTR_MOE_BIT ) ;

		    /* Enable the timer */
		    SET_BIT(TIM_1 -> CR1 , TIM1_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_3)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 3: Reset the CC2E Bit */
			CLR_BIT(TIM_1->CCER , TIM1_CCER_CC3E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_1->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_1->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_1->CCMR2;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR2_OC3M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR2_OC3M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR2_CC3S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR2_CC3S_BIT1);

			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 4U);

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM1_CCER_CC3P_BIT);

			/* Set the Output N Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM1_CCER_CC3NP_BIT) ;

			/* Set the Output N Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM1_CCER_CC3NP_BIT) ;
			/* Reset the Output N State */
			CLR_BIT(L_u32TempCCER , TIM1_CCER_CC3NE_BIT);

			/* Reset the Output Compare and Output Compare N IDLE State */
			CLR_BIT(L_u32TempCR2 , TIM1_CR2_OIS3_BIT);
			CLR_BIT(L_u32TempCR2 , TIM1_CR2_OIS3N_BIT);

			/* Write to TIM CR2 */
			TIM_1->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR1 */
			TIM_1->CCMR2 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_1->CCR3 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_1->CCER = L_u32TempCCER;

		    /* Set the Preload enable bit for channel3 */
		    SET_BIT (TIM_1->CCMR2 , TIM1_CCMR2_OC3PE_BIT);

		    /* Configure the Output Fast mode */
		    SET_BIT (TIM_1->CCMR2 , TIM1_CCMR2_OC3FE_BIT) ;

		    /* Enable the Capture compare channel */
		    SET_BIT(TIM_1-> CCER , TIM1_CCER_CC3E_BIT) ;

		    /* Enable the main output */
		    SET_BIT(TIM_1 ->BDTR , TIM1_BDTR_MOE_BIT ) ;

		    /* Enable the timer */
		    SET_BIT(TIM_1 -> CR1 , TIM1_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_4)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 4: Reset the CC2E Bit */
			CLR_BIT(TIM_1->CCER , TIM1_CCER_CC4E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_1->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_1->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_1->CCMR2;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_OC2M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_OC2M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_CC2S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM1_CCMR1_CC2S_BIT1);

			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 12U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM1_CCER_CC4P_BIT);

			/* Reset the Output Compare IDLE State */
			CLR_BIT(L_u32TempCR2 , TIM1_CR2_OIS4_BIT);

			/* Write to TIM CR2 */
			TIM_1->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR2 */
			TIM_1->CCMR2 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_1->CCR4 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_1->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel4 */
			SET_BIT (TIM_1->CCMR2 , TIM1_CCMR2_OC4PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_1->CCMR2 , TIM1_CCMR2_OC4FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_1-> CCER , TIM1_CCER_CC4E_BIT) ;

			/* Enable the main output */
			SET_BIT(TIM_1 ->BDTR , TIM1_BDTR_MOE_BIT ) ;

			/* Enable the timer */
			SET_BIT(TIM_1 -> CR1 , TIM1_CR1_CEN_BIT) ;
		}
	}
	else if (A_u8TimerSelected == TIM2_TYPE)
	{
		if (A_u8Channel == TIM_CHANNEL_1)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 1: Reset the CC1E Bit */
			CLR_BIT(TIM_2->CCER , TIM2_TO_TIM5_CCER_CC1E_BIT) ;

			/* Get the TIM CCER register value */
			L_u32TempCCMRX = TIM_2->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_2->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_2->CCMR1;

			/* Reset the Output Compare Mode Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC1M_BIT0) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC1M_BIT1) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC1M_BIT2) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC1S_BIT0) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC1S_BIT1) ;
			/* Select the Output Compare Mode1 */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 4U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC1P_BIT);

			/* Write to TIM CR2 */
			TIM_2->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR1 */
			TIM_2->CCMR1 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_2->CCR1 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_2->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel1 */
			SET_BIT (TIM_2->CCMR1 , TIM2_TO_TIM5_CCMR1_OC1PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_2->CCMR1 , TIM2_TO_TIM5_CCMR1_OC1FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_2-> CCER , TIM2_TO_TIM5_CCER_CC1E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_2 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_2)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
		    u32 L_u32TempCR2   = 0 ;

		    /* Disable the Channel 2: Reset the CC2E Bit */
		    CLR_BIT(TIM_2->CCER , TIM2_TO_TIM5_CCER_CC2E_BIT);

		    /* Get the TIM CCER register value */
		    L_u32TempCCER = TIM_2->CCER;
		    /* Get the TIM CR2 register value */
		    L_u32TempCR2 = TIM_2->CR2;

		    /* Get the TIM CCMR1 register value */
		    L_u32TempCCMRX = TIM_2->CCMR1;

		    /* Reset the Output Compare mode and Capture/Compare selection Bits */
		    CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT0);
		    CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT1);
		    CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT0);
		    CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT1);

		    /* Select the Output Compare Mode */
		    L_u32TempCCMRX |= (TIM_PWM_MODE1 << 12U) ;

		    /* Set the Output Compare Polarity as active high */
		    CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC2P_BIT);

		    /* Set the Output N Polarity as active high */
		    CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC2NP_BIT) ;

		    /* Write to TIM CR2 */
		    TIM_2->CR2 = L_u32TempCR2;

		    /* Write to TIM CCMR1 */
		    TIM_2->CCMR1 = L_u32TempCCMRX;

		    /* Set the Capture Compare Register value */
		    TIM_2->CCR2 = A_u16CompareValue;

		    /* Write to TIM CCER */
		    TIM_2->CCER = L_u32TempCCER;

		    /* Set the Preload enable bit for channel2 */
		    SET_BIT (TIM_2->CCMR1 , TIM2_TO_TIM5_CCMR1_OC2PE_BIT);

		    /* Configure the Output Fast mode */
		    SET_BIT (TIM_2->CCMR1 , TIM2_TO_TIM5_CCMR1_OC2FE_BIT) ;

		    /* Enable the Capture compare channel */
		    SET_BIT(TIM_2-> CCER , TIM2_TO_TIM5_CCER_CC2E_BIT) ;

		    /* Enable the timer */
		    SET_BIT(TIM_2 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_3)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 3: Reset the CC2E Bit */
			CLR_BIT(TIM_2->CCER , TIM2_TO_TIM5_CCER_CC3E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_2->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_2->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_2->CCMR2;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_OC3M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_OC3M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_CC3S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_CC3S_BIT1);

			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 4U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC3P_BIT);

			/* Set the Output N Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC3NP_BIT) ;

			/* Write to TIM CR2 */
			TIM_2->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR2 */
			TIM_2->CCMR2 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_2->CCR3 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_2->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel3 */
			SET_BIT (TIM_2->CCMR2 , TIM2_TO_TIM5_CCMR2_OC3PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_2->CCMR2 , TIM2_TO_TIM5_CCMR2_OC3FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_2-> CCER , TIM2_TO_TIM5_CCER_CC3E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_2 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_4)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 4: Reset the CC2E Bit */
			CLR_BIT(TIM_2->CCER , TIM2_TO_TIM5_CCER_CC4E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_2->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_2->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_2->CCMR2;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_OC4M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_OC4M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_CC4S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_CC4S_BIT1);

			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 12U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC4P_BIT);

			/* Write to TIM CR2 */
			TIM_2->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR2 */
			TIM_2->CCMR2 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_2->CCR4 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_2->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel4 */
			SET_BIT (TIM_2->CCMR2 , TIM2_TO_TIM5_CCMR2_OC4PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_2->CCMR2 , TIM2_TO_TIM5_CCMR2_OC4FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_2-> CCER , TIM2_TO_TIM5_CCER_CC4E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_2 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
	}
	else if (A_u8TimerSelected == TIM3_TYPE)
	{
		if (A_u8Channel == TIM_CHANNEL_1)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 1: Reset the CC1E Bit */
			CLR_BIT(TIM_3->CCER , TIM2_TO_TIM5_CCER_CC1E_BIT) ;

			/* Get the TIM CCER register value */
			L_u32TempCCMRX = TIM_3->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_3->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_3->CCMR1;

			/* Reset the Output Compare Mode Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC1M_BIT0) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC1M_BIT1) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC1M_BIT2) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC1S_BIT0) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC1S_BIT1) ;
			/* Select the Output Compare Mode1 */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 4U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC1P_BIT);

			/* Write to TIM CR2 */
			TIM_3->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR1 */
			TIM_3->CCMR1 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_3->CCR1 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_3->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel1 */
			SET_BIT (TIM_3->CCMR1 , TIM2_TO_TIM5_CCMR1_OC1PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_3->CCMR1 , TIM2_TO_TIM5_CCMR1_OC1FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_3-> CCER , TIM2_TO_TIM5_CCER_CC1E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_3 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_2)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
		    u32 L_u32TempCR2   = 0 ;

		    /* Disable the Channel 2: Reset the CC2E Bit */
		    CLR_BIT(TIM_3->CCER , TIM2_TO_TIM5_CCER_CC2E_BIT);

		    /* Get the TIM CCER register value */
		    L_u32TempCCER = TIM_3->CCER;
		    /* Get the TIM CR2 register value */
		    L_u32TempCR2 = TIM_3->CR2;

		    /* Get the TIM CCMR1 register value */
		    L_u32TempCCMRX = TIM_3->CCMR1;

		    /* Reset the Output Compare mode and Capture/Compare selection Bits */
		    CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT0);
		    CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT1);
		    CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT0);
		    CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT1);

		    /* Select the Output Compare Mode */
		    L_u32TempCCMRX |= (TIM_PWM_MODE1 << 12U) ;

		    /* Set the Output Compare Polarity as active high */
		    CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC2P_BIT);

		    /* Set the Output N Polarity as active high */
		    CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC2NP_BIT) ;

		    /* Write to TIM CR2 */
		    TIM_3->CR2 = L_u32TempCR2;

		    /* Write to TIM CCMR1 */
		    TIM_3->CCMR1 = L_u32TempCCMRX;

		    /* Set the Capture Compare Register value */
		    TIM_3->CCR2 = A_u16CompareValue;

		    /* Write to TIM CCER */
		    TIM_3->CCER = L_u32TempCCER;

		    /* Set the Preload enable bit for channel2 */
		    SET_BIT (TIM_3->CCMR1 , TIM2_TO_TIM5_CCMR1_OC2PE_BIT);

		    /* Configure the Output Fast mode */
		    SET_BIT (TIM_3->CCMR1 , TIM2_TO_TIM5_CCMR1_OC2FE_BIT) ;

		    /* Enable the Capture compare channel */
		    SET_BIT(TIM_3-> CCER , TIM2_TO_TIM5_CCER_CC2E_BIT) ;

		    /* Enable the timer */
		    SET_BIT(TIM_3 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_3)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 3: Reset the CC2E Bit */
            CLR_BIT(TIM_3->CCER , TIM2_TO_TIM5_CCER_CC3E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_3->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_3->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_3->CCMR2;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_OC3M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_OC3M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_CC3S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_CC3S_BIT1);

			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 <<4U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC3P_BIT);

			/* Set the Output N Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC3NP_BIT) ;

			/* Write to TIM CR2 */
			TIM_3->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR2 */
			TIM_3->CCMR2 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_3->CCR3 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_3->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel3 */
			SET_BIT (TIM_3->CCMR2 , TIM2_TO_TIM5_CCMR2_OC3PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_3->CCMR2 , TIM2_TO_TIM5_CCMR2_OC3FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_3-> CCER , TIM2_TO_TIM5_CCER_CC3E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_3 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_4)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 4: Reset the CC2E Bit */
			CLR_BIT(TIM_3->CCER , TIM2_TO_TIM5_CCER_CC4E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_3->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_3->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_3->CCMR2;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT1);

			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 12U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC4P_BIT);

			/* Write to TIM CR2 */
			TIM_3->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR2 */
			TIM_3->CCMR2 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_3->CCR4 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_3->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel4 */
			SET_BIT (TIM_3->CCMR2 , TIM2_TO_TIM5_CCMR2_OC4PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_3->CCMR2 , TIM2_TO_TIM5_CCMR2_OC4FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_3-> CCER , TIM2_TO_TIM5_CCER_CC4E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_3 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
	}
	else if (A_u8TimerSelected == TIM4_TYPE)
	{
		if (A_u8Channel == TIM_CHANNEL_1)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 1: Reset the CC1E Bit */
			CLR_BIT(TIM_4->CCER , TIM2_TO_TIM5_CCER_CC1E_BIT) ;

			/* Get the TIM CCER register value */
			L_u32TempCCMRX = TIM_4->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_4->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_4->CCMR1;

			/* Reset the Output Compare Mode Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC1M_BIT0) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC1M_BIT1) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC1M_BIT2) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC1S_BIT0) ;
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC1S_BIT1) ;
			/* Select the Output Compare Mode1 */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 4U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC1P_BIT);

			/* Write to TIM CR2 */
			TIM_4->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR1 */
			TIM_4->CCMR1 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_4->CCR1 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_4->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel1 */
			SET_BIT (TIM_4->CCMR1 , TIM2_TO_TIM5_CCMR1_OC1PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_4->CCMR1 , TIM2_TO_TIM5_CCMR1_OC1FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_4-> CCER , TIM2_TO_TIM5_CCER_CC1E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_4 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_2)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
		    u32 L_u32TempCR2   = 0 ;

		    /* Disable the Channel 2: Reset the CC2E Bit */
		    CLR_BIT(TIM_4->CCER , TIM2_TO_TIM5_CCER_CC2E_BIT);

		    /* Get the TIM CCER register value */
		    L_u32TempCCER = TIM_4->CCER;
		    /* Get the TIM CR2 register value */
		    L_u32TempCR2 = TIM_4->CR2;

		    /* Get the TIM CCMR1 register value */
		    L_u32TempCCMRX = TIM_4->CCMR1;

		    /* Reset the Output Compare mode and Capture/Compare selection Bits */
		    CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT0);
		    CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT1);
		    CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT0);
		    CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT1);

		    /* Select the Output Compare Mode */
		    L_u32TempCCMRX |= (TIM_PWM_MODE1 << 12U) ;

		    /* Set the Output Compare Polarity as active high */
		    CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC2P_BIT);

		    /* Set the Output N Polarity as active high */
		    CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC2NP_BIT) ;

		    /* Write to TIM CR2 */
		    TIM_4->CR2 = L_u32TempCR2;

		    /* Write to TIM CCMR1 */
		    TIM_4->CCMR1 = L_u32TempCCMRX;

		    /* Set the Capture Compare Register value */
		    TIM_4->CCR2 = A_u16CompareValue;

		    /* Write to TIM CCER */
		    TIM_4->CCER = L_u32TempCCER;

		    /* Set the Preload enable bit for channel2 */
		    SET_BIT (TIM_4->CCMR1 , TIM2_TO_TIM5_CCMR1_OC2PE_BIT);

		    /* Configure the Output Fast mode */
		    SET_BIT (TIM_4->CCMR1 , TIM2_TO_TIM5_CCMR1_OC2FE_BIT) ;

		    /* Enable the Capture compare channel */
		    SET_BIT(TIM_4-> CCER , TIM2_TO_TIM5_CCER_CC2E_BIT) ;

		    /* Enable the timer */
		    SET_BIT(TIM_4 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_3)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 3: Reset the CC2E Bit */
			CLR_BIT(TIM_4->CCER , TIM2_TO_TIM5_CCER_CC3E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_4->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_4->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_4->CCMR2;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_OC3M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_OC3M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_CC3S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR2_CC3S_BIT1);

			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 4U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC3P_BIT);

			/* Set the Output N Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC3NP_BIT) ;

			/* Write to TIM CR2 */
			TIM_4->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR2 */
			TIM_4->CCMR2 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_4->CCR3 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_4->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel3 */
			SET_BIT (TIM_4->CCMR2 , TIM2_TO_TIM5_CCMR2_OC3PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_4->CCMR2 , TIM2_TO_TIM5_CCMR2_OC3FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_4-> CCER , TIM2_TO_TIM5_CCER_CC3E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_4 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
		else if (A_u8Channel == TIM_CHANNEL_4)
		{
			u32 L_u32TempCCMRX = 0 ;
			u32 L_u32TempCCER  = 0 ;
			u32 L_u32TempCR2   = 0 ;

			/* Disable the Channel 4: Reset the CC2E Bit */
			CLR_BIT(TIM_4->CCER , TIM2_TO_TIM5_CCER_CC4E_BIT);

			/* Get the TIM CCER register value */
			L_u32TempCCER = TIM_4->CCER;
			/* Get the TIM CR2 register value */
			L_u32TempCR2 = TIM_4->CR2;

			/* Get the TIM CCMR1 register value */
			L_u32TempCCMRX = TIM_4->CCMR2;

			/* Reset the Output Compare mode and Capture/Compare selection Bits */
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_OC2M_BIT1);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT0);
			CLR_BIT(L_u32TempCCMRX , TIM2_TO_TIM5_CCMR1_CC2S_BIT1);

			/* Select the Output Compare Mode */
			L_u32TempCCMRX |= (TIM_PWM_MODE1 << 12U) ;

			/* Set the Output Compare Polarity as active high */
			CLR_BIT(L_u32TempCCER , TIM2_TO_TIM5_CCER_CC4P_BIT);

			/* Write to TIM CR2 */
			TIM_4->CR2 = L_u32TempCR2;

			/* Write to TIM CCMR2 */
			TIM_4->CCMR2 = L_u32TempCCMRX;

			/* Set the Capture Compare Register value */
			TIM_4->CCR4 = A_u16CompareValue;

			/* Write to TIM CCER */
			TIM_4->CCER = L_u32TempCCER;

			/* Set the Preload enable bit for channel4 */
			SET_BIT (TIM_4->CCMR2 , TIM2_TO_TIM5_CCMR2_OC4PE_BIT);

			/* Configure the Output Fast mode */
			SET_BIT (TIM_4->CCMR2 , TIM2_TO_TIM5_CCMR2_OC4FE_BIT) ;

			/* Enable the Capture compare channel */
			SET_BIT(TIM_4-> CCER , TIM2_TO_TIM5_CCER_CC4E_BIT) ;

			/* Enable the timer */
			SET_BIT(TIM_4 -> CR1 , TIM2_TO_TIM5_CR1_CEN_BIT) ;
		}
	}
	else
	{
		// error type of A_u8TimerSelected
	}
}
