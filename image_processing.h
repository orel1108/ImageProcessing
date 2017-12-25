#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>

class QAction;
class QLabel;
class QScrollArea;
class QScrollBar;

class ImageProcessing : public QMainWindow
{
    Q_OBJECT
public:
    explicit ImageProcessing(QWidget * ip_parent = nullptr);

    bool LoadImage(const QString & i_filename);

private slots:
    void _Open();
    void _SaveAs();

private:
    QImage       m_image;
    QLabel*      mp_image_label;
    QScrollArea* mp_scroll_area;
    double       m_scale;

    /// actions
    QAction*     mp_save_as;
    QAction*     mp_fit_to_window;
    QAction*     mp_zoom_in;
    QAction*     mp_zoom_out;
    QAction*     mp_normal_size;

    void _CreateActions();
    void _SetImage(const QImage & i_image);
    bool _SaveImage(const QString & i_filename);
    void _UpdateActions();
    void _FitToWindow();
    void _NormalSize();
    void _ZoomIn();
    void _ZoomOut();
    void _ScaleImage(double i_factor);
    void _AdjustScrollBar(QScrollBar* op_scroll_bar, double i_factor);
};

#endif // IMAGEVIEWER_H
