#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QMatrix4x4>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QBasicTimer>

class Object3D;
class Transformational;
class Object3DGroup;
class Eye;
class SkyBox;

class OGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    OGLWidget(QWidget *parent = nullptr);
    ~OGLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void timerEvent(QTimerEvent* event);

    void initShaders();
    void initParallelogram(float width, float height, float depth, const QString &texturepath, const QString &normalpath);

private:
    QMatrix4x4 m_ProjectionMatrix;
    QOpenGLShaderProgram m_ProgramObject;
    QOpenGLShaderProgram m_ProgramSkyBox;
    QVector2D m_MousePosition;
    QQuaternion m_Rotation;
    QVector<Object3D*> m_Objects;
    QVector<Object3DGroup*> m_Groups;
    Object3DGroup* m_GlobalGroup;
    Eye* m_Eye;
    SkyBox* m_SkyBox;
    QBasicTimer m_Timer;

    double m_AngleObject;
    double m_AngleGrop1;
    double m_AngleGrop2;
    double m_AngleGrop3;
    double m_AngleGrop4;
    double m_AngleGropMain;
    int currentGroup;
};

#endif // OGLWIDGET_H
