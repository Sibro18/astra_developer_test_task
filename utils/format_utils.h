#ifndef FORMAT_UTILS_H
#define FORMAT_UTILS_H

#include <QString>
#include <QLocale>
#include <QtGlobal>

class FormatUtils
{
public:
	static QString formatSize(qint64 bytes);
private:
	static constexpr qint64 kKb = 1024;
	static constexpr qint64 kMb = kKb * 1024;
};

#endif // FORMAT_UTILS_H
