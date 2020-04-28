#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <poppler/qt5/poppler-qt5.h>
#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QSettings>
#include <QDropEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;    
    QLineEdit *lineEdit_page_current;
    QLabel *label_page_total;
    QString filename;
    QComboBox *comboBox_scale;
    Poppler::Document *document;    
    QList<QRectF> list_rectf_search;
    int index_search;
    QMatrix matrix() const;
    QSettings settings;
    void load(QString fileName);
    void zoom(double scale);
    void search(const QString &text, Poppler::Page::SearchFlags flags);
    void readSettings();

private slots:
    void on_action_open_triggered();
    void on_action_close_triggered();
    void on_action_property_triggered();
    void on_action_export_current_page_to_image_triggered();
    void on_action_export_all_pages_to_images_triggered();
    void on_action_aboutQt_triggered();
    void on_action_about_triggered();    

};

#endif // MAINWINDOW_H