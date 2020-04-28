#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QShortcut>
#include <QMimeData>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    settings(QCoreApplication::organizationName(), QCoreApplication::applicationName())
{
    ui->setupUi(this);
    QAction *action_zoomout = new QAction;
    action_zoomout->setIcon(QIcon::fromTheme("zoom-out"));
    action_zoomout->setToolTip("缩小");
    action_zoomout->setShortcut(QKeySequence(Qt::ControlModifier + Qt::Key_Minus));
    ui->mainToolBar->addAction(action_zoomout);
    comboBox_scale = new QComboBox;
    QStringList scales;
    scales << "10%" << "25%" << "50%" << "75%" << "100%" << "125%" << "175%" << "200%" << "300%" << "400%" << "500%";
    comboBox_scale->addItems(scales);
    comboBox_scale->setFixedWidth(80);
    comboBox_scale->setCurrentText("100%");
    connect(comboBox_scale, qOverload<int>(&QComboBox::currentIndexChanged), [=](int index){
        double scale = comboBox_scale->itemText(index).replace("%","").toInt()/100.0;
        zoom(scale);
    });
    ui->mainToolBar->addWidget(comboBox_scale);
    QAction *action_zoomin = new QAction;
    action_zoomin->setIcon(QIcon::fromTheme("zoom-in"));
    action_zoomin->setToolTip("放大");
    action_zoomin->setShortcuts(QList<QKeySequence>() << QKeySequence(Qt::ControlModifier + Qt::Key_Equal) << QKeySequence(Qt::ControlModifier + Qt::Key_Plus));
    ui->mainToolBar->addAction(action_zoomin);
    connect(action_zoomout, &QAction::triggered, [=](){
        if (comboBox_scale->currentIndex() > 0) {
            comboBox_scale->setCurrentIndex(comboBox_scale->currentIndex() - 1);
            double scale = comboBox_scale->currentText().replace("%","").toInt()/100.0;
            zoom(scale);
        }
    });
    connect(action_zoomin, &QAction::triggered, [=](){
        if (comboBox_scale->currentIndex() < comboBox_scale->count() - 1) {
            comboBox_scale->setCurrentIndex(comboBox_scale->currentIndex() + 1);
            double scale = comboBox_scale->currentText().replace("%","").toInt()/100.0;
            zoom(scale);
        }
    });
    connect(new QShortcut(QKeySequence(Qt::ControlModifier + Qt::Key_0), this), &QShortcut::activated, [=](){
        comboBox_scale->setCurrentText("100%");
        zoom(1);
    });

    QAction *action_page_last = new QAction;
    action_page_last->setIcon(QIcon::fromTheme("media-skip-forward"));
    action_page_last->setToolTip("上一页");
    action_page_last->setShortcut(QKeySequence(Qt::Key_PageUp));
    ui->mainToolBar->addAction(action_page_last);
    lineEdit_page_current = new QLineEdit("0");
    lineEdit_page_current->setFixedWidth(40);
    ui->mainToolBar->addWidget(lineEdit_page_current);
    QLabel *label = new QLabel("/");
    ui->mainToolBar->addWidget(label);
    label_page_total = new QLabel("0");
    ui->mainToolBar->addWidget(label_page_total);
    QAction *action_page_next = new QAction;
    action_page_next->setIcon(QIcon::fromTheme("media-skip-backward"));
    action_page_next->setToolTip("下一页");
    action_page_next->setShortcut(QKeySequence(Qt::Key_PageDown));
    ui->mainToolBar->addAction(action_page_next);
    connect(action_page_last, &QAction::triggered, [=](){
        if (lineEdit_page_current->text() != "") {
            if (lineEdit_page_current->text().toInt() > 1) {
                lineEdit_page_current->setText(QString::number(lineEdit_page_current->text().toInt() - 1));
                list_rectf_search.clear();
                double scale = comboBox_scale->currentText().replace("%","").toInt()/100.0;
                zoom(scale);
            }
        }
    });
    connect(lineEdit_page_current, &QLineEdit::returnPressed, [=](){
        list_rectf_search.clear();
        double scale = comboBox_scale->currentText().replace("%","").toInt()/100.0;
        zoom(scale);
    });
    connect(action_page_next, &QAction::triggered, [=](){
        if (lineEdit_page_current->text() != "") {
            if (lineEdit_page_current->text().toInt() < document->numPages()) {
                list_rectf_search.clear();
                lineEdit_page_current->setText(QString::number(lineEdit_page_current->text().toInt() + 1));
                double scale = comboBox_scale->currentText().replace("%","").toInt()/100.0;
                zoom(scale);
            }
        }
    });

    QAction *action_search = new QAction;
    action_search->setIcon(QIcon::fromTheme("system-search"));
    QLineEdit *lineEdit_search = new QLineEdit;
    lineEdit_search->addAction(action_search, QLineEdit::LeadingPosition);
    lineEdit_search->setFixedWidth(120);
    ui->mainToolBar->addWidget(lineEdit_search);
    QAction *action_search_last = new QAction;
    action_search_last->setIcon(QIcon::fromTheme("media-skip-forward"));
    action_search_last->setToolTip("搜索上一个");
    ui->mainToolBar->addAction(action_search_last);
    QAction *action_search_next = new QAction;
    action_search_next->setIcon(QIcon::fromTheme("media-skip-backward"));
    action_search_next->setToolTip("搜索下一个");
    ui->mainToolBar->addAction(action_search_next);
    connect(action_search_last, &QAction::triggered, [=](){
        if (index_search > 0) {
            index_search--;
            ui->statusBar->showMessage("页" + lineEdit_page_current->text() + "：" + QString::number(index_search+1) + "/" + QString::number(list_rectf_search.length()), 5000);

        } else {
            if (lineEdit_page_current->text().toInt() == 1) {
                ui->statusBar->showMessage("已经搜索到最前一个", 5000);
                QApplication::beep();
                return;
            }
            action_page_last->trigger();
            ui->statusBar->showMessage("搜上一页", 5000);
            search(lineEdit_search->text(), Poppler::Page::SearchFlag::IgnoreCase);
            while (list_rectf_search.isEmpty()) {
                action_page_last->trigger();
                ui->statusBar->showMessage("搜上上页", 5000);
                search(lineEdit_search->text(), Poppler::Page::SearchFlag::IgnoreCase);
            }
        }
        double scale = comboBox_scale->currentText().replace("%","").toInt()/100.0;
        zoom(scale);
    });
    connect(lineEdit_search, &QLineEdit::returnPressed, [=](){
        search(lineEdit_search->text(), Poppler::Page::SearchFlag::IgnoreCase);
        double scale = comboBox_scale->currentText().replace("%","").toInt()/100.0;
        zoom(scale);
    });
    connect(action_search_next, &QAction::triggered, [=](){
        if (index_search < list_rectf_search.length() - 1){
            index_search++;
            ui->statusBar->showMessage("页" + lineEdit_page_current->text() + "：" + QString::number(index_search+1) + "/" + QString::number(list_rectf_search.length()), 5000);
        } else {
             if (lineEdit_page_current->text().toInt() == document->numPages()) {
                ui->statusBar->showMessage("已经搜索到最后一个", 5000);
                QApplication::beep();
                return;
             }
             action_page_next->trigger();
             ui->statusBar->showMessage("搜下一页", 5000);
             search(lineEdit_search->text(), Poppler::Page::SearchFlag::IgnoreCase);
             while (list_rectf_search.isEmpty()) {
                 action_page_next->trigger();
                 ui->statusBar->showMessage("搜下下页", 5000);
                 search(lineEdit_search->text(), Poppler::Page::SearchFlag::IgnoreCase);
             }
        }
        double scale = comboBox_scale->currentText().replace("%","").toInt()/100.0;
        zoom(scale);
    });
    connect(new QShortcut(QKeySequence(Qt::ControlModifier + Qt::Key_F), this), &QShortcut::activated, [=](){
        lineEdit_search->setFocus();
    });
    connect(new QShortcut(QKeySequence(Qt::Key_Escape), this), &QShortcut::activated, [=](){
        ui->label->setFocus();
    });

    connect(ui->action_quit, SIGNAL(triggered()), qApp, SLOT(quit()));

    readSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << event->mimeData()->formats();
    event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    qDebug() << urls;
    if(urls.isEmpty())
        return;
    load(urls.at(0).toLocalFile());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
}

void MainWindow::readSettings()
{
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
}

void MainWindow::on_action_open_triggered()
{
    comboBox_scale->setCurrentText("100%");
    filename = QFileDialog::getOpenFileName(this, "选择文件", filename, "pdf文件 (*.pdf)");
    if (filename.isNull() || !filename.endsWith(".pdf"))
        return;
    setWindowTitle(QFileInfo(filename).fileName());
    load(filename);
}

void MainWindow::load(QString fileName)
{
    document = Poppler::Document::load(fileName);
    document->setRenderHint(Poppler::Document::Antialiasing, true);     //graphics
    document->setRenderHint(Poppler::Document::TextAntialiasing, true);
    lineEdit_page_current->setText("1");
    QIntValidator validator(1, document->numPages());
    lineEdit_page_current->setValidator(&validator);
    label_page_total->setText(QString::number(document->numPages()));
    lineEdit_page_current->setFixedWidth(label_page_total->fontMetrics().width(QString::number(document->numPages()) + "****"));
    zoom(1);   
}

void MainWindow::zoom(double scale)
{
    QImage image = document->page(lineEdit_page_current->text().toInt() - 1)->renderToImage(scale * physicalDpiX(), scale * physicalDpiY());
    //qDebug() << rectf_search;
    if (!list_rectf_search.isEmpty()) {
        for (int i=0; i<list_rectf_search.length(); i++) {
            if (i == index_search) {
                QRect rect_highlight = matrix().mapRect(list_rectf_search.at(i)).toRect();
                qDebug() << rect_highlight;
                QImage image_highlight = image.copy(rect_highlight);
                //反色
                int w,h;
                w = image_highlight.width();
                h = image_highlight.height();
                QImage image_invert(w,h,QImage::Format_ARGB32);
                for (int x=0; x<w; x++) {
                    for (int y=0; y<h; y++) {
                        QRgb RGB = image_highlight.pixel(x,y);
                        QRgb RGBi = qRgba(255-qRed(RGB), 255-qGreen(RGB), 255-qBlue(RGB), qAlpha(RGB));
                        image_invert.setPixel(x,y,RGBi);
                    }
                }
                QPainter painter;
                painter.begin(&image);
                painter.drawImage(rect_highlight, image_invert);
                painter.end();
            }
        }
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_action_close_triggered()
{
    QPixmap pixmap;
    ui->label->setPixmap(pixmap);
}

void MainWindow::on_action_aboutQt_triggered()
{
    QMessageBox::aboutQt(nullptr, "关于 Qt");
}

void MainWindow::on_action_property_triggered()
{
    QString s = "";
    QStringList SL_infoKeys = document->infoKeys();
    for (int i=0; i<SL_infoKeys.length(); i++) {
        s = s + SL_infoKeys.at(i) + ": " + document->info(SL_infoKeys.at(i)) + "\n";
    }
    QMessageBox aboutMB(QMessageBox::NoIcon, "属性", s);
    aboutMB.setIconPixmap(QPixmap(":/HTYPDF.png"));
    aboutMB.exec();
}

void MainWindow::on_action_about_triggered()
{
    QMessageBox aboutMB(QMessageBox::NoIcon, "关于", "海天鹰PDF 1.0\n\n一款基于 poppler 的PDF查看软件。\n作者：海天鹰\nE-mail: sonichy@163.com");
    aboutMB.setIconPixmap(QPixmap(":/HTYPDF.png"));
    aboutMB.exec();
}

void MainWindow::on_action_export_current_page_to_image_triggered()
{
    int page = lineEdit_page_current->text().toInt() - 1;
    QString filepath = QFileDialog::getSaveFileName(this, "保存图片", QString::number(page+1) + ".jpg", "图片(*.png *.jpg)");
    if (filepath.isNull())
        return;
    double scale = comboBox_scale->currentText().replace("%","").toInt()/100.0;
    QImage image = document->page(page)->renderToImage(scale * physicalDpiX(), scale * physicalDpiY());
    if (image.save(filepath))
        ui->statusBar->showMessage("导出第" + QString::number(page) + "页到 " + filepath + " 成功");
}

void MainWindow::on_action_export_all_pages_to_images_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this, "保存图片", filename, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (dir.isNull())
        return;
    double scale = comboBox_scale->currentText().replace("%","").toInt()/100.0;
    for (int i=0; i<document->numPages(); i++) {
        QString filepath = dir + "/" + QString::number(i+1) + ".jpg";
        QImage image = document->page(i)->renderToImage(scale * physicalDpiX(), scale * physicalDpiY());
        if (image.save(filepath))
            ui->statusBar->showMessage("导出第" + QString::number(i+1) + "页到 " + filepath + " 成功");
        else {
            ui->statusBar->showMessage("导出第" + QString::number(i+1) + "页到 " + filepath + " 失败");
        }
    }
    ui->statusBar->showMessage("导出所有页面到 " + dir + " 结束");
}

void MainWindow::search(const QString &text, Poppler::Page::SearchFlags flags)
{
    int page = lineEdit_page_current->text().toInt() - 1;
    index_search = 0;
    list_rectf_search = document->page(page)->search(text, flags);
    //qDebug() << list_rectf_search;
}

QMatrix MainWindow::matrix() const
{
    double scale = comboBox_scale->currentText().replace("%","").toInt()/100.0;
    return QMatrix(scale * physicalDpiX() / 72.0, 0, 0, scale *  physicalDpiY() / 72.0, 0, 0);
}

