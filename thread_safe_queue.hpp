template<typename T>
class thread_safe_fifo
{
public:
	thread_safe_fifo() {
		pthread_mutex_init(&m_lock, NULL);
	}
	virtual ~thread_safe_fifo() {
		pthread_mutex_destroy(&m_lock);
	}
	void try_push(T t) {
		pthread_mutex_lock(&m_lock);
		m_queue.push(t);
		pthread_mutex_unlock(&m_lock);
	}
	T try_pop() {
		pthread_mutex_lock(&m_lock);
		const T res = m_queue.front();
		m_queue.pop();
		pthread_mutex_unlock(&m_lock);
		return res;
	}
	size_t size() const {
		return m_queue.size();
	}
	bool empty() const {
		return m_queue.empty();
	}

private:
	std::queue<T> m_queue;
	pthread_mutex_t m_lock;
};

