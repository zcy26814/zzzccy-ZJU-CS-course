import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Point;

public class EssayPaint {

	public static void main(String[] args) {
		
		JFrame frame = new JFrame("Essay Paint");
		frame.setSize(800, 500);
		frame.getContentPane().setBackground(Color.RED);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		MouseHandle panel = new MouseHandle();
		panel.setBackground(Color.WHITE);
		frame.add(panel);
		
		frame.setVisible(true);

	}
}

class MouseHandle extends JPanel {
	

	private static final long serialVersionUID = 1L;
	private Point priorLocation, currentLocation;
	int button;
	float size;
	static final float MAXSIZE = 20, MINSIZE = (float)2.5;
	
	{
		this.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				button = e.getButton();
				currentLocation = e.getPoint();
				priorLocation = null;
			}

			public void mouseReleased(MouseEvent e) {
				priorLocation = e.getPoint();
				currentLocation = null;
			}
			
		});
		
		this.addMouseMotionListener(new MouseMotionAdapter() {
			public void mouseDragged(MouseEvent e) {
				priorLocation = currentLocation;
				currentLocation = e.getPoint();
				size = (float)(1 / (1 + priorLocation.distance(currentLocation)) * (MAXSIZE - MINSIZE)) + MINSIZE;
				repaint();
			}
			
		});
	}
	

	
	public void paint(Graphics g) {
		Graphics2D g2D = (Graphics2D) g;
		if(priorLocation != null && currentLocation != null) {
			if(button == MouseEvent.BUTTON1) {
				g2D.setColor(Color.BLACK);
			} else if(button == MouseEvent.BUTTON3) {
				g2D.setColor(Color.WHITE);
			}
			g2D.setStroke(new BasicStroke(size));
			g2D.drawLine(priorLocation.x, priorLocation.y, currentLocation.x, currentLocation.y);
		}
		
	}
	
}
