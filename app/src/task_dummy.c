/*
 * Copyright (c) 2023 Juan Manuel Cruz <jcruz@fi.uba.ar> <jcruz@frba.utn.edu.ar>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * @file   : task_dummy.c
 * @date   : Set 26, 2023
 * @author : Juan Manuel Cruz <jcruz@fi.uba.ar> <jcruz@frba.utn.edu.ar>
 * @version	v1.0.0
 */

/********************** inclusions *******************************************/
/* Project includes. */
#include "main.h"

/* Demo includes. */
#include "logger.h"
#include "dwt.h"

/* Application & Tasks includes. */
#include "board.h"
#include "app.h"
#include "task_pwm.h"
#include "task_adc.h"

/********************** macros and definitions *******************************/
#define TEST_NUMBER TEST_1 //TEST_1, TEST_2, TEST_3


#define SAMPLES_COUNTER (100)
#define AVERAGER_SIZE (16)

#define DELAY_TICKS (4)
#define STEP (100)
#define PERIOD (65535)

/********************** internal data declaration ****************************/
//uint32_t tickstart;
uint16_t sample;

/********************** internal functions declaration ***********************/
void test1_tick_PWM(uint16_t muestras);
/********************** internal data definition *****************************/
const char *p_task_dummy 		= "Task Dummy";

/********************** external data declaration *****************************/


/********************** external functions definition ************************/
void task_dummy_init(void *parameters)
{
	/* Print out: Task Initialized */
	LOGGER_LOG("  %s is running - %s\r\n", GET_NAME(task_c_init), p_task_dummy);

}

void task_dummy_update(void *parameters)
{
	//PARTE DEL ADC
		uint16_t value;

		if (sample>=SAMPLES_COUNTER) {
			goto test1_tick_end;
		}

		if (HAL_OK==ADC_Poll_Read(&value)) {
			LOGGER_LOG("%u\n", value);
		}
		else
		{
			LOGGER_LOG("error\n");
		}
		sample++;
		test1_tick_end:
		test1_tick_PWM(value);


}


void test1_tick_PWM(uint16_t muestras) {
    static uint32_t tick;
    static bool first = true;

    if (first) {
        first = false;
        tick = HAL_GetTick() + DELAY_TICKS; // Inicializar el tick
    }

    if (HAL_GetTick() >= tick) {
        // Generar señal PWM con ancho proporcional a "muestras"
        setPWM(htim3, TIM_CHANNEL_1, PERIOD, muestras);

        // Actualizar el tick para el siguiente ciclo
        tick = HAL_GetTick() + DELAY_TICKS;
    }
}





/********************** end of file ******************************************/
