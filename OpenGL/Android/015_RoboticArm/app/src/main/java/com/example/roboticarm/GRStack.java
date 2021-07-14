package com.example.roboticarm;

import android.opengl.Matrix;

import java.util.Stack;

public class GRStack {
    public static Stack<float[]> grstackMatrix;
    public static int grposition = -1;
    float[] currentMatrix = new float[16];
    float[] identityMatrix = new float[16];

    GRStack()
    {
        grstackMatrix = new Stack<>();
        Matrix.setIdentityM(identityMatrix, 0);
    }

    public float[] pushToStack(float matrix[])
    {
        if(grposition == -1)
        {
            grstackMatrix.push(matrix.clone());
            grposition++;
        }
        else
        {
            currentMatrix = grstackMatrix.peek();
            Matrix.multiplyMM(matrix, 0, currentMatrix, 0, matrix, 0);
            grstackMatrix.push(matrix.clone());
            grposition++;
        }
        //System.out.println("OGL_GR Push : "+ matrix);
        return matrix.clone();
    }

    public float[] popFromStack()
    {
        if(grposition == -1)
        {
            //System.out.println("OGL_GR Pop grposition -1 : "+ identityMatrix);
            return identityMatrix;
        }
        else
        {
            grposition--;
            currentMatrix = grstackMatrix.pop();
            //System.out.println("OGL_GR Pop  : "+ currentMatrix);
            return currentMatrix.clone();
        }
    }

    public float[] peekFromStack()
    {
        return grstackMatrix.peek();
    }

    public void destroyStack()
    {
        currentMatrix = null;
        identityMatrix = null;
        grstackMatrix = null;
    }
}
