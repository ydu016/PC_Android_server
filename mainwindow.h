#include <QMainWindow>
#include <QDateTime>
#include "tableitem.h"
#include "linegraphwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

//protected slots:
    void addSocket(TableItem *item);
    void updateSocket(int i);
    void deleteSocket(int i);
    void addThread(TableItem *thread);
    void updateThread(int i);
    void deleteThread(int i);
    void test();
private slots:
    void on_socketTableWidget_2_clicked(const QModelIndex &index);

signals:
    void uiToServer(int tid);
private:
    Ui::MainWindow *ui;
    LineGraphWidget *graph;
};

