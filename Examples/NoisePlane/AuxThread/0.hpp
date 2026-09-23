#ifndef  AUX_THREAD_0_HPP
# define AUX_THREAD_0_HPP

# include "IdleLoopThread.hpp"

struct ContextNoisePlane;

# include "Telemetry/StopWatch.hpp"

struct AuxThread0 : public IdleLoopThread
{
	ContextNoisePlane &		Context;

	~AuxThread0() = default;
	AuxThread0() = delete;
	AuxThread0(const AuxThread0 & other) = delete;
	AuxThread0 & operator=(const AuxThread0 & other) = delete;
	AuxThread0(ContextNoisePlane & context);

		StopWatch sw;

	bool	CheckFunc() override;
	void	DoFunc() override;
};

#endif