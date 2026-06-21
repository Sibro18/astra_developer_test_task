#include <QFileInfo>
#include <QDir>

#include "custom_system_model.h"
#include "utils/format_utils/format_utils.h"
#include "utils/file_utils/file_utils.h"

CustomSystemModel::CustomSystemModel(QThreadPool* threadPool, QObject* parent)
	: QFileSystemModel(parent),
	  _threadPool{threadPool ? threadPool : QThreadPool::globalInstance()}
{}

QVariant CustomSystemModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
	{
		return QFileSystemModel::data(index, role);
	}

	if (index.column() == 1)
	{
		if (role == Qt::TextAlignmentRole)
		{
			return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);
		}

		const QString path = filePath(index);

		if (role == CustomRoles::InProgressRole)
		{
			QReadLocker lock(&_cacheMutex);
			return _inProgress.contains(path);
		}
		else if (role == Qt::DisplayRole)
		{
			QString sizeValue;
			{
				QReadLocker lock(&_cacheMutex);
				sizeValue = _sizeCache.value(path);
			}

			return !sizeValue.isEmpty() ? sizeValue : QFileSystemModel::data(index, role);
		}
	}

	return QFileSystemModel::data(index, role);
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

	QString path = info.absoluteFilePath();

	{
		QWriteLocker lock(&_cacheMutex);

		if (_inProgress.contains(path))
		{
			return;
		}

		_inProgress.insert(path);
	}

	emit dataChanged(index, index, {CustomRoles::InProgressRole});

	_threadPool->start([this, path, persistentIndex = QPersistentModelIndex(index)]() {
		if (!persistentIndex.isValid())
		{
			QWriteLocker lock(&_cacheMutex);
			_inProgress.remove(path);

			return;
		}

		qint64 size = FileUtils::calculateDirSize(path);
		{
			QWriteLocker lock(&_cacheMutex);
			_inProgress.remove(path);
			_sizeCache[path] = FormatUtils::formatSize(size);
		}

		emit dataChanged(persistentIndex, persistentIndex, {Qt::DisplayRole, CustomRoles::InProgressRole});
	});
}
