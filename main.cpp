#include <QtWidgets/QApplication>
#include <QtGui/qguiapplication.h>

#include <QtGui/qopenglwindow.h>
#include <QtGui/qopenglbuffer.h>
#include <QtGui/qopenglfunctions.h>
#include <QtGui/qopenglshaderprogram.h>
#include <QtGui/qopenglvertexarrayobject.h>
#include <qstring.h>
#include "viewer.h"


#include "viewer.h"
using std::vector;

static QString vertexShader =
    "#version 330 core\n"
    "\n"
    "layout(location = 0) in vec3 vertexPosition;\n"
    "layout(location = 1) in vec3 vertexNormal;\n"
    "\n"
    "out vec3 normal;\n"
    "out vec3 position;\n"
    "\n"
    "uniform mat4 MV;\n"
    "uniform mat3 N;\n"
    "uniform mat4 MVP;\n"
    " \n"
    "void main()\n"
    "{\n"
    "    normal = normalize( N * vertexNormal );\n"
    "    position = vec3( MV * vec4( vertexPosition, 1.0 ) );\n"
    "    gl_Position = MVP * vec4( vertexPosition, 1.0 );\n"
    "}\n"
    ;

static QString fragmentShader =
    "#version 330 core\n"
    "\n"
    "in vec3 normal;\n"
    "in vec3 position;\n"
    "\n"
    "layout (location = 0) out vec4 fragColor;\n"
    "\n"
    "struct Light\n"
    "{\n"
    "    vec4 position;\n"
    "    vec3 intensity;\n"
    "};\n"
    "uniform Light light;\n"
    "\n"
    "struct Material {\n"
    "    vec3 Ka;\n"
    "    vec3 Kd;\n"
    "    vec3 Ks;\n"
    "    float shininess;\n"
    "};\n"
    "uniform Material material;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    vec3 n = normalize( normal);\n"
    "    vec3 s = normalize( light.position.xyz - position);\n"
    "    vec3 v = normalize( -position.xyz);\n"
    "    vec3 h = normalize( v + s);\n"
    "    float sdn = dot( s, n);\n"
    "    vec3 ambient = material.Ka;\n"
    "    vec3 diffuse = material.Kd * max( sdn, 0.0);\n"
    "    vec3 specular = material.Ks * mix( 0.0, pow( dot(h, n), material.shininess), step( 0.0, sdn));\n"
    "    fragColor = vec4(light.intensity * (ambient + diffuse + specular), 1);\n"
    "}\n"
    ;

struct Window : QOpenGLWindow, QOpenGLFunctions
{
    Window() :
        m_vbo(QOpenGLBuffer::VertexBuffer),
        m_nbo(QOpenGLBuffer::VertexBuffer),
        m_ibo(QOpenGLBuffer::IndexBuffer)
    {
    }

    void createShaderProgram()
    {
        if (!m_pgm.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShader)) {
            qDebug() << "Error in vertex shader:" << m_pgm.log();
            exit(1);
        }
        if (!m_pgm.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShader)) {
            qDebug() << "Error in fragment shader:" << m_pgm.log();
            exit(1);
        }
        if (!m_pgm.link()) {
            qDebug() << "Error linking shader program:" << m_pgm.log();
            exit(1);
        }
    }

    void createGeometry()
    {
        // TODO: Add your own mesh data (from hapPLY) in here as member variables.
        // You should have something like the following available:

        // Initialize and bind the VAO that's going to capture all this vertex state
        m_vao.create();
        m_vao.bind();

        // Put all the vertex data in a FBO
        m_vbo.create();
        m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_vbo.bind();
        //m_vbo.allocate(&(*vPos)[0], vPos->size() * sizeof((*vPos)[0]));

        // Configure the attribute stream
        m_pgm.enableAttributeArray(0);
        m_pgm.setAttributeBuffer(0, GL_FLOAT, 0, 3);

        // Put all the normal data in a FBO
        m_nbo.create();
        m_nbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_nbo.bind();
        //m_nbo.allocate(&(*normals)[0], normals->size() * sizeof((*normals)[0]));

        // Configure the attribute stream
        m_pgm.enableAttributeArray(1);
        m_pgm.setAttributeBuffer(1, GL_FLOAT, 0, 3);

        // Put all the index data in a IBO
        m_ibo.create();
        m_ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_ibo.bind();
        //m_ibo.allocate(&(*fInd)[0], fInd->size() * sizeof((*fInd)[0]));

        // Okay, we've finished setting up the vao
        m_vao.release();
    
    }

    void initializeGL()
    {
        QOpenGLFunctions::initializeOpenGLFunctions();
        createShaderProgram(); m_pgm.bind();

        m_pgm.setUniformValue("light.position", QVector4D(-1.0f, 1.0f, 1.0f, 1.0f));
        m_pgm.setUniformValue("light.intensity", QVector3D(1.0f, 1.0f, 1.0f));

        createGeometry();
        m_view.setToIdentity();
        m_view.lookAt(QVector3D(0.0f, 0.0f, 1.2f),    // Camera Position
            QVector3D(0.0f, 0.0f, 0.0f),    // Point camera looks towards
            QVector3D(0.0f, 1.0f, 0.0f));   // Up vector

        glEnable(GL_DEPTH_TEST);

        glClearColor(.9f, .9f, .93f, 1.0f);
    }

    void resizeGL(int w, int h)
    {
        glViewport(0, 0, w, h);
        m_projection.setToIdentity();
        m_projection.perspective(60.0f, (float)w / h, .3f, 1000);
        update();
    }

    void draw()
    {
        QMatrix4x4 model;
        model.translate(-0.2f, 0.0f, .5f);
        model.rotate(55.0f, 0.0f, 1.0f, 0.0f);

        // Prepare matrices
        QMatrix4x4 mv = m_view * model;

        m_pgm.setUniformValue("MV", mv);
        m_pgm.setUniformValue("N", mv.normalMatrix());
        m_pgm.setUniformValue("MVP", m_projection * mv);

        m_pgm.setUniformValue("material.Ka", QVector3D(0.05f, 0.2f, 0.05f));
        m_pgm.setUniformValue("material.Kd", QVector3D(0.3f, 0.5f, 0.3f));
        m_pgm.setUniformValue("material.Ks", QVector3D(0.6f, 0.6f, 0.6f));
        m_pgm.setUniformValue("material.shininess", 50.f);

         //glDrawElements(GL_TRIANGLES, fInd.size(), GL_UNSIGNED_INT, (const GLvoid*)(fInd * sizeof(GLuint)));
    }

    void paintGL()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_pgm.bind();
        m_vao.bind();
        draw();
        m_vao.release();

        update();
    }


    //ModelLoader              m_loader;
    QMatrix4x4 m_projection, m_view;
    QOpenGLShaderProgram     m_pgm;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer            m_vbo, m_nbo;
    QOpenGLBuffer            m_ibo;
    GLsizei                  m_cnt;
};



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSurfaceFormat f;
    f.setMajorVersion(3);
    f.setMinorVersion(3);
    f.setProfile(QSurfaceFormat::CoreProfile);
    viewer w;
    w.show();
    
    return a.exec();



}

