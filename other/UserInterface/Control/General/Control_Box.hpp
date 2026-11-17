#ifndef  UI_CONTROL_CONTROL_BOX_HPP
# define UI_CONTROL_CONTROL_BOX_HPP

# include "Anchor2D.hpp"
# include "ValueType/_Include.hpp"

namespace UI
{
class Control_Box
{
	protected: public:
	VectorF2	AnchorSize;
	BoxF2		AnchorDist;
	VectorF2	AnchorNormal;
	protected: public:
	BoxF2		AnchorMargin;
	BoxF2		AnchorBoarder;
	BoxF2		AnchorPadding;
	protected: public:
	//VectorF2	AnchorOffset; ?
	protected: public:
	Anchor2D	Anchor;

	private: public:
	float	PaddingBox_Get_X_Size() const;
	float	PaddingBox_Get_Y_Size() const;

	private: public:
	void	PaddingBox_Set_X_Size(float val);
	void	PaddingBox_Set_Y_Size(float val);

	private: public:
	float	MarginBox_Get_X_Min_Min() const;
	float	MarginBox_Get_X_Min_Max() const;
	float	MarginBox_Get_X_Max_Min() const;
	float	MarginBox_Get_X_Max_Max() const;
	float	MarginBox_Get_Y_Min_Min() const;
	float	MarginBox_Get_Y_Min_Max() const;
	float	MarginBox_Get_Y_Max_Min() const;
	float	MarginBox_Get_Y_Max_Max() const;

	private: public:
	void	MarginBox_Set_X_Min_Min(float val);
	void	MarginBox_Set_X_Min_Max(float val);
	void	MarginBox_Set_X_Max_Min(float val);
	void	MarginBox_Set_X_Max_Max(float val);
	void	MarginBox_Set_Y_Min_Min(float val);
	void	MarginBox_Set_Y_Min_Max(float val);
	void	MarginBox_Set_Y_Max_Min(float val);
	void	MarginBox_Set_Y_Max_Max(float val);

	public:
	void	Make_Anchor_X_Min(const Control_Box * other);
	void	Make_Anchor_X_Min(const Control_Box * other, float size);
	void	Make_Anchor_X_Max(const Control_Box * other);
	void	Make_Anchor_X_Max(const Control_Box * other, float size);
	void	Make_Anchor_X_Both(const Control_Box * other_min, const Control_Box * other_max);

	public:
	void	Make_Anchor_Y_Min(const Control_Box * other);
	void	Make_Anchor_Y_Min(const Control_Box * other, float size);
	void	Make_Anchor_Y_Max(const Control_Box * other);
	void	Make_Anchor_Y_Max(const Control_Box * other, float size);
	void	Make_Anchor_Y_Both(const Control_Box * other_min, const Control_Box * other_max);

	private: protected:		bool			AnchorUpdateIsRequested = false;
	public:		void			AnchorUpdateRequest();
	protected:	virtual	void	AnchorUpdate();



//	private:	bool			BoxUpdateIsRequested = false;
//	public:		void			BoxUpdateRequest();
//	protected:	virtual	void	BoxUpdate();

//	protected: public:
//	BoxF2	BoxDisplay; // used for displaying Control
//	BoxF2	BoxBoarder; // used for culling Children
//	BoxF2	BoxContent; // used for anchoring Children

	protected:
	virtual bool	MetaIs() const = 0;
	virtual BoxF2	MetaBoxBoarder() const = 0;
	virtual BoxF2	MetaBoxContent() const = 0;

	public:
	BoxF2	BoxDisplay() const; // used for displaying Control
	BoxF2	BoxBoarder() const; // used for culling Children
	BoxF2	BoxContent() const; // used for anchoring Children



	public:
	enum class EAutoAnchorType
	{
		None,
		StackMin,		//next.MinDist = prev.MinSize
		//StackMinFit,	//next.MinDist = prev.MinSize but this.Size is made to Fit
	};
	EAutoAnchorType		AutoAnchorXType = EAutoAnchorType::None;
	EAutoAnchorType		AutoAnchorYType = EAutoAnchorType::None;

	private: protected:		bool	AutoAnchorUpdateIsRequested = false;
	public:			void	AutoAnchorUpdateRequest();
	public:	virtual	void	AutoAnchorUpdate();

	private:	virtual	void	AutoAnchorUpdate_Y_StackMin() = 0;
//	private:			void	AutoAnchorUpdate_Y_StackMinFit();

	/* should Children be able to effect Parent ?
		normal Controls dont do that ?
		the only ones I can think of are HTML
		HTML is very complex
		Controls can have Maximum and Minimum Sizes
		they also auto arange themselves
		which is what I want
		changing Children to is easy
		maybe make another to automatically make all Children use the "Both" Anchor
		making the Parent fit the Children is not really needed
	*/
	public:		virtual	void	AutoFitMinY() = 0;
	/* replace Fit
		make FitX() and FitY() functions
		changes Size to fit the highest / lowest Children
		checking for lowest child only makes sense if they are stacked from highest
		Make_Anchor_X_Fit_Min()
		{
			finds Max Child
			chanes Size to fit that
		}
	*/

	public:
	virtual ~Control_Box() = default;
	Control_Box();
	Control_Box(const Control_Box & other) = delete;
	Control_Box & operator=(const Control_Box & other) = delete;
};
};

#endif