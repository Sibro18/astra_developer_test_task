#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QThreadPool>
#include <QModelIndex>

#include "utils/file_utils.h"
#include "utils/types.h"

#include "src/ui_parts/custom_system_model.h"
#include "src/ui_parts/custom_sort_filter_proxy_model.h"
#include "src/ui_parts/custom_system_model_delegate.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();
private slots:
	void m_onTreeViewItemClicked(const QModelIndex& index);
	void m_onLineEditTextChanged(const QString& text);
private:
	QVBoxLayout* m_layout;
	QTreeView* m_treeView;
	QLineEdit* m_lineEdit;
	QThreadPool* m_thPool;
	StopFlag m_stopFlag;
	CustomSortFilterProxyModel* m_proxyModel;
	CustomSystemModelDelegate* m_delegate;
	CustomSystemModel* m_fsModel;
	const QString m_rootPath;

	void m_setupUi();
	void m_resetRootIndex();

	static constexpr int kDefaultWindowWidth = 800;
	static constexpr int kDefaultWindowHeight = 400;
	static constexpr int kTreeViewIndentation = 20;
	static constexpr double kThreadPoolUsageRatio = 0.5;
	static constexpr const char* kWindowTitle = "dirview with dir size calculation";
};

#endif // MAIN_WINDOW_H
