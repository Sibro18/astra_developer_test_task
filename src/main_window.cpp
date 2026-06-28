#include <QDir>
#include <QThread>
#include <QGuiApplication>
#include <QScreen>

#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	  m_layout{new QVBoxLayout},
	  m_treeView{new QTreeView},
	  m_lineEdit{new QLineEdit},
	  m_thPool{new QThreadPool(this)},
	  m_proxyModel{new CustomSortFilterProxyModel(this)},
	  m_delegate{new CustomSystemModelDelegate(this)},
	  m_fsModel{new CustomSystemModel(m_thPool, &m_stopFlag, this)},
	  m_rootPath{QDir::homePath()}
{
	int maxThreadCount = QThread::idealThreadCount();

	if (maxThreadCount < 2)
	{
		maxThreadCount = 2;
	}

	m_thPool->setMaxThreadCount(
		qMax(1, static_cast<int>(maxThreadCount * kThreadPoolUsageRatio))
	);

	m_fsModel->setFilter(
		QDir::AllEntries |
		QDir::Hidden |
		QDir::NoDotAndDotDot |
		QDir::NoSymLinks
	);
	m_fsModel->setRootPath(m_rootPath);

	m_proxyModel->setSourceModel(m_fsModel);
	m_proxyModel->setFilterKeyColumn(0);
	m_proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
	m_proxyModel->setRecursiveFilteringEnabled(true);

	m_setupUi();

	connect(
		m_treeView,
		&QTreeView::clicked,
		this,
		&MainWindow::m_onTreeViewItemClicked
	);
	connect(
		m_lineEdit,
		&QLineEdit::textChanged,
		this,
		&MainWindow::m_onLineEditTextChanged
	);
}

MainWindow::~MainWindow()
{
	m_stopFlag.setFlag(true);
	m_thPool->clear();
	m_thPool->waitForDone();
}

void MainWindow::m_setupUi()
{
	auto* widget = new QWidget(this);

	m_layout->addWidget(m_lineEdit);
	m_layout->addWidget(m_treeView);
	widget->setLayout(m_layout);

	m_treeView->setModel(m_proxyModel);
	m_treeView->setItemDelegateForColumn(1, m_delegate);
	m_treeView->setAnimated(false);
	m_treeView->setIndentation(kTreeViewIndentation);
	m_treeView->setSortingEnabled(true);
	m_resetRootIndex();


	setCentralWidget(widget);
	setWindowTitle(kWindowTitle);

	// Centering the window.
	int x = 0, y = 0;

	if (QScreen* screen = QGuiApplication::primaryScreen())
	{
		const QRect screenGeometry = screen->availableGeometry();
		x = (screenGeometry.width() - kDefaultWindowWidth) / 2;
		y = (screenGeometry.height() - kDefaultWindowHeight) / 2;
	}

	setGeometry(x, y, kDefaultWindowWidth, kDefaultWindowHeight);
}

void MainWindow::m_onLineEditTextChanged(const QString& text)
{
	m_proxyModel->setFilterWildcard(
		QString("*%1*").arg(text)
	);
	m_resetRootIndex();
}

void MainWindow::m_onTreeViewItemClicked(const QModelIndex& index)
{
	if (!index.isValid() || index.column() != 1)
	{
		return;
	}

	if (index.data(Qt::DisplayRole).toString().isEmpty())
	{
		m_fsModel->calculateAndSetDirSize(m_proxyModel->mapToSource(index));
	}
}

void MainWindow::m_resetRootIndex()
{
	m_treeView->setRootIndex(
		m_proxyModel->mapFromSource(
			m_fsModel->index(m_rootPath)
		)
	);
}
