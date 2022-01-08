#ifndef TPVIDEOWIDGET_H
#define TPVIDEOWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QGLShaderProgram>
#include <mutex>
#include "ITPVideoWidget.h"

struct AVFrame;
class TPVideoWidget : public QOpenGLWidget, protected QOpenGLFunctions,public ITPVideoWidget
{
	Q_OBJECT
private:
    TPVideoWidget(){}
public:
    static ITPVideoWidget *getInstance();
    QWidget *getVideoWidget() override;

    void Init(int m_width, int m_height) override;

	//不管成功与否都释放frame空间
    void Repaint(AVFrame *frame) override;

    TPVideoWidget(QWidget *parent);
    ~TPVideoWidget();
protected:
	//刷新显示
    void paintGL() override;

	//初始化gl
    void initializeGL() override;

	// 窗口尺寸变化
    void resizeGL(int m_width, int m_height) override;
private:
    std::mutex m_videoMux;

	//shader程序
    QGLShaderProgram m_program;

	//shader中yuv变量地址
    GLuint m_unis[3] = { 0 };
	//openg的 texture地址
    GLuint m_texs[3] = { 0 };

	//材质内存空间
    unsigned char *m_datas[3] = { 0 };

    int m_width = 240;
    int m_height = 128;

};

#endif
