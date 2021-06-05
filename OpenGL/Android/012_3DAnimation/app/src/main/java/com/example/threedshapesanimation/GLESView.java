package com.example.threedshapesanimation;

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

public class GLESView extends GLSurfaceView implements GLSurfaceView.Renderer, 
	OnGestureListener, OnDoubleTapListener
{
	// variables declaration
	private GestureDetector grgestureDetector;
	private final Context grcontext;
	
	private int grvertexShaderObject;
	private int grfragmentShaderObject;
	private int grshaderProgramObject;
	
	private int[] grvaoTriangle = new int[1];
	private int[] grvaoSquare = new int[1];
	private int[] grvboPositionTriangle = new int[1];
	private int[] grvboColorTriangle = new int[1];
	private int[] grvboPositionSquare = new int[1];
	private int[] grvboColorSquare = new int[1];
	private int grmvpUniform;
	
	// angle
	float grfangleTriangle = 0.0f;
	float grfangleSquare = 0.0f;
	
	private float grperspectiveProjectionMatrix[] = new float[16];
	
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
			"in vec4 vColor;" +
			"uniform mat4 u_mvpMatrix;" +
			"out vec4 out_color;" +
			"void main(void)" +
			"{" +
			"gl_Position = u_mvpMatrix * vPosition;" +
			"out_color = vColor;" +
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
			"out vec4 FragColor;" +
			"in vec4 out_color;" +
			"void main(void)" +
			"{" +
			"FragColor = out_color;" +
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
			GLES32.glGetShaderiv(grfragmentShaderObject, GLES32.GL_INFO_LOG_LENGTH,
				griInfoLength, 0);
			
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
		GLES32.glBindAttribLocation(grshaderProgramObject, GLESMacros.GR_ATTRIBUTE_COLOR,
			"vColor");
			
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
		grmvpUniform = GLES32.glGetUniformLocation(grshaderProgramObject, "u_mvpMatrix");
		
		final float grtriangleVertices[] = new float[]
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
		final float grtriangleColors[] = new float[]
		{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
	
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,

			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f,

			1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f,
		};
		final float grsquareVertices[] = new float[]
		{
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
											// right face
			1.0f, 1.0f, -1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, -1.0f,
											// back face
			-1.0f, 1.0f, -1.0f,
			1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
										    // left face
			-1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, 1.0f,
											// top face
			1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
											// bottom face
			1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, 1.0f
		};
		final float grcubeColors[] =		
		{
			1.0f, 0.0f, 0.0f,					// one color for single surface 
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,

			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,

			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,

			0.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 1.0f,

			1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f,

			1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
		};
		
		System.out.println("OGL_GR : initialize->before vao");
		///////////// Triangle Vao ////////////////
		GLES32.glGenVertexArrays(1, grvaoTriangle, 0);
		GLES32.glBindVertexArray(grvaoTriangle[0]);
		
		GLES32.glGenBuffers(1, grvboPositionTriangle, 0);
		GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER, grvboPositionTriangle[0]);
		
		// position
		ByteBuffer grbyteBuffer = ByteBuffer.allocateDirect(grtriangleVertices.length 
			* 4);
		grbyteBuffer.order(ByteOrder.nativeOrder());
		FloatBuffer grverticesBuffer = grbyteBuffer.asFloatBuffer();
		grverticesBuffer.put(grtriangleVertices);
		grverticesBuffer.position(0);
		
		GLES32.glBufferData(GLES32.GL_ARRAY_BUFFER, 
			grtriangleVertices.length * 4,
			grverticesBuffer,
			GLES32.GL_STATIC_DRAW);
			
		GLES32.glVertexAttribPointer(GLESMacros.GR_ATTRIBUTE_POSITION, 3,
			GLES32.GL_FLOAT, false, 0, 0);
			
		GLES32.glEnableVertexAttribArray(GLESMacros.GR_ATTRIBUTE_POSITION);
		
		GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER, 0);
		
		
		// color
		GLES32.glGenBuffers(1, grvboColorTriangle, 0);
		GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER, grvboColorTriangle[0]);
		grbyteBuffer = null;
		grbyteBuffer = ByteBuffer.allocateDirect(grtriangleColors.length 
			* 4);
		grbyteBuffer.order(ByteOrder.nativeOrder());
		FloatBuffer grcolorsBuffer = grbyteBuffer.asFloatBuffer();
		grcolorsBuffer.put(grtriangleColors);
		grcolorsBuffer.position(0);
		
		GLES32.glBufferData(GLES32.GL_ARRAY_BUFFER, 
			grtriangleColors.length * 4,
			grcolorsBuffer,
			GLES32.GL_STATIC_DRAW);
			
		GLES32.glVertexAttribPointer(GLESMacros.GR_ATTRIBUTE_COLOR, 3,
			GLES32.GL_FLOAT, false, 0, 0);
			
		GLES32.glEnableVertexAttribArray(GLESMacros.GR_ATTRIBUTE_COLOR);
		
		GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER, 0);
		
		GLES32.glBindVertexArray(0);
		
		System.out.println("OGL_GR : initialize->after vao of triangle");
		///////////////////// Square Vao ///////////////////////////////
		GLES32.glGenVertexArrays(1, grvaoSquare, 0);
		GLES32.glBindVertexArray(grvaoSquare[0]);
		
		GLES32.glGenBuffers(1, grvboPositionSquare, 0);
		GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER, grvboPositionSquare[0]);
		
		grbyteBuffer = null;
		// position
		grbyteBuffer = ByteBuffer.allocateDirect(grsquareVertices.length 
			* 4);
		grbyteBuffer.order(ByteOrder.nativeOrder());
		grverticesBuffer = grbyteBuffer.asFloatBuffer();
		grverticesBuffer.put(grsquareVertices);
		grverticesBuffer.position(0);
		
		GLES32.glBufferData(GLES32.GL_ARRAY_BUFFER, 
			grsquareVertices.length * 4,
			grverticesBuffer,
			GLES32.GL_STATIC_DRAW);
			
		GLES32.glVertexAttribPointer(GLESMacros.GR_ATTRIBUTE_POSITION, 3,
			GLES32.GL_FLOAT, false, 0, 0);
			
		GLES32.glEnableVertexAttribArray(GLESMacros.GR_ATTRIBUTE_POSITION);
		
		GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER, 0);
		
		// color
		GLES32.glGenBuffers(1, grvboColorSquare, 0);
		GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER, grvboColorSquare[0]);
		grbyteBuffer = null;
		grbyteBuffer = ByteBuffer.allocateDirect(grcubeColors.length 
			* 4);
		grbyteBuffer.order(ByteOrder.nativeOrder());
		grcolorsBuffer = grbyteBuffer.asFloatBuffer();
		grcolorsBuffer.put(grcubeColors);
		grcolorsBuffer.position(0);
		
		GLES32.glBufferData(GLES32.GL_ARRAY_BUFFER, 
			grcubeColors.length * 4,
			grcolorsBuffer,
			GLES32.GL_STATIC_DRAW);
			
		GLES32.glVertexAttribPointer(GLESMacros.GR_ATTRIBUTE_COLOR, 3,
			GLES32.GL_FLOAT, false, 0, 0);
			
		GLES32.glEnableVertexAttribArray(GLESMacros.GR_ATTRIBUTE_COLOR);
		
		GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER, 0);
		
		GLES32.glBindVertexArray(0);
		
		System.out.println("OGL_GR : initialize->after shaders");
		
		// enable depth testing
		GLES32.glEnable(GLES32.GL_DEPTH_TEST);
		GLES32.glEnable(GLES32.GL_LEQUAL);
		
		// cull back face for performance
		//GLES32.glDepthFunc(GLES32.GL_CULL_FACE);
		
		// set background color
		GLES32.glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		
		// set projection matrix to identity matrix
		Matrix.setIdentityM(grperspectiveProjectionMatrix, 0);
	}

	private void resize(int width, int height)
	{
		GLES32.glViewport(0, 0, width, height);
		
		Matrix.perspectiveM(grperspectiveProjectionMatrix, 0, 45.0f, (float) width / (float) height, 0.1f, 100.0f);
	}

	private void display()
	{
		GLES32.glClear(GLES32.GL_COLOR_BUFFER_BIT | GLES32.GL_DEPTH_BUFFER_BIT);
		
		GLES32.glUseProgram(grshaderProgramObject);
		
		float grmodelViewMatrix[] = new float[16];
		float grmodelViewProjectionMatrix[] = new float[16];
		float grtranslateMatrix[] = new float[16];
		float grrotateMatrix[] = new float[16];
		
		Matrix.setIdentityM(grmodelViewMatrix, 0);
		Matrix.setIdentityM(grtranslateMatrix, 0);
		Matrix.setIdentityM(grrotateMatrix, 0);
		Matrix.setIdentityM(grmodelViewProjectionMatrix, 0);
		
		
		//////////////////////////////////////////////////////// Triangle drawing
		Matrix.translateM(grtranslateMatrix, 0, -1.5f, 0.0f, -6.0f);
		Matrix.setRotateM(grrotateMatrix, 0, grfangleTriangle, 0.0f, 1.0f, 0.0f);
		
		//Matrix.multiplyMM(grrotateMatrix, 0, grrotateMatrix, 0, grtranslateMatrix, 0);
		//Matrix.multiplyMM(grmodelViewMatrix, 0, grmodelViewMatrix, 0, grrotateMatrix, 0);
		Matrix.multiplyMM(grmodelViewMatrix, 0, grtranslateMatrix, 0, grrotateMatrix, 0);
		
		Matrix.multiplyMM(grmodelViewProjectionMatrix, 0,
			grperspectiveProjectionMatrix, 0, grmodelViewMatrix, 0);
			
		GLES32.glUniformMatrix4fv(grmvpUniform, 1, false, grmodelViewProjectionMatrix, 0);
		
		// bind vao
		GLES32.glBindVertexArray(grvaoTriangle[0]);
		
		GLES32.glDrawArrays(GLES32.GL_TRIANGLES, 0, 12);
		
		// unbind vao
		GLES32.glBindVertexArray(0);
		
		
		////////////////////////////////////////////////////// Square drawing
		Matrix.setIdentityM(grmodelViewMatrix, 0);
		Matrix.setIdentityM(grtranslateMatrix, 0);
		Matrix.setIdentityM(grrotateMatrix, 0);
		Matrix.setIdentityM(grmodelViewProjectionMatrix, 0);
		
		Matrix.translateM(grtranslateMatrix, 0, 1.5f, 0.0f, -6.0f);
		Matrix.setRotateM(grrotateMatrix, 0, grfangleSquare, 1.0f, 0.0f, 0.0f);
		
		Matrix.multiplyMM(grrotateMatrix, 0, grtranslateMatrix, 0, grrotateMatrix, 0);
		Matrix.multiplyMM(grmodelViewMatrix, 0, grmodelViewMatrix, 0, grrotateMatrix, 0);
		Matrix.multiplyMM(grmodelViewProjectionMatrix, 0,
			grperspectiveProjectionMatrix, 0, grmodelViewMatrix, 0);
			
		GLES32.glUniformMatrix4fv(grmvpUniform, 1, false, grmodelViewProjectionMatrix, 0);
		
		// bind vao
		GLES32.glBindVertexArray(grvaoSquare[0]);
		
		GLES32.glDrawArrays(GLES32.GL_TRIANGLE_FAN, 0, 4);
		GLES32.glDrawArrays(GLES32.GL_TRIANGLE_FAN, 4, 4);
		GLES32.glDrawArrays(GLES32.GL_TRIANGLE_FAN, 8, 4);
		GLES32.glDrawArrays(GLES32.GL_TRIANGLE_FAN, 12, 4);
		GLES32.glDrawArrays(GLES32.GL_TRIANGLE_FAN, 16, 4);
		GLES32.glDrawArrays(GLES32.GL_TRIANGLE_FAN, 20, 4);
		
		// unbind vao
		GLES32.glBindVertexArray(0);
		
		
		GLES32.glUseProgram(0);
		
		// update call
		update();
		
		requestRender();
	}
	
	void update()
	{
		grfangleTriangle = grfangleTriangle + 0.5f;
		if(grfangleTriangle >= 360.0f)
			grfangleTriangle = 0.0f;
		
		grfangleSquare = grfangleSquare + 0.5f;
		if(grfangleSquare >= 360.0f)
			grfangleSquare = 0.0f;
	}
	
	void uninitialize()
	{
		// destroy vao
		if(grvaoTriangle[0] != 0)
		{
			GLES32.glDeleteVertexArrays(1, grvaoTriangle, 0);
			grvaoTriangle[0] = 0;
		}
		
		if(grvboPositionTriangle[0] != 0)
		{
			GLES32.glDeleteBuffers(1, grvboPositionTriangle, 0);
			grvboPositionTriangle[0] = 0;
		}
		
		if(grvboColorTriangle[0] != 0)
		{
			GLES32.glDeleteBuffers(1, grvboColorTriangle, 0);
			grvboColorTriangle[0] = 0;
		}
		
		if(grvaoSquare[0] != 0)
		{
			GLES32.glDeleteVertexArrays(1, grvaoSquare, 0);
			grvaoSquare[0] = 0;
		}
		
		if(grvboPositionSquare[0] != 0)
		{
			GLES32.glDeleteBuffers(1, grvboPositionSquare, 0);
			grvboPositionSquare[0] = 0;
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






























