#include "custom_sort_filter_proxy_model.h"
#include "utils/types.h"

CustomSortFilterProxyModel::CustomSortFilterProxyModel(QObject* parent)
	: QSortFilterProxyModel(parent)
{}

bool CustomSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
	// Guard against an unrepresented index.
	if (!source_parent.isValid())
	{
		return false;
	}

	return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}

bool CustomSortFilterProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
	int column = source_left.column();

	if (column == 1)
	{
		auto leftSize = sourceModel()->data(source_left, CustomRoles::SizeInBytesRole).toLongLong();
		auto rightSize = sourceModel()->data(source_right, CustomRoles::SizeInBytesRole).toLongLong();

		return leftSize < rightSize;
	}

	return QSortFilterProxyModel::lessThan(source_left, source_right);
}
