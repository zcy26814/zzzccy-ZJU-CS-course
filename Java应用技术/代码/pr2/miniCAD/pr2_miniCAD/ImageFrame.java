import java.awt.BasicStroke;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Point;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

import javax.imageio.ImageIO;
import javax.swing.Icon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.event.MenuEvent;
import javax.swing.event.MenuListener;

public class ImageFrame {

	public static void main(String[] args) {
		ImageDatabase imageDatabase = new ImageDatabase();
		
		JFrame frame = new JFrame("Image Paint");
		frame.setSize(800, 500);
		frame.getContentPane().setBackground(Color.RED);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setLayout(new BorderLayout());
		
		ImageMenu panelMenu = new ImageMenu(imageDatabase);
		panelMenu.setBackground(Color.WHITE);
		frame.add("North", panelMenu);
		
		ImagePlot panelPlot = new ImagePlot(imageDatabase);
		panelPlot.setBackground(Color.WHITE);
		frame.add("Center", panelPlot);
		
		ImageButton panelButton = new ImageButton(imageDatabase);
		panelButton.setBackground(Color.WHITE);
		frame.add("West", panelButton);
		
		frame.setVisible(true);
		
		imageDatabase.imageMenu = panelMenu;
		imageDatabase.imagePlot = panelPlot;
		imageDatabase.imageButton = panelButton;
		
		imageDatabase.focusComponent = panelPlot;
		imageDatabase.focusComponent.requestFocus();

	}

}

class ImageIcon implements Icon {
	
	public final static int LINE = 0, RECTANGLE = 1, CIRCLE = 2, TEXTAREA = 3;
	public final static int SHAPE_INITIAL = 0, SHAPE_NUMBER = 4;
	
	public final static Color[] COLOR_LIST = {
		Color.RED, Color.ORANGE, Color.YELLOW, Color.GREEN, 
		Color.BLUE, Color.GRAY,	Color.BLACK, Color.WHITE
	};
	public final static int RED = 0, ORANGE = 1, YELLOW = 2, GREEN = 3,
			BLUE = 4, GRAY = 5, BLACK = 6, WHITE = 7;
	public final static int COLOR_INITIAL = 0, COLOR_NUMBER = 8;
	public final static int SHAPE_COLOR = 4;

	
	private int type;
	private int width, height;
	private Color color;
	
	public ImageIcon() {
		super();
	}
	
	public ImageIcon(int type) {
		this.type = type;
		this.width = 1;
		this.height = 1;
		this.color = Color.BLACK;
	}
	
	public ImageIcon(int type, int width, int height) {
		this.type = type;
		this.width = width;
		this.height = height;
		this.color = Color.BLACK;
	}
	
	public ImageIcon(int type, int width, int height, Color color) {
		this.type = type;
		this.width = width;
		this.height = height;
		this.color = color;
	}

	@Override
	public void paintIcon(Component c, Graphics g, int x, int y) {
		Graphics2D g2d = (Graphics2D) g;
		g2d.setColor(color);
		switch(type) {
			case LINE:
				g2d.drawLine(x, y, x + width, y + height);
				break;
			case RECTANGLE:
				g2d.drawRect(x, y, width, height);
				break;
			case CIRCLE:
				g2d.draw(new Ellipse2D.Double(x, y, width, height));
				break;
			case TEXTAREA:
				g2d.drawString("text", x, y + height / 2);
				break;
			default:
				g2d.fillRect(x, y, width, height);
				break;
		}
	}

	@Override
	public int getIconWidth() {
		return width;
	}

	@Override
	public int getIconHeight() {
		return height;
	}
	
	public int getIconType() {
		return type;
	}
	
	public Color getIconColor() {
		return color;
	}
	
	public void setIconWidth(int width) {
		this.width = width;
	}
	
	public void setIconHeight(int height) {
		this.height = height;
	}
	
	public void setIconType(int type) {
		this.type = type;
	}
	
	public void setIconColor(Color color) {
		this.color = color;
	}
	
}

class ImageButton extends JPanel {
	
	ImageDatabase imageDatabase;
	
	JButton[] shapeButton;
	JButton[] colorButton;
	
	int buttonSize, iconSize;
	
	public ImageButton() {
		super();
	}
	
	public ImageButton(ImageDatabase imageDatabase) {
		super();
		this.imageDatabase = imageDatabase;
	}
	
	
	{
		
		buttonSize = 30;
		iconSize = 24;
		
		Dimension buttonDimension = new Dimension(buttonSize, buttonSize);
		
		this.setLayout(new GridLayout(ImageIcon.SHAPE_NUMBER + ImageIcon.COLOR_NUMBER, 1, 10, 5));
		
		shapeButton = new JButton[ImageIcon.SHAPE_NUMBER];
		for(int shape = ImageIcon.SHAPE_INITIAL; shape < ImageIcon.SHAPE_NUMBER; shape++) {
			shapeButton[shape] = new JButton(new ImageIcon(shape, iconSize, iconSize));
			shapeButton[shape].setPreferredSize(buttonDimension);
			this.add(shapeButton[shape]);
		}
		shapeButton[ImageIcon.LINE].addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				imageDatabase.imageEventHandle = ImageEventHandle.LINE;
			}
		});
		shapeButton[ImageIcon.RECTANGLE].addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				imageDatabase.imageEventHandle = ImageEventHandle.RECTANGLE;
			}
		});
		shapeButton[ImageIcon.CIRCLE].addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				imageDatabase.imageEventHandle = ImageEventHandle.CIRCLE;
			}
		});
		shapeButton[ImageIcon.TEXTAREA].addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				imageDatabase.imageEventHandle = ImageEventHandle.TEXTAREA;
			}
		});
		
		colorButton = new JButton[ImageIcon.COLOR_NUMBER];
		for(int color = ImageIcon.COLOR_INITIAL; color < ImageIcon.COLOR_NUMBER; color++) {
			colorButton[color] = new JButton(new ImageIcon(ImageIcon.SHAPE_COLOR, iconSize, iconSize, ImageIcon.COLOR_LIST[color]));
			colorButton[color].setPreferredSize(buttonDimension);
			this.add(colorButton[color]);
			
		}
		
		colorButton[ImageIcon.RED].addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				imageDatabase.selectedColor = ImageIcon.COLOR_LIST[ImageIcon.RED];
				imageDatabase.imageEventHandle.changeColor(imageDatabase);
			}
		});
		
		colorButton[ImageIcon.ORANGE].addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				imageDatabase.selectedColor = ImageIcon.COLOR_LIST[ImageIcon.ORANGE];
				imageDatabase.imageEventHandle.changeColor(imageDatabase);
			}
		});
		
		colorButton[ImageIcon.YELLOW].addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				imageDatabase.selectedColor = ImageIcon.COLOR_LIST[ImageIcon.YELLOW];
				imageDatabase.imageEventHandle.changeColor(imageDatabase);
			}
		});
		
		colorButton[ImageIcon.GREEN].addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				imageDatabase.selectedColor = ImageIcon.COLOR_LIST[ImageIcon.GREEN];
				imageDatabase.imageEventHandle.changeColor(imageDatabase);
			}
		});
		
		colorButton[ImageIcon.BLUE].addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				imageDatabase.selectedColor = ImageIcon.COLOR_LIST[ImageIcon.BLUE];
				imageDatabase.imageEventHandle.changeColor(imageDatabase);
			}
		});
		
		colorButton[ImageIcon.GRAY].addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				imageDatabase.selectedColor = ImageIcon.COLOR_LIST[ImageIcon.GRAY];
				imageDatabase.imageEventHandle.changeColor(imageDatabase);
			}
		});
		
		colorButton[ImageIcon.BLACK].addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				imageDatabase.selectedColor = ImageIcon.COLOR_LIST[ImageIcon.BLACK];
				imageDatabase.imageEventHandle.changeColor(imageDatabase);
			}
		});
		
		colorButton[ImageIcon.WHITE].addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				imageDatabase.selectedColor = ImageIcon.COLOR_LIST[ImageIcon.WHITE];
				imageDatabase.imageEventHandle.changeColor(imageDatabase);
			}
		});
		
		
	}
}

class ImageMenu extends JPanel {
	
	ImageDatabase imageDatabase;
	
	JMenuBar menuBar;
	JMenu saveMenu, selectMenu, plotMenu, fillMenu, deleteMenu, resumeMenu;
	
	
	MouseAdapter mouseAdapter;
	MouseMotionAdapter mouseMotionAdapter;
	KeyAdapter keyAdapter;
	
	public ImageMenu() {
		super();
	}
	public ImageMenu(ImageDatabase imageDatabase) {
		super();
		this.imageDatabase = imageDatabase;
	}
	
	{
		menuBar = new JMenuBar();
		saveMenu = new JMenu("Save");
		selectMenu = new JMenu("Select");
		plotMenu = new JMenu("Plot");
		fillMenu = new JMenu("Fill");
		deleteMenu = new JMenu("Delete");
		resumeMenu = new JMenu("Resume");
		
		this.add(menuBar);	
		menuBar.add(saveMenu);
		saveMenu.addMenuListener(new MenuListener() {

			@Override
			public void menuSelected(MenuEvent e) {
				imageDatabase.saveImage();
				
			}

			@Override
			public void menuDeselected(MenuEvent e) {
				imageDatabase.imagePlot.requestFocus();
				
			}

			@Override
			public void menuCanceled(MenuEvent e) {
				// TODO Auto-generated method stub
				
			}
			
		});
		
		
		menuBar.add(selectMenu);
		selectMenu.addMenuListener(new MenuListener() {

			@Override
			public void menuSelected(MenuEvent e) {
				imageDatabase.imageEventHandle.selectShape(imageDatabase);
			}

			@Override
			public void menuDeselected(MenuEvent e) {
				imageDatabase.imagePlot.requestFocus();
			}

			@Override
			public void menuCanceled(MenuEvent e) {
				//
			}
			
		});
		
		menuBar.add(plotMenu);
		plotMenu.addMenuListener(new MenuListener() {

			@Override
			public void menuSelected(MenuEvent e) {
				imageDatabase.imageEventHandle.plotShape(imageDatabase);
				
			}

			@Override
			public void menuDeselected(MenuEvent e) {
				imageDatabase.imagePlot.requestFocus();
			}

			@Override
			public void menuCanceled(MenuEvent e) {
				//
			}
			
		});
		
		menuBar.add(fillMenu);
		fillMenu.addMenuListener(new MenuListener() {

			@Override
			public void menuSelected(MenuEvent e) {
				imageDatabase.imageEventHandle.fillShape(imageDatabase);
			}

			@Override
			public void menuDeselected(MenuEvent e) {
				imageDatabase.imagePlot.requestFocus();
			}

			@Override
			public void menuCanceled(MenuEvent e) {
				//
			}
			
		});
		menuBar.add(deleteMenu);
		deleteMenu.addMenuListener(new MenuListener() {

			@Override
			public void menuSelected(MenuEvent e) {
				imageDatabase.imageEventHandle.deleteShape(imageDatabase);
				
			}

			@Override
			public void menuDeselected(MenuEvent e) {
				imageDatabase.imagePlot.requestFocus();
			}

			@Override
			public void menuCanceled(MenuEvent e) {
			}
			
		});
		
		menuBar.add(resumeMenu);
		resumeMenu.addMenuListener(new MenuListener() {

			@Override
			public void menuSelected(MenuEvent e) {
				imageDatabase.imageEventHandle.resumeShape(imageDatabase);
			}

			@Override
			public void menuDeselected(MenuEvent e) {
				imageDatabase.imagePlot.requestFocus();
			}

			@Override
			public void menuCanceled(MenuEvent e) {
			}
			
		});
		
	}
}

class ImagePlot extends JPanel {
	
	ImageDatabase imageDatabase;
		
	MouseAdapter mouseAdapter;
	MouseMotionAdapter mouseMotionAdapter;
	KeyAdapter keyAdapter;
	
	public ImagePlot() {
		super();
	}
	public ImagePlot(ImageDatabase imageDatabase) {
		super();
		this.imageDatabase = imageDatabase;
	}
	
	{
		this.setLayout(null);
		
		this.addFocusListener(new FocusAdapter() {
			public void focusLost(FocusEvent e) {
				imageDatabase.focusComponent = e.getOppositeComponent();
				if(!imageDatabase.plotted) { 
					if(e.getOppositeComponent() instanceof JTextArea 
							&& !imageDatabase.selectedTextAreaList.contains(e.getOppositeComponent())) {
						imageDatabase.selectedTextAreaList.add((JTextArea) e.getOppositeComponent());
					}
					e.getComponent().requestFocus();
				}
			}
			public void focusGained(FocusEvent e) {
				if(imageDatabase.changed) {
					repaint();
					imageDatabase.changed = false;
				}
			}
		});
		
		mouseAdapter = new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				imageDatabase.imageEventHandle.mousePressed(e, imageDatabase);
			}

			public void mouseReleased(MouseEvent e) {
				imageDatabase.imageEventHandle.mouseReleased(e, imageDatabase);
			}
			public void mouseClicked(MouseEvent e) {
				imageDatabase.imageEventHandle.mouseClicked(e, imageDatabase);
			}
		};
		this.addMouseListener(mouseAdapter);
		
		mouseMotionAdapter = new MouseMotionAdapter() {
			public void mouseDragged(MouseEvent e) {
				imageDatabase.imageEventHandle.mouseDragged(e, imageDatabase);
				repaint();
			}
		};
		this.addMouseMotionListener(mouseMotionAdapter);
		
		keyAdapter = new KeyAdapter() {
			public void keyReleased(KeyEvent e) {
				imageDatabase.imageEventHandle.keyReleased(e, imageDatabase);
				repaint();
			}
		};
		this.addKeyListener(keyAdapter);
		
		this.addMouseWheelListener(new MouseWheelListener() {

			@Override
			public void mouseWheelMoved(MouseWheelEvent e) {
				imageDatabase.imageEventHandle.mouseWheelMoved(e, imageDatabase);
				repaint();
			}
			
		});
	}
	
	
	
	public void paint(Graphics g) {
		super.paint(g);
		ImageEventHandle.LINE.paintImage(g, imageDatabase);
		ImageEventHandle.RECTANGLE.paintImage(g, imageDatabase);
		ImageEventHandle.CIRCLE.paintImage(g, imageDatabase);
		ImageEventHandle.TEXTAREA.paintImage(g, imageDatabase);
		for(JTextArea textArea:imageDatabase.textAreaList) {
			this.add(textArea);
		}
	}
	
	
	
	
}

class Image<T> {
	public T shape;
	public Color color;
	public boolean filled;
	public float size;
	
	Image() {
		super();
	}
	
	Image(T shape) {
		this.shape = shape;
		color = Color.BLACK;
		filled = false;
		size = 1;
	}
	
}

enum ImageEventHandle {
	LINE{
		public String getType( ) {
			return "Line";
		}
		
		@Override
		public void paintImage(Graphics g, ImageDatabase idb) {
			Graphics2D g2d = (Graphics2D) g;
			for(Image<Line2D> image:idb.lineList) {
				g2d.setColor(image.color);
				g2d.setStroke(new BasicStroke(image.size));
				g2d.draw(image.shape);
			}
		}
		
		@Override
		public void mousePressed(MouseEvent e, ImageDatabase idb) {
			if(e.getButton() == MouseEvent.BUTTON1) {
				idb.startPoint = e.getPoint();
			}
		}

		@Override
		public void mouseReleased(MouseEvent e, ImageDatabase idb) {
			idb.startPoint = null;
			idb.createdLine = null;
			idb.selected = !idb.selectedLineList.isEmpty();
		}
		
		@Override
		public void mouseClicked(MouseEvent e, ImageDatabase idb) {
			int button = e.getButton();
			if(idb.plotted) {
				
			} else {
				if(button == MouseEvent.BUTTON1) {
					Point clickPoint = e.getPoint();
					for(Image<Line2D> image:idb.lineList) {
						if(!idb.selectedLineList.contains(image) && image.shape.intersects(clickPoint.getX() - 1, clickPoint.getY() - 1, 2, 2)) {
							idb.selectedLineList.add(image);
						}
					}
				} else if(button == MouseEvent.BUTTON3) {
					if(idb.selectedLineList != null) {
						idb.selectedLineList.clear();
					}
				}
			}
		}
	
		@Override
		public void mouseDragged(MouseEvent e, ImageDatabase idb) {
			if(idb.plotted) {
				Point currentPoint = e.getPoint();
				Line2D newLine = new Line2D.Double(idb.startPoint, currentPoint);
				if(idb.createdLine != null) {
					idb.createdLine.shape = newLine;
				} else {
					
					idb.createdLine = new Image<Line2D>(newLine);
					idb.createdLine.color = idb.selectedColor;
					idb.createdLine.filled = idb.filled;
					idb.lineList.add(idb.createdLine);
				}
			} else {
				if(idb.selected) {
					Point currentPoint = e.getPoint();
					double deltaX = currentPoint.getX() - idb.startPoint.getX();
					double deltaY = currentPoint.getY() - idb.startPoint.getY();
					idb.startPoint = currentPoint;
					Point2D p1, p2;
					Line2D selectedLine, newLine;
					
					for(Image<Line2D> image:idb.selectedLineList) {
						selectedLine = image.shape;
					
						p1 = new Point2D.Double(selectedLine.getP1().getX() + deltaX, selectedLine.getP1().getY() + deltaY);
						p2 = new Point2D.Double(selectedLine.getP2().getX() + deltaX, selectedLine.getP2().getY() + deltaY);
						
						newLine = new Line2D.Double(p1, p2);
						image.shape = newLine;
					}
				} else {
					Rectangle2D rect = new Rectangle2D.Double(idb.startPoint.getX(), idb.startPoint.getY(), 
							e.getX() - idb.startPoint.getX(), e.getY() - idb.startPoint.getY());
					for(Image<Line2D> image:idb.lineList) {
						if(!idb.selectedLineList.contains(image) && image.shape.intersects(rect)) {
							idb.selectedLineList.add(image);
						}
					}
				}
			}
			
		}
		
		@Override
		public void keyReleased(KeyEvent e, ImageDatabase idb) {
			int key = e.getKeyCode();
			switch(key) {
			case KeyEvent.VK_DELETE:
				if(idb.selected) {
					idb.resumedLineList.addAll(idb.selectedLineList);
					idb.lineList.removeAll(idb.selectedLineList);
					idb.selectedLineList.clear();
					idb.selected = false;
					idb.resumedLine = true;
					idb.changed = true;
				}
				break;
			}
		}
		
		@Override
		public void mouseWheelMoved(MouseWheelEvent e, ImageDatabase idb) {
			if(!idb.plotted && idb.selected) {
				if(e.getWheelRotation() == 1) {
					for(Image<Line2D> image:idb.selectedLineList) {
						image.size = Math.min(image.size + (float)0.5, 32);
					}
				} else {
					for(Image<Line2D> image:idb.selectedLineList) {
						image.size = Math.max(image.size + (float)0.5, 1);
					}
				}
				idb.changed = true;
			}
		}

		@Override
		public void changeColor(ImageDatabase idb) {
			if(!idb.selectedLineList.isEmpty()) {
				
				for(Image<Line2D> image:idb.selectedLineList) {
					image.color = idb.selectedColor;
				}
				idb.changed = true;
			}
		}

		@Override
		public void fillShape(ImageDatabase idb) {
			
			idb.filled = !idb.filled;
			for(Image<Line2D> image:idb.selectedLineList) {
				image.filled = idb.filled;
			}
			idb.changed = true;
		}

		@Override
		public void deleteShape(ImageDatabase idb) {
			if(!idb.selectedLineList.isEmpty()) {
				idb.resumedLineList.addAll(idb.selectedLineList);
				idb.lineList.removeAll(idb.selectedLineList);
				idb.selectedLineList.clear();
				idb.selected = false;
				idb.resumedLine = true;
				idb.changed = true;
			}
		}

		@Override
		public void selectShape(ImageDatabase idb) {
			idb.plotted = false;
			
		}

		@Override
		public void plotShape(ImageDatabase idb) {
			idb.plotted = true;
			
		}
		
		@Override
		public void resumeShape(ImageDatabase idb) {
			if(idb.resumedLine) {
				idb.lineList.addAll(idb.resumedLineList);
				idb.resumedLine = false;
				idb.changed = true;
			}
		}
	},
	RECTANGLE{
		public String getType() {
			return "Rectangle";
		}

		@Override
		public void paintImage(Graphics g, ImageDatabase idb) {
			Graphics2D g2d = (Graphics2D) g;
			for(Image<Rectangle2D> image:idb.rectangleList) {
				g2d.setColor(image.color);
				g2d.setStroke(new BasicStroke(image.size));
				if(image.filled) {
					g2d.fill(image.shape);
				} else {
					g2d.draw(image.shape);
				}
			}
		}
		
		@Override
		public void mousePressed(MouseEvent e, ImageDatabase idb) {
			if(e.getButton() == MouseEvent.BUTTON1) {
				idb.startPoint = e.getPoint();
			}
			
		}

		@Override
		public void mouseReleased(MouseEvent e, ImageDatabase idb) {
			idb.startPoint = null;
			idb.createdRectangle = null;
			idb.selected = !idb.selectedRectangleList.isEmpty();
		}

		@Override
		public void mouseClicked(MouseEvent e, ImageDatabase idb) {
			if(idb.plotted) {
				
			} else {
				int button = e.getButton();
				if(button == MouseEvent.BUTTON1) {
					idb.selectedRectangleList.clear();
					Point clickPoint = e.getPoint();
					for(Image<Rectangle2D> image:idb.rectangleList) {
						if(!idb.selectedRectangleList.contains(image) && image.shape.intersects(clickPoint.getX() - 1, clickPoint.getY() - 1, 2, 2)) {
							idb.selectedRectangleList.add(image);
						}
					}
				} else if(button == MouseEvent.BUTTON3) {
					if(idb.selectedRectangleList != null) {
						idb.selectedRectangleList.clear();
					}
				}
			}
			
			
		}

		@Override
		public void mouseDragged(MouseEvent e, ImageDatabase idb) {
			if(idb.plotted) {
				Point currentPoint = e.getPoint();
				double x = Math.min(currentPoint.getX(), idb.startPoint.getX());
				double y = Math.min(currentPoint.getY(), idb.startPoint.getY());
				double w = Math.abs(currentPoint.getX() - idb.startPoint.getX());
				double h = Math.abs(currentPoint.getY() - idb.startPoint.getY());
				Rectangle2D newRectangle = new Rectangle2D.Double(x, y, w, h);
				if(idb.createdRectangle != null) {
					idb.createdRectangle.shape = newRectangle;
				} else {
					
					idb.createdRectangle = new Image<Rectangle2D>(newRectangle);
					idb.createdRectangle.color = idb.selectedColor;
					idb.createdRectangle.filled = idb.filled;
					idb.rectangleList.add(idb.createdRectangle);
				}
			} else {
				if(idb.selected) {		
					Point currentPoint = e.getPoint();
					double deltaX = currentPoint.getX() - idb.startPoint.getX();
					double deltaY = currentPoint.getY() - idb.startPoint.getY();
					idb.startPoint = currentPoint;
					Rectangle2D selectedRectangle;
					double x, y;
					for(Image<Rectangle2D> image:idb.selectedRectangleList) {
						selectedRectangle = image.shape;
					
						x = selectedRectangle.getX() + deltaX;
						y = selectedRectangle.getY() + deltaY;
						
						Rectangle2D newRectangle = new Rectangle2D.Double(x, y, selectedRectangle.getWidth(), selectedRectangle.getHeight());
						image.shape = newRectangle;
					}
				} else {
					Rectangle2D rect = new Rectangle2D.Double(idb.startPoint.getX(), idb.startPoint.getY(), 
							e.getX() - idb.startPoint.getX(), e.getY() - idb.startPoint.getY());
					for(Image<Rectangle2D> image:idb.rectangleList) {
						if(!idb.selectedRectangleList.contains(image) && image.shape.intersects(rect)) {
							idb.selectedRectangleList.add(image);
						}
					}
				}
			};
			
		}

		@Override
		public void keyReleased(KeyEvent e, ImageDatabase idb) {
			int key = e.getKeyCode();
			switch(key) {
			case KeyEvent.VK_DELETE:
				if(idb.selected) {
					idb.resumedRectangleList.addAll(idb.selectedRectangleList);
					idb.rectangleList.removeAll(idb.selectedRectangleList);
					idb.selectedRectangleList.clear();
					idb.selected = false;
					idb.resumedRectangle = true;
					idb.changed = true;
				}
				break;
			}
			
		}
		
		@Override
		public void mouseWheelMoved(MouseWheelEvent e, ImageDatabase idb) {
			if(!idb.plotted && idb.selected) {
				if(e.getWheelRotation() == 1) {
					for(Image<Rectangle2D> image:idb.selectedRectangleList) {
						image.size = Math.min(image.size + (float)0.5, 32);
					}
				} else {
					for(Image<Rectangle2D> image:idb.selectedRectangleList) {
						image.size = Math.max(image.size - (float)0.5, 1);
					}
				}
				idb.changed = true;
			}
		}

		@Override
		public void changeColor(ImageDatabase idb) {
			if(!idb.selectedRectangleList.isEmpty()) {
				
				for(Image<Rectangle2D> image:idb.selectedRectangleList) {
					image.color = idb.selectedColor;
				}
				idb.changed = true;
			}
		}

		@Override
		public void fillShape(ImageDatabase idb) {
			
			idb.filled = !idb.filled;
			for(Image<Rectangle2D> image:idb.selectedRectangleList) {
				image.filled = idb.filled;
			}
			idb.changed = true;
			
		}

		@Override
		public void deleteShape(ImageDatabase idb) {
			if(!idb.selectedRectangleList.isEmpty()) {
				idb.resumedRectangleList.addAll(idb.selectedRectangleList);
				idb.rectangleList.removeAll(idb.selectedRectangleList);
				idb.selectedRectangleList.clear();
				idb.selected = false;
				idb.resumedRectangle = true;
				idb.changed = true;
			}
		}

		@Override
		public void selectShape(ImageDatabase idb) {
			idb.plotted = false;
			
		}

		@Override
		public void plotShape(ImageDatabase idb) {
			idb.plotted = true;
			
		}
		
		@Override
		public void resumeShape(ImageDatabase idb) {
			if(idb.resumedRectangle) {
				idb.rectangleList.addAll(idb.resumedRectangleList);
				idb.resumedRectangle = false;
				idb.changed = true;
			}
		}
	},
	CIRCLE{
		public String getType() {
			return "Circle";
		}

		@Override
		public void paintImage(Graphics g, ImageDatabase idb) {
			Graphics2D g2d = (Graphics2D) g;
			for(Image<Ellipse2D> image:idb.circleList) {
				g2d.setColor(image.color);
				g2d.setStroke(new BasicStroke(image.size));
				if(image.filled) {
					g2d.fill(image.shape);
				} else {
					g2d.draw(image.shape);
				}
			}
		}
		
		@Override
		public void mousePressed(MouseEvent e, ImageDatabase idb) {
			if(e.getButton() == MouseEvent.BUTTON1) {
				idb.startPoint = e.getPoint();
			}
			
		}

		@Override
		public void mouseReleased(MouseEvent e, ImageDatabase idb) {
			idb.startPoint = null;
			idb.createdCircle = null;
			idb.selected = !idb.selectedCircleList.isEmpty();
			if(idb.selected) {
				
			}
			
		}

		@Override
		public void mouseClicked(MouseEvent e, ImageDatabase idb) {
			if(idb.plotted) {
				
			} else {
				int button = e.getButton();
				if(button == MouseEvent.BUTTON1) {
					Point clickPoint = e.getPoint();
					idb.selectedCircleList.clear();
					for(Image<Ellipse2D> image:idb.circleList) {
						if(!idb.selectedCircleList.contains(image) && image.shape.intersects(clickPoint.getX() - 1, clickPoint.getY() - 1, 2, 2)) {
							idb.selectedCircleList.add(image);
						}
					}
				} else if(button == MouseEvent.BUTTON3) {
					if(idb.selectedCircleList != null) {
						idb.selectedCircleList.clear();
					}
				}
			}
		}

		@Override
		public void mouseDragged(MouseEvent e, ImageDatabase idb) {
			if(idb.plotted) {
				Point currentPoint = e.getPoint();
				double r = Math.min(Math.abs(currentPoint.getX() - idb.startPoint.getX()),
						Math.abs(currentPoint.getY() - idb.startPoint.getY()));
				Ellipse2D newCircle = new Ellipse2D.Double(idb.startPoint.getX() - r, idb.startPoint.getY() - r, r*2, r*2);
				if(idb.createdCircle != null) {
					idb.createdCircle.shape = newCircle;
				} else {
					
					idb.createdCircle = new Image<Ellipse2D>(newCircle);
					idb.createdCircle.color = idb.selectedColor;
					idb.createdCircle.filled = idb.filled;
					idb.circleList.add(idb.createdCircle);
				}
			} else {
				if(idb.selected) {		
					Point currentPoint = e.getPoint();
					double deltaX = currentPoint.getX() - idb.startPoint.getX();
					double deltaY = currentPoint.getY() - idb.startPoint.getY();
					idb.startPoint = currentPoint;
					Ellipse2D selectedCircle;
					double x, y;
					for(Image<Ellipse2D> image:idb.selectedCircleList) {
						selectedCircle = image.shape;
					
						x = selectedCircle.getX() + deltaX;
						y = selectedCircle.getY() + deltaY;
						
						Ellipse2D newCircle = new Ellipse2D.Double(x, y, selectedCircle.getWidth(), selectedCircle.getHeight());
						image.shape = newCircle;
					}
				} else {
					Rectangle2D rect = new Rectangle2D.Double(idb.startPoint.getX(), idb.startPoint.getY(), 
							e.getX() - idb.startPoint.getX(), e.getY() - idb.startPoint.getY());
					for(Image<Ellipse2D> image:idb.circleList) {
						if(!idb.selectedCircleList.contains(image) && image.shape.intersects(rect)) {
							idb.selectedCircleList.add(image);
						}
					}
				}
			}
		}

		@Override
		public void keyReleased(KeyEvent e, ImageDatabase idb) {
			int key = e.getKeyCode();
			switch(key) {
			case KeyEvent.VK_DELETE:
				if(idb.selected) {
					idb.resumedCircleList.addAll(idb.selectedCircleList);
					idb.circleList.removeAll(idb.selectedCircleList);
					idb.selectedCircleList.clear();
					idb.selected = false;
					idb.resumedCircle = true;
					idb.changed = true;
				}
				break;
			}
		}
		
		@Override
		public void mouseWheelMoved(MouseWheelEvent e, ImageDatabase idb) {
			if(!idb.plotted && idb.selected) {
				if(e.getWheelRotation() == 1) {
					for(Image<Ellipse2D> image:idb.selectedCircleList) {
						image.size = Math.min(image.size + (float)0.5, 32);
					}
				} else {
					for(Image<Ellipse2D> image:idb.selectedCircleList) {
						image.size = Math.max(image.size - (float)0.5, 1);
					}
				}
				idb.changed = true;
			}
		}

		@Override
		public void changeColor(ImageDatabase idb) {
			if(!idb.selectedCircleList.isEmpty()) {
				
				for(Image<Ellipse2D> image:idb.selectedCircleList) {
					image.color = idb.selectedColor;
				}
				idb.changed = true;
			}
		}

		@Override
		public void fillShape(ImageDatabase idb) {
			
			idb.filled = !idb.filled;
			for(Image<Ellipse2D> image:idb.selectedCircleList) {
				image.filled = idb.filled;
			}
			idb.changed = true;
		}

		@Override
		public void deleteShape(ImageDatabase idb) {
			if(!idb.selectedCircleList.isEmpty()) {
				idb.resumedCircleList.addAll(idb.selectedCircleList);
				idb.circleList.removeAll(idb.selectedCircleList);
				idb.selectedCircleList.clear();
				idb.selected = false;
				idb.changed = true;
			}
		}

		@Override
		public void selectShape(ImageDatabase idb) {
			idb.plotted = false;
			
		}

		@Override
		public void plotShape(ImageDatabase idb) {
			idb.plotted = true;
			
		}
		
		@Override
		public void resumeShape(ImageDatabase idb) {
			if(idb.resumedCircle) {
				idb.circleList.addAll(idb.resumedCircleList);
				idb.resumedCircle = false;
				idb.changed = true;
			}
		}
	},
	TEXTAREA{
		public String getType() {
			return "TextArea";
		}

		@Override
		public void paintImage(Graphics g, ImageDatabase idb) {
			for(JTextArea image:idb.textAreaList) {
				image.setLineWrap(true);
				image.setForeground(Color.BLACK);
			}
		}
		
		@Override
		public void mousePressed(MouseEvent e, ImageDatabase idb) {
			if(e.getButton() == MouseEvent.BUTTON1) {
				idb.startPoint = e.getPoint();
			}
			
		}

		@Override
		public void mouseReleased(MouseEvent e, ImageDatabase idb) {
			idb.startPoint = null;
			idb.createdTextArea = null;
			idb.selected = !idb.selectedTextAreaList.isEmpty();
			if(idb.selected) {
				
			}
			
		}

		@Override
		public void mouseClicked(MouseEvent e, ImageDatabase idb) {
			int button = e.getButton();
			if(button == MouseEvent.BUTTON3) {
				idb.selectedTextAreaList.clear();
			}
			
		}

		@Override
		public void mouseDragged(MouseEvent e, ImageDatabase idb) {
			if(idb.plotted) {
				Point currentPoint = e.getPoint();
				if(idb.createdTextArea != null) {
					idb.createdTextArea.setBounds(
							(int)idb.startPoint.getX(), (int)idb.startPoint.getY(),
							(int)(currentPoint.getX() - idb.startPoint.getX()), 
							(int)(currentPoint.getY() - idb.startPoint.getY()));
				} else {
					
					idb.createdTextArea = new JTextArea();
					idb.createdTextArea.setBounds(
							(int)idb.startPoint.getX(), (int)idb.startPoint.getY(),
							(int)(currentPoint.getX() - idb.startPoint.getX()), 
							(int)(currentPoint.getY() - idb.startPoint.getY()));
					idb.createdTextArea.setBackground(idb.selectedColor);
					idb.createdTextArea.setFont(new Font("����", Font.BOLD, 16));
					idb.textAreaList.add(idb.createdTextArea);
				}
			} else {
				if(idb.selected) {
					Point currentPoint = e.getPoint();
					double deltaX = currentPoint.getX() - idb.startPoint.getX();
					double deltaY = currentPoint.getY() - idb.startPoint.getY();
					idb.startPoint = currentPoint;
					Rectangle rect;
					
					for(JTextArea textArea:idb.selectedTextAreaList) {
						rect = textArea.getBounds();
						textArea.setBounds((int)(rect.getX() + deltaX), (int)(rect.getY() + deltaY), 
								(int)rect.getWidth(), (int)rect.getHeight());
					}
				} else {
					Point currentPoint = e.getPoint();
					for(JTextArea textArea:idb.textAreaList) {
						if(!idb.selectedTextAreaList.contains(textArea) && textArea.getBounds().intersects(idb.startPoint.getX(), idb.startPoint.getY(), 
								currentPoint.getX() - idb.startPoint.getX(), currentPoint.getY() - idb.startPoint.getY())) {
							idb.selectedTextAreaList.add(textArea);
						}
					}
				}
			}
			
		}

		@Override
		public void keyReleased(KeyEvent e, ImageDatabase idb) {
			if(idb.plotted) {
				if(!idb.selectedTextAreaList.isEmpty()) {
					for(JTextArea textArea:idb.selectedTextAreaList) {
						textArea.append(String.valueOf(e.getKeyChar()));
					}
				}
			} else {
				int key = e.getKeyCode();
				switch(key) {
				case KeyEvent.VK_DELETE:
					if(idb.selected) {
						idb.resumedTextAreaList.addAll(idb.selectedTextAreaList);
						idb.textAreaList.removeAll(idb.selectedTextAreaList);
						for(JTextArea textArea :idb.selectedTextAreaList) {
							idb.imagePlot.remove(textArea);
						}
						idb.selectedTextAreaList.clear();
						idb.selected = false;
						idb.resumedTextArea = true;
					}
					break;
				}
			}
			
		}
		
		@Override
		public void mouseWheelMoved(MouseWheelEvent e, ImageDatabase idb) {
			if(!idb.plotted && idb.selected) {
				if(e.getWheelRotation() == 1) {
					for(JTextArea textArea:idb.selectedTextAreaList) {
						textArea.setFont(textArea.getFont().deriveFont(
								Math.min(textArea.getFont().getSize2D()+(float)0.5, 32)));
					}
				} else {
					for(JTextArea textArea:idb.selectedTextAreaList) {
						textArea.setFont(textArea.getFont().deriveFont(
								Math.max(textArea.getFont().getSize2D()-(float)0.5, 1)));
					}
				}
				idb.changed = true;
			}
		}

		@Override
		public void changeColor(ImageDatabase idb) {
			
			for(JTextArea textArea:idb.selectedTextAreaList) {
				textArea.setBackground(idb.selectedColor);
			}
			idb.changed = true;
		}

		@Override
		public void fillShape(ImageDatabase idb) {
			idb.filled = !idb.filled;
			
		}

		@Override
		public void deleteShape(ImageDatabase idb) {
			if(!idb.selectedTextAreaList.isEmpty()) {
				idb.resumedTextAreaList.addAll(idb.selectedTextAreaList);
				idb.textAreaList.removeAll(idb.selectedTextAreaList);
				for(JTextArea textArea :idb.selectedTextAreaList) {
					idb.imagePlot.remove(textArea);
				}
				idb.selectedTextAreaList.clear();
				idb.selected = false;
				idb.resumedTextArea = true;
				idb.changed = true;
			}
			
		}

		@Override
		public void selectShape(ImageDatabase idb) {
			idb.plotted = false;
			
		}

		@Override
		public void plotShape(ImageDatabase idb) {
			idb.plotted = true;
			
		}

		@Override
		public void resumeShape(ImageDatabase idb) {
			if(idb.resumedTextArea) {
				idb.textAreaList.addAll(idb.resumedTextAreaList);
				for(JTextArea textArea:idb.resumedTextAreaList) {
					idb.imagePlot.add(textArea);
				}
				idb.resumedTextArea = false;
				idb.changed = true;
			}
		}
	};
	
	public abstract String getType();
	public abstract void paintImage(Graphics g, ImageDatabase idb);
	public abstract void mousePressed(MouseEvent e, ImageDatabase idb);
	public abstract void mouseReleased(MouseEvent e, ImageDatabase idb);
	public abstract void mouseClicked(MouseEvent e, ImageDatabase idb);
	public abstract void mouseDragged(MouseEvent e, ImageDatabase idb);
//	public abstract void mouseMoved(MouseEvent e, ImageDatabase idb);
	public abstract void keyReleased(KeyEvent e, ImageDatabase idb);
	public abstract void mouseWheelMoved(MouseWheelEvent e, ImageDatabase idb);
	public abstract void changeColor(ImageDatabase idb);
	public abstract void fillShape(ImageDatabase idb);
	public abstract void deleteShape(ImageDatabase idb);
	public abstract void selectShape(ImageDatabase idb);
	public abstract void plotShape(ImageDatabase idb);
	public abstract void resumeShape(ImageDatabase idb);
}

class ImageDatabase {
	public List<Image<Line2D>> lineList;
	public List<Image<Rectangle2D>> rectangleList;
	public List<Image<Ellipse2D>> circleList;
	public List<JTextArea> textAreaList;
	
	public List<Image<Line2D>> selectedLineList;
	public List<Image<Rectangle2D>> selectedRectangleList;
	public List<Image<Ellipse2D>> selectedCircleList;
	public List<JTextArea> selectedTextAreaList;
	
	public Image<Line2D> createdLine;
	public Image<Rectangle2D> createdRectangle;
	public Image<Ellipse2D> createdCircle;
	public JTextArea createdTextArea;
	
	public List<Image<Line2D>> resumedLineList;
	public List<Image<Rectangle2D>> resumedRectangleList;
	public List<Image<Ellipse2D>> resumedCircleList;
	public List<JTextArea> resumedTextAreaList;
	
	public Point startPoint;
	
	public Color selectedColor;
	
	public boolean selected, filled, plotted, changed;
	public boolean resumedLine, resumedRectangle, resumedCircle, resumedTextArea;
	
	public Component focusComponent;
	
	public ImageMenu imageMenu;
	public ImagePlot imagePlot;
	public ImageButton imageButton;
	
	public ImageEventHandle imageEventHandle;
	
	
	
	
	ImageDatabase() {
		super();
		lineList = new ArrayList<Image<Line2D>>();
		rectangleList = new ArrayList<Image<Rectangle2D>>();
		circleList = new ArrayList<Image<Ellipse2D>>();
		textAreaList = new ArrayList<JTextArea>();
		
		selectedLineList = new ArrayList<Image<Line2D>>();
		selectedRectangleList = new ArrayList<Image<Rectangle2D>>();
		selectedCircleList = new ArrayList<Image<Ellipse2D>>();
		selectedTextAreaList = new ArrayList<JTextArea>();
		
		resumedLineList = new ArrayList<Image<Line2D>>();
		resumedRectangleList = new ArrayList<Image<Rectangle2D>>();
		resumedCircleList = new ArrayList<Image<Ellipse2D>>();
		resumedTextAreaList = new ArrayList<JTextArea>();
	}
	
	{
		selectedColor = Color.BLACK;
		imageEventHandle = ImageEventHandle.LINE;
	}
	
	public boolean saveImage() {
		Dimension imageSize = imagePlot.getSize();
		BufferedImage image = new BufferedImage(imageSize.width, imageSize.height, BufferedImage.TYPE_INT_RGB);
		Graphics2D g2d = image.createGraphics();
		imagePlot.paint(g2d);
		g2d.dispose();
		File file = new File(this.getClass().getResource("").getPath());
		file = new File(file.getParent() + File.separatorChar + "image");
		if(!file.exists()) {
			file.mkdir();
		}
		file = new File(file.getAbsolutePath() + File.separatorChar + "plot.jpg");
		try {
			file.createNewFile();
			ImageIO.write(image, "jpg", file);
		} catch(IOException e) {
			e.printStackTrace();
			return false;
		}
		
		return true;
	}
	
}