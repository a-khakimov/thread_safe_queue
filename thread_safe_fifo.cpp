/*
 * thread_safe_fifo.cpp
 *
 *  Created on: 14.02.2020
 *      Author: a.khakimov
 */

#include "thread_safe_fifo.h"
#include <pthread.h>
#include <errno.h>
#include <stdio.h>

#include <queue>

struct thread_safe_fifo_t
{
	std::queue<uint8_t> queue;
	pthread_mutex_t mutex;
};


int thread_safe_fifo_init(struct thread_safe_fifo_t** fifo)
{
	(*fifo) = new thread_safe_fifo_t;
	return pthread_mutex_init(&(**fifo).mutex, NULL);
}

int thread_safe_fifo_destroy(struct thread_safe_fifo_t** fifo)
{
	int ret = pthread_mutex_destroy(&(**fifo).mutex);
	delete (*fifo);
	*fifo = NULL;
	return ret;
}

void thread_safe_fifo_try_push(struct thread_safe_fifo_t* fifo, const uint8_t data)
{
	if (fifo == NULL) {
		return;
	}
	pthread_mutex_lock(&fifo->mutex);
	fifo->queue.push(data);
	pthread_mutex_unlock(&fifo->mutex);
}

uint8_t thread_safe_fifo_try_pop(struct thread_safe_fifo_t* fifo)
{
	if (fifo == NULL) {
		return -1;
	}
	pthread_mutex_lock(&fifo->mutex);
	const uint8_t data = fifo->queue.front();
	fifo->queue.pop();
	pthread_mutex_unlock(&fifo->mutex);
	return data;
}

size_t thread_safe_fifo_size(struct thread_safe_fifo_t* fifo)
{
	return fifo->queue.size();
}

bool thread_safe_fifo_empty(struct thread_safe_fifo_t* fifo)
{
	return fifo->queue.empty();
}
