#include <QFileInfo>
#include <QPointer>
#include <QDebug>

#include "custom_system_model.h"
#include "utils/format_utils.h"

CustomSystemModel::CustomSystemModel(QThreadPool* threadPool, StopFlag* stopFlag, QObject* parent)
	: QFileSystemModel(parent),
	  m_thPool{threadPool ? threadPool : QThreadPool::globalInstance()},
	  m_stopFlag{stopFlag ? stopFlag : nullptr}
{}

QVariant CustomSystemModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid() || index.column() != 1)
	{
		return QFileSystemModel::data(index, role);
	}

	switch (role)
	{
		case Qt::TextAlignmentRole:
			return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);

		case CustomRoles::SizeInBytesRole:
			return m_getRawSize(index);

		case CustomRoles::InProgressRole:
			return m_getInProgressStatus(index);

		case Qt::DisplayRole:
			return m_getFormattedSize(index, role);

		default:
			return QFileSystemModel::data(index, role);
	}
}

QVariant CustomSystemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::TextAlignmentRole)
	{
		return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);
	}

	return QFileSystemModel::headerData(section, orientation, role);
}

void CustomSystemModel::calculateAndSetDirSize(const QModelIndex& index)
{
	if (!index.isValid())
	{
		return;
	}

	QFileInfo info = fileInfo(index);

	if (!info.isDir())
	{
		return;
	}

	QString path = filePath(index);

	{
		QWriteLocker lock(&m_cacheMutex);

		if (m_inProgress.contains(path))
		{
			return;
		}

		m_inProgress.insert(path);
	}

	emit dataChanged(index, index, {CustomRoles::InProgressRole});

	m_thPool->start([this, path, persistentIndex = QPersistentModelIndex(index), filters = filter()]() {
		if (!persistentIndex.isValid())
		{
			m_removeFromInProgress(path);
			return;
		}

		qint64 size = FileUtils::calculateDirSize(path, filters, m_stopFlag);

		if (!persistentIndex.isValid() || (m_stopFlag && m_stopFlag->value()))
		{
			m_removeFromInProgress(path);
			return;
		}

		{
			QWriteLocker lock(&m_cacheMutex);
			m_inProgress.remove(path);
			m_sizeCache[path] = size;
		}

		emit dataChanged(persistentIndex, persistentIndex, {Qt::DisplayRole, CustomRoles::InProgressRole});
	});
}

QVariant CustomSystemModel::m_getRawSize(const QModelIndex& index) const
{
	const auto fInfo = fileInfo(index);

	if (fInfo.isDir())
	{
		QReadLocker lock(&m_cacheMutex);
		return m_sizeCache.value(filePath(index), kDefaultDirSizeValue);
	}
	else
	{
		return fInfo.size();
	}
}

QVariant CustomSystemModel::m_getInProgressStatus(const QModelIndex& index) const
{
	QReadLocker lock(&m_cacheMutex);
	return m_inProgress.contains(filePath(index));
}

QVariant CustomSystemModel::m_getFormattedSize(const QModelIndex& index, int role) const
{
	qint64 sizeValue = kDefaultDirSizeValue;
	{
		QReadLocker lock(&m_cacheMutex);
		sizeValue = m_sizeCache.value(filePath(index), kDefaultDirSizeValue);
	}

	return sizeValue != kDefaultDirSizeValue
		? FormatUtils::formatSize(sizeValue)
		: QFileSystemModel::data(index, role);
}

void CustomSystemModel::m_removeFromInProgress(const QString& path)
{
	QWriteLocker lock(&m_cacheMutex);
	m_inProgress.remove(path);
}
