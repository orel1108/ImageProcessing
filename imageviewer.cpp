#include "imageviewer.h"

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

ImageViewer::ImageViewer(QWidget * ip_parent)
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

bool ImageViewer::LoadImage(const QString & i_filename)
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

void ImageViewer::_Open()
{
  QFileDialog dialog(this, tr("Open File"));
  _InitializeImageFileDialog(dialog, QFileDialog::AcceptOpen);
  while (dialog.exec() == QDialog::Accepted && !LoadImage(dialog.selectedFiles().first())) {}
}

///////////////////////////////////////////////////////////////////////////////

void ImageViewer::_SaveAs()
{
  QFileDialog dialog(this, tr("Save File As"));
  _InitializeImageFileDialog(dialog, QFileDialog::AcceptSave);
  while (dialog.exec() == QDialog::Accepted && !_SaveImage(dialog.selectedFiles().first())) {}
}

///////////////////////////////////////////////////////////////////////////////

void ImageViewer::_CreateActions()
{
  // setup file menu
  QMenu* p_file_menu = menuBar()->addMenu(tr("&File"));

  QAction* p_open_action = p_file_menu->addAction(tr("&Open..."), this, &ImageViewer::_Open);
  p_open_action->setShortcut(QKeySequence::Open);

  mp_save_as = p_file_menu->addAction(tr("&Save As..."), this, &ImageViewer::_SaveAs);
  mp_save_as->setEnabled(false);

  p_file_menu->addSeparator();

  QAction* p_exit_action = p_file_menu->addAction(tr("E&xit"), this, &QWidget::close);
  p_exit_action->setShortcut(tr("Ctrl+Q"));

  // setup edit menu
  QMenu* p_edit_menu = menuBar()->addMenu(tr("&Edit"));

  //copyAct = editMenu->addAction(tr("&Copy"), this, &ImageViewer::copy);
  //copyAct->setShortcut(QKeySequence::Copy);
  //copyAct->setEnabled(false);
  //
  //QAction *pasteAct = editMenu->addAction(tr("&Paste"), this, &ImageViewer::paste);
  //pasteAct->setShortcut(QKeySequence::Paste);

  // setup view menu
  QMenu* p_view_menu = menuBar()->addMenu(tr("&View"));

  mp_zoom_in = p_view_menu->addAction(tr("Zoom &In (25%)"), this, &ImageViewer::_ZoomIn);
  mp_zoom_in->setShortcut(QKeySequence::ZoomIn);
  mp_zoom_in->setEnabled(false);

  mp_zoom_out = p_view_menu->addAction(tr("Zoom &Out (25%)"), this, &ImageViewer::_ZoomOut);
  mp_zoom_out->setShortcut(QKeySequence::ZoomOut);
  mp_zoom_out->setEnabled(false);

  mp_normal_size = p_view_menu->addAction(tr("&Normal Size"), this, &ImageViewer::_NormalSize);
  mp_normal_size->setShortcut(tr("Ctrl+S"));
  mp_normal_size->setEnabled(false);

  p_view_menu->addSeparator();

  mp_fit_to_window = p_view_menu->addAction(tr("&Fit to Window"), this, &ImageViewer::_FitToWindow);
  mp_fit_to_window->setEnabled(false);
  mp_fit_to_window->setCheckable(true);
  mp_fit_to_window->setShortcut(tr("Ctrl+F"));
}

///////////////////////////////////////////////////////////////////////////////

void ImageViewer::_SetImage(const QImage & i_image)
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

bool ImageViewer::_SaveImage(const QString & i_filename)
{
  QImageWriter writer(i_filename);
  return writer.write(m_image);
}

///////////////////////////////////////////////////////////////////////////////

void ImageViewer::_UpdateActions()
{
  mp_save_as->setEnabled(!m_image.isNull());

  mp_zoom_in->setEnabled(!mp_fit_to_window->isChecked());
  mp_zoom_out->setEnabled(!mp_fit_to_window->isChecked());
  mp_normal_size->setEnabled(!mp_fit_to_window->isChecked());
}

///////////////////////////////////////////////////////////////////////////////

void ImageViewer::_FitToWindow()
{
  const bool fit = mp_fit_to_window->isChecked();
  mp_scroll_area->setWidgetResizable(fit);
  if (!fit)
    _NormalSize();

  _UpdateActions();
}

///////////////////////////////////////////////////////////////////////////////

void ImageViewer::_NormalSize()
{
  mp_image_label->adjustSize();
  m_scale = 1.0;
}

///////////////////////////////////////////////////////////////////////////////

void ImageViewer::_ZoomIn()
{
  _ScaleImage(1.25);
}

///////////////////////////////////////////////////////////////////////////////

void ImageViewer::_ZoomOut()
{
  _ScaleImage(0.75);
}

///////////////////////////////////////////////////////////////////////////////

void ImageViewer::_ScaleImage(double i_factor)
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

void ImageViewer::_AdjustScrollBar(QScrollBar* op_scroll_bar, double i_factor)
{
  op_scroll_bar->setValue(int(i_factor * op_scroll_bar->value()
                              + ((i_factor - 1) * op_scroll_bar->pageStep() / 2)));
}

///////////////////////////////////////////////////////////////////////////////
