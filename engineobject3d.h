#ifndef ENGINEOBJECT3D_H
#define ENGINEOBJECT3D_H

#include "elementobject3d.h"
#include "materiallibrary.h"

#include <QVector>

class EngineObject3D :public Transformational
{
public:
    EngineObject3D(){}
    ~EngineObject3D();
    bool load(const QString &filename);
    void add(ElementObject3D* obj);
    ElementObject3D* get(int index);
    void calculateTBN(QVector<VertexData> &vertdata);

    virtual void rotate(const QQuaternion &r);
    virtual void translate(const QVector3D &t);
    virtual void scale(const float &s);
    virtual void setGlobalTransform(const QMatrix4x4 &gt);
    virtual void draw(QOpenGLShaderProgram* program, QOpenGLFunctions* functions);

private:
    QVector<ElementObject3D*> m_Elements;
    MaterialLibrary m_MatLibrary;
};

#endif // ENGINEOBJECT3D_H
