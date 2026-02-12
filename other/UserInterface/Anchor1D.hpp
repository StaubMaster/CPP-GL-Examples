#ifndef  ANCHOR_1D_HPP
# define ANCHOR_1D_HPP

struct AxisBox1D;
enum class AnchorType : unsigned char;

/*	do I ever not use the Padded numbers ?
if I dont want to have Padding, I can setReal it to 0
if I introduce Margin for the Parents
and I dont want a Margin to that Parent from the child:
"suck to suck" ?
of just subtract the Parent Margin
the point of the Padding is that I dont have to worry about it
so having to specify, that I want the Padded values defeats the point of that
obviously have the real values internally, but make them private

but when I add Boarders, should that specify the inside or the outside ?
right now it is tecnically the outside, so just keep doing that
*/

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

/*
	Stored			Calculated
	----------------------------#
	Size			HalfSize	|	should these be Padded ?
	MinDist			MinSize		|	Padding is for Distance
	MaxDist			MaxSize		|	Padding is for Distance
	NormalCenter	Center		|	might change if Padding is not Equal
	----------------------------#
	Sizes Normal means the Space it Displays in
	Sizes Padded means the Space it takes up
*/

	private:
	float GetRealSize();
	float GetRealHalfSize();
	float GetRealMinDist();
	float GetRealMinSize();
	float GetRealMaxDist();
	float GetRealMaxSize();
	float GetRealNormalCenter();
	float GetRealCenter();



	private:
	void SetRealSize(float val);
	void SetRealHalfSize(float val);
	void SetRealMinDist(float val);
	void SetRealMinSize(float val);
	void SetRealMaxDist(float val);
	void SetRealMaxSize(float val);
	void SetRealNormalCenter(float val);
	void SetRealCenter(float val);



	private:
	float GetPaddedSize();
	float GetPaddedHalfSize();
	float GetPaddedMinDist();
	float GetPaddedMinSize();
	float GetPaddedMaxDist();
	float GetPaddedMaxSize();

	private:
	void SetPaddedSize(float val);
	void SetPaddedHalfSize(float val);
	void SetPaddedMinDist(float val);
	void SetPaddedMinSize(float val);
	void SetPaddedMaxDist(float val);
	void SetPaddedMaxSize(float val);



	public:
	float GetSize();
//	float GetHalfSize();
	float GetMinDist();
	float GetMinSize();
	float GetMaxDist();
	float GetMaxSize();
//	float GetNormalCenter();
//	float GetCenter();

	public:
	void SetSize(float val);
//	void SetHalfSize(float val);
	void SetMinDist(float val);
	void SetMinSize(float val);
	void SetMaxDist(float val);
	void SetMaxSize(float val);
//	void SetNormalCenter(float val);
//	void SetCenter(float val);



	void	AnchorMin(float dist);
	void	AnchorMin(float dist, float size);
	void	AnchorMax(float dist);
	void	AnchorMax(float dist, float size);
	void	AnchorBoth(float min, float max);

	AxisBox1D Calculate(AxisBox1D Parent);
};

#endif