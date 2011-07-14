package com.shaubert.andcopter;

public class Quad extends Group {

    public Quad() {
        this(1f, 1);
    }
     
    public Quad(float size, int segments) {
        this(segments, 
                -size/2, size/2, 0,
                -size/2, -size/2, 0, 
                 size/2, -size/2, 0,
                 size/2, size/2, 0);
    }
    
    public Quad(int segments, float ... points) {
        if (points.length != 12) {
            throw new IllegalArgumentException("points count must be equal 12, not " + points.length);
        }
        if (!equalPoints(points, 0, 1) && !equalPoints(points, 1, 3) && !equalPoints(points, 0, 3)) {
            add(new Triangle(segments, 
                    points[0], points[1], points[2],
                    points[3], points[4], points[5],
                    points[9], points[10], points[11]));
        }
        if (!equalPoints(points, 1, 2) && !equalPoints(points, 2, 3) && !equalPoints(points, 1, 3)) {
            add(new Triangle(segments, 
                points[3], points[4], points[5],
                points[6], points[7], points[8],
                points[9], points[10], points[11]));
        }
    }

    private boolean equalPoints(float[] points, int pIndex1, int pIndex2) {
        for (int i = 0; i < 3; i++) {
            if (points[pIndex1 * 3 + i] != points[pIndex2 * 3 + i]) {
                return false;
            }
        }
        return true;
    }
}
