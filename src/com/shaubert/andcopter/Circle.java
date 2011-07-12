package com.shaubert.andcopter;

public class Circle extends Group {

    public Circle() {
        this(2, 10, 3);
    }
    
    public Circle(float radius, float parts, int segmentsInPart) {
        float dAngle = (float)(Math.PI * 2 / parts);
        float angle = 0;;
        for (int i = 0; i < parts; i++) {
            add(new Triangle(segmentsInPart, 
                    0f, 0f, 0f,
                    (float)(Math.cos(angle) * radius), (float)(Math.sin(angle) * radius), 0f,
                    (float)(Math.cos(angle + dAngle) * radius), (float)(Math.sin(angle + dAngle) * radius), 0f));
            angle += dAngle;
        }
    }
}
