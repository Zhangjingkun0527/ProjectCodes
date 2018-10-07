package codes.objects;

import codes.superclasses.GameObject;

import java.awt.*;
import java.awt.event.KeyEvent;

public class Plane extends GameObject {
    private boolean left, right, up, down;

    @Override
    public void drawSelf(Graphics g){
        g.drawImage(img, (int)x, (int)y, null);
        speed = 10;
        if(left){
            x -= speed;
        }

        if(right){
            x += speed;
        }

        if(up){
            y -= speed;
        }

        if(down){
            y += speed;
        }
    }

    public Plane(Image img, double x, double y){
        super();
        this.img = img;
        this.x = x;
        this.y = y;
    }

    public void addDirection(KeyEvent e){
        switch (e.getKeyCode()){
            case KeyEvent.VK_LEFT:
                left = true;
                break;
            case KeyEvent.VK_RIGHT:
                right = true;
                break;
            case KeyEvent.VK_UP:
                up = true;
                break;
            case KeyEvent.VK_DOWN:
                down = true;
                break;
        }
    }

    public void deleteDirection(KeyEvent e){
        switch (e.getKeyCode()){
            case KeyEvent.VK_LEFT:
                left = false;
                break;
            case KeyEvent.VK_RIGHT:
                right = false;
                break;
            case KeyEvent.VK_UP:
                up = false;
                break;
            case KeyEvent.VK_DOWN:
                down = false;
                break;
        }
    }

}
