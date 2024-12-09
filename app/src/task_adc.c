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
 * @file   : task_adc.c
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

/********************** macros and definitions *******************************/
#define TEST_NUMBER TEST_1 //TEST_1, TEST_2, TEST_3


#define SAMPLES_COUNTER (100)
#define AVERAGER_SIZE (16)

/********************** internal data declaration ****************************/
uint32_t tickstart;
uint16_t sample_idx;

/********************** internal functions declaration ***********************/
/********************** internal functions definitions ***********************/
bool test1_tick();

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef ADC_Poll_Read(uint16_t *value);

/********************** internal data definition *****************************/
const char *p_task_adc 		= "Task ADC";

/********************** external data declaration *****************************/

extern ADC_HandleTypeDef hadc1;

/********************** external functions definition ************************/
void task_adc_init(void *parameters)
{

	sample_idx = 0;
	tickstart = HAL_GetTick();
	/* Print out: Task Initialized */
	LOGGER_LOG("  %s is running - %s\r\n", GET_NAME(task_adc_init), p_task_adc);

}

void task_adc_update(void *parameters)
{
//	static bool b_test_done = false;
//	b_test_done = test1_tick();
//	if (b_test_done) {
//		LOGGER_LOG("Test #%u ends. Ticks: %lu\n", TEST_NUMBER, HAL_GetTick()-tickstart);
//	}


}

HAL_StatusTypeDef ADC_Poll_Read(uint16_t *value) {
	HAL_StatusTypeDef res;

	res=HAL_ADC_Start(&hadc1);
	if ( HAL_OK==res ) {
		res=HAL_ADC_PollForConversion(&hadc1, 0);
		if ( HAL_OK==res ) {
			*value = HAL_ADC_GetValue(&hadc1);
		}
	}
	return res;
}


bool test1_tick() {

	uint16_t value;
	bool b_done = false;

	if (sample_idx>=SAMPLES_COUNTER) {
		b_done = true;
		goto test1_tick_end;
	}

	if (HAL_OK==ADC_Poll_Read(&value)) {
		LOGGER_LOG("%u\n", value);
	}
	else
	{
		LOGGER_LOG("error\n");
	}
	sample_idx++;
test1_tick_end:
	return b_done;
}





/********************** end of file ******************************************/
