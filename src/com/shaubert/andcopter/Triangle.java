package com.shaubert.andcopter;

public class Triangle extends Mesh {

    public Triangle() {
        this(1f, 1);
    }
     
    public Triangle(float size, int segmentsInDimension) {
        this(segmentsInDimension, 
                0, (float)(size / Math.sqrt(3)), 0
               -size/2, (float)(-size/(2 * Math.sqrt(3))), 0, 
                size/2, (float)(-size/(2 * Math.sqrt(3))), 0);
    }
    
    public Triangle(int segmentsInDimension, float ... points) {
        if (points.length != 9) {
           throw new IllegalArgumentException("points count must be equal 9, not " + points.length);
        }
        float[] vertices = new float[((segmentsInDimension + 1) * ((segmentsInDimension + 1) + 2) / 2) * 3];
        short[] indices = new short[segmentsInDimension * segmentsInDimension * 3];
        
        int vCounter = 0;
        int iCounter = 0;
        for (int j = 0; j <= segmentsInDimension; j++) {
            float part = (float)j / segmentsInDimension;
            float leftPointX = getPart(getPointX(points, 0), getPointX(points, 1), part); 
            float leftPointY = getPart(getPointY(points, 0), getPointY(points, 1), part);
            float leftPointZ = getPart(getPointZ(points, 0), getPointZ(points, 1), part);
            float rightPointX = getPart(getPointX(points, 0), getPointX(points, 2), part); 
            float rightPointY = getPart(getPointY(points, 0), getPointY(points, 2), part);
            float rightPointZ = getPart(getPointZ(points, 0), getPointZ(points, 2), part);
            for (int i = 0; i <= j; i++) {
                float part2 = j == 0 ? 0 : ((float)i / j);
                vertices[vCounter++] = getPart(leftPointX, rightPointX, part2); 
                vertices[vCounter++] = getPart(leftPointY, rightPointY, part2);
                vertices[vCounter++] = getPart(leftPointZ, rightPointZ, part2);
                
                short dotIndex = (short)((vCounter - 1) / 3); 
                if (j < segmentsInDimension) {
                    indices[iCounter++] = dotIndex;
                    indices[iCounter++] = (short)(dotIndex + j + 1);
                    indices[iCounter++] = (short)(dotIndex + j + 2);
                    if (i > 0) {
                        indices[iCounter++] = (short)(dotIndex - 1);
                        indices[iCounter++] = (short)(dotIndex + j + 1);
                        indices[iCounter++] = (short)(dotIndex);
                    }
                }
            }
        }
        
        setVertices(vertices);
        setIndices(indices);
    }
    
    private float getPart(float x1, float x2, float part) {
        return x1 + (x2 - x1) * part;
    }
    
    private float getPointZ(float[] points, int index) {
        return points[index * 3 + 2];
    }
    
    private float getPointY(float[] points, int index) {
        return points[index * 3 + 1];
    }
    
    private float getPointX(float[] points, int index) {
        return points[index * 3];
    }
}
