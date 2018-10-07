package codes.superclasses;

import java.awt.*;

public class GameObject {
    protected Image img;
    protected double x,y;
    protected int speed;
    protected int width,height;

    public GameObject(){}

    public GameObject(Image img, double x, double y){
        super();
        this.img = img;
        this.x = x;
        this.y = y;
    }

    public GameObject(Image img, double x, double y, int speed, int width, int height){
        super();
        this.img = img;
        this.x = x;
        this.y = y;
        this.speed = speed;
        this.width = width;
        this.height = height;
    }

    public GameObject(Image img, double x, double y, int width, int height){
        super();
        this.img = img;
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
    }

    /**
     * paint object itself
     * @param g
     */
    public void drawSelf(Graphics g){
        g.drawImage(img, (int)x, (int)y ,null);
    }

    /**
     * return the rect of object in order to detect conflict
     * @return
     */
    public  Rectangle getRect(){
        return new Rectangle((int)x, (int)y, width, height);
    }
}
