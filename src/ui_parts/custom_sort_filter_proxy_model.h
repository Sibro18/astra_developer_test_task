#ifndef CUSTOM_SORT_FILTER_PROXY_MODEL_H
#define CUSTOM_SORT_FILTER_PROXY_MODEL_H

#include <QSortFilterProxyModel>
#include <QModelIndex>

class CustomSortFilterProxyModel : public QSortFilterProxyModel
{
public:
	explicit CustomSortFilterProxyModel(QObject *parent = nullptr);
protected:
	bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const override;
	bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;
};

#endif // CUSTOM_SORT_FILTER_PROXY_MODEL_H
