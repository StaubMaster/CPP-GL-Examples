#ifndef  STOP_WATCH_HPP
# define STOP_WATCH_HPP

class StopWatch
{
	private:
	bool	Running;
	double	TimeStamp;
	double	TimeSum;

	public:
	bool	IsRunning() const;
	double	ElapsedTime() const;

	public:
	~StopWatch();
	StopWatch();

	public:
	void	Clear();
	void	Stop();
	void	Start();
	void	TakeOver(StopWatch & other);
};

#endif