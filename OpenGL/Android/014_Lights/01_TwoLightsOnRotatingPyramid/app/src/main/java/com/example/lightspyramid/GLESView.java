package com.example.lightspyramid;

import android.content.Context;

import android.view.MotionEvent;
import android.view.GestureDetector;
import android.view.GestureDetector.OnGestureListener;
import android.view.GestureDetector.OnDoubleTapListener;

import android.opengl.GLSurfaceView;				// OGL SurfaceView and related
import android.opengl.GLES32;						// for OpenGLES32
import android.opengl.Matrix;
import javax.microedition.khronos.opengles.GL10;	// OpenGLES 1.0 needed for param GL10
import javax.microedition.khronos.egl.EGLConfig;	// for EGLConfig

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.util.ArrayList;
import java.util.List;

public class GLESView extends GLSurfaceView implements GLSurfaceView.Renderer,
	OnGestureListener, OnDoubleTapListener
{
	// variables declaration
	private GestureDetector grgestureDetector;
	private final Context grcontext;

	private int grvertexShaderObject;
	private int grfragmentShaderObject;
	private int grshaderProgramObject;

	private int[] grvaoPyramid = new int[1];
	private int[] grvboPositionPyramid = new int[1];
	private int[] grvboNormalPyramid = new int[1];

	private int grmodelMatrixUniform;
	private int grviewMatrixUniform;
	private int grprojectionMatrixUniform;
	private int grlKeyPressedUniform;
	private int grkdUniform;
	private int grkaUniform;
	private int grksUniform;
	private int grmaterialShinynessUniform;

	private int grldUniform[] = new int[2];
	private int grlaUniform[] = new int[2];
	private int grlsUniform[] = new int[2];
	private int grlightPositionUniform[] = new int[2];

	float grKa[] = {0.0f, 0.0f, 0.0f, 1.0f};
	float grKd[] = {1.0f, 1.0f, 1.0f, 1.0f};
	float grKs[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float grmaterialShinyness = 128.0f;
    List<Light> grlightList = new ArrayList<>(2);
	// angle
	float grfangleTriangle = 0.0f;
	float grfangleSquare = 0.0f;
	int i;
	boolean grbLight = false;
	boolean grbAnimate = false;

	private float grperspectiveMatrix[] = new float[16];

	public GLESView(Context drawingContext)
	{
		super(drawingContext);
		grcontext = drawingContext;

		// set EGLContext to current supported version of opengl
		setEGLContextClientVersion(3);
		// set rendered for drawing on GLSurfaceView
		setRenderer(this);

		// render the view when there is change in drawing data
		setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);

		// gestureDetector is same as handler (who is going to handle events)
		grgestureDetector = new GestureDetector(grcontext, this, null, false);
		grgestureDetector.setOnDoubleTapListener(this);
	}

	// overridden method of GLSurfaceView.Renderer
	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config)
	{
		// Opengles version check
		String version = gl.glGetString(GL10.GL_VERSION);
		String glslVersion = gl.glGetString(GLES32.GL_SHADING_LANGUAGE_VERSION);
		System.out.println("OGL_GR : OGLES version : " + version);
		System.out.println("OGL_GR : GLSL Vrsion : " + glslVersion);

		initialize(gl);
	}

	// overridden method of GLSurfaceView.Renderer
	@Override
	public void onSurfaceChanged(GL10 unused, int width, int height)
	{
		System.out.println("OGL_GR : in onSurfaceChanged");
		resize(width, height);
	}

	// overridden method of GLSurfaceView.Renderer
	@Override
	public void onDrawFrame(GL10 unused)
	{
		display();
	}

	@Override
	public boolean onTouchEvent(MotionEvent event)
	{
		int eventAction = event.getAction();
		if(!grgestureDetector.onTouchEvent(event))
		{
			super.onTouchEvent(event);
		}
		return(true);
	}

	@Override
	public boolean onDoubleTap(MotionEvent e)
	{
	    grbAnimate = !grbAnimate;
		return(true);
	}

	@Override
	public boolean onDoubleTapEvent(MotionEvent e)
	{
		return(true);
	}

	@Override
	public boolean onSingleTapConfirmed(MotionEvent e)
	{
	    grbLight = !grbLight;
		return(true);
	}

	@Override
	public boolean onDown(MotionEvent e)
	{
		return(true);
	}

	@Override
	public boolean onFling(MotionEvent e1, MotionEvent e2,
		float distanceX, float distanceY)
	{
		return(true);
	}

	@Override
	public void onLongPress(MotionEvent e)
	{

	}

	@Override
	public boolean onScroll(MotionEvent e1, MotionEvent e2,
		float distanceX, float distanceY)
	{
		// exit the application if scrolled
		uninitialize();
		System.exit(0);
		return(true);
	}

	@Override
	public void onShowPress(MotionEvent e)
	{
	}

	@Override
	public boolean onSingleTapUp(MotionEvent e)
	{
		return(true);
	}

	// user defined methods

	private void initialize(GL10 gl)
	{
		System.out.println("OGL_GR : in initialize");
		///////////////// Vertex Shader
		//create shader
		grvertexShaderObject = GLES32.glCreateShader(GLES32.GL_VERTEX_SHADER);

		// vertex shader source code
		final String grvertexShaderSourceCode = String.format(
				"#version 320 es" +
				"\n" +
				"in vec4 vPosition;" +
				"in vec3 vNormal;" +
				"uniform mat4 u_model_matrix;" +
				"uniform mat4 u_view_matrix;" +
				"uniform mat4 u_projection_matrix;" +
				"uniform int u_l_key_pressed;" +
				"uniform vec3 u_la[2];" +
				"uniform vec3 u_ld[2];" +
				"uniform vec3 u_ls[2];" +
				"uniform vec3 u_ka;" +
				"uniform vec3 u_kd;" +
				"uniform vec3 u_ks;" +
				"uniform float u_material_shinyness;" +
				"uniform vec4 u_light_position[2];" +
				"out vec3 phong_ads_light;" +
				"int i;" +
				"void main(void)" +
				"{" +
				"if(u_l_key_pressed == 1)" +
				"{" +
				"vec4 eye_coordinates =  u_view_matrix * u_model_matrix * vPosition;" +
				"vec3 transformed_normal = normalize(mat3(u_view_matrix * u_model_matrix) * vNormal);" +
				"vec3 view_vector = normalize(-eye_coordinates.xyz);" +
				"vec3 light_direction[2];" +
				"vec3 reflection_vector[2];" +
				"vec3 ambient[2];" +
				"vec3 diffuse[2];" +
				"vec3 specular[2];" +
				"for(i = 0; i < 2; i++)" +
				"{" +
				"light_direction[i] = normalize(vec3(u_light_position[i] - eye_coordinates));" +
				"reflection_vector[i] = reflect(-light_direction[i], transformed_normal);" +
				"ambient[i] = u_la[i] * u_ka;" +
				"diffuse[i] = u_ld[i] * u_kd * max(dot(light_direction[i], transformed_normal), 0.0);" +
				"specular[i] = u_ls[i] * u_ks * pow(max(dot(reflection_vector[i], view_vector), 0.0), u_material_shinyness);" +
				"phong_ads_light = phong_ads_light + ambient[i] + diffuse[i] + specular[i];" +
				"}" +
				"}" +
				"else" +
				"{" +
				"phong_ads_light = vec3(1.0, 1.0, 1.0);" +
				"}" +
				"gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vPosition;" +
				"}"
		);

		// provide source code to shader
		GLES32.glShaderSource(grvertexShaderObject, grvertexShaderSourceCode);

		// compile shader and check for error
		GLES32.glCompileShader(grvertexShaderObject);
		int[] griShaderCompileStatus = new int[1];
		int[] griInfoLength = new int[1];
		String grszInfoLog = null;

		GLES32.glGetShaderiv(grvertexShaderObject, GLES32.GL_COMPILE_STATUS,
			griShaderCompileStatus, 0);
		if(griShaderCompileStatus[0] == GLES32.GL_FALSE)
		{
			GLES32.glGetShaderiv(grvertexShaderObject, GLES32.GL_INFO_LOG_LENGTH,
				griInfoLength, 0);

			if(griInfoLength[0] > 0)
			{
				grszInfoLog = GLES32.glGetShaderInfoLog(grvertexShaderObject);
				System.out.println("OGL_GR : Vertex shader compilation log : " + grszInfoLog);
				uninitialize();
				System.exit(0);
			}
		}

		////////// Fragment shader
		// create shader
		grfragmentShaderObject = GLES32.glCreateShader(GLES32.GL_FRAGMENT_SHADER);

		// fragment shader source code
		final String grfragmentShaderSourceCode = String.format(
				"#version 320 es" +
				"\n" +
				"precision highp float;" +
				"in vec3 phong_ads_light;" +
				"out vec4 FragColor;" +
				"void main(void)" +
				"{" +
				"FragColor = vec4(phong_ads_light, 1.0);" +
				"}"
		);

		// provide source code to shader
		GLES32.glShaderSource(grfragmentShaderObject, grfragmentShaderSourceCode);

		// compile shader
		GLES32.glCompileShader(grfragmentShaderObject);
		griShaderCompileStatus[0] = 0;
		griInfoLength[0] = 0;
		grszInfoLog = null;
		GLES32.glGetShaderiv(grfragmentShaderObject, GLES32.GL_COMPILE_STATUS,
			griShaderCompileStatus, 0);
		if(griShaderCompileStatus[0] == GLES32.GL_FALSE)
		{
			GLES32.glGetShaderiv(grfragmentShaderObject, GLES32.GL_INFO_LOG_LENGTH, griInfoLength, 0);

			if(griInfoLength[0] > 0)
			{
				grszInfoLog = GLES32.glGetShaderInfoLog(grfragmentShaderObject);
				System.out.println("OGL_GR : Fragment shader compilation log : " + grszInfoLog);
				uninitialize();
				System.exit(0);
			}
		}

		System.out.println("OGL_GR : initialize->after shaders");
		// create shader program
		grshaderProgramObject = GLES32.glCreateProgram();

		// attach vertex shader to shader program
		GLES32.glAttachShader(grshaderProgramObject, grvertexShaderObject);

		// attach fragment shader to shader program
		GLES32.glAttachShader(grshaderProgramObject, grfragmentShaderObject);

		// prelink binding of shader program object with vertex shader attributes
		GLES32.glBindAttribLocation(grshaderProgramObject, GLESMacros.GR_ATTRIBUTE_POSITION,
			"vPosition");
		GLES32.glBindAttribLocation(grshaderProgramObject, GLESMacros.GR_ATTRIBUTE_NORMAL,
			"vNormal");

		// link
		GLES32.glLinkProgram(grshaderProgramObject);
		int[] griShaderProgramLinkStatus = new int[1];
		griInfoLength[0] = 0;
		grszInfoLog = null;
		GLES32.glGetProgramiv(grshaderProgramObject, GLES32.GL_LINK_STATUS,
			griShaderProgramLinkStatus, 0);
		if(griShaderProgramLinkStatus[0] == GLES32.GL_FALSE)
		{
			GLES32.glGetProgramiv(grshaderProgramObject, GLES32.GL_INFO_LOG_LENGTH,
				griInfoLength, 0);

			if(griInfoLength[0] > 0)
			{
				grszInfoLog = GLES32.glGetProgramInfoLog(grshaderProgramObject);
				System.out.println("OGL_GR : Shader program link log : " + grszInfoLog);
				uninitialize();
				System.exit(0);
			}
		}

		// get uniform location
		grmodelMatrixUniform = GLES32.glGetUniformLocation(grshaderProgramObject, "u_model_matrix");
		grviewMatrixUniform = GLES32.glGetUniformLocation(grshaderProgramObject, "u_view_matrix");
		grprojectionMatrixUniform = GLES32.glGetUniformLocation(grshaderProgramObject, "u_projection_matrix");
		grldUniform[0] = GLES32.glGetUniformLocation(grshaderProgramObject, "u_ld[0]");
		grlaUniform[0] = GLES32.glGetUniformLocation(grshaderProgramObject, "u_la[0]");
		grlsUniform[0] = GLES32.glGetUniformLocation(grshaderProgramObject, "u_ls[0]");
		grldUniform[1] = GLES32.glGetUniformLocation(grshaderProgramObject, "u_ld[1]");
		grlaUniform[1] = GLES32.glGetUniformLocation(grshaderProgramObject, "u_la[1]");
		grlsUniform[1] = GLES32.glGetUniformLocation(grshaderProgramObject, "u_ls[1]");
		grlightPositionUniform[0] = GLES32.glGetUniformLocation(grshaderProgramObject, "u_light_position[0]");
		grlightPositionUniform[1] = GLES32.glGetUniformLocation(grshaderProgramObject, "u_light_position[1]");

		grkaUniform = GLES32.glGetUniformLocation(grshaderProgramObject, "u_ka");
		grkdUniform = GLES32.glGetUniformLocation(grshaderProgramObject, "u_kd");
		grksUniform = GLES32.glGetUniformLocation(grshaderProgramObject, "u_ks");

		grlKeyPressedUniform = GLES32.glGetUniformLocation(grshaderProgramObject, "u_l_key_pressed");
		grmaterialShinynessUniform = GLES32.glGetUniformLocation(grshaderProgramObject, "u_material_shinyness");

		final float grpyramidVertices[] = new float[]
		{
			0.0f, 1.0f, 0.0f,
			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
								//right face
			0.0f, 1.0f, 0.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, 1.0f,
								// back face
			0.0f, 1.0f, 0.0f,
			-1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
								// left face
			0.0f, 1.0f, 0.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, 1.0f
		};
		final float grpyramidNormals[] = new float[]
		{
			0.0f, 0.447214f, 0.894427f,
		    0.0f, 0.447214f, 0.894427f,
			0.0f, 0.447214f, 0.894427f,
            0.0f, 0.447214f, 0.894427f,

			0.894427f, 0.447214f, 0.0f,
			0.894427f, 0.447214f, 0.0f,
			0.894427f, 0.447214f, 0.0f,

			0.0f, 0.447214f, -0.894427f,
			0.0f, 0.447214f, -0.894427f,
			0.0f, 0.447214f, -0.894427f,

			-0.894427f, 0.447214f, 0.0f,
			-0.894427f, 0.447214f, 0.0f,
			-0.894427f, 0.447214f, 0.0f
		};

		System.out.println("OGL_GR : initialize->before vao");
		///////////// Triangle Vao ////////////////
		GLES32.glGenVertexArrays(1, grvaoPyramid, 0);
		GLES32.glBindVertexArray(grvaoPyramid[0]);

		GLES32.glGenBuffers(1, grvboPositionPyramid, 0);
		GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER, grvboPositionPyramid[0]);

		// position
		ByteBuffer grbyteBuffer = ByteBuffer.allocateDirect(grpyramidVertices.length
			* 4);
		grbyteBuffer.order(ByteOrder.nativeOrder());
		FloatBuffer grverticesBuffer = grbyteBuffer.asFloatBuffer();
		grverticesBuffer.put(grpyramidVertices);
		grverticesBuffer.position(0);

		GLES32.glBufferData(GLES32.GL_ARRAY_BUFFER, grpyramidVertices.length * 4, grverticesBuffer,
			GLES32.GL_STATIC_DRAW);
		GLES32.glVertexAttribPointer(GLESMacros.GR_ATTRIBUTE_POSITION, 3,
			GLES32.GL_FLOAT, false, 0, 0);
		GLES32.glEnableVertexAttribArray(GLESMacros.GR_ATTRIBUTE_POSITION);
		GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER, 0);

		// color
		GLES32.glGenBuffers(1, grvboNormalPyramid, 0);
		GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER, grvboNormalPyramid[0]);
		grbyteBuffer = ByteBuffer.allocateDirect(grpyramidNormals.length * 4);
		grbyteBuffer.order(ByteOrder.nativeOrder());
		FloatBuffer grcolorsBuffer = grbyteBuffer.asFloatBuffer();
		grcolorsBuffer.put(grpyramidNormals);
		grcolorsBuffer.position(0);
		GLES32.glBufferData(GLES32.GL_ARRAY_BUFFER, grpyramidNormals.length * 4, grcolorsBuffer,
				GLES32.GL_STATIC_DRAW);
		GLES32.glVertexAttribPointer(GLESMacros.GR_ATTRIBUTE_NORMAL, 3,
			GLES32.GL_FLOAT, false, 0, 0);
		GLES32.glEnableVertexAttribArray(GLESMacros.GR_ATTRIBUTE_NORMAL);
		GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER, 0);

		GLES32.glBindVertexArray(0);

		// light colors initialization
        Light grlight1 = new Light();
        grlight1.lightAmbientColor = new float[]{0.0f, 0.0f, 0.0f, 1.0f};
        grlight1.lightDiffuseColor = new float[] {1.0f, 0.0f, 0.0f, 1.0f};
        grlight1.lightSpecularColor = new float[] {1.0f, 0.0f, 0.0f, 1.0f};
        grlight1.lightPosition = new float[] {-2.0f, 0.0f, 0.0f, 1.0f};
        grlightList.add(grlight1);
        Light grlight2 = new Light();
        grlight2.lightAmbientColor = new float[]{0.0f, 0.0f, 0.0f, 1.0f};
        grlight2.lightDiffuseColor = new float[] {0.0f, 0.0f, 1.0f, 1.0f};
        grlight2.lightSpecularColor = new float[] {0.0f, 0.0f, 1.0f, 1.0f};
        grlight2.lightPosition = new float[] {2.0f, 0.0f, 0.0f, 1.0f};
        grlightList.add(grlight2);

		System.out.println("OGL_GR : initialize->after vao of triangle");
		System.out.println("OGL_GR : initialize->after shaders");

		// enable depth testing
		GLES32.glEnable(GLES32.GL_DEPTH_TEST);
		GLES32.glEnable(GLES32.GL_LEQUAL);
		GLES32.glClearDepthf(1.0f);

		// cull back face for performance
		//GLES32.glDepthFunc(GLES32.GL_CULL_FACE);

		// set background color
		GLES32.glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// set projection matrix to identity matrix
		Matrix.setIdentityM(grperspectiveMatrix, 0);
	}

	private void resize(int width, int height)
	{
		GLES32.glViewport(0, 0, width, height);

		Matrix.perspectiveM(grperspectiveMatrix, 0, 45.0f, (float) width / (float) height, 0.1f, 100.0f);
	}

	private void display()
	{
		GLES32.glClear(GLES32.GL_COLOR_BUFFER_BIT | GLES32.GL_DEPTH_BUFFER_BIT);

		GLES32.glUseProgram(grshaderProgramObject);

		float grmodelMatrix[] = new float[16];
		float grviewMatrix[] = new float[16];
		float grprojectionMatrix[] = new float[16];
		float grtranslateMatrix[] = new float[16];
		float grrotateMatrix[] = new float[16];


		Matrix.setIdentityM(grtranslateMatrix, 0);
		Matrix.setIdentityM(grrotateMatrix, 0);
        Matrix.setIdentityM(grmodelMatrix, 0);
        Matrix.setIdentityM(grviewMatrix, 0);
		Matrix.setIdentityM(grprojectionMatrix, 0);

		//////////////////////////////////////////////////////// Triangle drawing
		Matrix.translateM(grtranslateMatrix, 0, 0.0f, 0.0f, -6.0f);
		Matrix.setRotateM(grrotateMatrix, 0, grfangleTriangle, 0.0f, 1.0f, 0.0f);

		if(grbLight == true)
        {
            GLES32.glUniform1i(grlKeyPressedUniform, 1);
            GLES32.glUniform3fv(grkdUniform, 1, grKd, 0);
            GLES32.glUniform3fv(grkaUniform, 1, grKa, 0);
            GLES32.glUniform3fv(grksUniform, 1, grKs, 0);
            GLES32.glUniform1f(grmaterialShinynessUniform, grmaterialShinyness);

            for(i = 0; i < 2; i++)
            {
                GLES32.glUniform3fv(grldUniform[i], 1, grlightList.get(i).lightDiffuseColor, 0);
                GLES32.glUniform3fv(grlaUniform[i], 1, grlightList.get(i).lightAmbientColor, 0);
                GLES32.glUniform3fv(grlsUniform[i], 1, grlightList.get(i).lightSpecularColor, 0);
                GLES32.glUniform4fv(grlightPositionUniform[i], 1, grlightList.get(i).lightPosition, 0);
            }
        }
		else
        {
            GLES32.glUniform1i(grlKeyPressedUniform, 0);
        }

		Matrix.multiplyMM(grmodelMatrix, 0, grtranslateMatrix, 0, grrotateMatrix, 0);
		Matrix.multiplyMM(grprojectionMatrix, 0,
			grprojectionMatrix, 0, grperspectiveMatrix, 0);

		GLES32.glUniformMatrix4fv(grmodelMatrixUniform, 1, false, grmodelMatrix, 0);
        GLES32.glUniformMatrix4fv(grviewMatrixUniform, 1, false, grviewMatrix, 0);
        GLES32.glUniformMatrix4fv(grprojectionMatrixUniform, 1, false, grprojectionMatrix, 0);

		// bind vao
		GLES32.glBindVertexArray(grvaoPyramid[0]);
		GLES32.glDrawArrays(GLES32.GL_TRIANGLES, 0, 12);
		GLES32.glBindVertexArray(0);

		GLES32.glUseProgram(0);


		if(grbAnimate == true)
		{
			update();
		}
		requestRender();
	}

	void update()
	{
		grfangleTriangle = grfangleTriangle + 0.5f;
		if(grfangleTriangle >= 360.0f)
			grfangleTriangle = 0.0f;
	}

	void uninitialize()
	{
		// destroy vao
		if(grvaoPyramid[0] != 0)
		{
			GLES32.glDeleteVertexArrays(1, grvaoPyramid, 0);
			grvaoPyramid[0] = 0;
		}

		if(grvboPositionPyramid[0] != 0)
		{
			GLES32.glDeleteBuffers(1, grvboPositionPyramid, 0);
			grvboPositionPyramid[0] = 0;
		}

		if(grvboNormalPyramid[0] != 0)
		{
			GLES32.glDeleteBuffers(1, grvboNormalPyramid, 0);
			grvboNormalPyramid[0] = 0;
		}


		if(grshaderProgramObject != 0)
		{
			if(grvertexShaderObject != 0)
			{
				// detach vertex shader from shader program
				GLES32.glDetachShader(grshaderProgramObject, grvertexShaderObject);
				// delete vertex shader
				GLES32.glDeleteShader(grvertexShaderObject);
				grvertexShaderObject = 0;
			}
			if(grfragmentShaderObject != 0)
			{
				// detach vertex shader from shader program
				GLES32.glDetachShader(grshaderProgramObject, grfragmentShaderObject);
				// delete vertex shader
				GLES32.glDeleteShader(grfragmentShaderObject);
				grfragmentShaderObject = 0;
			}
		}
		// delete shader program object
		if(grshaderProgramObject != 0)
		{
			GLES32.glDeleteProgram(grshaderProgramObject);
			grshaderProgramObject = 0;
		}

	}
}






























