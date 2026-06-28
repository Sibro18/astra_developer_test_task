#ifndef CUSTOM_SYSTEM_MODEL_H
#define CUSTOM_SYSTEM_MODEL_H

#include <QFileSystemModel>
#include <QVariant>
#include <QModelIndex>
#include <QThreadPool>
#include <QReadWriteLock>
#include <QHash>
#include <QSet>

#include "utils/file_utils.h"
#include "utils/types.h"

class CustomSystemModel : public QFileSystemModel
{
	Q_OBJECT
public:
	CustomSystemModel(QThreadPool* threadPool, StopFlag* _stopFlag, QObject* parent = nullptr);
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	void calculateAndSetDirSize(const QModelIndex& index);
private:
	mutable QReadWriteLock m_cacheMutex;
	QHash<QString, qint64> m_sizeCache;
	QSet<QString> m_inProgress;
	StopFlag* m_stopFlag;
	QThreadPool* m_thPool;

	QVariant m_getRawSize(const QModelIndex& index) const;
	QVariant m_getInProgressStatus(const QModelIndex& index) const;
	QVariant m_getFormattedSize(const QModelIndex& index, int role) const;
	void m_removeFromInProgress(const QString& path);

	static constexpr qint64 kDefaultDirSizeValue = -1;
};

#endif // CUSTOM_SYSTEM_MODEL_H
