package com.example.roboticarm;

import android.content.Context;

import android.opengl.GLES20;
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
import java.nio.ShortBuffer;

public class GLESView extends GLSurfaceView implements GLSurfaceView.Renderer,
	OnGestureListener, OnDoubleTapListener
{
	// variables declaration
	private GestureDetector grgestureDetector;
	private final Context grcontext;

	private int grvertexShaderObject;
	private int grfragmentShaderObject;
	private int grshaderProgramObject;

	private int[] grvaoSphere = new int[1];
	private int[] grvboSpherePosition = new int[1];
	private int[] grvboSphereNormal = new int[1];
	private int[] grvboSphereElement = new int[1];
	private int grnumVertices;
	private int grnumElements;

	private int grmodelMatrixUniform;
	private int grviewMatrixUniform;
	private int grprojectionMatrixUniform;

	int i;
	int grshoulder = 0;
	boolean grswitch = false;
	int grelbow = 0;
	private float grperspectiveMatrix[] = new float[16];
	GRStack grStack;

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
		grelbow = (grelbow + 10) % 360;
		System.out.println("Elbow : " + grelbow);
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
	    //grbLight = !grbLight;
		grshoulder = (grshoulder + 10) % 360;
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
		Sphere grsphere = new Sphere();
		float grsphereVertices[] = new float[1146];
		float grsphereNormals[] = new float[1146];
		float grsphereTextures[] = new float[764];
		short grsphereElements[] = new short[2280];
		grsphere.getSphereVertexData(grsphereVertices, grsphereNormals, grsphereTextures, grsphereElements);
		grnumVertices = grsphere.getNumberOfSphereVertices();
		grnumElements = grsphere.getNumberOfSphereElements();

		///////////////// Vertex Shader
		//create shader
		grvertexShaderObject = GLES32.glCreateShader(GLES32.GL_VERTEX_SHADER);

		// vertex shader source code
		final String grvertexShaderSourceCode = String.format(
				"#version 320 es" +
				"\n" +
				"in vec4 vPosition;" +
				"in vec3 vColor;" +
				"uniform mat4 u_model_matrix;" +
				"uniform mat4 u_view_matrix;" +
				"uniform mat4 u_projection_matrix;" +
				"out vec3 out_color;" +
				"void main(void)" +
				"{" +
				"out_color = vColor;" +
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
				"in vec3 out_color;" +
				"out vec4 FragColor;" +
				"void main(void)" +
				"{" +
				"FragColor = vec4(out_color, 1.0);" +
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
		GLES32.glBindAttribLocation(grshaderProgramObject, GLESMacros.GR_ATTRIBUTE_POSITION, "vPosition");
		GLES32.glBindAttribLocation(grshaderProgramObject, GLESMacros.GR_ATTRIBUTE_COLOR, "vColor");

		// link
		GLES32.glLinkProgram(grshaderProgramObject);
		int[] griShaderProgramLinkStatus = new int[1];
		griInfoLength[0] = 0;
		grszInfoLog = null;
		GLES32.glGetProgramiv(grshaderProgramObject, GLES32.GL_LINK_STATUS, griShaderProgramLinkStatus, 0);
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


		// vao
		GLES32.glGenVertexArrays(1, grvaoSphere, 0);
		GLES32.glBindVertexArray(grvaoSphere[0]);
		// vbo position
		GLES32.glGenBuffers(1, grvboSpherePosition, 0);
		GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER, grvboSpherePosition[0]);
		ByteBuffer grbyteBuffer = ByteBuffer.allocateDirect(grsphereVertices.length * 4);
		grbyteBuffer.order(ByteOrder.nativeOrder());
		FloatBuffer grverticesBuffer = grbyteBuffer.asFloatBuffer();
		grverticesBuffer.put(grsphereVertices);
		grverticesBuffer.position(0);

		GLES32.glBufferData(GLES32.GL_ARRAY_BUFFER, grsphereVertices.length * 4, grverticesBuffer, GLES32.GL_STATIC_DRAW);
		GLES32.glVertexAttribPointer(GLESMacros.GR_ATTRIBUTE_POSITION, 3, GLES32.GL_FLOAT, false, 0, 0);
		GLES32.glEnableVertexAttribArray(GLESMacros.GR_ATTRIBUTE_POSITION);
		GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER, 0);
		GLES32.glVertexAttrib3f(GLESMacros.GR_ATTRIBUTE_COLOR, 0.5f, 0.35f, 0.05f);
		// vbo element
		GLES32.glGenBuffers(1, grvboSphereElement, 0);
		GLES32.glBindBuffer(GLES32.GL_ELEMENT_ARRAY_BUFFER, grvboSphereElement[0]);
		grbyteBuffer = ByteBuffer.allocateDirect(grsphereElements.length * 2);
		grbyteBuffer.order(ByteOrder.nativeOrder());
		ShortBuffer grelementsBuffer = grbyteBuffer.asShortBuffer();
		grelementsBuffer.put(grsphereElements);
		grelementsBuffer.position(0);
		GLES32.glBufferData(GLES32.GL_ELEMENT_ARRAY_BUFFER, grsphereElements.length * 2, grelementsBuffer, GLES32.GL_STATIC_DRAW);
		GLES32.glBindBuffer(GLES32.GL_ELEMENT_ARRAY_BUFFER, 0);
		GLES32.glBindVertexArray(0);

		System.out.println("OGL_GR : initialize->after vao of cube");
		System.out.println("OGL_GR : initialize->after shaders");

		// enable depth testing
		GLES32.glEnable(GLES32.GL_DEPTH_TEST);
		GLES32.glEnable(GLES32.GL_LEQUAL);
		GLES32.glClearDepthf(1.0f);

		// initialize stack
		grStack = new GRStack();

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

		float[] grmodelMatrix = new float[16];
		float[] grviewMatrix = new float[16];
		float[] grprojectionMatrix = new float[16];
		float[] grtranslateMatrix = new float[16];
		float[] grrotateMatrix = new float[16];
		float[] grscaleMatrix = new float[16];

		Matrix.setIdentityM(grtranslateMatrix, 0);
		Matrix.setIdentityM(grrotateMatrix, 0);
		Matrix.setIdentityM(grscaleMatrix, 0);
        Matrix.setIdentityM(grmodelMatrix, 0);
		Matrix.setIdentityM(grviewMatrix, 0);
		Matrix.setIdentityM(grprojectionMatrix, 0);

		Matrix.translateM(grtranslateMatrix, 0, 0.0f, 0.0f, -12.0f);
		Matrix.setRotateM(grrotateMatrix, 0, (float)grshoulder, 0.0f, 0.0f, 1.0f);
		Matrix.multiplyMM(grmodelMatrix, 0, grtranslateMatrix, 0, grrotateMatrix, 0);
		Matrix.multiplyMM(grprojectionMatrix, 0, grprojectionMatrix, 0, grperspectiveMatrix, 0);

		// push to stack for whole geometry
		grStack.pushToStack(grmodelMatrix);

		//******************** shoulder
		Matrix.setIdentityM(grtranslateMatrix, 0);
		Matrix.setIdentityM(grrotateMatrix, 0);
		Matrix.setIdentityM(grscaleMatrix, 0);
		Matrix.setIdentityM(grmodelMatrix, 0);
		Matrix.setIdentityM(grviewMatrix, 0);
		Matrix.setIdentityM(grprojectionMatrix, 0);

		Matrix.translateM(grtranslateMatrix, 0, 1.0f, 0.0f, 0.0f);
		Matrix.scaleM(grscaleMatrix, 0, 2.0f, 0.5f, 1.0f);
		Matrix.multiplyMM(grmodelMatrix, 0, grtranslateMatrix, 0, grscaleMatrix, 0);
		Matrix.multiplyMM(grprojectionMatrix, 0, grprojectionMatrix, 0, grperspectiveMatrix, 0);

		// push to stack for whole geometry
		grmodelMatrix = grStack.pushToStack(grmodelMatrix);
		grStack.popFromStack();

		GLES32.glUniformMatrix4fv(grmodelMatrixUniform, 1, false, grmodelMatrix, 0);
		GLES32.glUniformMatrix4fv(grviewMatrixUniform, 1, false, grviewMatrix, 0);
		GLES32.glUniformMatrix4fv(grprojectionMatrixUniform, 1, false, grprojectionMatrix, 0);

		// bind vao
		GLES32.glBindVertexArray(grvaoSphere[0]);
		GLES32.glBindBuffer(GLES32.GL_ELEMENT_ARRAY_BUFFER, grvboSphereElement[0]);
		GLES32.glDrawElements(GLES32.GL_TRIANGLES, grnumElements, GLES32.GL_UNSIGNED_SHORT, 0);
		GLES32.glBindVertexArray(0);

		//******************** elbow
		Matrix.setIdentityM(grtranslateMatrix, 0);
		Matrix.setIdentityM(grrotateMatrix, 0);
		Matrix.setIdentityM(grscaleMatrix, 0);
		Matrix.setIdentityM(grmodelMatrix, 0);
		Matrix.setIdentityM(grviewMatrix, 0);
		Matrix.setIdentityM(grprojectionMatrix, 0);

		Matrix.translateM(grtranslateMatrix, 0, 1.8f, 0.0f, 0.0f);
		Matrix.rotateM(grrotateMatrix, 0, (float)grelbow, 0.0f, 0.0f, 1.0f);
		Matrix.multiplyMM(grmodelMatrix, 0, grtranslateMatrix, 0, grrotateMatrix, 0);

		Matrix.setIdentityM(grtranslateMatrix, 0);
		Matrix.setIdentityM(grrotateMatrix, 0);
		Matrix.setIdentityM(grscaleMatrix, 0);
		Matrix.setIdentityM(grviewMatrix, 0);

		Matrix.translateM(grtranslateMatrix, 0, 1.0f, 0.0f, 0.0f);
		Matrix.multiplyMM(grmodelMatrix, 0, grmodelMatrix, 0, grtranslateMatrix, 0);
		Matrix.scaleM(grscaleMatrix, 0, 2.0f, 0.5f, 1.0f);
		Matrix.multiplyMM(grmodelMatrix, 0, grmodelMatrix, 0, grscaleMatrix, 0);
		Matrix.multiplyMM(grprojectionMatrix, 0, grprojectionMatrix, 0, grperspectiveMatrix, 0);

		// push to stack for whole geometry
		grmodelMatrix = grStack.pushToStack(grmodelMatrix);
		grStack.popFromStack();

		GLES32.glUniformMatrix4fv(grmodelMatrixUniform, 1, false, grmodelMatrix, 0);
		GLES32.glUniformMatrix4fv(grviewMatrixUniform, 1, false, grviewMatrix, 0);
		GLES32.glUniformMatrix4fv(grprojectionMatrixUniform, 1, false, grprojectionMatrix, 0);

		// bind vao
		GLES32.glBindVertexArray(grvaoSphere[0]);
		GLES32.glBindBuffer(GLES32.GL_ELEMENT_ARRAY_BUFFER, grvboSphereElement[0]);
		GLES32.glDrawElements(GLES32.GL_TRIANGLES, grnumElements, GLES32.GL_UNSIGNED_SHORT, 0);
		GLES32.glBindVertexArray(0);

		grStack.popFromStack();
		GLES32.glUseProgram(0);
		requestRender();
	}

	void update()
	{
		// code
	}

	void uninitialize()
	{
		// uninitialze stack
		grStack.destroyStack();
		grStack = null;

		// destroy vao
		if(grvaoSphere[0] != 0)
		{
			GLES32.glDeleteVertexArrays(1, grvaoSphere, 0);
			grvaoSphere[0] = 0;
		}

		if(grvboSpherePosition[0] != 0)
		{
			GLES32.glDeleteBuffers(1, grvboSpherePosition, 0);
			grvboSpherePosition[0] = 0;
		}

		if(grvboSphereNormal[0] != 0)
		{
			GLES32.glDeleteBuffers(1, grvboSphereNormal, 0);
			grvboSphereNormal[0] = 0;
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






























