#pragma once

#include <QLabel>
#include <QScrollArea>

#include <QtWidgets/QMainWindow>

#include <memory>

class QAction;
class QScrollBar;

class BoxFilterWidget;

/**
 * @class ImageProcessing.
 * @brief Class implements image processing GUI.
 */
class ImageProcessing : public QMainWindow
  {
  Q_OBJECT

  public:
    /**
     * @brief Default constructor.
     * @param[in] ip_parent Pointer to the parent widget.
     */
    explicit ImageProcessing(QWidget * ip_parent = nullptr);

  private slots:
    void _Open();
    void _SaveAs();

  private:
    // class member
    QImage                       m_image;
    std::unique_ptr<QLabel>      mp_image_label;
    std::unique_ptr<QScrollArea> mp_scroll_area;
    double                       m_scale;

    /// actions
    QAction* mp_save_as_action;

    QAction* mp_fit_to_window;
    QAction* mp_zoom_in;
    QAction* mp_zoom_out;
    QAction* mp_normal_size;

    /// filtering menu
    QMenu* mp_filter_menu;
    QAction* mp_box5x5_filter;
    QAction* mp_gaussian5x5_filter;
    QAction* mp_circular5x5_filter;

    QAction* mp_gray_scale;

    QAction* mp_invert;

    BoxFilterWidget* mp_box_filter_widget = nullptr;

    // actions setup
    void _CreateActions();
    void _CreateFileMenuActions();
    void _CreateOperationsMenuActions();
    void _CreateViewMenuActions();
    void _UpdateActions();

    // IO
    bool _LoadImage(const QString & i_filename);
    bool _SaveImage(const QString & i_filename);
    
    void _SetImage(const QImage & i_image);
    
    // scale
    void _FitToWindow();
    void _NormalSize();
    void _ZoomIn();
    void _ZoomOut();
    void _ScaleImage(double i_factor);
    void _AdjustScrollBar(QScrollBar* op_scroll_bar, double i_factor);

    void _Box5x5Filter();
    void _Gaussian5x5Filter();
    void _Circular5x5Filter();
    void _ToGrayScale();

    void _Invert();
  };
