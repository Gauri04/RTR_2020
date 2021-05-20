package com.example.bluewindow;

import android.content.Context;

import android.view.MotionEvent;
import android.view.GestureDetector;
import android.view.GestureDetector.OnGestureListener;
import android.view.GestureDetector.OnDoubleTapListener;

import android.opengl.GLSurfaceView;				// OGL SurfaceView and related
import android.opengl.GLES32;						// for OpenGLES32
import javax.microedition.khronos.opengles.GL10;	// OpenGLES 1.0 needed for param GL10
import javax.microedition.khronos.egl.EGLConfig;	// for EGLConfig

public class GLESView extends GLSurfaceView implements GLSurfaceView.Renderer, 
	OnGestureListener, OnDoubleTapListener
{
	// variables declaration
	private GestureDetector grgestureDetector;
	private final Context grcontext;
	
	private int grvertexShaderObject;
	private int grfragmentShaderObject;
	private int grshaderProgramObject;
	
	private int[] grvao = new int[1];
	private int[] grvbo = new int[1];
	private int grmvpUniform;
	
	private float grorthographicProjectionMatrix[] = new float[16];
	
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
		// set background color
		GLES32.glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	}

	private void resize(int width, int height)
	{
		GLES32.glViewport(0, 0, width, height);
		
	}

	private void display()
	{
		GLES32.glClear(GLES32.GL_COLOR_BUFFER_BIT | GLES32.GL_DEPTH_BUFFER_BIT);
		
	}

	private void uninitialize()
	{
		// code
	}
}






























