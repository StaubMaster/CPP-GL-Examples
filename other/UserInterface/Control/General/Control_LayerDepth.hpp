#ifndef  UI_CONTROL_CONTROL_LAYER_DEPTH_HPP
# define UI_CONTROL_CONTROL_LAYER_DEPTH_HPP

namespace UI
{
class Control_LayerDepth
{
//	private:	unsigned int	Layer_ = 0;
//	public:		unsigned int	Layer() const;
//	public:		void			LayerUpdate();
//	public:		void			LayerUpdateRecursive();
	public:		virtual	unsigned int	Layer() const = 0;

	public:		virtual	unsigned int	LayerLimit() const = 0;

//	protected:	float			Depth_ = 0.0f;
//	public:		float			Depth() const;
//	public:		virtual	void	DepthUpdate();
//	protected:			void	DepthUpdateRecursive();
//	public:		float			Depth() const;
	public:		virtual float	Depth(float depth = 0.0f) const = 0;
};
};

#endif