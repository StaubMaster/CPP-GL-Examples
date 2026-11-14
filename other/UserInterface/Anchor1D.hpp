#ifndef  ANCHOR_1D_HPP
# define ANCHOR_1D_HPP

struct BoxF1;

enum class AnchorType : unsigned char;

struct refBoxF1
{
	float & Min;
	float & Max;
	refBoxF1(float & min, float & max);
};

struct Anchor1D
{
	private:
	float &		Size;
	refBoxF1	Dist;
	//refBoxF1	Margin;
	//refBoxF1	Boarder;
	//refBoxF1	Padding;
	float &		NormalCenter;

	public:
	AnchorType	Anchor;

	Anchor1D(
		float & size,
		refBoxF1 dist,
		//refBoxF1 margin,
		//refBoxF1 boarder,
		//refBoxF1 padding,
		float & normal_center
	);

	public:
	//float	GetMarginMinDist() const;
	//float	GetMarginMinSize() const;
	//float	GetMarginMaxDist() const;
	//float	GetMarginMaxSize() const;

	public:
	//void	SetMarginMinDist(float val);
	//void	SetMarginMinSize(float val);
	//void	SetMarginMaxDist(float val);
	//void	SetMarginMaxSize(float val);

	public:
	//float	AnchorMarginMin(float dist);
	//float	AnchorMarginMin(float dist, float size);
	//float	AnchorMarginMax(float dist);
	//float	AnchorMarginMax(float dist, float size);
	//void	AnchorMarginBoth(float min, float max); // return Size ?

	private:
	void	ChangeO_Size(float sizeO);
	void	ChangeO_NormalCenter(float sizeO);

	public:
	void	UpdateO(const BoxF1 & boxO);
	void	UpdateO(const BoxF1 & boxO, const BoxF1 & boxI);

	public:
	BoxF1	ToInnerBox(const BoxF1 & boxO) const;
};

#endif