#ifndef  ANCHOR_AXIS_HPP
# define ANCHOR_AXIS_HPP

struct BoxF1;

enum class AnchorType : unsigned char;

struct AnchorAxis
{
	private:
	float &		Size;
	float &		DistMin;
	float &		DistMax;
	float &		NormalCenter;

	public:
	AnchorType	Anchor;

	AnchorAxis(
		float & size,
		float & dist_min,
		float & dist_max,
		float & normal_center
	);

	public:
	void	ChangeBox(
		float boxO_min,
		float boxO_max,
		float boxI_min,
		float boxI_max
	);
	void	Update(float size);
};

#endif