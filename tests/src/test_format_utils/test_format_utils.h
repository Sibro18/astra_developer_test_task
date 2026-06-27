#ifndef TEST_FORMAT_UTILS_H
#define TEST_FORMAT_UTILS_H

#include <QtTest>
#include <QObject>
#include "utils/format_utils.h"

class TestFormatUtils : public QObject
{
	Q_OBJECT
private slots:
	void initTestCase();
	void testBytes();
	void testKilobytes();
	void testMegabytes();
	void testGigabytes();
	void testBoundaryValues();
};

#endif
