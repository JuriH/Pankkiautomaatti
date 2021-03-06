#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_writeCardBtn_clicked()
{
    if(ui->cardId->text() == ""){
        ui->writerLog->appendPlainText("ERROR: Cannot write empty id");
    }else{
        ui->writerLog->appendPlainText("Attempting to write card with id: "+ui->cardId->text());
        if(false){
            ui->writerLog->appendPlainText("ERROR: RFID device not present");
        }else{
            ui->writerLog->appendPlainText("Writer waiting, insert card");
            ui->writeCardBtn->setDisabled(1);

            // here it should go to a thread which waits the rfid card for writing, but it seems that our
            // hardware does not support writing, so this program remains as a proof of consept
        }

    }
}

void MainWindow::on_searchBtn_clicked()
{
    if(ui->search->text().length() < 3){
        ui->writerLog->appendPlainText("FETCH ERROR: Input at least 3 characters");
    }else{
        ui->searchBtn->setText("...");
        ui->searchBtn->setDisabled(true);
        ui->writerLog->appendPlainText("Searching from database");
        this->repaint();
        // sql connection and search
        QSqlDatabase db;
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("mysli.oamk.fi");
        db.setDatabaseName("opisk_t9haju03");
        db.setPort(3306);
        db.setUserName("t9haju03");
        db.setPassword("a6n6QLe8pEC7nJ4j");

        if(!db.open()){
            ui->writerLog->appendPlainText("FETCH ERROR: Connection to database failed");
            ui->searchBtn->setText("Search");
            ui->searchBtn->setDisabled(0);
            return;
        }

        QSqlQuery query;
        query.prepare("SELECT * FROM tilitiedot WHERE user_first LIKE :param OR user_last LIKE :param");
        query.bindValue(":param", "%"+ui->search->text()+"%");
        query.exec();

        if(query.size() == 0){
            ui->writerLog->appendPlainText("FETCH ERROR: No matches found");
            ui->searchBtn->setText("Search");
            ui->searchBtn->setDisabled(0);
            return;
        }

        ui->searchResults->clear();

        while(query.next()){
            ui->searchResults->addItem(QString(query.value(1).toString()) + " " + QString(query.value(2).toString()) + ": "+query.value(0).toString());
        }

        ui->searchBtn->setText("Search");
        ui->searchBtn->setDisabled(0);
    }
}

void MainWindow::on_insertSelectedBtn_clicked()
{
    if(ui->searchResults->selectedItems().size() != 0){
        QString s_id = ui->searchResults->currentItem()->text();
        int pos = s_id.indexOf(":");
        s_id = s_id.right(s_id.length()-pos-2);
        ui->cardId->setText(s_id);
    }
}
