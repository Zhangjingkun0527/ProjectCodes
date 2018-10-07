package codes.objects;

import codes.superclasses.GameObject;
import codes.util.Constant;

import java.awt.*;

public class Shell extends GameObject {

    private double degree;
    public Shell(){
        x = 200;
        y = 200;
        width = 10;
        height = 10;
        speed = 3;
        degree = Math.random() * Math.PI * 2;
    }

    @Override
    public void drawSelf(Graphics g){
        var c = g.getColor();
        g.setColor(Color.yellow);
        g.fillOval((int)x, (int)y,width,height);

        x += speed*Math.cos(degree);
        y += speed*Math.sin(degree);
        if(x < 0 || x > Constant.GAME_WIDTH){

        }

        g.setColor(c);
    }


}
