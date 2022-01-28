
#include "TPVideoWidget.h"
#include <QDebug>
#include <QTimer>
extern "C" {
#include <libavutil/frame.h>
}
//自动加双引号
#define GET_STR(x) #x
#define A_VER 3
#define T_VER 4

FILE *fp = NULL;
ITPVideoWidget *g_pVideoWidget = Q_NULLPTR;

//顶点shader
const char *vString = GET_STR(
	attribute vec4 vertexIn;
attribute vec2 textureIn;
varying vec2 textureOut;
void main(void)
{
	gl_Position = vertexIn;
	textureOut = textureIn;
}
);


//片元shader
const char *tString = GET_STR(
	varying vec2 textureOut;
uniform sampler2D tex_y;
uniform sampler2D tex_u;
uniform sampler2D tex_v;
void main(void)
{
	vec3 yuv;
	vec3 rgb;
	yuv.x = texture2D(tex_y, textureOut).r;
	yuv.y = texture2D(tex_u, textureOut).r - 0.5;
	yuv.z = texture2D(tex_v, textureOut).r - 0.5;
	rgb = mat3(1.0, 1.0, 1.0,
		0.0, -0.39465, 2.03211,
		1.13983, -0.58060, 0.0) * yuv;
	gl_FragColor = vec4(rgb, 1.0);
}

);



//准备yuv数据
// ffmpeg -i v1080.mp4 -t 10 -s 240x128 -pix_fmt yuv420p  out240x128.yuv
TPVideoWidget::TPVideoWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
}

TPVideoWidget::~TPVideoWidget()
{
}

void TPVideoWidget::Repaint(AVFrame *frame)
{

	if (!frame)return;
	m_videoMux.lock();
	//容错，保证尺寸正确
	if (!m_datas[0] || m_width*m_height == 0 || frame->width != this->m_width || frame->height != this->m_height)
	{
		av_frame_free(&frame);
		m_videoMux.unlock();
		return;
	}
	if (m_width == frame->linesize[0]) //无需对齐
	{
		memcpy(m_datas[0], frame->data[0], m_width*m_height);
		memcpy(m_datas[1], frame->data[1], m_width*m_height / 4);
		memcpy(m_datas[2], frame->data[2], m_width*m_height / 4);
	}
	else//行对齐问题
	{
		for(int i = 0; i < m_height; i++) //Y 
			memcpy(m_datas[0] + m_width*i, frame->data[0] + frame->linesize[0]*i, m_width);
		for (int i = 0; i < m_height/2; i++) //U
			memcpy(m_datas[1] + m_width/2*i, frame->data[1] + frame->linesize[1] * i, m_width);
		for (int i = 0; i < m_height/2; i++) //V
			memcpy(m_datas[2] + m_width/2*i, frame->data[2] + frame->linesize[2] * i, m_width);

	}
	
	m_videoMux.unlock();
	av_frame_free(&frame);
	//qDebug() << "刷新显示" << endl;
	//刷新显示
	update();
}
QWidget *TPVideoWidget::getVideoWidget()
{
    return this;
}

ITPVideoWidget *TPVideoWidget::getInstance()
{
    if(g_pVideoWidget == Q_NULLPTR)
    {
        g_pVideoWidget = new TPVideoWidget;
    }
    return g_pVideoWidget;
}

void TPVideoWidget::Init(int width, int height)
{
	m_videoMux.lock();
	this->m_width = width;
	this->m_height = height;
	delete m_datas[0];
	delete m_datas[1];
	delete m_datas[2];
	///分配材质内存空间
	m_datas[0] = new unsigned char[width*height];		//Y
	m_datas[1] = new unsigned char[width*height / 4];	//U
	m_datas[2] = new unsigned char[width*height / 4];	//V


	if (m_texs[0])
	{
		glDeleteTextures(3, m_texs);
	}
	//创建材质
	glGenTextures(3, m_texs);

	//Y
	glBindTexture(GL_TEXTURE_2D, m_texs[0]);
	//放大过滤，线性插值   GL_NEAREST(效率高，但马赛克严重)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//创建材质显卡空间
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RED_NV, width, height, 0, GL_RED_NV, GL_UNSIGNED_BYTE, 0);

	//U
	glBindTexture(GL_TEXTURE_2D, m_texs[1]);
	//放大过滤，线性插值
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//创建材质显卡空间
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED_NV, width / 2, height / 2, 0, GL_RED_NV, GL_UNSIGNED_BYTE, 0);

	//V
	glBindTexture(GL_TEXTURE_2D, m_texs[2]);
	//放大过滤，线性插值
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//创建材质显卡空间
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED_NV, width / 2, height / 2, 0, GL_RED_NV, GL_UNSIGNED_BYTE, 0);


	m_videoMux.unlock();


}
//初始化opengl
void TPVideoWidget::initializeGL()
{
	qDebug() << "initializeGL";
	m_videoMux.lock();
	//初始化opengl （QOpenGLFunctions继承）函数 
	initializeOpenGLFunctions();

	//program加载shader（顶点和片元）脚本
	//片元（像素）
	qDebug() << m_program.addShaderFromSourceCode(QGLShader::Fragment, tString);
	//顶点shader
	qDebug() << m_program.addShaderFromSourceCode(QGLShader::Vertex, vString);

	//设置顶点坐标的变量
	m_program.bindAttributeLocation("vertexIn", A_VER);

	//设置材质坐标
	m_program.bindAttributeLocation("textureIn", T_VER);

	//编译shader
	qDebug() << "program.link() = " << m_program.link();

	qDebug() << "program.bind() = " << m_program.bind();

	//传递顶点和材质坐标
	//顶点
	static const GLfloat ver[] = {
		-1.0f,-1.0f,
		1.0f,-1.0f,
		-1.0f, 1.0f,
		1.0f,1.0f
	};

	//材质
	static const GLfloat tex[] = {
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f
	};

	//顶点
	glVertexAttribPointer(A_VER, 2, GL_FLOAT, 0, 0, ver);
	glEnableVertexAttribArray(A_VER);

	//材质
	glVertexAttribPointer(T_VER, 2, GL_FLOAT, 0, 0, tex);
	glEnableVertexAttribArray(T_VER);


	//从shader获取材质
	m_unis[0] = m_program.uniformLocation("tex_y");
	m_unis[1] = m_program.uniformLocation("tex_u");
	m_unis[2] = m_program.uniformLocation("tex_v");

	m_videoMux.unlock();

	//fp = fopen("out240x128.yuv", "rb");
	//if (!fp)
	//{
	//	qDebug() << "out240x128.yuv file open failed!";
	//}


	////启动定时器
	//QTimer *ti = new QTimer(this);
	//connect(ti, SIGNAL(timeout()), this, SLOT(update()));
	//ti->start(40);
}

//刷新显示
void TPVideoWidget::paintGL()
{
	//if (feof(fp))
	//{
	//	fseek(fp, 0, SEEK_SET);
	//}
	//fread(datas[0], 1, width*height, fp);
	//fread(datas[1], 1, width*height / 4, fp);
	//fread(datas[2], 1, width*height / 4, fp);
	m_videoMux.lock();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texs[0]); //0层绑定到Y材质
										   //修改材质内容(复制内存内容)
        //glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_RED, GL_UNSIGNED_BYTE, m_datas[0]);
	//与shader uni遍历关联
	glUniform1i(m_unis[0], 0);


	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, m_texs[1]); //1层绑定到U材质
										   //修改材质内容(复制内存内容)
        //glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width / 2, m_height / 2, GL_RED, GL_UNSIGNED_BYTE, m_datas[1]);
	//与shader uni遍历关联
	glUniform1i(m_unis[1], 1);


	glActiveTexture(GL_TEXTURE0 + 2);
	glBindTexture(GL_TEXTURE_2D, m_texs[2]); //2层绑定到V材质
										   //修改材质内容(复制内存内容)
        //glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width / 2, m_height / 2, GL_RED, GL_UNSIGNED_BYTE, m_datas[2]);
	//与shader uni遍历关联
	glUniform1i(m_unis[2], 2);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	//qDebug() << "paintGL";
	m_videoMux.unlock();
}


// 窗口尺寸变化
void TPVideoWidget::resizeGL(int width, int height)
{
	m_videoMux.lock();
	qDebug() << "resizeGL " << width << ":" << height;
	m_videoMux.unlock();
}
