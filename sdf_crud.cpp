#include "sdf_crud.h"

#include <QSqlQuery>

#include <QSqlQueryModel>

#include "ui_mainwindow.h"

#include "mainwindow.h"

#include <QDebug>

#include <QSqlError>

#include <QMessageBox>
#include "SMTPClient/email.h"
#include "SMTPClient/emailaddress.h"
#include "SMTPClient/smtpclient.h"

SDF_CRUD::SDF_CRUD()
{

}

Email MainWindow::createEmail()
{
    // Create the credentials EmailAddress
    EmailAddress credentials("nourhene.ouhichi@esprit.tn",
                             "ecikvjohchilpnmb");

    // Create the from EmailAddress
    EmailAddress from("nourhene.ouhichi@esprit.tn");

    // Create the to EmailAddress
    EmailAddress to(ui->to->text());

    // Create the email
    Email email(credentials,
                from,
                to,
                ui->subject->text(),
                ui->content->toPlainText());

    return email;
}

void MainWindow::on_delete_3_clicked()
{
    // Get the selection model of the table view
    QItemSelectionModel * selectionModel = ui ->table_sdf -> selectionModel();
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
        query.prepare("DELETE FROM HAROUN.SDF WHERE ID=?");
        query.addBindValue(primaryKey);
        query.exec();
        ui->table_sdf->setModel(print_table("SDF"));
    }
}

void MainWindow::on_Add_2_clicked()
{
    bool test=true;
    QString error;
    QRegExp re("\\d*");
    if (!re.exactMatch(ui->ID_3->text())){
           error = "id not digits";test=false;}
    for(int i=0;i<ui->preno->text().length();i++){
    if(re.exactMatch(ui->preno->text().at(i))){
        test=false;
        error = "prenom non chaine";
    }
}
    for(int i=0;i<ui->nom->text().length();i++){
    if(re.exactMatch(ui->nom->text().at(i))){
        test=false;
        error = "nom non chaine";
    }
}
    if(!test) QMessageBox::information(this, "Information", error); else {
    QSqlQuery qry;
    qry.prepare("INSERT INTO HAROUN.SDF (ID, NOM, PRENOM, DN, ETAT,BESOIN)"
   " VALUES (:id, :nom, :prenom, TO_DATE(:date, 'MM-DD-YYYY'),:etat,:besoin )");
    qry.bindValue(":id",ui->ID_3->text().toInt());
    qry.bindValue(":date",ui->datedenaissance->text());
    qry.bindValue(":prenom",ui->preno->text());
    qry.bindValue(":nom",ui->nom->text());
    qry.bindValue(":etat",ui->dropdownetat->currentText());
    qry.bindValue(":besoin",ui->dropdowsante->currentText());
    if(!qry.exec()) QMessageBox::information(this, "check input","erreur cle primaire");
    ui->table_sdf->setModel(print_table("SDF"));
}
}

void MainWindow::on_Edit_2_clicked()
{
    bool test=true;
    QString error;
    QRegExp re("\\d*");
    if (!re.exactMatch(ui->ID_3->text())){
           error = "id not digits";test=false;}
    for(int i=0;i<ui->preno->text().length();i++){
    if(re.exactMatch(ui->preno->text().at(i))){
        test=false;
        error = "prenom non chaine";
    }
}
    for(int i=0;i<ui->nom->text().length();i++){
    if(re.exactMatch(ui->nom->text().at(i))){
        test=false;
        error = "nom non chaine";
    }
}
    if(!test) QMessageBox::information(this, "Information", error); else {
    QSqlQuery qry;
    qry.prepare("UPDATE HAROUN.SDF SET NOM=:nom,DN=TO_DATE(:date, 'MM-DD-YYYY'), PRENOM=:prenom, ETAT=:etat,BESOIN=:besoin WHERE id=:id");
    qry.bindValue(":id",ui->ID_3->text().toInt());
    qry.bindValue(":date",ui->datedenaissance->text());
    qry.bindValue(":prenom",ui->preno->text());
    qry.bindValue(":nom",ui->nom->text());
    qry.bindValue(":etat",ui->dropdownetat->currentText());
    qry.bindValue(":besoin",ui->dropdowsante->currentText());
    if(!qry.exec()) qDebug() << "error adding into sdf";
    if (qry.numRowsAffected() == 0) QMessageBox::information(this, "Information", "erreur cle primaire");
    ui->table_sdf->setModel(print_table("SDF"));
}
}
void MainWindow::on_pushButton_24_clicked()
{
    using namespace qrcodegen;
                    QString value=ui->qr_id->text();


                         QSqlQuery qry;




                         qry.prepare("select * from SDF where ID='"+value+"'");
                         qry.exec();
                         qry.next();




                        QString idvehicule = qry.value(0).toString();
                        QString idclient= qry.value(1).toString();
                        QString typev = qry.value(2).toString();
                        QString matreculev = qry.value(3).toString();
                        QString numberv = qry.value(4).toString();
                        QString sante = qry.value(5).toString();





                    QString text = idvehicule+"\n"+typev+"\n"+idclient+"\n"+numberv+"\n"+matreculev+"\n"+sante+"\n";
                      // Create the QR Code object
                      QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );

                      qint32 sz = qr.getSize();
                      QImage im(sz,sz, QImage::Format_RGB32);
                        QRgb black = qRgb( 191,112,105 );
                        QRgb white = qRgb(255,255,255);
                      for (int y = 0; y < sz; y++)
                        for (int x = 0; x < sz; x++)
                          im.setPixel(x,y,qr.getModule(x, y) ? black : white );//setpixelmap tafichilek qr code
                      ui->qrcode->setPixmap( QPixmap::fromImage(im.scaled(100,100,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
}

