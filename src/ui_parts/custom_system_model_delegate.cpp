// custom_system_model_delegate.cpp
#include <QPainterPath>
#include <QPen>
#include <QStyleOptionButton>
#include <QPushButton>
#include <QStyle>

#include "custom_system_model_delegate.h"

CustomSystemModelDelegate::CustomSystemModelDelegate(QObject* parent)
	: QStyledItemDelegate(parent)
{}

void CustomSystemModelDelegate::paint(
	QPainter* painter,
	const QStyleOptionViewItem& option,
	const QModelIndex& index
) const
{
	if (!index.isValid())
	{
		return;
	}

	const bool isInProgress = index.data(CustomRoles::InProgressRole).toBool();
	const bool hasSize = !index.data(Qt::DisplayRole).toString().isEmpty();

	// size already calculated and not in progress => use parent paint.
	if (hasSize && !isInProgress)
	{
		QStyledItemDelegate::paint(painter, option, index);
		return;
	}

	ButtonState state
	{
		static_cast<bool>(option.state & QStyle::State_MouseOver),
		static_cast<bool>(option.state & QStyle::State_Selected),
		isInProgress
	};

	m_paintButton(painter, option, state);
}

void CustomSystemModelDelegate::m_paintButton(
	QPainter* painter,
	const QStyleOptionViewItem& option,
	const ButtonState& state
) const
{
	static const QPushButton tempButton;

	painter->save();
	painter->setRenderHint(QPainter::Antialiasing);


	QStyleOptionButton buttonOption;
	buttonOption.initFrom(&tempButton);
	buttonOption.rect = option.rect.adjusted(0, 0, 0, 0);
	buttonOption.text = state.isInProgress
		? kInProccessButtonText
		: kCalculateButtonText;

	if (state.isSelected || state.isHovered)
	{
		buttonOption.state |= QStyle::State_MouseOver;
	}

	if (state.isInProgress)
	{
		buttonOption.state |= QStyle::State_Sunken;
	}

	QApplication::style()->drawControl(
		QStyle::CE_PushButton,
		&buttonOption,
		painter,
		&tempButton
	);

	painter->restore();
}
