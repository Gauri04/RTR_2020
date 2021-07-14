package com.example.threelightsonsteadysphere;

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
import java.nio.ShortBuffer;

public class GLESView extends GLSurfaceView implements GLSurfaceView.Renderer,
	OnGestureListener, OnDoubleTapListener
{
	// variables declaration
	private GestureDetector grgestureDetector;
	private final Context grcontext;

	private int grvertexShaderObjectPF;
	private int grfragmentShaderObjectPF;
	private int grshaderProgramObjectPF;
	private int grvertexShaderObjectPV;
	private int grfragmentShaderObjectPV;
	private int grshaderProgramObjectPV;

	private int[] grvaoSphere = new int[1];
	private int[] grvboSpherePosition = new int[1];
	private int[] grvboSphereNormal = new int[1];
	private int[] grvboSphereElement = new int[1];
	private int grnumVertices;
	private int grnumElements;

	private int grmodelMatrixUniformPF;
	private int grviewMatrixUniformPF;
	private int grprojectionMatrixUniformPF;
	private int grlaUniformPF[] = new int[3];
	private int grldUniformPF[] = new int[3];
	private int grlsUniformPF[] = new int[3];
	private int grlightPositionUniformPF[] = new int[3];
	private int grkaUniformPF;
	private int grkdUniformPF;
	private int grksUniformPF;
	private int grmaterialShinynessUniformPF;
	private int grlKeyPressedUniformPF;

	private int grmodelMatrixUniformPV;
	private int grviewMatrixUniformPV;
	private int grprojectionMatrixUniformPV;
	private int grlaUniformPV[] = new int[3];
	private int grldUniformPV[] = new int[3];
	private int grlsUniformPV[] = new int[3];
	private int grlightPositionUniformPV[] = new int[3];
	private int grkaUniformPV;
	private int grkdUniformPV;
	private int grksUniformPV;
	private int grmaterialShinynessUniformPV;
	private int grlKeyPressedUniformPV;

	private float grka[] = new float[]{0.0f, 0.0f, 0.0f, 1.0f};
	private float grkd[] = new float[]{1.0f, 1.0f, 1.0f, 1.0f};
	private float grks[] = new float[]{1.0f, 1.0f, 1.0f, 1.0f};
	private float grmaterialShinyness = 128.0f;
	Light[] grlight = new Light[3];

	int i;
	boolean grbLight = false;
	private boolean grisPerVertexLight = true;
	private boolean grX = false;
	private boolean grY = false;
	private boolean grZ = false;
	private float grangle = 0.0f;
	private float grangleX = 0.0f;
	private float grangleY = 0.0f;
	private float grangleZ = 0.0f;
	private int grcount = 0;
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
		grisPerVertexLight = !grisPerVertexLight;
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
		grcount++;
		if(grcount == 1)
			grZ = true;
		if(grcount == 2)
			grY = true;
		if(grcount == 3)
			grX = true;
		if(grcount > 3)
			grcount = 0;

		if(grcount == 0)
		{
			grX = false;
			grY = false;
			grZ = false;
		}


		System.out.println("OGL_GR : count : " + grcount);
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
		grbLight = !grbLight;
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
		System.out.println("OGL_GR : in initialize b4 shaders");
		//************************************************** Per Fragment - shaders **************************************
		//****************************************************************************************************************
		// Vertex Shader
		//create shader
		grvertexShaderObjectPF = GLES32.glCreateShader(GLES32.GL_VERTEX_SHADER);

		// vertex shader source code
		final String grvertexShaderSourceCode = String.format(
				"#version 320 es" +
				"\n" +
				"in vec4 vPosition;" +
				"in vec3 vNormal;" +
				"uniform mat4 u_model_matrix;" +
				"uniform mat4 u_view_matrix;" +
				"uniform mat4 u_projection_matrix;" +
				"uniform mediump int u_l_key_pressed;" +
				"uniform vec4 u_light_position[3];" +
				"out vec3 out_transformed_normal;" +
				"out vec3 out_light_direction[3];" +
				"out vec3 out_view_vector;" +
				"int i;" +
				"void main(void)" +
				"{" +
				"vec4 eye_coordinates = u_model_matrix * u_view_matrix * vPosition;" +
				"out_transformed_normal = mat3(u_view_matrix * u_model_matrix) * vNormal;" +
				"out_view_vector = -eye_coordinates.xyz;" +
				"for(i = 0; i < 3; i++)" +
				"{" +
				"out_light_direction[i] = vec3(u_light_position[i] - eye_coordinates);" +
				"}" +
				"gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vPosition;" +
				"}"
		);

		// provide source code to shader
		GLES32.glShaderSource(grvertexShaderObjectPF, grvertexShaderSourceCode);

		// compile shader and check for error
		GLES32.glCompileShader(grvertexShaderObjectPF);
		int[] griShaderCompileStatus = new int[1];
		int[] griInfoLength = new int[1];
		String grszInfoLog = null;

		GLES32.glGetShaderiv(grvertexShaderObjectPF, GLES32.GL_COMPILE_STATUS,
			griShaderCompileStatus, 0);
		if(griShaderCompileStatus[0] == GLES32.GL_FALSE)
		{
			GLES32.glGetShaderiv(grvertexShaderObjectPF, GLES32.GL_INFO_LOG_LENGTH,
				griInfoLength, 0);

			if(griInfoLength[0] > 0)
			{
				grszInfoLog = GLES32.glGetShaderInfoLog(grvertexShaderObjectPF);
				System.out.println("OGL_GR : Vertex shader compilation log : " + grszInfoLog);
				uninitialize();
				System.exit(0);
			}
		}

		////////// Fragment shader
		// create shader
		grfragmentShaderObjectPF = GLES32.glCreateShader(GLES32.GL_FRAGMENT_SHADER);

		// fragment shader source code
		final String grfragmentShaderSourceCode = String.format(
				"#version 320 es" +
				"\n" +
				"precision highp float;" +
				"in vec3 out_transformed_normal;" +
				"in vec3 out_light_direction[3];" +
				"in vec3 out_view_vector;" +
				"uniform vec3 u_la[3];" +
				"uniform vec3 u_ld[3];" +
				"uniform vec3 u_ls[3];" +
				"uniform vec3 u_ka;" +
				"uniform vec3 u_kd;" +
				"uniform vec3 u_ks;" +
				"uniform float u_material_shinyness;" +
				"uniform int u_l_key_pressed;" +
				"vec3 phong_ads_light;" +
				"out vec4 FragColor;" +
				"int i;" +
				"void main(void)" +
				"{" +
				"if(u_l_key_pressed == 1)" +
				"{" +
					"vec3 reflection_vector[3];" +
					"vec3 ambient[3];" +
					"vec3 diffuse[3];" +
					"vec3 specular[3];" +
					"vec3 normalized_light_direction[3];" +
					"vec3 normalized_transform_normal = normalize(out_transformed_normal);" +
					"vec3 normalized_view_vector = normalize(out_view_vector);" +
					"for(i = 0; i < 3; i++)" +
					"{" +
						"normalized_light_direction[i] = normalize(out_light_direction[i]);" +
						"reflection_vector[i] = reflect(-normalized_light_direction[i], normalized_transform_normal);" +
						"ambient[i] = u_la[i] * u_ka;" +
						"diffuse[i] = u_ld[i] * u_kd * max(dot(normalized_light_direction[i], normalized_transform_normal), 0.0);" +
						"specular[i] = u_ls[i] * u_ks * pow(max(dot(reflection_vector[i], normalized_view_vector), 0.0), u_material_shinyness);" +
						"phong_ads_light = phong_ads_light + ambient[i] + diffuse[i] + specular[i];" +
					"}"	+
				"}" +
				"else" +
				"{" +
					"phong_ads_light = vec3(1.0, 1.0, 1.0);" +
				"}"	+
				"FragColor = vec4(phong_ads_light, 1.0);" +
				"}"
		);

		// provide source code to shader
		GLES32.glShaderSource(grfragmentShaderObjectPF, grfragmentShaderSourceCode);

		// compile shader
		GLES32.glCompileShader(grfragmentShaderObjectPF);
		griShaderCompileStatus[0] = 0;
		griInfoLength[0] = 0;
		grszInfoLog = null;
		GLES32.glGetShaderiv(grfragmentShaderObjectPF, GLES32.GL_COMPILE_STATUS,
			griShaderCompileStatus, 0);
		if(griShaderCompileStatus[0] == GLES32.GL_FALSE)
		{
			GLES32.glGetShaderiv(grfragmentShaderObjectPF, GLES32.GL_INFO_LOG_LENGTH, griInfoLength, 0);

			if(griInfoLength[0] > 0)
			{
				grszInfoLog = GLES32.glGetShaderInfoLog(grfragmentShaderObjectPF);
				System.out.println("OGL_GR : Fragment shader compilation log : " + grszInfoLog);
				uninitialize();
				System.exit(0);
			}
		}

		// create shader program
		grshaderProgramObjectPF = GLES32.glCreateProgram();

		// attach vertex shader to shader program
		GLES32.glAttachShader(grshaderProgramObjectPF, grvertexShaderObjectPF);

		// attach fragment shader to shader program
		GLES32.glAttachShader(grshaderProgramObjectPF, grfragmentShaderObjectPF);

		// prelink binding of shader program object with vertex shader attributes
		GLES32.glBindAttribLocation(grshaderProgramObjectPF, GLESMacros.GR_ATTRIBUTE_POSITION,
			"vPosition");
		GLES32.glBindAttribLocation(grshaderProgramObjectPF, GLESMacros.GR_ATTRIBUTE_NORMAL,
			"vNormal");

		// link
		GLES32.glLinkProgram(grshaderProgramObjectPF);
		int[] griShaderProgramLinkStatus = new int[1];
		griInfoLength[0] = 0;
		grszInfoLog = null;
		GLES32.glGetProgramiv(grshaderProgramObjectPF, GLES32.GL_LINK_STATUS,
			griShaderProgramLinkStatus, 0);
		if(griShaderProgramLinkStatus[0] == GLES32.GL_FALSE)
		{
			GLES32.glGetProgramiv(grshaderProgramObjectPF, GLES32.GL_INFO_LOG_LENGTH,
				griInfoLength, 0);

			if(griInfoLength[0] > 0)
			{
				grszInfoLog = GLES32.glGetProgramInfoLog(grshaderProgramObjectPF);
				System.out.println("OGL_GR : Shader program link log : " + grszInfoLog);
				uninitialize();
				System.exit(0);
			}
		}

		// get uniform location
		grmodelMatrixUniformPF = GLES32.glGetUniformLocation(grshaderProgramObjectPF, "u_model_matrix");
		grviewMatrixUniformPF = GLES32.glGetUniformLocation(grshaderProgramObjectPF, "u_view_matrix");
		grprojectionMatrixUniformPF = GLES32.glGetUniformLocation(grshaderProgramObjectPF, "u_projection_matrix");

		grlaUniformPF[0] = GLES32.glGetUniformLocation(grshaderProgramObjectPF, "u_la[0]");
		grldUniformPF[0] = GLES32.glGetUniformLocation(grshaderProgramObjectPF, "u_ld[0]");
		grlsUniformPF[0] = GLES32.glGetUniformLocation(grshaderProgramObjectPF, "u_ls[0]");
		grlaUniformPF[1] = GLES32.glGetUniformLocation(grshaderProgramObjectPF, "u_la[1]");
		grldUniformPF[1] = GLES32.glGetUniformLocation(grshaderProgramObjectPF, "u_ld[1]");
		grlsUniformPF[1] = GLES32.glGetUniformLocation(grshaderProgramObjectPF, "u_ls[1]");
		grlaUniformPF[2] = GLES32.glGetUniformLocation(grshaderProgramObjectPF, "u_la[2]");
		grldUniformPF[2] = GLES32.glGetUniformLocation(grshaderProgramObjectPF, "u_ld[2]");
		grlsUniformPF[2] = GLES32.glGetUniformLocation(grshaderProgramObjectPF, "u_ls[2]");
		grlightPositionUniformPF[0] = GLES32.glGetUniformLocation(grshaderProgramObjectPF, "u_light_position[0]");
		grlightPositionUniformPF[1] = GLES32.glGetUniformLocation(grshaderProgramObjectPF, "u_light_position[1]");
		grlightPositionUniformPF[2] = GLES32.glGetUniformLocation(grshaderProgramObjectPF, "u_light_position[2]");
		grkaUniformPF = GLES32.glGetUniformLocation(grshaderProgramObjectPF, "u_ka");
		grkdUniformPF = GLES32.glGetUniformLocation(grshaderProgramObjectPF, "u_kd");
		grksUniformPF = GLES32.glGetUniformLocation(grshaderProgramObjectPF, "u_ks");

		grlKeyPressedUniformPF = GLES32.glGetUniformLocation(grshaderProgramObjectPF, "u_l_key_pressed");
		grmaterialShinynessUniformPF = GLES32.glGetUniformLocation(grshaderProgramObjectPF, "u_material_shinyness");

		//************************************************** Per Fragment - shaders **************************************
		//****************************************************************************************************************
		// Vertex Shader
		//create shader
		System.out.println("OGL_GR : In initialize - per vertex shaders");
		grvertexShaderObjectPV = GLES32.glCreateShader(GLES32.GL_VERTEX_SHADER);

		// vertex shader source code
		final String grvertexShaderSourceCodePV = String.format(
						"#version 320 es" +
						"\n" +
						"in vec4 vPosition;" +
						"in vec3 vNormal;" +
						"uniform mat4 u_model_matrix;" +
						"uniform mat4 u_view_matrix;" +
						"uniform mat4 u_projection_matrix;" +
						"uniform mediump int u_l_key_pressed;" +
						"uniform vec3 u_ld[3];" +
						"uniform vec3 u_la[3];" +
						"uniform vec3 u_ls[3];" +
						"uniform vec3 u_ka;" +
						"uniform vec3 u_kd;" +
						"uniform vec3 u_ks;" +
						"uniform float u_material_shinyness;" +
						"uniform vec4 u_light_position[3];" +
						"out vec3 out_phong_light;" +
						"int i;" +
						"void main(void)" +
						"{" +
						"if(u_l_key_pressed == 1)" +
						"{" +
						"vec4 eye_coordinates = u_model_matrix * u_view_matrix * vPosition;" +
						"vec3 transformed_normal = normalize(mat3(u_view_matrix * u_model_matrix) * vNormal);" +
						"vec3 view_vector = normalize(-eye_coordinates.xyz);" +
						"vec3 light_direction[3];" +
						"vec3 reflection_vector[3];" +
						"vec3 ambient[3];" +
						"vec3 diffuse[3];" +
						"vec3 specular[3];" +
						"for(i = 0; i < 3; i++)" +
						"{" +
						"light_direction[i] = normalize(vec3(u_light_position[i] - eye_coordinates));" +
						"reflection_vector[i] = reflect(-light_direction[i], transformed_normal);" +
						"ambient[i] = u_la[i] * u_ka;" +
						"diffuse[i] = u_ld[i] * u_kd * max(dot(light_direction[i], transformed_normal), 0.0);" +
						"specular[i] = u_ls[i] * u_ks * pow(max(dot(reflection_vector[i], view_vector), 0.0), u_material_shinyness);" +
						"out_phong_light = out_phong_light + ambient[i] + diffuse[i] + specular[i];" +
						"}" +
						"}" +
						"else" +
						"{" +
						"out_phong_light = vec3(1.0, 1.0, 1.0);" +
						"}" +
						"gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vPosition;" +
						"}"
		);

		// provide source code to shader
		GLES32.glShaderSource(grvertexShaderObjectPV, grvertexShaderSourceCodePV);

		// compile shader and check for error
		GLES32.glCompileShader(grvertexShaderObjectPV);
		griShaderCompileStatus[0] = 0;
		griInfoLength[0] = 0;
		grszInfoLog = null;

		GLES32.glGetShaderiv(grvertexShaderObjectPV, GLES32.GL_COMPILE_STATUS,
				griShaderCompileStatus, 0);
		if(griShaderCompileStatus[0] == GLES32.GL_FALSE)
		{
			GLES32.glGetShaderiv(grvertexShaderObjectPV, GLES32.GL_INFO_LOG_LENGTH,
					griInfoLength, 0);

			if(griInfoLength[0] > 0)
			{
				grszInfoLog = GLES32.glGetShaderInfoLog(grvertexShaderObjectPV);
				System.out.println("OGL_GR : PV Vertex shader compilation log : " + grszInfoLog);
				uninitialize();
				System.exit(0);
			}
		}

		////////// Fragment shader
		// create shader
		grfragmentShaderObjectPV = GLES32.glCreateShader(GLES32.GL_FRAGMENT_SHADER);

		// fragment shader source code
		final String grfragmentShaderSourceCodePV = String.format(
						"#version 320 es" +
						"\n" +
						"precision highp float;" +
						"in vec3 out_phong_light;" +
						"out vec4 FragColor;" +
						"void main(void)" +
						"{" +
						"FragColor = vec4(out_phong_light, 1.0);" +
						"}"
		);

		// provide source code to shader
		GLES32.glShaderSource(grfragmentShaderObjectPV, grfragmentShaderSourceCodePV);

		// compile shader
		GLES32.glCompileShader(grfragmentShaderObjectPV);
		griShaderCompileStatus[0] = 0;
		griInfoLength[0] = 0;
		grszInfoLog = null;
		GLES32.glGetShaderiv(grfragmentShaderObjectPV, GLES32.GL_COMPILE_STATUS,
				griShaderCompileStatus, 0);
		if(griShaderCompileStatus[0] == GLES32.GL_FALSE)
		{
			GLES32.glGetShaderiv(grfragmentShaderObjectPV, GLES32.GL_INFO_LOG_LENGTH, griInfoLength, 0);

			if(griInfoLength[0] > 0)
			{
				grszInfoLog = GLES32.glGetShaderInfoLog(grfragmentShaderObjectPV);
				System.out.println("OGL_GR : PV Fragment shader compilation log : " + grszInfoLog);
				uninitialize();
				System.exit(0);
			}
		}

		// create shader program
		grshaderProgramObjectPV = GLES32.glCreateProgram();

		// attach vertex shader to shader program
		GLES32.glAttachShader(grshaderProgramObjectPV, grvertexShaderObjectPV);

		// attach fragment shader to shader program
		GLES32.glAttachShader(grshaderProgramObjectPV, grfragmentShaderObjectPV);

		// prelink binding of shader program object with vertex shader attributes
		GLES32.glBindAttribLocation(grshaderProgramObjectPV, GLESMacros.GR_ATTRIBUTE_POSITION,
				"vPosition");
		GLES32.glBindAttribLocation(grshaderProgramObjectPV, GLESMacros.GR_ATTRIBUTE_NORMAL,
				"vNormal");

		// link
		GLES32.glLinkProgram(grshaderProgramObjectPV);
		griShaderProgramLinkStatus = new int[1];
		griInfoLength[0] = 0;
		grszInfoLog = null;
		GLES32.glGetProgramiv(grshaderProgramObjectPV, GLES32.GL_LINK_STATUS,
				griShaderProgramLinkStatus, 0);
		if(griShaderProgramLinkStatus[0] == GLES32.GL_FALSE)
		{
			GLES32.glGetProgramiv(grshaderProgramObjectPV, GLES32.GL_INFO_LOG_LENGTH,
					griInfoLength, 0);

			if(griInfoLength[0] > 0)
			{
				grszInfoLog = GLES32.glGetProgramInfoLog(grshaderProgramObjectPV);
				System.out.println("OGL_GR : Shader program link log : " + grszInfoLog);
				uninitialize();
				System.exit(0);
			}
		}
		System.out.println("OGL_GR : PV before uniform location");
		// get uniform location
		grmodelMatrixUniformPV = GLES32.glGetUniformLocation(grshaderProgramObjectPV, "u_model_matrix");
		grviewMatrixUniformPV = GLES32.glGetUniformLocation(grshaderProgramObjectPV, "u_view_matrix");
		grprojectionMatrixUniformPV = GLES32.glGetUniformLocation(grshaderProgramObjectPV, "u_projection_matrix");

		grlaUniformPV[0] = GLES32.glGetUniformLocation(grshaderProgramObjectPV, "u_la[0]");
		grldUniformPV[0] = GLES32.glGetUniformLocation(grshaderProgramObjectPV, "u_ld[0]");
		grlsUniformPV[0] = GLES32.glGetUniformLocation(grshaderProgramObjectPV, "u_ls[0]");
		grlaUniformPV[1] = GLES32.glGetUniformLocation(grshaderProgramObjectPV, "u_la[1]");
		grldUniformPV[1] = GLES32.glGetUniformLocation(grshaderProgramObjectPV, "u_ld[1]");
		grlsUniformPV[1] = GLES32.glGetUniformLocation(grshaderProgramObjectPV, "u_ls[1]");
		grlaUniformPV[2] = GLES32.glGetUniformLocation(grshaderProgramObjectPV, "u_la[2]");
		grldUniformPV[2] = GLES32.glGetUniformLocation(grshaderProgramObjectPV, "u_ld[2]");
		grlsUniformPV[2] = GLES32.glGetUniformLocation(grshaderProgramObjectPV, "u_ls[2]");
		grlightPositionUniformPV[0] = GLES32.glGetUniformLocation(grshaderProgramObjectPV, "u_light_position[0]");
		grlightPositionUniformPV[1] = GLES32.glGetUniformLocation(grshaderProgramObjectPV, "u_light_position[1]");
		grlightPositionUniformPV[2] = GLES32.glGetUniformLocation(grshaderProgramObjectPV, "u_light_position[2]");
		grkaUniformPV = GLES32.glGetUniformLocation(grshaderProgramObjectPV, "u_ka");
		grkdUniformPV = GLES32.glGetUniformLocation(grshaderProgramObjectPV, "u_kd");
		grksUniformPV = GLES32.glGetUniformLocation(grshaderProgramObjectPV, "u_ks");

		grlKeyPressedUniformPV = GLES32.glGetUniformLocation(grshaderProgramObjectPV, "u_l_key_pressed");
		grmaterialShinynessUniformPV = GLES32.glGetUniformLocation(grshaderProgramObjectPV, "u_material_shinyness");
		System.out.println("OGL_GR : PV after uniform location");
		// Initialize colors
		grlight[0] = new Light();
		grlight[0].lightAmbientColor = new float[]{0.0f, 0.0f, 0.0f, 1.0f};
		grlight[0].lightDiffuseColor = new float[]{1.0f, 0.0f, 0.0f, 1.0f};
		grlight[0].lightSpecularColor = new float[]{1.0f, 0.0f, 0.0f, 1.0f};
		grlight[0].lightPosition = new float[]{0.0f, 0.0f, 0.0f, 1.0f};

		grlight[1] = new Light();
		grlight[1].lightAmbientColor = new float[]{0.0f, 0.0f, 0.0f, 1.0f};
		grlight[1].lightDiffuseColor = new float[]{0.0f, 1.0f, 0.0f, 1.0f};
		grlight[1].lightSpecularColor = new float[]{0.0f, 1.0f, 0.0f, 1.0f};
		grlight[1].lightPosition = new float[]{0.0f, 0.0f, 0.0f, 1.0f};

		grlight[2] = new Light();
		grlight[2].lightAmbientColor = new float[]{0.0f, 0.0f, 0.0f, 1.0f};
		grlight[2].lightDiffuseColor = new float[]{0.0f, 0.0f, 1.0f, 1.0f};
		grlight[2].lightSpecularColor = new float[]{0.0f, 0.0f, 1.0f, 1.0f};
		grlight[2].lightPosition = new float[]{0.0f, 0.0f, 0.0f, 1.0f};
		System.out.println("OGL_GR : colors initialization done");
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
		// vbo normal
		GLES32.glGenBuffers(1, grvboSphereNormal, 0);
		GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER, grvboSphereNormal[0]);
		grbyteBuffer = ByteBuffer.allocateDirect(grsphereNormals.length * 4);
		grbyteBuffer.order(ByteOrder.nativeOrder());
		grverticesBuffer = grbyteBuffer.asFloatBuffer();
		grverticesBuffer.put(grsphereNormals);
		grverticesBuffer.position(0);

		GLES32.glBufferData(GLES32.GL_ARRAY_BUFFER, grsphereNormals.length * 4, grverticesBuffer, GLES32.GL_STATIC_DRAW);
		GLES32.glVertexAttribPointer(GLESMacros.GR_ATTRIBUTE_NORMAL, 3, GLES32.GL_FLOAT, false, 0, 0);
		GLES32.glEnableVertexAttribArray(GLESMacros.GR_ATTRIBUTE_NORMAL);
		GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER, 0);
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

		// enable depth testing
		GLES32.glEnable(GLES32.GL_DEPTH_TEST);
		GLES32.glEnable(GLES32.GL_LEQUAL);
		GLES32.glClearDepthf(1.0f);

		// set background color
		GLES32.glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// set projection matrix to identity matrix
		Matrix.setIdentityM(grperspectiveMatrix, 0);
		System.out.println("OGL_GR : initialize end");
	}

	private void resize(int width, int height)
	{
		GLES32.glViewport(0, 0, width, height);

		Matrix.perspectiveM(grperspectiveMatrix, 0, 45.0f, (float) width / (float) height, 0.1f, 100.0f);
	}

	private void display()
	{
		GLES32.glClear(GLES32.GL_COLOR_BUFFER_BIT | GLES32.GL_DEPTH_BUFFER_BIT);

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

		Matrix.translateM(grtranslateMatrix, 0, 0.0f, 0.0f, -4.0f);
		Matrix.multiplyMM(grmodelMatrix, 0, grmodelMatrix, 0, grtranslateMatrix, 0);
		Matrix.multiplyMM(grprojectionMatrix, 0, grprojectionMatrix, 0, grperspectiveMatrix, 0);

		if(grisPerVertexLight)
		{
			GLES32.glUseProgram(grshaderProgramObjectPV);
			if(grbLight == true)
			{
				GLES32.glUniform1i(grlKeyPressedUniformPV, 1);
				GLES32.glUniform3fv(grkdUniformPV, 1, grkd, 0);
				GLES32.glUniform3fv(grkaUniformPV, 1, grka, 0);
				GLES32.glUniform3fv(grksUniformPV, 1, grks, 0);
				GLES32.glUniform1f(grmaterialShinynessUniformPV, grmaterialShinyness);
				if(grX == true)
				{
					/*
					grlight[0].lightPosition[0] = 0.0f;
					grlight[0].lightPosition[1] = (float) (5.5 * Math.sin(grangle));
					grlight[0].lightPosition[2] = (float) (5.5 * Math.cos(grangle));
					grlight[0].lightPosition[3] = 1.0f;									// light direction - 1 for positional light

					 */
					grlight[0].lightPosition[0] = (float) (5.5 * Math.sin(grangleX));
					grlight[0].lightPosition[1] = 0.0f;
					grlight[0].lightPosition[2] = (float) (5.5 * Math.cos(grangleX));
					grlight[0].lightPosition[3] = 1.0f;
				}
				if(grY == true)
				{
					grlight[1].lightPosition[0] = (float) (4.5 * Math.sin(grangle));
					grlight[1].lightPosition[1] = 0.0f;
					grlight[1].lightPosition[2] = (float) (4.5 * Math.cos(grangle));
					grlight[1].lightPosition[3] = 1.0f;
				}
				if(grZ == true)
				{
					grlight[2].lightPosition[0] = (float) (6.5 * Math.sin(grangle));
					grlight[2].lightPosition[1] = (float) (6.5 * Math.cos(grangle));
					grlight[2].lightPosition[2] = 0.0f;
					grlight[2].lightPosition[3] = 1.0f;
				}
				for(i = 0; i < 3; i++)
				{
					GLES32.glUniform3fv(grldUniformPV[i], 1, grlight[i].lightDiffuseColor, 0);
					GLES32.glUniform3fv(grlaUniformPV[i], 1, grlight[i].lightAmbientColor, 0);
					GLES32.glUniform3fv(grlsUniformPV[i], 1, grlight[i].lightSpecularColor, 0);
					GLES32.glUniform4fv(grlightPositionUniformPV[i], 1, grlight[i].lightPosition, 0);
				}
			}
			else
			{
				GLES32.glUniform1i(grlKeyPressedUniformPV, 0);
			}

			GLES32.glUniformMatrix4fv(grmodelMatrixUniformPV, 1, false, grmodelMatrix, 0);
			GLES32.glUniformMatrix4fv(grviewMatrixUniformPV, 1, false, grviewMatrix, 0);
			GLES32.glUniformMatrix4fv(grprojectionMatrixUniformPV, 1, false, grprojectionMatrix, 0);
		}
		else
		{
			GLES32.glUseProgram(grshaderProgramObjectPF);
			if(grbLight == true)
			{
				GLES32.glUniform1i(grlKeyPressedUniformPF, 1);
				GLES32.glUniform3fv(grkdUniformPF, 1, grkd, 0);
				GLES32.glUniform3fv(grkaUniformPF, 1, grka, 0);
				GLES32.glUniform3fv(grksUniformPF, 1, grks, 0);
				GLES32.glUniform1f(grmaterialShinynessUniformPF, grmaterialShinyness);

				if(grZ == true)
				{
					grlight[2].lightPosition[0] = (float) (6.5 * Math.sin(grangle));
					grlight[2].lightPosition[1] = (float) (6.5 * Math.cos(grangle));
					grlight[2].lightPosition[2] = 0.0f;
					grlight[2].lightPosition[3] = 1.0f;
				}
				if(grY == true)
				{
					grlight[1].lightPosition[0] = (float) (4.5 * Math.sin(grangle));
					grlight[1].lightPosition[1] = 0.0f;
					grlight[1].lightPosition[2] = (float) (4.5 * Math.cos(grangle));
					grlight[1].lightPosition[3] = 1.0f;
				}
				if(grX == true)
				{
					grlight[0].lightPosition[0] = 0.0f;
					grlight[0].lightPosition[1] = (float) (5.5 * Math.sin(grangleX));
					grlight[0].lightPosition[2] = (float) (5.5 * Math.cos(grangleX));
					grlight[0].lightPosition[3] = 1.0f;									// light direction - 1 for positional light
				}

				for(i = 0; i < 3; i++)
				{
					GLES32.glUniform3fv(grldUniformPF[i], 1, grlight[i].lightDiffuseColor, 0);
					GLES32.glUniform3fv(grlaUniformPF[i], 1, grlight[i].lightAmbientColor, 0);
					GLES32.glUniform3fv(grlsUniformPF[i], 1, grlight[i].lightSpecularColor, 0);
					GLES32.glUniform4fv(grlightPositionUniformPF[i], 1, grlight[i].lightPosition, 0);
				}
			}
			else
			{
				GLES32.glUniform1i(grlKeyPressedUniformPF, 0);
			}

			GLES32.glUniformMatrix4fv(grmodelMatrixUniformPF, 1, false, grmodelMatrix, 0);
			GLES32.glUniformMatrix4fv(grviewMatrixUniformPF, 1, false, grviewMatrix, 0);
			GLES32.glUniformMatrix4fv(grprojectionMatrixUniformPF, 1, false, grprojectionMatrix, 0);
		}

		// bind vao
		GLES32.glBindVertexArray(grvaoSphere[0]);
		GLES32.glBindBuffer(GLES32.GL_ELEMENT_ARRAY_BUFFER, grvboSphereElement[0]);
		GLES32.glDrawElements(GLES32.GL_TRIANGLES, grnumElements, GLES32.GL_UNSIGNED_SHORT, 0);
		GLES32.glBindVertexArray(0);

		GLES32.glUseProgram(0);
		update();
		requestRender();
	}

	void update()
	{
		// code
		//if(grX || grY || grZ)
		//{
			grangle = grangle + 0.05f;
			if(grangle >= 360.0f)
				grangle = 0.0f;
		//}
		grangleX = grangleX + 0.05f;
		if(grangleX >= 360.0f)
			grangleX = 0.0f;

		grangleY = grangleY + 0.05f;
		if(grangleY >= 360.0f)
			grangleY = 0.0f;

	}

	void uninitialize()
	{
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

		// shader for per vertex
		if(grshaderProgramObjectPV != 0)
		{
			if(grvertexShaderObjectPV != 0)
			{
				// detach vertex shader from shader program
				GLES32.glDetachShader(grshaderProgramObjectPV, grvertexShaderObjectPV);
				// delete vertex shader
				GLES32.glDeleteShader(grvertexShaderObjectPV);
				grvertexShaderObjectPV = 0;
			}
			if(grfragmentShaderObjectPV != 0)
			{
				// detach vertex shader from shader program
				GLES32.glDetachShader(grshaderProgramObjectPV, grfragmentShaderObjectPV);
				// delete vertex shader
				GLES32.glDeleteShader(grfragmentShaderObjectPV);
				grfragmentShaderObjectPV = 0;
			}
		}
		// delete shader program object
		if(grshaderProgramObjectPV != 0)
		{
			GLES32.glDeleteProgram(grshaderProgramObjectPV);
			grshaderProgramObjectPV = 0;
		}

		// shaders for Per Fragment
		if(grshaderProgramObjectPF != 0)
		{
			if(grvertexShaderObjectPF != 0)
			{
				// detach vertex shader from shader program
				GLES32.glDetachShader(grshaderProgramObjectPF, grvertexShaderObjectPF);
				// delete vertex shader
				GLES32.glDeleteShader(grvertexShaderObjectPF);
				grvertexShaderObjectPF = 0;
			}
			if(grfragmentShaderObjectPF != 0)
			{
				// detach vertex shader from shader program
				GLES32.glDetachShader(grshaderProgramObjectPF, grfragmentShaderObjectPF);
				// delete vertex shader
				GLES32.glDeleteShader(grfragmentShaderObjectPF);
				grfragmentShaderObjectPF = 0;
			}
		}
		// delete shader program object
		if(grshaderProgramObjectPF != 0)
		{
			GLES32.glDeleteProgram(grshaderProgramObjectPF);
			grshaderProgramObjectPF = 0;
		}

	}
}






























