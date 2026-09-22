#ifndef  AUX_THREAD_0_HPP
# define AUX_THREAD_0_HPP

# include "AuxThreadBase.hpp"

struct ContextNoisePlane;

struct AuxThread0 : public AuxThreadBase
{
	ContextNoisePlane &		Context;

	~AuxThread0() = default;
	AuxThread0() = delete;
	AuxThread0(const AuxThread0 & other) = delete;
	AuxThread0 & operator=(const AuxThread0 & other) = delete;
	AuxThread0(ContextNoisePlane & context);

	bool	CheckFunc() override;
	void	DoFunc() override;
};

#endif