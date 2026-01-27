#ifndef  BASE_CALLBACK_HPP
# define BASE_CALLBACK_HPP

template<typename ... Arguments>
struct BaseCallBack
{
	BaseCallBack()
	{ }
	virtual ~BaseCallBack()
	{ }

	virtual void Run(Arguments ... args) = 0;
};

#endif