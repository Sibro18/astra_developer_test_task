#ifndef TEST_FILE_UTILS_H
#define TEST_FILE_UTILS_H

#include <QtTest>
#include <QDir>
#include <QObject>

#include "utils/file_utils.h"

class TestFileUtils : public QObject
{
	Q_OBJECT
private slots:
	void testEmptyDirectory();
	void testSingleFile();
	void testMultipleFiles();
	void testNestedDirectories();
	void testDeepNesting();
	void testHiddenFiles();
	void testIgnoresSymlinks();
	void testNonExistentDirectory();
	void testMixedContent();

private:
	// Supporting method for creating a file of a given size
	bool m_createFileWithSize(const QString& path, qint64 size);

	static constexpr QDir::Filters kFilters = QDir::AllEntries | QDir::Hidden | QDir::NoDotAndDotDot | QDir::NoSymLinks;
};

#endif // TEST_FILE_UTILS_H
