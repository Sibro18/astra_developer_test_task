#include <QLocale>

#include "format_utils.h"

QString FormatUtils::formatSize(qint64 bytes)
{
	static const QLocale locale;
	int precision = 2;

	if (bytes < kKb)
	{
		precision = 0;
	}
	else if (bytes < kMb)
	{
		precision = 1;
	}


	return locale.formattedDataSize(bytes, precision, QLocale::DataSizeIecFormat);
}
