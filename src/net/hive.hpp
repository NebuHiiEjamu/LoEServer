#ifndef _HIVE_H
#define _HIVE_H

#include <atomic>
#include <boost/asio.hpp>
#include <memory>

class Hive : public std::enable_shared_from_this<Hive>
{
public:
	Hive();
	boost::asio::io_context& getIOContext();
	bool stopped();
	void poll();
	void run();
	void stop();
	void reset();
private:
	boost::asio::io_context ioContext;
	std::shared_ptr<boost::asio::executor_work_guard
		<boost::asio::io_context::executor_type>> workGuard;
	std::atomic_uint32_t shutdownSignal;
};

#endif // _HIVE_H
