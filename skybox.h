#ifndef SKYBOX_H
#define SKYBOX_H

#include "transformational.h"

#include <QQuaternion>
#include <QVector3D>
#include <QMatrix4x4>

class EngineObject3D;
class QImage;

class SkyBox : public Transformational
{
public:
    SkyBox(float width, const QImage &img);
    SkyBox(float width, const QString &str);
    ~SkyBox();
    void draw(QOpenGLShaderProgram* program, QOpenGLFunctions*functions = nullptr);
    void rotate(const QQuaternion &r);
    void translate(const QVector3D &t);
    void scale(const float &s);
    void setGlobalTransform(const QMatrix4x4 &gt);

private:
    EngineObject3D* m_Box;
};

#endif // SKYBOX_H
