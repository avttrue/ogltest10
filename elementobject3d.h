#ifndef ELEMENTOBJECT3D_H
#define ELEMENTOBJECT3D_H

#include "transformational.h"

#include<QOpenGLBuffer>
#include<QMatrix4x4>
#include<QVector2D>

class QOpenGLTexture;
class QOpenGLShaderProgram;
class QOpenGLFunctions;
class Material;

struct VertexData
{
    VertexData() {}
    VertexData(QVector3D p, QVector2D t, QVector3D n)
        : position(p), textcoord(t), normal(n) {}
    QVector3D position;
    QVector2D textcoord;
    QVector3D normal;
    QVector3D tangent;
    QVector3D bitangent;
};

class ElementObject3D : public Transformational
{
public:
    ElementObject3D();
    ElementObject3D(const QVector<VertexData> &vert, const QVector<GLuint> &ind, Material* mat);
    ~ElementObject3D();

    void init(const QVector<VertexData> &vert, const QVector<GLuint> &ind, Material* mat);
    void draw(QOpenGLShaderProgram* program, QOpenGLFunctions* functions);
    void rotate(const QQuaternion &r);
    void translate(const QVector3D &t);
    void scale(const float &s);
    void setGlobalTransform(const QMatrix4x4 &gt);

protected:
    void free();

private:
    QOpenGLBuffer m_VertexBuffer;
    QOpenGLBuffer m_IndexBuffer;
    QOpenGLTexture* m_DiffuseMap = nullptr;
    QOpenGLTexture* m_NormalMap = nullptr;
    QQuaternion m_Rotate;
    QVector3D m_Translate;
    float m_Scale;
    QMatrix4x4 m_GlobalTransform;
    Material* m_Material;
};

#endif // ELEMENTOBJECT3D_H
