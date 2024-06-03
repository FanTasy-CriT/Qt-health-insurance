#include "service_crud.h"

#include <QSqlQuery>

#include <QSqlQueryModel>

#include "ui_mainwindow.h"

#include "mainwindow.h"

#include <QDebug>

#include <QSqlError>

#include <QMessageBox>

service_crud::service_crud()
{

}

void MainWindow::on_delete_4_clicked()
{
    // Get the selection model of the table view
    QItemSelectionModel * selectionModel = ui ->table_service -> selectionModel();
    // Get the currently selected indexes
    QModelIndexList selectedIndexes = selectionModel -> selectedIndexes();

    // Extract the primary keys of the selected rows
    QList < int > primaryKeys;
    foreach(const QModelIndex & index, selectedIndexes) {
      if (index.column() == 0) {
        primaryKeys.append(index.data().toInt());
      }
    }

    // Delete the selected rows from the SQL table
    QSqlQuery query;
    foreach(int primaryKey, primaryKeys) {
        qDebug() << "primary key found";
        query.prepare("DELETE FROM HAROUN.SERVICES WHERE ID=?");
        query.addBindValue(primaryKey);
        query.exec();
        ui->table_service->setModel(print_table("SERVICES"));
    }
}

void MainWindow::on_Add_3_clicked()
{
    bool test=true;
    QString error;
    QRegExp re("\\d*");
    for(int i=0;i<ui->nom_2->text().length();i++){
    if(re.exactMatch(ui->nom_2->text().at(i))){
        test=false;
        error = "nom non chaine";
    }
}
    if(ui->nom_2->text()==""){
        test=false;
        error = "nom vide";
    }
    if(!test) QMessageBox::information(this, "Information", error); else {
    QSqlQuery qry;
    qry.prepare("INSERT INTO HAROUN.services (NOM, type, location,dater)"
   " VALUES (:nom, :type,:location,TO_DATE(:date, 'DD/MM/YYYY'))");
    qry.bindValue(":nom",ui->nom_2->text());
    qry.bindValue(":type",ui->dropdowntype->currentText());
    qry.bindValue(":location",ui->dropdownlocation->currentText());
    qry.bindValue(":date",ui->dateEdit->text());
    if(!qry.exec()) QMessageBox::information(this, "check input","erreur cle primaire");
    ui->table_service->setModel(print_table("SERVICES"));
}
}

void MainWindow::on_Edit_3_clicked()
{
    bool test=true;
    QString error;
    QRegExp re("\\d*");
    for(int i=0;i<ui->nom_2->text().length();i++){
    if(re.exactMatch(ui->nom_2->text().at(i))){
        test=false;
        error = "nom non chaine";
    }
}
    if(!test) QMessageBox::information(this, "Information", error); else {
    QSqlQuery qry;
    qry.prepare("UPDATE HAROUN.SERVICES SET NOM=:nom, TYPE=:type,LOCATION=:location,dater=TO_DATE(:date, 'DD/MM/YYYY') WHERE id=:id");
    qry.bindValue(":id",ui->lineEdit->text().toInt());
    qry.bindValue(":nom",ui->nom_2->text());
    qry.bindValue(":type",ui->dropdowntype->currentText());
    qry.bindValue(":location",ui->dropdownlocation->currentText());
    qry.bindValue(":date",ui->dateEdit->text());
    if(!qry.exec()) qDebug() << "error adding into services";
    if (qry.numRowsAffected() == 0) QMessageBox::information(this, "Information", "erreur cle primaire");else QMessageBox::information(this, "Information", "modifier done");
    ui->table_service->setModel(print_table("SERVICES"));

}
}

void MainWindow::on_table_service_doubleClicked(const QModelIndex &index)
{
    if (index.isValid())
        {
                QVariant data = ui->table_service->model()->data(index);
                QString id = ui->table_service->model()->data(ui->table_service->model()->index(index.row(), 0)).toString();
                QString type = ui->table_service->model()->data(ui->table_service->model()->index(index.row(), 1)).toString();
                QString montant = ui->table_service->model()->data(ui->table_service->model()->index(index.row(), 2)).toString();
                QString date = ui->table_service->model()->data(ui->table_service->model()->index(index.row(), 3)).toString().left(10);
                qDebug() << "Double-clicked on row " << index.row() << " with data: " << id << "First Name: " << montant << "Last Name: " << date;
                    //materiel
                    if(type=="recu")ui->recu->setChecked(true);else ui->rendu->setChecked(true);
                    ui->lineEdit->setText(id);
                    ui->dropdowntype->setCurrentText(type);
                    ui->dropdownlocation->setCurrentText(date);
                    ui->nom_2->setText(montant);
        }
}


