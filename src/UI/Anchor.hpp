#ifndef  ANCHOR_HPP
# define ANCHOR_HPP



struct AxisBox1D;
struct AxisBox2D;



enum class AnchorType : unsigned char
{
	None	= 0b00,
	Min		= 0b01,
	Max		= 0b10,
	Both	= 0b11,
};



struct Anchor1D
{
	private:
	float & Size;
	float & MinDist;
	float & MaxDist;
	float & NormalCenter;

	float & MinPadding;
	float & MaxPadding;

	public:
	AnchorType Anchor;

	Anchor1D(float & size, float & min_dist, float & max_dist, float & normal_center, float & min_padding, float & max_padding);



	float GetSize();
	float GetMinDist();
	float GetMaxDist();
	float GetNormalCenter();

	float GetHalfSize();
	float GetMinSize();
	float GetMaxSize();
	float GetCenter();



	void SetSize(float val);
	void SetMinDist(float val);
	void SetMaxDist(float val);
	void SetNormalCenter(float val);

	void SetHalfSize(float val);
	void SetMinSize(float val);
	void SetMaxSize(float val);
	void SetCenter(float val);



	float GetPaddedSize();
	float GetPaddedMinDist();
	float GetPaddedMaxDist();

	float GetPaddedHalfSize();
	float GetPaddedMinSize();
	float GetPaddedMaxSize();



	void SetPaddedSize(float val);
	void SetPaddedMinDist(float val);
	void SetPaddedMaxDist(float val);

	void SetPaddedHalfSize(float val);
	void SetPaddedMinSize(float val);
	void SetPaddedMaxSize(float val);



	

	AxisBox1D Calculate(AxisBox1D Parent);
};



struct Anchor2D
{
	Anchor1D X;
	Anchor1D Y;

	Anchor2D(Anchor1D x, Anchor1D y);

	AxisBox2D Calculate(AxisBox2D Parent);
};



#endif