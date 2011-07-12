package com.shaubert.andcopter;


public class Cube extends Group {

    public Cube() {
        this(1, 1, 1, 1, 1, 1);
    }
    
    public Cube(float width, float height, float depth) {
        this(width, height, depth, 1, 1, 1);
    }
    
    public Cube(float width, float height, float depth,
            int widthSegments, int heightSegments, int depthSegments) {
        //front
        Plane plane = new Plane(width, height, widthSegments, heightSegments);
        plane.translate(0, 0, -depth/2);
        add(plane);
        
        //rear
        plane = new Plane(width, height, widthSegments, heightSegments);
        plane.translate(0, 0, depth/2);
        add(plane);
        
        //top
        plane = new Plane(width, depth, widthSegments, depthSegments);
        plane.translate(0, height/2, 0);
        plane.rotate(-90f, 0, 0);
        add(plane);
        
        //bottom
        plane = new Plane(width, depth, widthSegments, depthSegments);
        plane.translate(0, -height/2, 0);
        plane.rotate(90f, 0, 0);
        add(plane);

        //left
        plane = new Plane(depth, height, depthSegments, heightSegments);
        plane.translate(-width/2, 0, 0);
        plane.rotate(0, 90f, 0);
        add(plane);

        //right
        plane = new Plane(depth, height, depthSegments, heightSegments);
        plane.translate(width/2, 0, 0);
        plane.rotate(0, 90f, 0);
        add(plane);
    }    
}
