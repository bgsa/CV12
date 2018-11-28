#include "Panel.h"

void Panel::init()
{
	string vertexShaderSource = "#version 300 es \n"
		"uniform mat4 projectionView; \n"
		"uniform mat4 model; \n"
		"uniform vec4 Color; \n"

		"in  vec2 Position; \n"
		"in  vec2 Texture; \n"
		
		"out vec4 fragmentColor; \n"
		"out vec2 textureCoordinate; \n"

		"void main() \n"
		"{													\n"
		"	gl_Position = projectionView * model * vec4(Position, 0.0, 1.0); \n"
		"	fragmentColor = Color; \n"
		"	textureCoordinate = Texture; \n"
		"}													\n";


	string fragmentShaderSource = "#version 300 es \n"
		"precision mediump float; \n"
		
		"in vec4 fragmentColor; \n"
		"in vec2 textureCoordinate; \n"

		"out vec4 FragColor; \n"

		"uniform sampler2D inputImageTexture; \n"

		"uniform int useHomography; \n"
		"uniform mat3 inverseHomographyMatrix; \n"

		"void main() \n"
		"{ \n"
			"float width = 800.0f; \n"
			"float height = 600.0f; \n"

			"if (useHomography == 0) \n"
				"FragColor = texture(inputImageTexture, textureCoordinate) * fragmentColor; \n"
			"else \n"
			"{ \n"
				"vec3 frameCoordinate = vec3(textureCoordinate.x * width, textureCoordinate.y * height, 1.0); \n"

				"vec3 m = inverseHomographyMatrix[2] * frameCoordinate; \n"
				"float zed = 1.0 / (m.x + m.y + m.z); \n"
				"frameCoordinate = frameCoordinate * zed; \n"

				"float xTrans = inverseHomographyMatrix[0][0] * frameCoordinate.x + inverseHomographyMatrix[0][1] * frameCoordinate.y + inverseHomographyMatrix[0][2] * frameCoordinate.z; \n"
				"float yTrans = inverseHomographyMatrix[1][0] * frameCoordinate.x + inverseHomographyMatrix[1][1] * frameCoordinate.y + inverseHomographyMatrix[1][2] * frameCoordinate.z; \n"

				"vec2 coords = vec2(xTrans / width, yTrans / height); \n"

				"if (coords.x >= 0.0 && coords.x <= 1.0 && coords.y >= 0.0 && coords.y <= 1.0) \n"
					"FragColor = texture(inputImageTexture, coords); \n"
				"else \n"
					"FragColor = vec4(0.0, 0.0, 0.0, 0.0); \n"
			"} \n"
		"} \n";

	/*
	string fragmentShaderSource = "#version 300 es \n"
		"precision mediump float; \n"

		"in  vec4 fragmentColor; \n"
		"in  vec2 fragmentTexture; \n"

		"out vec4 FragColor; \n"
		"uniform sampler2D tex; \n"

		"void main() \n"
		"{           \n"
			"FragColor = texture(tex, fragmentTexture) * fragmentColor; \n"
		"}";
		*/

	programShader = Shader::loadShaderProgram(vertexShaderSource.c_str(), fragmentShaderSource.c_str());

	initVBO();
}

void Panel::setUpPositionAttribute()
{
	glVertexAttribPointer(positionAttribute,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		0); //Specify that our coordinate data is going into attribute index 0(shaderAttribute), and contains three floats per vertex
	glEnableVertexAttribArray(positionAttribute); //habilita atributo de coordenadas
}

void Panel::setUpTextureAttribute()
{
	if (!hasBackgroundImage())
		return;

	glVertexAttribPointer(textureAttribute,
		2, //quantidad de valores por vertices da textura
		GL_FLOAT,		   // o tipo de cada elementos
		GL_FALSE,          // estado dos nossos valores.
		0,					// sem dados intercalados em cada posição da textura, ou seja, os valores da texturas estão contíguos no array de vértices
		(void*)sizeof(panelAttributes.position) // deslocamento do primeiro elemento
	);
	glEnableVertexAttribArray(textureAttribute);
}

void Panel::setUpImage(string filename)
{
	Image *image = ImageFactory::load(filename.c_str());
	unsigned char* pixels = image->getData();
	GLsizei width = image->getWidth();
	GLsizei height = image->getHeight();
	GLenum colorFormat = image->getColorFormat();

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//caso utilize mipmap ...
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//set texture border color
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

	glTexImage2D(GL_TEXTURE_2D, //target
		0, //level
		colorFormat, //GL_RGB, //internalFormat
		width, //width,
		height, //height,
		0, //border
		colorFormat, //format GL_RGB  or GL_RGBA (format of data read from textel file) (GL_RGB for *.bmp files and GL_RGBA for *.rgb files) GL_ALPHA GL_RGB GL_RGBA GL_LUMINANCE GL_LUMINANCE_ALPHA
		GL_UNSIGNED_BYTE, //type , GL_FLOAT
		pixels); //const void *pixels

	delete image;
}

void Panel::setBackgroundImage(string filename) 
{
	backgroundImage = filename;
}

bool Panel::hasBackgroundImage() 
{
	return backgroundImage != "";
}

void Panel::initVBO()
{	
	cout << "vbo1" << endl;

	glGenBuffers(1, &vertexBufferObject);  //aloca o buffr
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject); //associa o bufffer ao ponteiro
	glBufferData(GL_ARRAY_BUFFER, sizeof(PanelShaderAttributes), &panelAttributes, GL_STATIC_DRAW);  //insere os dados no buffer para usar glDraw*
	
	projectionViewLocation = glGetUniformLocation(programShader, "projectionView");
	modelViewLocation = glGetUniformLocation(programShader, "model");	
	colorLocation = glGetUniformLocation(programShader, "Color");
	cout << "vbo2" << endl;
	
	positionAttribute = glGetAttribLocation(programShader, "Position");
	textureAttribute = glGetAttribLocation(programShader, "Texture");

	useHomographyLocation = glGetUniformLocation(programShader, "useHomography");
	inverseHomographyMatrixLocation = glGetUniformLocation(programShader, "inverseHomographyMatrix");
	
	setUpPositionAttribute();

	cout << "vbo3" << endl;

	setUpTextureAttribute();

	cout << "vbo4" << endl;
		
	if (hasBackgroundImage())
		setUpImage(backgroundImage);

	cout << "vbo5" << endl;
}

void Panel::render(Mat4f projectionViewMatrix)
{
	glUseProgram(programShader);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

	if (hasBackgroundImage())
		glBindTexture(GL_TEXTURE_2D, texture);

	glUniformMatrix4fv(projectionViewLocation, 1, GL_FALSE, projectionViewMatrix);
	glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, modelView);
	glUniform4f(colorLocation, color->Red, color->Green, color->Blue, color->Alpha);

	glUniform1i(useHomographyLocation, useHomography);
	glUniformMatrix3fv(inverseHomographyMatrixLocation, 1, GL_FALSE, homographyMatrix);
	
	setUpPositionAttribute();
	setUpTextureAttribute();	

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

Panel::~Panel()
{
	if (texture != 0 && glIsTexture(texture) )
		glDeleteTextures(1, &texture);
}