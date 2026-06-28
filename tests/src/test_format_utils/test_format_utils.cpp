#include <QLocale>

#include "test_format_utils.h"

void TestFormatUtils::initTestCase()
{
	QLocale::setDefault(QLocale::c());
}

void TestFormatUtils::testBytes()
{
	QCOMPARE(FormatUtils::formatSize(0), QString("0 bytes"));
	QCOMPARE(FormatUtils::formatSize(1), QString("1 bytes"));
	QCOMPARE(FormatUtils::formatSize(512), QString("512 bytes"));
	QCOMPARE(FormatUtils::formatSize(1023), QString("1023 bytes"));
}

void TestFormatUtils::testKilobytes()
{
	QCOMPARE(FormatUtils::formatSize(1024), QString("1.0 KiB"));
	QCOMPARE(FormatUtils::formatSize(1536), QString("1.5 KiB"));
	QCOMPARE(FormatUtils::formatSize(1024 * 100), QString("100.0 KiB"));
}

void TestFormatUtils::testMegabytes()
{
	QCOMPARE(FormatUtils::formatSize(1024 * 1024), QString("1.00 MiB"));
	QCOMPARE(FormatUtils::formatSize(1024 * 1024 * 5), QString("5.00 MiB"));
}

void TestFormatUtils::testGigabytes()
{
	QCOMPARE(FormatUtils::formatSize(1024LL * 1024 * 1024), QString("1.00 GiB"));
	QCOMPARE(FormatUtils::formatSize(1024LL * 1024 * 1024 * 2.5), QString("2.50 GiB"));
}

void TestFormatUtils::testBoundaryValues()
{
	QCOMPARE(FormatUtils::formatSize(1023), QString("1023 bytes"));
	QCOMPARE(FormatUtils::formatSize(1024), QString("1.0 KiB"));
	QCOMPARE(FormatUtils::formatSize(1024 * 1024 - 1), QString("1024.0 KiB"));
	QCOMPARE(FormatUtils::formatSize(1024 * 1024), QString("1.00 MiB"));
}

QTEST_MAIN(TestFormatUtils)
