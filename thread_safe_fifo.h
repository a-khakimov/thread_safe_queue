/*
 * thread_safe_fifo.h
 *
 *  Created on: 14.02.2020
 *      Author: a.khakimov
 */

#ifndef THREAD_SAFE_FIFO_H_
#define THREAD_SAFE_FIFO_H_

#include <sys/types.h>
#include <stdint.h>

struct thread_safe_fifo_t;

#ifdef __cplusplus
extern "C" {
#endif

int 	thread_safe_fifo_init		(struct thread_safe_fifo_t**				);
int 	thread_safe_fifo_destroy	(struct thread_safe_fifo_t**				);
void 	thread_safe_fifo_try_push	(struct thread_safe_fifo_t*, const uint8_t	);
uint8_t thread_safe_fifo_try_pop	(struct thread_safe_fifo_t*					);
size_t 	thread_safe_fifo_size		(struct thread_safe_fifo_t* 				);
bool 	thread_safe_fifo_empty		(struct thread_safe_fifo_t*					);

#ifdef __cplusplus
}
#endif

#endif /* THREAD_SAFE_FIFO_H_ */
