#ifndef  UI_CONTROL_CONTROL_USER_RELAY_HPP
# define UI_CONTROL_CONTROL_USER_RELAY_HPP

struct MoveArgs;
struct HoverArgs;
struct ClickArgs;
struct ScrollArgs;
struct DragArgs;
struct KeyArgs;
struct TextArgs;

namespace UI
{
namespace Control
{
class Control_UserRelay
{
	public:
	virtual ~Control_UserRelay() = default; // make this non virtual ?
	Control_UserRelay() = default;
	Control_UserRelay(const Control_UserRelay & other) = delete;
	Control_UserRelay & operator=(const Control_UserRelay & other) = delete;

	/* User Relay
		these should only be called automatically by the Window/Manager
		these change the Controll internally,
		and might call Function Pointers for external stuff
		they should not be accessible to the outside
		they should not be called from inside the Control
	*/
	/* User Relay Invoker
		(const void *) or (const Control::Base *)
		not const ?
		? the Invoker Control is this
		the Control Pointer would be needed for Func Pointers
	*/
	/* User Relay return
		0: dont try to relay to parent
		1: try to relay this event to parent
	*/

	public:
	virtual void	RelayHover(HoverArgs args);
	virtual void	RelayClick(ClickArgs args);
	virtual void	RelayScroll(ScrollArgs args);
	virtual void	RelayDrag(DragArgs args);
	virtual void	RelayKey(KeyArgs args);
	virtual void	RelayText(TextArgs args);
	// make args const & ?
};
};
};

#endif