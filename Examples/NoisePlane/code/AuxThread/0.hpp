#ifndef  AUX_THREAD_0_HPP
# define AUX_THREAD_0_HPP

# include "Threading/Thread/Loop/Tick.hpp"

struct ContextNoisePlane;

# include "Telemetry/StopWatch.hpp"

struct AuxThread0 : public TickLoopThread
{
	ContextNoisePlane &		Context;

	~AuxThread0() = default;
	AuxThread0() = delete;
	AuxThread0(const AuxThread0 & other) = delete;
	AuxThread0 & operator=(const AuxThread0 & other) = delete;
	AuxThread0(ContextNoisePlane & context);

		StopWatch sw;

	void	DoFunc() override;
};

#endif