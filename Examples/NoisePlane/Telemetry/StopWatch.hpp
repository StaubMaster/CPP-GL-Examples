#ifndef  STOP_WATCH_HPP
# define STOP_WATCH_HPP

class StopWatch
{
	private:
	bool	Watching;
	double	Time0;
	double	Time1;

	public:
	bool	IsWatching() const;
	double	ElapsedTime() const;

	public:
	~StopWatch();
	StopWatch();

	public:
	void	Stop();
	void	Start();
	void	ReStart();
};

#endif