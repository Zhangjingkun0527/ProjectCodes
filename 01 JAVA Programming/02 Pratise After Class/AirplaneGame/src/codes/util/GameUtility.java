package codes.util;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.IOException;

public class GameUtility {
    private GameUtility(){}

    /**
     * return a image through its path
     * @param path
     * @return
     */
    public static Image getImage(String path){
        BufferedImage bufferedImage = null;
        try {
            var u = GameUtility.class.getClassLoader().getResource(path);
            bufferedImage = ImageIO.read(u);
        }catch (IOException e){
            e.printStackTrace();
        }
        return bufferedImage;
    }
}
