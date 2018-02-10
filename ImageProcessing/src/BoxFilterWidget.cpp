#include <BoxFilterWidget.h>

#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>

///////////////////////////////////////////////////////////////////////////////

BoxFilterWidget::BoxFilterWidget(QWidget* ip_parent)
  : QWidget(ip_parent)
  {
  QGroupBox *groupBox = new QGroupBox(tr("Matrix Size"));

  QRadioButton *radio1 = new QRadioButton(tr("3x3"));
  QRadioButton *radio2 = new QRadioButton(tr("5x5"));
  QRadioButton *radio3 = new QRadioButton(tr("7x7"));

  radio1->setChecked(true);

  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->addWidget(radio1);
  vbox->addWidget(radio2);
  vbox->addWidget(radio3);
  vbox->addStretch(1);
  groupBox->setLayout(vbox);

  QGridLayout *grid = new QGridLayout;
  grid->addWidget(groupBox, 0, 0);
  setLayout(grid);

  setWindowTitle(tr("Box filter"));
  resize(240, 120);
  }
