// custom_system_model_delegate.h
#ifndef CUSTOM_SYSTEM_MODEL_DELEGATE_H
#define CUSTOM_SYSTEM_MODEL_DELEGATE_H

#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QPainter>
#include <QColor>
#include <QApplication>
#include <QPalette>

#include "utils/types.h"

class CustomSystemModelDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	explicit CustomSystemModelDelegate(QObject* parent = nullptr);
	void paint(
		QPainter* painter,
		const QStyleOptionViewItem& option,
		const QModelIndex& index
	) const override;

private:
	void m_paintButton(
		QPainter* painter,
		const QStyleOptionViewItem& option,
		const ButtonState& state
	) const;

	static constexpr const char* kInProccessButtonText = "Processing";
	static constexpr const char* kCalculateButtonText = "Calculate";
};

#endif // CUSTOM_SYSTEM_MODEL_DELEGATE_H
