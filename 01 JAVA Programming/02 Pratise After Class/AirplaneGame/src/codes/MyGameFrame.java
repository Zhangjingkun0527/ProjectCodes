package codes;

import codes.objects.Plane;
import codes.objects.Shell;
import codes.util.Constant;
import codes.util.GameUtility;

import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

/**
 * create the main windows of this game
 */
public class MyGameFrame extends Frame {

    public static void main(String args[]){
        var myGameFrame = new MyGameFrame();
        myGameFrame.launchFrame();
    }

    /**
     * initial the windows
     */
    private void launchFrame(){
        this.setTitle("Airplane Game Made by zjk");
        this.setVisible(true);
        this.setSize(Constant.GAME_WIDTH,Constant.GAME_HEIGHT);
        this.setLocation(100,100);


        this.addWindowStateListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent event){
                System.exit(0);
            }
        });

        new PaintThread().start();
        addKeyListener(new KeyMonitor());
    }

    private Image bg = GameUtility.getImage("images/bg.jpg");
    private Image planeImage = GameUtility.getImage("images/plane.png");
    private Plane plane = new Plane(planeImage,100,100);
    private Shell shell = new Shell();
    @Override
    public void paint(Graphics g){
        g.drawImage(bg, 0,0,null);
        plane.drawSelf(g);
        shell.drawSelf(g);
    }

    class PaintThread extends Thread{
        @Override
        public void run(){
            while (true){
                repaint();
                try {
                    Thread.sleep(40);
                }catch (InterruptedException ie){
                    ie.printStackTrace();
                }
            }
        }
    }

    class KeyMonitor extends KeyAdapter{

        @Override
        public void keyPressed(KeyEvent e){
            plane.addDirection(e);
        }

        @Override
        public void keyReleased(KeyEvent e){
            plane.deleteDirection(e);
        }

    }

    private Image offScreenImage = null;
    @Override
    public void update(Graphics g){
        if(offScreenImage == null)
            offScreenImage = this.createImage(Constant.GAME_WIDTH, Constant.GAME_HEIGHT);

        var gOff = offScreenImage.getGraphics();
        paint(gOff);
        gOff.dispose();
        g.drawImage(offScreenImage, 0, 0, null);
    }
}
