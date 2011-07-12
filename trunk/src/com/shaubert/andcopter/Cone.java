package com.shaubert.andcopter;


public class Cone extends Group {

    public Cone() {
        this(1, 1, 1, 10, 2);
    }
    
    public Cone(float baseRadius, float topRadius, float height, int numberOfSides, int segmentsInSideDimension) {
        float dy = height / 2;
        float dangle = 360f / numberOfSides;
        float degree = 0;
        for (int i = 0; i < numberOfSides; i++) {
            if (baseRadius > 0) {
                float[] pointTop = getPoint(topRadius, dy, degree);
                float[] pointBottom = getPoint(baseRadius, -dy, degree);
                float[] pointBottomNext = getPoint(baseRadius, -dy, degree+dangle);
                add(new Triangle(segmentsInSideDimension, concatArrays(pointTop, pointBottom, pointBottomNext)));
            }
            if (topRadius > 0) {
                float[] pointTop = getPoint(topRadius, dy, degree);
                float[] pointTopNext = getPoint(topRadius, dy, degree+dangle);
                float[] pointBottomNext = getPoint(baseRadius, -dy, degree+dangle);
                add(new Triangle(segmentsInSideDimension, concatArrays(pointTop, pointBottomNext, pointTopNext)));
            }
            degree += dangle;
        }
        
        if (baseRadius > 0) {
            Circle circle = new Circle(baseRadius, numberOfSides, segmentsInSideDimension);
            circle.translate(0, -dy, 0);
            circle.rotate(90, 0, 0);
            add(circle);
        }
        
        if (topRadius > 0) {
            Circle circle = new Circle(topRadius, numberOfSides, segmentsInSideDimension);
            circle.translate(0, dy, 0);
            circle.rotate(-90, 0, 0);
            add(circle);
        }
    }
    
    private float[] getPoint(float radius, float dy, float degree) {
        float[] result = new float[3];
        result[0] = (float)(radius * Math.cos(Math.toRadians(degree)));
        result[1] = dy;
        result[2] = -(float)(radius * Math.sin(Math.toRadians(degree)));
        return result;
    }
    
    private float[] concatArrays(float[] ... arrays) {
        int size = arrays[0].length * arrays.length;
        float[] result = new float[size];
        int pos = 0;
        for (int i = 0; i < arrays.length; i++) {
            for (int j = 0; j < arrays[i].length; j++) {
                result[pos++] = arrays[i][j];
            }
        }
        return result;
    }
    
}
