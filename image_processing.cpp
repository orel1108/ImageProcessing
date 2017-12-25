#include "image_processing.h"

#include <QByteArray>
#include <QFileDialog>
#include <QGuiApplication>
#include <QImageReader>
#include <QImageWriter>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QScreen>
#include <QScrollArea>
#include <QScrollBar>
#include <QStandardPaths>

namespace
{
  void _InitializeImageFileDialog(QFileDialog & o_dialog, const QFileDialog::AcceptMode & i_accept_mode)
  {
    static bool first_dialog = true;

    if (first_dialog)
      {
        first_dialog  = false;
        const QStringList pic_loc = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        o_dialog.setDirectory(pic_loc.isEmpty() ? QDir::currentPath() : pic_loc.last());
      }

    const QByteArrayList supportedMimeTypes = i_accept_mode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();

    QStringList mime_type_filters;
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
      mime_type_filters.append(mimeTypeName);

    mime_type_filters.sort();
    o_dialog.setMimeTypeFilters(mime_type_filters);
    o_dialog.selectMimeTypeFilter("image/jpeg");
    if (i_accept_mode == QFileDialog::AcceptSave)
      o_dialog.setDefaultSuffix("jpg");
  }
}

///////////////////////////////////////////////////////////////////////////////

ImageProcessing::ImageProcessing(QWidget * ip_parent)
  : QMainWindow(ip_parent)
  , mp_image_label(new QLabel)
  , mp_scroll_area(new QScrollArea)
  , m_scale(1.0)
{
  // setup image label
  mp_image_label->setBackgroundRole(QPalette::Base);
  mp_image_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  mp_image_label->setScaledContents(true);

  // setup scroll area
  mp_scroll_area->setBackgroundRole(QPalette::Dark);
  mp_scroll_area->setWidget(mp_image_label);
  mp_scroll_area->setVisible(false);
  setCentralWidget(mp_scroll_area);

  _CreateActions();

  resize(QGuiApplication::primaryScreen()->availableSize() * 4 / 5);
}

///////////////////////////////////////////////////////////////////////////////

bool ImageProcessing::LoadImage(const QString & i_filename)
{
  QImageReader reader(i_filename);
  reader.setAutoTransform(true);

  const auto image = reader.read();
  if (image.isNull())
    return false;

  _SetImage(image);
  setWindowFilePath(i_filename);
  return true;
}

///////////////////////////////////////////////////////////////////////////////

void ImageProcessing::_Open()
{
  QFileDialog dialog(this, tr("Open File"));
  _InitializeImageFileDialog(dialog, QFileDialog::AcceptOpen);
  while (dialog.exec() == QDialog::Accepted && !LoadImage(dialog.selectedFiles().first())) {}
}

///////////////////////////////////////////////////////////////////////////////

void ImageProcessing::_SaveAs()
{
  QFileDialog dialog(this, tr("Save File As"));
  _InitializeImageFileDialog(dialog, QFileDialog::AcceptSave);
  while (dialog.exec() == QDialog::Accepted && !_SaveImage(dialog.selectedFiles().first())) {}
}

///////////////////////////////////////////////////////////////////////////////

void ImageProcessing::_CreateActions()
{
  // setup file menu
  QMenu* p_file_menu = menuBar()->addMenu(tr("&File"));

  QAction* p_open_action = p_file_menu->addAction(tr("&Open..."), this, &ImageProcessing::_Open);
  p_open_action->setShortcut(QKeySequence::Open);

  mp_save_as = p_file_menu->addAction(tr("&Save As..."), this, &ImageProcessing::_SaveAs);
  mp_save_as->setEnabled(false);

  p_file_menu->addSeparator();

  QAction* p_exit_action = p_file_menu->addAction(tr("E&xit"), this, &QWidget::close);
  p_exit_action->setShortcut(tr("Ctrl+Q"));

  // setup edit menu
  QMenu* p_edit_menu = menuBar()->addMenu(tr("&Edit"));

  //copyAct = editMenu->addAction(tr("&Copy"), this, &ImageProcessing::copy);
  //copyAct->setShortcut(QKeySequence::Copy);
  //copyAct->setEnabled(false);
  //
  //QAction *pasteAct = editMenu->addAction(tr("&Paste"), this, &ImageProcessing::paste);
  //pasteAct->setShortcut(QKeySequence::Paste);

  // setup view menu
  QMenu* p_view_menu = menuBar()->addMenu(tr("&View"));

  mp_zoom_in = p_view_menu->addAction(tr("Zoom &In (25%)"), this, &ImageProcessing::_ZoomIn);
  mp_zoom_in->setShortcut(QKeySequence::ZoomIn);
  mp_zoom_in->setEnabled(false);

  mp_zoom_out = p_view_menu->addAction(tr("Zoom &Out (25%)"), this, &ImageProcessing::_ZoomOut);
  mp_zoom_out->setShortcut(QKeySequence::ZoomOut);
  mp_zoom_out->setEnabled(false);

  mp_normal_size = p_view_menu->addAction(tr("&Normal Size"), this, &ImageProcessing::_NormalSize);
  mp_normal_size->setShortcut(tr("Ctrl+S"));
  mp_normal_size->setEnabled(false);

  p_view_menu->addSeparator();

  mp_fit_to_window = p_view_menu->addAction(tr("&Fit to Window"), this, &ImageProcessing::_FitToWindow);
  mp_fit_to_window->setEnabled(false);
  mp_fit_to_window->setCheckable(true);
  mp_fit_to_window->setShortcut(tr("Ctrl+F"));

  // operations
  QMenu* p_operation_menu = menuBar()->addMenu(tr("&Operations"));

  mp_invert = p_operation_menu->addAction(tr("Invert"), this, &ImageProcessing::_Invert);
  mp_invert->setEnabled(false);
}

///////////////////////////////////////////////////////////////////////////////

void ImageProcessing::_SetImage(const QImage & i_image)
{
  m_image = i_image;

  mp_image_label->setPixmap(QPixmap::fromImage(m_image));
  mp_image_label->adjustSize();

  m_scale = 1.0;

  mp_scroll_area->setVisible(true);

  mp_fit_to_window->setEnabled(true);

  _UpdateActions();

  if (!mp_fit_to_window->isChecked())
    mp_image_label->adjustSize();
}

///////////////////////////////////////////////////////////////////////////////

bool ImageProcessing::_SaveImage(const QString & i_filename)
{
  QImageWriter writer(i_filename);
  return writer.write(m_image);
}

///////////////////////////////////////////////////////////////////////////////

void ImageProcessing::_UpdateActions()
{
  mp_save_as->setEnabled(!m_image.isNull());

  mp_zoom_in->setEnabled(!mp_fit_to_window->isChecked());
  mp_zoom_out->setEnabled(!mp_fit_to_window->isChecked());
  mp_normal_size->setEnabled(!mp_fit_to_window->isChecked());

  mp_invert->setEnabled(!m_image.isNull());
}

///////////////////////////////////////////////////////////////////////////////

void ImageProcessing::_FitToWindow()
{
  const bool fit = mp_fit_to_window->isChecked();
  mp_scroll_area->setWidgetResizable(fit);
  if (!fit)
    _NormalSize();

  _UpdateActions();
}

///////////////////////////////////////////////////////////////////////////////

void ImageProcessing::_NormalSize()
{
  mp_image_label->adjustSize();
  m_scale = 1.0;
}

///////////////////////////////////////////////////////////////////////////////

void ImageProcessing::_ZoomIn()
{
  _ScaleImage(1.25);
}

///////////////////////////////////////////////////////////////////////////////

void ImageProcessing::_ZoomOut()
{
  _ScaleImage(0.75);
}

///////////////////////////////////////////////////////////////////////////////

void ImageProcessing::_ScaleImage(double i_factor)
{
  Q_ASSERT(mp_image_label->pixmap());
  m_scale *= i_factor;
  mp_image_label->resize(m_scale * mp_image_label->pixmap()->size());

  _AdjustScrollBar(mp_scroll_area->horizontalScrollBar(), i_factor);
  _AdjustScrollBar(mp_scroll_area->verticalScrollBar(), i_factor);

  mp_zoom_in->setEnabled(m_scale < 3.0);
  mp_zoom_out->setEnabled(m_scale > 0.333);
}

///////////////////////////////////////////////////////////////////////////////

void ImageProcessing::_AdjustScrollBar(QScrollBar* op_scroll_bar, double i_factor)
{
  op_scroll_bar->setValue(int(i_factor * op_scroll_bar->value()
                              + ((i_factor - 1) * op_scroll_bar->pageStep() / 2)));
}

///////////////////////////////////////////////////////////////////////////////

void ImageProcessing::_Invert()
{
  m_image = mp_image_label->pixmap()->toImage();
  m_image.invertPixels(QImage::InvertMode::InvertRgb);
  mp_image_label->setPixmap(QPixmap::fromImage(m_image));
}

///////////////////////////////////////////////////////////////////////////////
