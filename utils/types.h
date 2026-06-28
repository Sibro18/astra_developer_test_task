#ifndef MY_TYPES
#define MY_TYPES

#include <atomic>
#include <Qt>

struct StopFlag
{
public:
	inline StopFlag()
	{
		setFlag(false);
	}

	inline void setFlag(bool flag)
	{
		m_flag.store(flag);
	}

	inline bool value() const
	{
		return m_flag.load();
	}
private:
	std::atomic<bool> m_flag;
};

struct ButtonState
{
	bool isHovered;
	bool isSelected;
	bool isInProgress;
};

enum CustomRoles
{
	InProgressRole = Qt::UserRole + 1,
	SizeInBytesRole = Qt::UserRole + 2
};

#endif // MY_TYPES
